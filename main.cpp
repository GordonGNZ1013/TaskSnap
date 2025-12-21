// ========================================
// 主程序入口 (main.cpp)
// 功能: 應用程序的啟動點，進行初始化配置和日誌設置
// ========================================

#include "mainwindow.h"           // 主窗口類
#include <QApplication>           // Qt應用程序類
#include <QFile>                  // 文件操作
#include <QDebug>                 // 調試輸出
#include <QDateTime>              // 日期時間

/**
 * 自定義消息處理器 - customMessageHandler()
 * 功能: 攔截所有的qDebug、qWarning等調試輸出
 * 操作: 
 *  1. 將所有日誌信息寫入 debug.log 文件
 *  2. 同時輸出到控制台（stderr）
 *  3. 為每條日誌添加時間戳和日誌級別標記
 * 
 * 參數:
 *   - type: 消息類型（Debug、Warning、Critical等）
 *   - context: 消息上下文信息（文件、行號等）
 *   - msg: 消息內容
 */
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QFile logFile;       // 日誌文件（靜態變量，全程序生命周期保存）
    static bool fileOpened = false;  // 文件打開標誌
    
    // 首次調用時打開日誌文件
    if (!fileOpened) {
        // 構建日誌文件路徑：應用程序目錄/debug.log
        QString logPath = QCoreApplication::applicationDirPath() + "/debug.log";
        logFile.setFileName(logPath);
        // 以追加模式打開文件（文本模式）
        if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            fileOpened = true;
        }
    }
    
    // 獲取當前時間戳，格式：yyyy-MM-dd HH:mm:ss.zzz
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    QString formattedMessage;  // 格式化後的日誌信息
    
    // 根據消息類型設置相應的日誌前綴
    switch (type) {
        case QtDebugMsg:
            // 調試信息前綴為 [DEBUG]
            formattedMessage = QString("[DEBUG] %1 - %2\n").arg(timestamp, msg);
            break;
        case QtWarningMsg:
            // 警告信息前綴為 [WARN ]
            formattedMessage = QString("[WARN ] %1 - %2\n").arg(timestamp, msg);
            break;
        case QtCriticalMsg:
            // 嚴重錯誤前綴為 [CRIT ]
            formattedMessage = QString("[CRIT ] %1 - %2\n").arg(timestamp, msg);
            break;
        case QtFatalMsg:
            // 致命錯誤前綴為 [FATAL]
            formattedMessage = QString("[FATAL] %1 - %2\n").arg(timestamp, msg);
            break;
        case QtInfoMsg:
            // 信息提示前綴為 [INFO ]
            formattedMessage = QString("[INFO ] %1 - %2\n").arg(timestamp, msg);
            break;
    }
    
    // 若日誌文件已成功打開，則寫入格式化的日誌信息
    if (fileOpened) {
        logFile.write(formattedMessage.toUtf8());  // 寫入文件
        logFile.flush();                            // 立即刷新文件緩衝
    }
    
    // 同時輸出到控制台（標準錯誤流）用於實時查看
    fprintf(stderr, "%s", formattedMessage.toUtf8().constData());
}
/**
 * 主函數 - main()
 * 參數:
 *   - argc: 命令行參數個數
 *   - argv: 命令行參數數組
 * 返回值: int - 應用程序退出碼
 * 功能: 
 *  1. 初始化Qt應用程序
 *  2. 安裝自定義日誌處理器
 *  3. 設置應用程序信息（名稱、版本等）
 *  4. 創建並顯示主窗口
 *  5. 進入事件循環
 */
int main(int argc, char *argv[])
{
    // 創建Qt應用程序對象
    // 這必須在所有其他Qt對象之前完成
    QApplication a(argc, argv);
    
    // 安裝自定義消息處理器
    // 之後的所有qDebug()和qWarning()調用都會被攔截
    qInstallMessageHandler(customMessageHandler);

    // 設定應用程式資訊（用於文件對話框、關於對話框等）
    QCoreApplication::setApplicationName("專案小幫手");  // 應用程序名稱
    QCoreApplication::setOrganizationName("專案小幫手");  // 組織名稱
    QCoreApplication::setApplicationVersion("1.0.0");   // 應用版本號
    
    // 應用程序啟動日誌
    qDebug() << "\n========== 應用程序啟動 ==========";
    qDebug() << "應用目錄:" << QCoreApplication::applicationDirPath();
    qDebug() << "時間:" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // 創建並顯示主窗口
    MainWindow w;
    w.show();

    // 進入Qt事件循環，程序在此等待用戶操作
    // 直到用戶關閉應用程序或調用quit()時才返回
    return a.exec();
}
