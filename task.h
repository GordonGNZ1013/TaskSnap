#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QList>

// 附件資料結構
struct Attachment {
    int id = -1;                          // 資料庫 ID
    int taskId = -1;                      // 所屬任務 ID
    QString originalName;                  // 原始檔案名稱
    QString storedPath;                    // 儲存路徑
    QString mimeType;                      // MIME 類型
    QDateTime addedAt;                     // 新增時間
    QString snapshotPath;                  // 完成快照路徑（可選）
    
    // 便利方法：取得檔案圖示
    QString icon() const {
        if (mimeType.startsWith("image/")) return "🖼️";
        if (mimeType.startsWith("video/")) return "🎬";
        if (mimeType.startsWith("audio/")) return "🎵";
        if (mimeType.contains("pdf")) return "📄";
        if (mimeType.contains("word") || mimeType.contains("document")) return "📝";
        if (mimeType.contains("excel") || mimeType.contains("spreadsheet")) return "📊";
        if (mimeType.contains("zip") || mimeType.contains("rar") || mimeType.contains("7z")) return "📦";
        return "📎";
    }
};

// 子任務資料結構
struct SubTask {
    int id = -1;                          // 資料庫 ID
    int taskId = -1;                      // 所屬父任務 ID
    QString title;                         // 子任務標題
    bool isCompleted = false;              // 是否完成
    int sortOrder = 0;                     // 排序順序
    QDateTime createdAt;                   // 建立時間
    QDateTime completedAt;                 // 完成時間
};

// 靈感/待辦事項資料結構
struct IdeaNote {
    int id = -1;                          // 資料庫 ID
    int taskId = -1;                      // 所屬任務 ID
    QString content;                       // 靈感內容
    QDateTime createdAt;                   // 建立時間
    bool isImportant = false;              // 是否重要/標星
};

// 任務資料結構
struct Task {
    int id = -1;                          // 資料庫 ID（-1 表示新任務）
    QString title;                         // 標題
    QString description;                   // 描述
    QDateTime dueDateTime;                 // 截止日期時間
    int priority = 0;                      // 優先級：0=低, 1=中, 2=高
    QString tags;                          // 標籤（逗號分隔）
    QDateTime createdAt;                   // 建立時間
    QDateTime updatedAt;                   // 更新時間
    bool isCompleted = false;              // 是否完成
    QDateTime completedAt;                 // 完成時間
    QDateTime reminderAt;                  // 提醒時間
    QList<Attachment> attachments;         // 附件列表
    QList<SubTask> subTasks;               // 子任務列表
    QList<IdeaNote> ideas;                 // 靈感/待辦列表

    // 便利方法：取得優先級文字
    QString priorityText() const {
        switch (priority) {
            case 2: return "高";
            case 1: return "中";
            default: return "低";
        }
    }

    // 便利方法：檢查是否過期
    bool isOverdue() const {
        if (isCompleted) return false;
        if (!dueDateTime.isValid()) return false;
        return QDateTime::currentDateTime() > dueDateTime;
    }
    
    // 便利方法：取得子任務完成進度
    QString subTaskProgress() const {
        if (subTasks.isEmpty()) return "";
        int completed = 0;
        for (const SubTask &st : subTasks) {
            if (st.isCompleted) completed++;
        }
        return QString("%1/%2").arg(completed).arg(subTasks.size());
    }
    
    // 便利方法：取得子任務完成百分比
    int subTaskPercentage() const {
        if (subTasks.isEmpty()) return 100;
        int completed = 0;
        for (const SubTask &st : subTasks) {
            if (st.isCompleted) completed++;
        }
        return (completed * 100) / subTasks.size();
    }
};

#endif // TASK_H
