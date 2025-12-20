#include "snapshotmanager.h"
#include "database.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QTextStream>
#include <QProcess>
#include <QCoreApplication>
#include <QStringConverter>

SnapshotManager::SnapshotManager(QObject *parent)
    : QObject(parent)
{
}

SnapshotManager::~SnapshotManager()
{
}

QString SnapshotManager::snapshotsDir()
{
    // 使用統一的數據目錄
    QString dir = Database::dataDir() + "/snapshots";
    QDir().mkpath(dir);
    return dir;
}

QString SnapshotManager::createSnapshot(const Task &task)
{
    qDebug() << "========== 開始建立快照 ==========";
    qDebug() << "任務 ID:" << task.id;
    qDebug() << "任務標題:" << task.title;
    
    if (task.id <= 0) {
        qWarning() << "無效的任務 ID";
        return "";
    }

    // 建立臨時目錄用於組織快照文件
    QString snapshotsDirectory = snapshotsDir();
    qDebug() << "快照目錄:" << snapshotsDirectory;
    
    QString tempDir = snapshotsDirectory + "/.temp_" + QString::number(task.id) + "_" + QString::number(QDateTime::currentMSecsSinceEpoch());
    qDebug() << "臨時目錄:" << tempDir;
    
    if (!QDir().mkpath(tempDir)) {
        qWarning() << "無法建立臨時目錄:" << tempDir;
        return "";
    }
    qDebug() << "臨時目錄建立成功";

    // 生成任務信息文件
    if (!createTaskInfoFile(task, tempDir)) {
        qWarning() << "無法建立任務信息文件";
        QDir(tempDir).removeRecursively();
        return "";
    }
    qDebug() << "任務信息文件建立成功";

    // 複製附件（如果有的話）
    if (!task.attachments.isEmpty()) {
        qDebug() << "開始複製附件，數量:" << task.attachments.size();
        if (!copyAttachments(task, tempDir)) {
            qWarning() << "複製附件時失敗";
            QDir(tempDir).removeRecursively();
            return "";
        }
        qDebug() << "附件複製完成";
    } else {
        qDebug() << "沒有附件";
    }

    // 生成快照文件名
    // 格式：Task_123_2025-12-18_15-30-45.zip
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
    QString zipFileName = QString("Task_%1_%2.zip")
        .arg(task.id, 6, 10, QChar('0'))
        .arg(timestamp);
    QString zipPath = snapshotsDir() + "/" + zipFileName;
    
    qDebug() << "ZIP 文件名:" << zipFileName;
    qDebug() << "ZIP 文件完整路徑:" << zipPath;

    // 建立 ZIP 存檔
    qDebug() << "開始建立 ZIP 存檔...";
    if (!createZipArchive(tempDir, zipPath)) {
        qWarning() << "無法建立 ZIP 存檔";
        QDir(tempDir).removeRecursively();
        return "";
    }
    qDebug() << "ZIP 存檔建立成功";

    // 刪除臨時目錄
    if (QDir(tempDir).removeRecursively()) {
        qDebug() << "臨時目錄已清理";
    } else {
        qWarning() << "無法刪除臨時目錄";
    }

    qDebug() << "========== 快照建立完成 ==========";
    qDebug() << "快照已建立：" << zipPath;
    return zipPath;
}

bool SnapshotManager::createTaskInfoFile(const Task &task, const QString &targetDir)
{
    qDebug() << "開始建立任務信息文件...";
    qDebug() << "目標目錄：" << targetDir;
    
    QString infoFilePath = targetDir + "/TaskInfo.txt";
    qDebug() << "信息文件路徑：" << infoFilePath;
    
    QFile file(infoFilePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "無法建立任務信息文件：" << infoFilePath;
        qWarning() << "錯誤信息：" << file.errorString();
        return false;
    }
    
    qDebug() << "✓ 文件已打開";

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    qDebug() << "✓ 文本流已初始化";

    // 寫入任務信息
    out << "================== 任務快照 ==================\n\n";
    out << "任務 ID：" << task.id << "\n";
    out << "標題：" << task.title << "\n";
    out << "描述：" << task.description << "\n";
    out << "優先級：" << task.priorityText() << "\n";
    out << "標籤：" << (task.tags.isEmpty() ? "無" : task.tags) << "\n";
    out << "\n================== 時間信息 ==================\n\n";
    out << "建立時間：" << task.createdAt.toString("yyyy-MM-dd HH:mm:ss") << "\n";
    out << "更新時間：" << task.updatedAt.toString("yyyy-MM-dd HH:mm:ss") << "\n";
    
    if (task.dueDateTime.isValid()) {
        out << "截止時間：" << task.dueDateTime.toString("yyyy-MM-dd HH:mm:ss") << "\n";
    }
    
    if (task.completedAt.isValid()) {
        out << "完成時間：" << task.completedAt.toString("yyyy-MM-dd HH:mm:ss") << "\n";
    }

    out << "\n================== 附件列表 ==================\n\n";
    if (task.attachments.isEmpty()) {
        out << "無附件\n";
    } else {
        for (int i = 0; i < task.attachments.size(); ++i) {
            const Attachment &att = task.attachments[i];
            out << (i + 1) << ". " << att.originalName << "\n";
            out << "   添加時間：" << att.addedAt.toString("yyyy-MM-dd HH:mm:ss") << "\n";
            out << "   文件類型：" << att.mimeType << "\n";
        }
    }

    out << "\n================== 快照信息 ==================\n\n";
    out << "快照建立時間：" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n";
    out << "應用程序版本：1.0.0\n";

    out.flush();
    file.close();
    
    qDebug() << "✓ 任務信息文件建立成功";
    return true;
}

