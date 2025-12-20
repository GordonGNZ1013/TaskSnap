#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>

Database::Database(QObject *parent)
    : QObject(parent)
{
}

Database::~Database()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

QString Database::dataDir()
{
    // 使用應用程序運行目錄下的 data 文件夾
    // 這樣所有數據都會保存在一個地方
    QString dir = QCoreApplication::applicationDirPath() + "/data";
    QDir().mkpath(dir);
    return dir;
}

bool Database::initialize()
{
    // 使用統一的數據目錄
    QString dataPath = dataDir();
    qDebug() << "數據目錄:" << dataPath;

    // 設定資料庫路徑
    QString dbPath = dataPath + "/tasks.db";
    qDebug() << "資料庫路徑:" << dbPath;

    // 開啟 SQLite 資料庫
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "無法開啟資料庫:" << m_db.lastError().text();
        return false;
    }

    // 建立資料表
    return createTables();
}

bool Database::createTables()
{
    QSqlQuery query;

    // 建立任務表
    QString createTasksTable = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            description TEXT,
            due_datetime INTEGER,
            priority INTEGER DEFAULT 0,
            tags TEXT,
            created_at INTEGER,
            updated_at INTEGER,
            is_completed INTEGER DEFAULT 0,
            completed_at INTEGER,
            reminder_at INTEGER
        )
    )";

    if (!query.exec(createTasksTable)) {
        qDebug() << "建立任務表失敗:" << query.lastError().text();
        return false;
    }

    // 建立附件表（預留）
    QString createAttachmentsTable = R"(
        CREATE TABLE IF NOT EXISTS attachments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            task_id INTEGER,
            original_name TEXT,
            stored_path TEXT,
            mime_type TEXT,
            added_at INTEGER,
            snapshot_path TEXT,
            FOREIGN KEY (task_id) REFERENCES tasks(id) ON DELETE CASCADE
        )
    )";

    if (!query.exec(createAttachmentsTable)) {
        qDebug() << "建立附件表失敗:" << query.lastError().text();
        return false;
    }

    qDebug() << "資料表建立成功";
    return true;
}

bool Database::addTask(Task &task)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO tasks (title, description, due_datetime, priority, tags,
                          created_at, updated_at, is_completed, reminder_at)
        VALUES (:title, :description, :due, :priority, :tags,
                :created, :updated, :completed, :reminder)
    )");

    QDateTime now = QDateTime::currentDateTime();
    task.createdAt = now;
    task.updatedAt = now;

    query.bindValue(":title", task.title);
    query.bindValue(":description", task.description);
    query.bindValue(":due", task.dueDateTime.isValid() ? task.dueDateTime.toSecsSinceEpoch() : QVariant());
    query.bindValue(":priority", task.priority);
    query.bindValue(":tags", task.tags);
    query.bindValue(":created", now.toSecsSinceEpoch());
    query.bindValue(":updated", now.toSecsSinceEpoch());
    query.bindValue(":completed", task.isCompleted ? 1 : 0);
    query.bindValue(":reminder", task.reminderAt.isValid() ? task.reminderAt.toSecsSinceEpoch() : QVariant());

    if (!query.exec()) {
        qDebug() << "新增任務失敗:" << query.lastError().text();
        return false;
    }

    // 取得自動產生的 ID
    task.id = query.lastInsertId().toInt();
    qDebug() << "新增任務成功，ID:" << task.id;
    return true;
}

