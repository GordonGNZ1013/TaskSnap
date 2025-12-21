// ========================================
// 數據庫管理類實現 (database.cpp)
// 功能: 管理任務和附件的數據庫操作，包括增、刪、改、查
// 數據庫: SQLite (tasks.db)
// ========================================

#include "database.h"
#include <QSqlQuery>              // SQL查詢執行
#include <QSqlError>              // SQL錯誤信息
#include <QStandardPaths>         // 標準路徑查詢
#include <QDir>                   // 目錄操作
#include <QFile>                  // 文件操作
#include <QDebug>                 // 調試輸出
#include <QCoreApplication>       // 應用程序核心功能

/**
 * 構造函數 - Database()
 * 參數: parent - 父對象指針（用於Qt的對象樹管理）
 * 功能: 初始化Database對象
 */
Database::Database(QObject *parent)
    : QObject(parent)
{
    // 初始化完成
}

/**
 * 析構函數 - ~Database()
 * 功能: 清理數據庫資源，關閉數據庫連接
 */
Database::~Database()
{
    // 檢查數據庫是否已打開，若打開則關閉連接
    if (m_db.isOpen()) {
        m_db.close();
    }
}

/**
 * 獲取數據目錄 - dataDir()
 * 返回值: QString - 數據文件夾的完整路徑
 * 功能: 返回應用程序數據存儲目錄，若目錄不存在則自動創建
 * 路徑: [應用程序目錄]/data
 */
QString Database::dataDir()
{
    // 使用應用程序運行目錄下的 data 文件夾
    // 這樣所有數據都會保存在一個地方
    QString dir = QCoreApplication::applicationDirPath() + "/data";
    // 若目錄不存在則創建
    QDir().mkpath(dir);
    return dir;
}

/**
 * 初始化數據庫 - initialize()
 * 返回值: bool - 初始化成功返回true，失敗返回false
 * 功能: 
 *  1. 確定數據目錄
 *  2. 打開SQLite數據庫連接
 *  3. 創建必要的數據表
 * 流程: 數據目錄 → 數據庫路徑 → 打開連接 → 創建表
 */
bool Database::initialize()
{
    // 使用統一的數據目錄
    QString dataPath = dataDir();
    qDebug() << "數據目錄:" << dataPath;

    // 設定資料庫路徑
    QString dbPath = dataPath + "/tasks.db";
    qDebug() << "資料庫路徑:" << dbPath;

    // 開啟 SQLite 資料庫
    m_db = QSqlDatabase::addDatabase("QSQLITE");  // 使用SQLite驅動
    m_db.setDatabaseName(dbPath);                  // 設置數據庫文件路徑

    // 嘗試打開數據庫連接
    if (!m_db.open()) {
        qDebug() << "無法開啟資料庫:" << m_db.lastError().text();
        return false;
    }

    // 建立資料表
    return createTables();  // 委託給createTables()函數
}

/**
 * 創建數據表 - createTables()
 * 返回值: bool - 創建成功返回true，失敗返回false
 * 功能: 創建兩個主要的數據表
 *  1. tasks 表 - 存儲任務信息
 *  2. attachments 表 - 存儲任務附件信息
 */
bool Database::createTables()
{
    QSqlQuery query;

    // 建立任務表 - 存儲所有任務的基本信息
    QString createTasksTable = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,        -- 任務唯一ID
            title TEXT NOT NULL,                         -- 任務標題（必填）
            description TEXT,                            -- 任務描述
            due_datetime INTEGER,                        -- 截止日期時間戳
            priority INTEGER DEFAULT 0,                  -- 優先級（0=低，1=中，2=高）
            tags TEXT,                                   -- 標籤（逗號分隔）
            created_at INTEGER,                          -- 創建時間戳
            updated_at INTEGER,                          -- 更新時間戳
            is_completed INTEGER DEFAULT 0,              -- 完成狀態（0=未完成，1=已完成）
            completed_at INTEGER,                        -- 完成時間戳
            reminder_at INTEGER                          -- 提醒時間戳
        )
    )";

    // 執行任務表創建語句
    if (!query.exec(createTasksTable)) {
        qDebug() << "建立任務表失敗:" << query.lastError().text();
        return false;
    }

    // 建立附件表 - 存儲與任務關聯的附件信息
    QString createAttachmentsTable = R"(
        CREATE TABLE IF NOT EXISTS attachments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,        -- 附件唯一ID
            task_id INTEGER,                             -- 關聯的任務ID
            original_name TEXT,                          -- 附件原始文件名
            stored_path TEXT,                            -- 附件存儲路徑
            mime_type TEXT,                              -- 文件MIME類型
            added_at INTEGER,                            -- 添加時間戳
            snapshot_path TEXT,                          -- 附件的快照/縮略圖路徑
            FOREIGN KEY (task_id) REFERENCES tasks(id) ON DELETE CASCADE  -- 外鍵約束，任務刪除時自動刪除附件
        )
    )";

    // 執行附件表創建語句
    if (!query.exec(createAttachmentsTable)) {
        qDebug() << "建立附件表失敗:" << query.lastError().text();
        return false;
    }

    qDebug() << "資料表建立成功";
    return true;
}

