#ifndef POMODOROSETTINGS_H
#define POMODOROSETTINGS_H

#include <QString>

class PomodoroSettings
{
public:
    PomodoroSettings();
    
    // 從磁盤加載設置
    void loadSettings();
    
    // 保存設置到磁盤
    void saveSettings();
    
    // 設置工作時間（分鐘）
    void setWorkDuration(int minutes);
    
    // 設置短休息時間（分鐘）
    void setShortBreakDuration(int minutes);
    
    // 設置長休息時間（分鐘）
    void setLongBreakDuration(int minutes);
    
    // 設置長休息前的番茄個數
    void setCyclesBeforeLongBreak(int cycles);
    
    // 設置是否自動開始下一個番茄
    void setAutoStartNext(bool enabled);
    
    // 獲取工作時間（分鐘）
    int getWorkDuration() const { return m_workDuration; }
    
    // 獲取短休息時間（分鐘）
    int getShortBreakDuration() const { return m_shortBreakDuration; }
    
    // 獲取長休息時間（分鐘）
    int getLongBreakDuration() const { return m_longBreakDuration; }
    
    // 獲取長休息前的番茄個數
    int getCyclesBeforeLongBreak() const { return m_cyclesBeforeLongBreak; }
    
    // 獲取是否自動開始下一個番茄
    bool isAutoStartNext() const { return m_autoStartNext; }
    
    // 重置為預設值
    void resetToDefaults();
    
    // 預設設置常數
    static constexpr int DEFAULT_WORK_DURATION = 25;           // 分鐘
    static constexpr int DEFAULT_SHORT_BREAK = 5;              // 分鐘
    static constexpr int DEFAULT_LONG_BREAK = 15;              // 分鐘
    static constexpr int DEFAULT_CYCLES_BEFORE_LONG_BREAK = 4; // 個

private:
    // 獲取設置文件路徑
    QString getSettingsFilePath() const;
    
    // 工作時間（分鐘）
    int m_workDuration = DEFAULT_WORK_DURATION;
    
    // 短休息時間（分鐘）
    int m_shortBreakDuration = DEFAULT_SHORT_BREAK;
    
    // 長休息時間（分鐘）
    int m_longBreakDuration = DEFAULT_LONG_BREAK;
    
    // 長休息前的番茄個數
    int m_cyclesBeforeLongBreak = DEFAULT_CYCLES_BEFORE_LONG_BREAK;
    
    // 是否自動開始下一個番茄
    bool m_autoStartNext = false;
};

#endif // POMODOROSETTINGS_H
