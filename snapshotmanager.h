#ifndef SNAPSHOTMANAGER_H
#define SNAPSHOTMANAGER_H

#include <QString>
#include <QObject>
#include "task.h"

/**
 * @brief 快照管理器
 * 當任務完成時，自動建立快照存檔
 * 包含任務信息和所有附件
 */
class SnapshotManager : public QObject
{
    Q_OBJECT

public:
    explicit SnapshotManager(QObject *parent = nullptr);
    ~SnapshotManager();

    /**
     * @brief 為已完成的任務建立快照
     * @param task 任務信息
     * @return 快照存檔路徑；失敗返回空字符串
     */
    QString createSnapshot(const Task &task);

    /**
     * @brief 取得快照存儲目錄
     * @return 快照存儲目錄路徑
     */
    static QString snapshotsDir();

    /**
     * @brief 刪除指定快照
     * @param snapshotPath 快照路徑
     * @return 成功返回 true
     */
    bool deleteSnapshot(const QString &snapshotPath);

private:
    /**
     * @brief 生成任務信息文件
     * @param task 任務信息
     * @param targetDir 目標目錄
     * @return 成功返回 true
     */
    bool createTaskInfoFile(const Task &task, const QString &targetDir);

    /**
     * @brief 複製附件到快照目錄
     * @param task 任務信息
     * @param targetDir 目標目錄
     * @return 成功返回 true
     */
    bool copyAttachments(const Task &task, const QString &targetDir);

    /**
     * @brief 建立 ZIP 存檔
     * @param sourceDir 源目錄
     * @param zipPath ZIP 存檔路徑
     * @return 成功返回 true
     */
    bool createZipArchive(const QString &sourceDir, const QString &zipPath);
};

#endif // SNAPSHOTMANAGER_H