/**
 * 添加任務 - addTask()
 * 參數: task - 要添加的任務對象（引用傳遞，函數會修改其id和時間戳）
 * 返回值: bool - 添加成功返回true，失敗返回false
 * 功能: 
 *  1. 為任務設置創建時間和更新時間為當前時間
 *  2. 將任務信息插入到tasks表中
 *  3. 將自動生成的ID賦回給task對象
 */
bool Database::addTask(Task &task)
{
    QSqlQuery query;
    // 使用參數化查詢防止SQL注入，並指定要插入的所有字段
    query.prepare(R"(
        INSERT INTO tasks (title, description, due_datetime, priority, tags,
                          created_at, updated_at, is_completed, reminder_at)
        VALUES (:title, :description, :due, :priority, :tags,
                :created, :updated, :completed, :reminder)
    )");

    // 獲取當前時間戳
    QDateTime now = QDateTime::currentDateTime();
    task.createdAt = now;  // 設置任務創建時間
    task.updatedAt = now;  // 設置任務更新時間

    // 綁定所有參數值到SQL語句中
    query.bindValue(":title", task.title);
    query.bindValue(":description", task.description);
    // 若due_datetime有效則轉換為時間戳，否則傳NULL
    query.bindValue(":due", task.dueDateTime.isValid() ? task.dueDateTime.toSecsSinceEpoch() : QVariant());
    query.bindValue(":priority", task.priority);
    query.bindValue(":tags", task.tags);
    query.bindValue(":created", now.toSecsSinceEpoch());
    query.bindValue(":updated", now.toSecsSinceEpoch());
    query.bindValue(":completed", task.isCompleted ? 1 : 0);  // 布爾值轉換為0或1
    query.bindValue(":reminder", task.reminderAt.isValid() ? task.reminderAt.toSecsSinceEpoch() : QVariant());

    // 執行INSERT語句
    if (!query.exec()) {
        qDebug() << "新增任務失敗:" << query.lastError().text();
        return false;
    }

    // 取得自動產生的 ID 並賦值回Task對象
    task.id = query.lastInsertId().toInt();
    qDebug() << "新增任務成功，ID:" << task.id;
    return true;
}

/**
 * 更新任務 - updateTask()
 * 參數: task - 包含要更新信息的任務對象
 * 返回值: bool - 更新成功返回true，失敗返回false
 * 功能: 根據任務ID更新該任務在數據庫中的所有信息
 * 注意: 自動更新updated_at為當前時間
 */
bool Database::updateTask(const Task &task)
{
    QSqlQuery query;
    // 準備UPDATE語句，更新所有可編輯的字段
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

    // 綁定所有參數值
    query.bindValue(":id", task.id);  // 用於WHERE子句，定位要更新的任務
    query.bindValue(":title", task.title);
    query.bindValue(":description", task.description);
    query.bindValue(":due", task.dueDateTime.isValid() ? task.dueDateTime.toSecsSinceEpoch() : QVariant());
    query.bindValue(":priority", task.priority);
    query.bindValue(":tags", task.tags);
    // 自動更新為當前時間
    query.bindValue(":updated", QDateTime::currentDateTime().toSecsSinceEpoch());
    query.bindValue(":completed", task.isCompleted ? 1 : 0);
    query.bindValue(":completedAt", task.completedAt.isValid() ? task.completedAt.toSecsSinceEpoch() : QVariant());
    query.bindValue(":reminder", task.reminderAt.isValid() ? task.reminderAt.toSecsSinceEpoch() : QVariant());

    // 執行UPDATE語句
    if (!query.exec()) {
        qDebug() << "更新任務失敗:" << query.lastError().text();
        return false;
    }

    qDebug() << "更新任務成功，ID:" << task.id;
    return true;
}

