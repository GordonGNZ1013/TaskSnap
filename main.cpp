#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDateTime>

// 自定義消息處理器，將所有 qDebug 和 qWarning 寫入文件
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QFile logFile;
    static bool fileOpened = false;
    
    if (!fileOpened) {
        QString logPath = QCoreApplication::applicationDirPath() + "/debug.log";
        logFile.setFileName(logPath);
        if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            fileOpened = true;
        }
    }
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    QString formattedMessage;
    
    switch (type) {
        case QtDebugMsg:
            formattedMessage = QString("[DEBUG] %1 - %2\n").arg(timestamp, msg);
            break;
        case QtWarningMsg:
            formattedMessage = QString("[WARN ] %1 - %2\n").arg(timestamp, msg);
            break;
        case QtCriticalMsg:
            formattedMessage = QString("[CRIT ] %1 - %2\n").arg(timestamp, msg);
            break;
        case QtFatalMsg:
            formattedMessage = QString("[FATAL] %1 - %2\n").arg(timestamp, msg);
            break;
        case QtInfoMsg:
            formattedMessage = QString("[INFO ] %1 - %2\n").arg(timestamp, msg);
            break;
    }
    
    if (fileOpened) {
        logFile.write(formattedMessage.toUtf8());
        logFile.flush();
    }
    
    // 同時輸出到控制台
    fprintf(stderr, "%s", formattedMessage.toUtf8().constData());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 安裝自定義消息處理器
    qInstallMessageHandler(customMessageHandler);

    // 設定應用程式資訊
    QCoreApplication::setApplicationName("專案小幫手");
    QCoreApplication::setOrganizationName("專案小幫手");
    QCoreApplication::setApplicationVersion("1.0.0");
    
    qDebug() << "\n========== 應用程序啟動 ==========";
    qDebug() << "應用目錄:" << QCoreApplication::applicationDirPath();
    qDebug() << "時間:" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    MainWindow w;
    w.show();

    return a.exec();
}
