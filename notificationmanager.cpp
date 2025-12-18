#include "notificationmanager.h"
#include <QApplication>
#include <QDebug>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <string>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

NotificationManager::NotificationManager(QObject *parent)
    : QObject(parent)
    , m_reminderTimer(new QTimer(this))
    , m_mediaPlayer(new QMediaPlayer(this))
    , m_audioOutput(new QAudioOutput(this))
{
    // 設定音效播放器
    m_mediaPlayer->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.8);  // 80% 音量

    // 設定提醒檢查計時器（每分鐘檢查一次）
    m_reminderTimer->setInterval(60 * 1000);  // 60 秒
    connect(m_reminderTimer, &QTimer::timeout, this, &NotificationManager::checkReminders);
}

NotificationManager::~NotificationManager()
{
}

void NotificationManager::setTrayIcon(QSystemTrayIcon *trayIcon)
{
    m_trayIcon = trayIcon;
}

void NotificationManager::startReminderCheck()
{
    if (!m_reminderTimer->isActive()) {
        m_reminderTimer->start();
        // 立即檢查一次
        checkReminders();
        qDebug() << "提醒檢查已啟動";
    }
}

void NotificationManager::stopReminderCheck()
{
    m_reminderTimer->stop();
    qDebug() << "提醒檢查已停止";
}

void NotificationManager::updateTasks(const QList<Task> &tasks)
{
    m_tasks = tasks;
}

void NotificationManager::showNotification(NotificationType type, const QString &title, const QString &message)
{
    qDebug() << "顯示通知:" << title << "-" << message;
    qDebug() << "系統匣圖示狀態:" << (m_trayIcon ? "存在" : "不存在") 
             << ", 可見:" << (m_trayIcon && m_trayIcon->isVisible() ? "是" : "否")
             << ", 支援訊息:" << (m_trayIcon && m_trayIcon->supportsMessages() ? "是" : "否");

    // 如果有系統匣圖示，使用它顯示通知
    if (m_trayIcon && m_trayIcon->isVisible()) {
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information;
        
        switch (type) {
            case TaskReminder:
                icon = QSystemTrayIcon::Information;
                break;
            case TaskOverdue:
                icon = QSystemTrayIcon::Warning;
                break;
            case PomodoroComplete:
                icon = QSystemTrayIcon::Information;
                break;
            case BreakComplete:
                icon = QSystemTrayIcon::Information;
                break;
        }
        
        // 顯示通知，持續時間 5 秒
        m_trayIcon->showMessage(title, message, icon, 5000);
    } else {
        qDebug() << "警告：系統匣圖示不可用，無法顯示通知";
    }
}

void NotificationManager::playSound(NotificationType type)
{
    if (!m_soundEnabled) {
        return;
    }

    qDebug() << "播放音效，類型:" << type;

#ifdef Q_OS_WIN
    // 使用 Windows Media 資料夾中的悅耳音效
    QString soundPath;
    
    switch (type) {
        case TaskReminder:
            // 任務提醒 - 使用日曆通知音效（溫和）
            soundPath = "C:\\Windows\\Media\\Windows Notify Calendar.wav";
            break;
        case TaskOverdue:
            // 任務逾期 - 使用較緊急但不刺耳的音效
            soundPath = "C:\\Windows\\Media\\Windows Notify System Generic.wav";
            break;
        case PomodoroComplete:
            // 番茄鐘完成 - 使用愉快的完成音效 🎉
            soundPath = "C:\\Windows\\Media\\Windows Print complete.wav";
            if (!QFile::exists(soundPath)) {
                soundPath = "C:\\Windows\\Media\\tada.wav";
            }
            break;
        case BreakComplete:
            // 休息結束 - 使用輕柔的提醒音效
            soundPath = "C:\\Windows\\Media\\chimes.wav";
            if (!QFile::exists(soundPath)) {
                soundPath = "C:\\Windows\\Media\\notify.wav";
            }
            break;
    }
    
    // 嘗試播放指定音效檔
    if (QFile::exists(soundPath)) {
        std::wstring wpath = soundPath.toStdWString();
        PlaySoundW(wpath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        qDebug() << "播放音效:" << soundPath;
    } else {
        // 備用：使用 ding 音效（最友善的預設音）
        PlaySoundW(L"C:\\Windows\\Media\\ding.wav", NULL, SND_FILENAME | SND_ASYNC);
        qDebug() << "使用備用音效 ding.wav";
    }
#else
    // 其他平台使用 Qt 的 beep
    QApplication::beep();
    
    // 嘗試使用 QMediaPlayer 播放系統音效
    QString soundFile;
    switch (type) {
        case TaskReminder:
        case PomodoroComplete:
            soundFile = "/usr/share/sounds/freedesktop/stereo/complete.oga";
            break;
        case TaskOverdue:
        case BreakComplete:
            soundFile = "/usr/share/sounds/freedesktop/stereo/alarm-clock-elapsed.oga";
            break;
    }
    
    if (QFile::exists(soundFile)) {
        m_mediaPlayer->setSource(QUrl::fromLocalFile(soundFile));
        m_mediaPlayer->play();
    }
#endif
}

void NotificationManager::checkReminders()
{
    QDateTime now = QDateTime::currentDateTime();
    
    for (const Task &task : m_tasks) {
        // 跳過已完成的任務
        if (task.isCompleted) {
            continue;
        }

        // 檢查是否有設定提醒時間
        if (task.reminderAt.isValid() && !m_notifiedTaskIds.contains(task.id)) {
            // 檢查提醒時間是否在現在的 1 分鐘內
            qint64 diff = now.secsTo(task.reminderAt);
            
            if (diff <= 60 && diff >= -60) {  // 提醒時間在前後 1 分鐘內
                // 觸發提醒
                showNotification(TaskReminder, 
                    "📋 任務提醒",
                    QString("任務「%1」提醒您注意！").arg(task.title));
                
                if (m_soundEnabled) {
                    playSound(TaskReminder);
                }
                
                // 記錄已提醒
                m_notifiedTaskIds.insert(task.id);
                emit reminderTriggered(task.id, task.title);
                
                qDebug() << "任務提醒觸發:" << task.title;
            }
        }

        // 檢查是否逾期（截止時間已過）
        if (task.dueDateTime.isValid() && !m_notifiedTaskIds.contains(-task.id)) {  // 用負數 ID 區分逾期通知
            if (task.dueDateTime < now) {
                // 只在剛逾期時提醒（10 分鐘內）
                qint64 overdueMins = task.dueDateTime.secsTo(now) / 60;
                
                if (overdueMins <= 10) {
                    showNotification(TaskOverdue,
                        "⚠️ 任務逾期",
                        QString("任務「%1」已經逾期了！").arg(task.title));
                    
                    if (m_soundEnabled) {
                        playSound(TaskOverdue);
                    }
                    
                    m_notifiedTaskIds.insert(-task.id);
                    emit overdueTaskDetected(task.id, task.title);
                    
                    qDebug() << "任務逾期提醒:" << task.title;
                }
            }
        }
    }
}

void NotificationManager::loadSoundResources()
{
    // 預載音效資源（如果需要的話）
}