/**
 * 刪除任務 - deleteTask()
 * 參數: taskId - 要刪除的任務ID
 * 返回值: bool - 刪除成功返回true，失敗返回false
 * 功能: 根據ID刪除指定的任務
 * 副作用: 由於外鍵約束(ON DELETE CASCADE)，該任務的所有附件也會被自動刪除
 */
bool Database::deleteTask(int taskId)
{
    QSqlQuery query;
    // 使用參數化查詢刪除指定ID的任務
    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    // 執行DELETE語句
    if (!query.exec()) {
        qDebug() << "刪除任務失敗:" << query.lastError().text();
        return false;
    }

    qDebug() << "刪除任務成功，ID:" << taskId;
    return true;
}

/**
 * 標記任務完成狀態 - markTaskCompleted()
 * 參數: 
 *   - taskId: 任務ID
 *   - completed: 完成狀態（true=標記為已完成，false=標記為未完成）
 * 返回值: bool - 操作成功返回true，失敗返回false
 * 功能: 切換指定任務的完成狀態，並自動更新completed_at時間戳
 * 流程: 更新is_completed狀態 → 若completed為true則設置completed_at為當前時間 → 更新updated_at
 */
bool Database::markTaskCompleted(int taskId, bool completed)
{
    QSqlQuery query;
    // 準備UPDATE語句來修改完成狀態和相關時間戳
    query.prepare(R"(
        UPDATE tasks SET
            is_completed = :completed,
            completed_at = :completedAt,
            updated_at = :updated
        WHERE id = :id
    )");

    QDateTime now = QDateTime::currentDateTime();  // 獲取當前時間
    query.bindValue(":id", taskId);
    query.bindValue(":completed", completed ? 1 : 0);  // 布爾值轉換為0或1
    // 若completed為true則設置completed_at為當前時間，否則設為NULL
    query.bindValue(":completedAt", completed ? now.toSecsSinceEpoch() : QVariant());
    query.bindValue(":updated", now.toSecsSinceEpoch());

    // 執行UPDATE語句
    if (!query.exec()) {
        qDebug() << "標記完成失敗:" << query.lastError().text();
        return false;
    }

    // 根據狀態輸出相應的調試信息
    qDebug() << "標記任務" << (completed ? "完成" : "未完成") << "，ID:" << taskId;
    return true;
}

/**
 * 獲取單個任務 - getTask()
 * 參數: taskId - 要查詢的任務ID
 * 返回值: Task - 返回查詢結果的Task對象（若未找到則返回空Task對象）
 * 功能: 根據ID查詢數據庫中的任務信息，並將其還原為Task對象
 * 流程: 執行SELECT查詢 → 從結果集提取數據 → 將時間戳轉換回QDateTime → 返回Task對象
 */
