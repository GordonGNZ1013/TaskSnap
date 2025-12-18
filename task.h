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
};

#endif // TASK_H