bool SnapshotManager::copyAttachments(const Task &task, const QString &targetDir)
{
    qDebug() << "開始複製附件...";
    qDebug() << "附件數量：" << task.attachments.size();
    
    // 建立附件子目錄
    QString attachmentsSubDir = targetDir + "/attachments";
    if (!QDir().mkpath(attachmentsSubDir)) {
        qWarning() << "無法建立附件目錄：" << attachmentsSubDir;
        return false;
    }
    qDebug() << "✓ 附件目錄已建立：" << attachmentsSubDir;

    // 複製每個附件
    int copiedCount = 0;
    for (const Attachment &att : task.attachments) {
        qDebug() << "處理附件：" << att.originalName;
        qDebug() << "源路徑：" << att.storedPath;
        
        if (!QFile::exists(att.storedPath)) {
            qWarning() << "✗ 附件不存在：" << att.storedPath;
            continue;  // 繼續複製其他附件
        }

        QString destPath = attachmentsSubDir + "/" + att.originalName;
        
        // 如果目標文件已存在，添加序號
        if (QFile::exists(destPath)) {
            int counter = 1;
            QString baseName = att.originalName;
            int dotIndex = baseName.lastIndexOf('.');
            QString nameWithoutExt = (dotIndex > 0) ? baseName.left(dotIndex) : baseName;
            QString ext = (dotIndex > 0) ? baseName.mid(dotIndex) : "";

            while (QFile::exists(destPath)) {
                destPath = attachmentsSubDir + "/" + nameWithoutExt + "_" + QString::number(counter) + ext;
                counter++;
            }
        }

        if (!QFile::copy(att.storedPath, destPath)) {
            qWarning() << "✗ 無法複製附件：" << att.storedPath << " -> " << destPath;
            continue;  // 繼續複製其他附件
        }

        qDebug() << "✓ 附件已複製：" << destPath;
        copiedCount++;
    }

    qDebug() << "✓ 附件複製完成，共複製" << copiedCount << "個文件";
    return true;
}

bool SnapshotManager::createZipArchive(const QString &sourceDir, const QString &zipPath)
{
    qDebug() << "開始建立 ZIP 存檔";
    qDebug() << "源目錄:" << sourceDir;
    qDebug() << "ZIP 路徑:" << zipPath;

#ifdef Q_OS_WIN
    // 嘗試使用 tar 命令（Windows 10+ 內置）
    QProcess process;
    
    // 首先嘗試 tar 命令
    QStringList args;
    args << "-a"  // 自動檢測格式
         << "-c"  // 創建存檔
         << "-f" << zipPath  // 指定輸出文件
         << "-C" << sourceDir  // 改變到源目錄
         << ".";  // 壓縮當前目錄的所有文件
    
    qDebug() << "嘗試使用 tar 命令...";
    process.start("tar", args);
    bool success = process.waitForFinished(30000);
    
    if (success && process.exitCode() == 0 && QFile::exists(zipPath)) {
        qDebug() << "✓ 使用 tar 命令成功建立 ZIP 存檔";
        return true;
    }
    
    qDebug() << "tar 命令失敗，嘗試 PowerShell...";
    
    // 備用方案：使用 PowerShell
    QString escapedSourceDir = QString(sourceDir).replace("\\", "\\\\");
    QString escapedZipPath = QString(zipPath).replace("\\", "\\\\");
    
    QString psCommand = QString(
        "cd '%1' && tar -cf '%2' ."
    ).arg(sourceDir, zipPath);
    
    process.start("cmd.exe", QStringList() << "/c" << psCommand);
    success = process.waitForFinished(30000);
    
    if (success && process.exitCode() == 0 && QFile::exists(zipPath)) {
        qDebug() << "✓ 使用 PowerShell 命令成功建立 ZIP 存檔";
        return true;
    }
    
    qWarning() << "ZIP 壓縮失敗";
    qWarning() << "標準輸出:" << QString::fromUtf8(process.readAllStandardOutput());
    qWarning() << "標準錯誤:" << QString::fromUtf8(process.readAllStandardError());
    return false;

#else
    // Linux/Mac 上使用 zip 命令
    QProcess process;
    process.start("zip", QStringList() << "-r" << zipPath << sourceDir);
    bool success = process.waitForFinished(30000);
    
    if (!success || process.exitCode() != 0) {
        qWarning() << "ZIP 壓縮失敗";
        return false;
    }
    
    qDebug() << "ZIP 存檔建立成功：" << zipPath;
    return true;
#endif
}

bool SnapshotManager::deleteSnapshot(const QString &snapshotPath)
{
    if (!QFile::exists(snapshotPath)) {
        qWarning() << "快照不存在：" << snapshotPath;
        return false;
    }

    if (!QFile::remove(snapshotPath)) {
        qWarning() << "無法刪除快照：" << snapshotPath;
        return false;
    }

    qDebug() << "快照已刪除：" << snapshotPath;
    return true;
}