Task Database::getTask(int taskId)
{
    Task task;  // 創建空的Task對象作為返回值
    QSqlQuery query;
    // 使用參數化查詢防止SQL注入
    query.prepare("SELECT * FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    // 執行查詢並檢查是否有結果
    if (!query.exec() || !query.next()) {
        qDebug() << "取得任務失敗，ID:" << taskId;
        return task;  // 返回空Task對象
    }

    // 逐個從查詢結果中提取字段值並賦值到Task對象
    task.id = query.value("id").toInt();
    task.title = query.value("title").toString();
    task.description = query.value("description").toString();

    // 提取並轉換due_datetime（從時間戳轉回QDateTime）
    qint64 dueSecs = query.value("due_datetime").toLongLong();
    if (dueSecs > 0) {
        task.dueDateTime = QDateTime::fromSecsSinceEpoch(dueSecs);
    }

    task.priority = query.value("priority").toInt();
    task.tags = query.value("tags").toString();

    // 提取並轉換created_at
    qint64 createdSecs = query.value("created_at").toLongLong();
    if (createdSecs > 0) {
        task.createdAt = QDateTime::fromSecsSinceEpoch(createdSecs);
    }

    // 提取並轉換updated_at
    qint64 updatedSecs = query.value("updated_at").toLongLong();
    if (updatedSecs > 0) {
        task.updatedAt = QDateTime::fromSecsSinceEpoch(updatedSecs);
    }

    // 提取完成狀態（0或1轉換為布爾值）
    task.isCompleted = query.value("is_completed").toInt() == 1;

    // 提取並轉換completed_at
    qint64 completedSecs = query.value("completed_at").toLongLong();
    if (completedSecs > 0) {
        task.completedAt = QDateTime::fromSecsSinceEpoch(completedSecs);
    }

    // 提取並轉換reminder_at
    qint64 reminderSecs = query.value("reminder_at").toLongLong();
    if (reminderSecs > 0) {
        task.reminderAt = QDateTime::fromSecsSinceEpoch(reminderSecs);
    }

    return task;  // 返回構建完成的Task對象
}

/**
 * 獲取所有任務 - getAllTasks()
 * 返回值: QList<Task> - 包含所有任務的列表
 * 功能: 從數據庫中查詢所有任務並返回List
 * 排序方式: 優先顯示未完成的任務 → 按截止日期升序 → 按優先級降序
 * 副作用: 自動為每個任務加載其關聯的附件列表
 */
QList<Task> Database::getAllTasks()
{
    QList<Task> tasks;  // 創建任務列表
    // 執行SELECT查詢，獲取所有任務，並按指定方式排序
    QSqlQuery query("SELECT * FROM tasks ORDER BY is_completed ASC, due_datetime ASC, priority DESC");

    // 遍歷查詢結果集中的每一行
    while (query.next()) {
        Task task;  // 為每個結果創建一個Task對象
        
        // 逐個提取字段值
        task.id = query.value("id").toInt();
        task.title = query.value("title").toString();
        task.description = query.value("description").toString();

        // 提取並轉換due_datetime
        qint64 dueSecs = query.value("due_datetime").toLongLong();
        if (dueSecs > 0) {
            task.dueDateTime = QDateTime::fromSecsSinceEpoch(dueSecs);
        }

        task.priority = query.value("priority").toInt();
        task.tags = query.value("tags").toString();

        // 提取並轉換created_at
        qint64 createdSecs = query.value("created_at").toLongLong();
        if (createdSecs > 0) {
            task.createdAt = QDateTime::fromSecsSinceEpoch(createdSecs);
        }

        // 提取並轉換updated_at
        qint64 updatedSecs = query.value("updated_at").toLongLong();
        if (updatedSecs > 0) {
            task.updatedAt = QDateTime::fromSecsSinceEpoch(updatedSecs);
        }

        // 提取完成狀態
        task.isCompleted = query.value("is_completed").toInt() == 1;

        // 提取並轉換completed_at
        qint64 completedSecs = query.value("completed_at").toLongLong();
        if (completedSecs > 0) {
            task.completedAt = QDateTime::fromSecsSinceEpoch(completedSecs);
        }

        // 提取並轉換reminder_at
        qint64 reminderSecs = query.value("reminder_at").toLongLong();
        if (reminderSecs > 0) {
            task.reminderAt = QDateTime::fromSecsSinceEpoch(reminderSecs);
        }
        
        // 載入該任務的附件列表
        task.attachments = getAttachments(task.id);

        // 將構建完成的Task對象添加到列表中
        tasks.append(task);
    }

    // 輸出調試信息：已加載的任務數量
    qDebug() << "載入任務數量:" << tasks.size();
    return tasks;  // 返回任務列表
}

// ============================================================
// 附件操作模塊 - 處理任務附件的增、刪、查操作
// ============================================================

/**
 * 獲取附件目錄 - attachmentsDir()
 * 返回值: QString - 附件存儲文件夾的完整路徑
 * 功能: 返回應用程序附件存儲目錄，若目錄不存在則自動創建
 * 路徑: [應用程序目錄]/data/attachments
 */
QString Database::attachmentsDir()
{
    // 在data文件夾下創建attachments子文件夾
    QString dir = dataDir() + "/attachments";
    // 若目錄不存在則創建
    QDir().mkpath(dir);
    return dir;
}

/**
 * 添加附件 - addAttachment()
 * 參數: attachment - 要添加的附件對象（引用傳遞，函數會修改其id和addedAt）
 * 返回值: bool - 添加成功返回true，失敗返回false
 * 功能: 
 *  1. 為附件設置添加時間為當前時間
 *  2. 將附件信息記錄到attachments表中
 *  3. 將自動生成的ID賦回給attachment對象
 */
bool Database::addAttachment(Attachment &attachment)
{
    QSqlQuery query;
    // 使用參數化查詢將附件信息插入到attachments表
    query.prepare(R"(
        INSERT INTO attachments (task_id, original_name, stored_path, mime_type, added_at, snapshot_path)
        VALUES (:task_id, :name, :path, :mime, :added, :snapshot)
    )");
    
    // 設置附件的添加時間為當前時間
    attachment.addedAt = QDateTime::currentDateTime();
    
    // 綁定所有參數值
    query.bindValue(":task_id", attachment.taskId);      // 關聯的任務ID
    query.bindValue(":name", attachment.originalName);   // 原始文件名
    query.bindValue(":path", attachment.storedPath);     // 存儲路徑
    query.bindValue(":mime", attachment.mimeType);       // MIME類型
    query.bindValue(":added", attachment.addedAt.toSecsSinceEpoch());  // 添加時間戳
    query.bindValue(":snapshot", attachment.snapshotPath);  // 快照路徑
    
    // 執行INSERT語句
    if (!query.exec()) {
        qDebug() << "新增附件失敗:" << query.lastError().text();
        return false;
    }
    
    // 取得自動產生的ID並賦值回attachment對象
    attachment.id = query.lastInsertId().toInt();
    qDebug() << "附件已新增，ID:" << attachment.id;
    return true;
}

/**
 * 刪除附件 - deleteAttachment()
 * 參數: attachmentId - 要刪除的附件ID
 * 返回值: bool - 刪除成功返回true，失敗返回false
 * 功能: 
 *  1. 查詢附件的存儲路徑
 *  2. 刪除磁盤上的附件文件
 *  3. 從數據庫中刪除附件記錄
 */
bool Database::deleteAttachment(int attachmentId)
{
    // 先查詢附件信息以獲取文件存儲路徑
    QSqlQuery query;
    query.prepare("SELECT stored_path FROM attachments WHERE id = :id");
    query.bindValue(":id", attachmentId);
    
    // 若查詢成功且找到記錄，則刪除對應的磁盤文件
    if (query.exec() && query.next()) {
        QString filePath = query.value(0).toString();  // 獲取存儲路徑
        // 檢查文件是否存在，若存在則刪除
        if (QFile::exists(filePath)) {
            QFile::remove(filePath);  // 物理刪除磁盤上的文件
        }
    }
    
    // 從數據庫中刪除附件記錄
    query.prepare("DELETE FROM attachments WHERE id = :id");
    query.bindValue(":id", attachmentId);
    
    // 執行DELETE語句
    if (!query.exec()) {
        qDebug() << "刪除附件失敗:" << query.lastError().text();
        return false;
    }
    
    qDebug() << "附件已刪除，ID:" << attachmentId;
    return true;
}

/**
 * 獲取任務的所有附件 - getAttachments()
 * 參數: taskId - 任務ID
 * 返回值: QList<Attachment> - 該任務的所有附件列表
 * 功能: 根據任務ID查詢所有關聯的附件
 * 排序方式: 按添加時間降序（最新的附件顯示在前）
 */
QList<Attachment> Database::getAttachments(int taskId)
{
    QList<Attachment> attachments;  // 創建附件列表
    
    QSqlQuery query;
    // 查詢指定任務的所有附件，並按添加時間降序排列
    query.prepare("SELECT * FROM attachments WHERE task_id = :task_id ORDER BY added_at DESC");
    query.bindValue(":task_id", taskId);
    
    // 執行查詢
    if (!query.exec()) {
        qDebug() << "查詢附件失敗:" << query.lastError().text();
        return attachments;  // 查詢失敗則返回空列表
    }
    
    // 遍歷查詢結果集中的每一行
    while (query.next()) {
        Attachment att;  // 為每個結果創建一個Attachment對象
        
        // 逐個提取字段值
        att.id = query.value("id").toInt();
        att.taskId = query.value("task_id").toInt();
        att.originalName = query.value("original_name").toString();
        att.storedPath = query.value("stored_path").toString();
        att.mimeType = query.value("mime_type").toString();
        att.snapshotPath = query.value("snapshot_path").toString();
        
        // 提取並轉換added_at（從時間戳轉回QDateTime）
        qint64 addedSecs = query.value("added_at").toLongLong();
        if (addedSecs > 0) {
            att.addedAt = QDateTime::fromSecsSinceEpoch(addedSecs);
        }
        
        // 將構建完成的Attachment對象添加到列表中
        attachments.append(att);
    }
    
    return attachments;  // 返回附件列表
}