bool Database::updateTask(const Task &task)
{
    QSqlQuery query;
    query.prepare(R"(
        UPDATE tasks SET
            title = :title,
            description = :description,
            due_datetime = :due,
            priority = :priority,
            tags = :tags,
            updated_at = :updated,
            is_completed = :completed,
            completed_at = :completedAt,
            reminder_at = :reminder
        WHERE id = :id
    )");

    query.bindValue(":id", task.id);
    query.bindValue(":title", task.title);
    query.bindValue(":description", task.description);
    query.bindValue(":due", task.dueDateTime.isValid() ? task.dueDateTime.toSecsSinceEpoch() : QVariant());
    query.bindValue(":priority", task.priority);
    query.bindValue(":tags", task.tags);
    query.bindValue(":updated", QDateTime::currentDateTime().toSecsSinceEpoch());
    query.bindValue(":completed", task.isCompleted ? 1 : 0);
    query.bindValue(":completedAt", task.completedAt.isValid() ? task.completedAt.toSecsSinceEpoch() : QVariant());
    query.bindValue(":reminder", task.reminderAt.isValid() ? task.reminderAt.toSecsSinceEpoch() : QVariant());

    if (!query.exec()) {
        qDebug() << "更新任務失敗:" << query.lastError().text();
        return false;
    }

    qDebug() << "更新任務成功，ID:" << task.id;
    return true;
}

bool Database::deleteTask(int taskId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    if (!query.exec()) {
        qDebug() << "刪除任務失敗:" << query.lastError().text();
        return false;
    }

    qDebug() << "刪除任務成功，ID:" << taskId;
    return true;
}

bool Database::markTaskCompleted(int taskId, bool completed)
{
    QSqlQuery query;
    query.prepare(R"(
        UPDATE tasks SET
            is_completed = :completed,
            completed_at = :completedAt,
            updated_at = :updated
        WHERE id = :id
    )");

    QDateTime now = QDateTime::currentDateTime();
    query.bindValue(":id", taskId);
    query.bindValue(":completed", completed ? 1 : 0);
    query.bindValue(":completedAt", completed ? now.toSecsSinceEpoch() : QVariant());
    query.bindValue(":updated", now.toSecsSinceEpoch());

    if (!query.exec()) {
        qDebug() << "標記完成失敗:" << query.lastError().text();
        return false;
    }

    qDebug() << "標記任務" << (completed ? "完成" : "未完成") << "，ID:" << taskId;
    return true;
}

Task Database::getTask(int taskId)
{
    Task task;
    QSqlQuery query;
    query.prepare("SELECT * FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    if (!query.exec() || !query.next()) {
        qDebug() << "取得任務失敗，ID:" << taskId;
        return task;
    }

    task.id = query.value("id").toInt();
    task.title = query.value("title").toString();
    task.description = query.value("description").toString();

    qint64 dueSecs = query.value("due_datetime").toLongLong();
    if (dueSecs > 0) {
        task.dueDateTime = QDateTime::fromSecsSinceEpoch(dueSecs);
    }

    task.priority = query.value("priority").toInt();
    task.tags = query.value("tags").toString();

    qint64 createdSecs = query.value("created_at").toLongLong();
    if (createdSecs > 0) {
        task.createdAt = QDateTime::fromSecsSinceEpoch(createdSecs);
    }

    qint64 updatedSecs = query.value("updated_at").toLongLong();
    if (updatedSecs > 0) {
        task.updatedAt = QDateTime::fromSecsSinceEpoch(updatedSecs);
    }

    task.isCompleted = query.value("is_completed").toInt() == 1;

    qint64 completedSecs = query.value("completed_at").toLongLong();
    if (completedSecs > 0) {
        task.completedAt = QDateTime::fromSecsSinceEpoch(completedSecs);
    }

    qint64 reminderSecs = query.value("reminder_at").toLongLong();
    if (reminderSecs > 0) {
        task.reminderAt = QDateTime::fromSecsSinceEpoch(reminderSecs);
    }

    return task;
}

