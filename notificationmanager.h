#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QList>
#include <QSet>
#include "task.h"

class NotificationManager : public QObject
{
    Q_OBJECT

public:
    explicit NotificationManager(QObject *parent = nullptr);
    ~NotificationManager();

    // 設定系統匣圖示（用於顯示通知）
    void setTrayIcon(QSystemTrayIcon *trayIcon);

    // 開始檢查任務提醒
    void startReminderCheck();
    void stopReminderCheck();

    // 更新任務列表（用於檢查提醒）
    void updateTasks(const QList<Task> &tasks);

    // 通知類型
    enum NotificationType {
        TaskReminder,       // 任務提醒
        TaskOverdue,        // 任務逾期
        PomodoroComplete,   // 番茄鐘完成
        BreakComplete       // 休息結束
    };
    Q_ENUM(NotificationType)

    // 顯示通知
    void showNotification(NotificationType type, const QString &title, const QString &message);

    // 播放音效
    void playSound(NotificationType type);

    // 音效設定
    void setSoundEnabled(bool enabled) { m_soundEnabled = enabled; }
    bool isSoundEnabled() const { return m_soundEnabled; }

signals:
    void reminderTriggered(int taskId, const QString &taskTitle);
    void overdueTaskDetected(int taskId, const QString &taskTitle);

private slots:
    void checkReminders();

private:
    QSystemTrayIcon *m_trayIcon = nullptr;
    QTimer *m_reminderTimer;
    QList<Task> m_tasks;
    QSet<int> m_notifiedTaskIds;  // 已經提醒過的任務ID
    
    // 音效
    QMediaPlayer *m_mediaPlayer;
    QAudioOutput *m_audioOutput;
    bool m_soundEnabled = true;

    void loadSoundResources();
};

#endif // NOTIFICATIONMANAGER_H
