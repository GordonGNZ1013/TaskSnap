#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include "task.h"

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    // 初始化資料庫
    bool initialize();

    // 任務 CRUD 操作
    bool addTask(Task &task);                    // 新增任務（會更新 task.id）
    bool updateTask(const Task &task);           // 更新任務
    bool deleteTask(int taskId);                 // 刪除任務
    bool markTaskCompleted(int taskId, bool completed);  // 標記完成
    Task getTask(int taskId);                    // 取得單一任務
    QList<Task> getAllTasks();                   // 取得所有任務

    // 附件操作
    bool addAttachment(Attachment &attachment);            // 新增附件
    bool deleteAttachment(int attachmentId);               // 刪除附件
    QList<Attachment> getAttachments(int taskId);          // 取得任務的附件
    
    // 子任務操作
    bool addSubTask(SubTask &subTask);                     // 新增子任務
    bool updateSubTask(const SubTask &subTask);            // 更新子任務
    bool deleteSubTask(int subTaskId);                     // 刪除子任務
    bool markSubTaskCompleted(int subTaskId, bool completed);  // 標記子任務完成
    QList<SubTask> getSubTasks(int taskId);                // 取得任務的子任務
    
    // 靈感/待辦操作
    bool addIdeaNote(IdeaNote &idea);                      // 新增靈感
    bool updateIdeaNote(const IdeaNote &idea);             // 更新靈感
    bool deleteIdeaNote(int ideaId);                       // 刪除靈感
    bool toggleIdeaImportant(int ideaId, bool important);  // 切換重要標記
    QList<IdeaNote> getIdeaNotes(int taskId);              // 取得任務的靈感列表
    
    // 取得附件儲存目錄
    static QString attachmentsDir();
    
    // 取得數據根目錄
    static QString dataDir();

private:
    QSqlDatabase m_db;
    bool createTables();
};

#endif // DATABASE_H
