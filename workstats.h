#ifndef WORKSTATS_H
#define WORKSTATS_H

#include <QString>
#include <QDate>

class WorkStats
{
public:
    WorkStats();
    
    // 從磁盤加載統計數據
    void loadStats();
    
    // 保存統計數據到磁盤
    void saveStats();
    
    // 添加工作時間（秒數）
    void addWorkSeconds(int seconds);
    
    // 完成一個番茄鐘
    void completePomodoroSession();
    
    // 獲取今日工作秒數
    int getTodayWorkSeconds() const;
    
    // 獲取累計工作秒數
    int getTotalWorkSeconds() const;
    
    // 獲取今日完成番茄個數
    int getTodayPomodoroCount() const;
    
    // 獲取累計完成番茄個數
    int getTotalPomodoroCount() const;
    
    // 重置今日數據（時間改變時）
    void resetDailyStats();
    
    // 獲取上次保存的日期
    QDate getLastSavedDate() const;
    
private:
    // 檢查日期是否改變，如果改變則重置今日數據
    void checkAndResetIfNewDay();
    
    // 獲取統計文件路徑
    QString getStatsFilePath() const;
    
    // 今日工作秒數
    int m_todayWorkSeconds;
    
    // 累計工作秒數
    int m_totalWorkSeconds;
    
    // 今日完成番茄個數
    int m_todayPomodoroCount;
    
    // 累計完成番茄個數
    int m_totalPomodoroCount;
    
    // 上次保存的日期
    QDate m_lastSavedDate;
};

#endif // WORKSTATS_H