QList<Task> Database::getAllTasks()
{
    QList<Task> tasks;
    QSqlQuery query("SELECT * FROM tasks ORDER BY is_completed ASC, due_datetime ASC, priority DESC");

    while (query.next()) {
        Task task;
        task.id = query.value("id").toInt();
        task.title = query.value("title").toString();
        task.description = query.value("description").toString();

        qint64 dueSecs = query.value("due_datetime").toLongLong();
        if (dueSecs > 0) {
            task.dueDateTime = QDateTime::fromSecsSinceEpoch(dueSecs);
        }

        task.priority = query.value("priority").toInt();
        task.tags = query.value("tags").toString();

        qint64 createdSecs = query.value("created_at").toLongLong();
        if (createdSecs > 0) {
            task.createdAt = QDateTime::fromSecsSinceEpoch(createdSecs);
        }

        qint64 updatedSecs = query.value("updated_at").toLongLong();
        if (updatedSecs > 0) {
            task.updatedAt = QDateTime::fromSecsSinceEpoch(updatedSecs);
        }

        task.isCompleted = query.value("is_completed").toInt() == 1;

        qint64 completedSecs = query.value("completed_at").toLongLong();
        if (completedSecs > 0) {
            task.completedAt = QDateTime::fromSecsSinceEpoch(completedSecs);
        }

        qint64 reminderSecs = query.value("reminder_at").toLongLong();
        if (reminderSecs > 0) {
            task.reminderAt = QDateTime::fromSecsSinceEpoch(reminderSecs);
        }
        
        // 載入附件
        task.attachments = getAttachments(task.id);

        tasks.append(task);
    }

    qDebug() << "載入任務數量:" << tasks.size();
    return tasks;
}

// ============ 附件操作 ============

QString Database::attachmentsDir()
{
    QString dir = dataDir() + "/attachments";
    QDir().mkpath(dir);
    return dir;
}

bool Database::addAttachment(Attachment &attachment)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO attachments (task_id, original_name, stored_path, mime_type, added_at, snapshot_path)
        VALUES (:task_id, :name, :path, :mime, :added, :snapshot)
    )");
    
    attachment.addedAt = QDateTime::currentDateTime();
    
    query.bindValue(":task_id", attachment.taskId);
    query.bindValue(":name", attachment.originalName);
    query.bindValue(":path", attachment.storedPath);
    query.bindValue(":mime", attachment.mimeType);
    query.bindValue(":added", attachment.addedAt.toSecsSinceEpoch());
    query.bindValue(":snapshot", attachment.snapshotPath);
    
    if (!query.exec()) {
        qDebug() << "新增附件失敗:" << query.lastError().text();
        return false;
    }
    
    attachment.id = query.lastInsertId().toInt();
    qDebug() << "附件已新增，ID:" << attachment.id;
    return true;
}

bool Database::deleteAttachment(int attachmentId)
{
    // 先取得檔案路徑
    QSqlQuery query;
    query.prepare("SELECT stored_path FROM attachments WHERE id = :id");
    query.bindValue(":id", attachmentId);
    
    if (query.exec() && query.next()) {
        QString filePath = query.value(0).toString();
        // 刪除實際檔案
        if (QFile::exists(filePath)) {
            QFile::remove(filePath);
        }
    }
    
    // 從資料庫刪除
    query.prepare("DELETE FROM attachments WHERE id = :id");
    query.bindValue(":id", attachmentId);
    
    if (!query.exec()) {
        qDebug() << "刪除附件失敗:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "附件已刪除，ID:" << attachmentId;
    return true;
}

QList<Attachment> Database::getAttachments(int taskId)
{
    QList<Attachment> attachments;
    
    QSqlQuery query;
    query.prepare("SELECT * FROM attachments WHERE task_id = :task_id ORDER BY added_at DESC");
    query.bindValue(":task_id", taskId);
    
    if (!query.exec()) {
        qDebug() << "查詢附件失敗:" << query.lastError().text();
        return attachments;
    }
    
    while (query.next()) {
        Attachment att;
        att.id = query.value("id").toInt();
        att.taskId = query.value("task_id").toInt();
        att.originalName = query.value("original_name").toString();
        att.storedPath = query.value("stored_path").toString();
        att.mimeType = query.value("mime_type").toString();
        att.snapshotPath = query.value("snapshot_path").toString();
        
        qint64 addedSecs = query.value("added_at").toLongLong();
        if (addedSecs > 0) {
            att.addedAt = QDateTime::fromSecsSinceEpoch(addedSecs);
        }
        
        attachments.append(att);
    }
    
    return attachments;
}