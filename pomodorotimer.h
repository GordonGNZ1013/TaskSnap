#ifndef POMODOROTIMER_H
#define POMODOROTIMER_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QMap>

class WorkStats;  // 前向聲明
class PomodoroConfig;  // 前向聲明

class PomodoroTimer : public QObject
{
    Q_OBJECT

public:
    // 計時器模式
    enum Mode {
        PomodoroMode,   // 番茄鐘模式
        StopwatchMode   // 碼錶模式
    };
    Q_ENUM(Mode)

    // 番茄鐘階段
    enum Phase {
        Work,       // 工作
        ShortBreak, // 短休息
        LongBreak   // 長休息
    };
    Q_ENUM(Phase)

    explicit PomodoroTimer(QObject *parent = nullptr);
    
    // 設置工作統計管理器
    void setWorkStats(WorkStats *workStats) { m_workStats = workStats; }
    
    // 設置番茄鐘設置管理器
    void setPomodoroConfig(PomodoroConfig *config) { m_pomodoroConfig = config; }
    
    // 從配置文件加載設置
    void loadSettingsFromConfig();

    // 模式切換
    void setMode(Mode mode);
    Mode currentMode() const { return m_mode; }

    // 控制方法
    void start();
    void pause();
    void reset();
    void resetQuiet();  // 重設但不發送 phaseChanged 信號（用於調整設定）
    void stop();  // 完全停止並記錄

    // 設定時間（分鐘）
    void setWorkDuration(int minutes);
    void setShortBreakDuration(int minutes);
    void setLongBreakDuration(int minutes);
    void setCyclesBeforeLongBreak(int cycles);

    // 取得狀態
    int remainingSeconds() const;
    int elapsedSeconds() const;  // 碼錶模式用
    Phase currentPhase() const;
    bool isRunning() const;
    
    // 取得設定值（分鐘）
    int getWorkDuration() const { return m_workDuration / 60; }
    int getShortBreakDuration() const { return m_shortBreakDuration / 60; }
    int getLongBreakDuration() const { return m_longBreakDuration / 60; }
    int getCyclesBeforeLongBreak() const { return m_cyclesBeforeLongBreak; }

    // 統計資料
    int todayWorkSeconds() const { return m_todayWorkSeconds; }
    int todayPomodoroCount() const { return m_todayPomodoroCount; }
    int totalWorkSeconds() const { return m_totalWorkSeconds; }

    // 任務計時
    void startTaskTimer(int taskId);
    void stopTaskTimer();
    int getTaskElapsedSeconds(int taskId) const;
    int getCurrentTaskId() const { return m_currentTaskId; }

    // 格式化時間
    static QString formatTime(int totalSeconds);
    static QString formatDuration(int totalSeconds);  // 顯示時:分:秒

signals:
    void tick(int seconds);                    // 每秒更新
    void phaseChanged(Phase newPhase);         // 階段切換
    void pomodoroCompleted();                  // 一個番茄鐘完成
    void modeChanged(Mode newMode);            // 模式切換
    void workSessionRecorded(int seconds);     // 工作時段記錄

private slots:
    void onTick();

private:
    QTimer *m_timer;
    Mode m_mode = PomodoroMode;
    Phase m_currentPhase = Work;
    
    // 番茄鐘設定
    int m_remainingSeconds = 25 * 60;
    int m_workDuration = 25 * 60;          // 25 分鐘
    int m_shortBreakDuration = 5 * 60;     // 5 分鐘
    int m_longBreakDuration = 15 * 60;     // 15 分鐘
    int m_cyclesBeforeLongBreak = 4;
    int m_completedCycles = 0;
    
    // 碼錶
    int m_elapsedSeconds = 0;
    
    // 狀態
    bool m_isRunning = false;
    
    // 統計
    int m_todayWorkSeconds = 0;      // 今日工作秒數
    int m_todayPomodoroCount = 0;    // 今日完成的番茄鐘數
    int m_totalWorkSeconds = 0;      // 總工作秒數
    int m_sessionStartSeconds = 0;   // 本次工作開始時的秒數
    
    // 任務計時
    int m_currentTaskId = -1;
    QMap<int, int> m_taskElapsedSeconds;  // 任務ID -> 累計秒數
    
    // 工作統計
    WorkStats *m_workStats = nullptr;
    
    // 番茄鐘設置
    PomodoroConfig *m_pomodoroConfig = nullptr;
    
    void switchToNextPhase();
    void recordWorkSession();
};

#endif // POMODOROTIMER_H
