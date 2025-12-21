// ========================================
// 番茄鐘計時器類實現 (pomodorotimer.cpp)
// 功能: 實現番茄鐘和碼錶的計時邏輯
// 特性: 支持兩種模式切換、工作統計、任務計時
// ========================================

#include "pomodorotimer.h"        // 番茄鐘計時器頭文件
#include "workstats.h"            // 工作統計模塊
#include "pomodoroconfig.h"       // 番茄鐘配置模塊
#include <QDebug>                 // 調試輸出

/**
 * 構造函數 - PomodoroTimer()
 * 參數: parent - 父對象指針
 * 功能: 初始化番茄鐘計時器
 *  1. 創建內部計時器（QTimer）
 *  2. 連接計時器的timeout信號到onTick槽函數
 *  3. 設置計時器間隔為1000毫秒（1秒）
 */
PomodoroTimer::PomodoroTimer(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))  // 創建内部計時器，以this為父對象（自動銷毀）
{
    // 連接計時器的timeout信號到本對象的onTick槽函數
    // 每當計時器發出timeout信號時，都會調用onTick()
    connect(m_timer, &QTimer::timeout, this, &PomodoroTimer::onTick);
    
    m_timer->setInterval(1000);  // 設置計時器間隔為1秒（1000毫秒）
}

void PomodoroTimer::loadSettingsFromConfig()
{
    if (!m_pomodoroConfig) {
        qWarning() << "PomodoroConfig 未設置";
        return;
    }
    
    m_workDuration = m_pomodoroConfig->getWorkDuration() * 60;
    m_shortBreakDuration = m_pomodoroConfig->getShortBreakDuration() * 60;
    m_longBreakDuration = m_pomodoroConfig->getLongBreakDuration() * 60;
    m_cyclesBeforeLongBreak = m_pomodoroConfig->getCyclesBeforeLongBreak();
    
    // 重置計時器
    m_currentPhase = Work;
    m_remainingSeconds = m_workDuration;
    m_completedCycles = 0;
    m_isRunning = false;
    m_timer->stop();
    
    emit tick(m_remainingSeconds);
    emit phaseChanged(m_currentPhase);
    
    qDebug() << "✓ 番茄鐘設置已加載到計時器"
             << "工作:" << m_workDuration / 60 << "分"
             << "短休:" << m_shortBreakDuration / 60 << "分"
             << "長休:" << m_longBreakDuration / 60 << "分";
}

void PomodoroTimer::setMode(Mode mode)
{
    if (m_mode != mode) {
        // 如果正在運行，先停止
        if (m_isRunning) {
            stop();
        }
        
        m_mode = mode;
        
        // 重設計時器狀態但不發送 phaseChanged 信號（避免誤觸發通知）
        m_timer->stop();
        m_isRunning = false;
        
        if (m_mode == PomodoroMode) {
            m_currentPhase = Work;
            m_remainingSeconds = m_workDuration;
            m_completedCycles = 0;
            // 不發送 phaseChanged 信號，因為這只是模式切換
            emit tick(m_remainingSeconds);
        } else {
            m_elapsedSeconds = 0;
            emit tick(0);
        }
        
        emit modeChanged(mode);
        
        qDebug() << "切換模式:" << (mode == PomodoroMode ? "番茄鐘" : "碼錶");
    }
}

void PomodoroTimer::start()
{
    if (!m_isRunning) {
        m_isRunning = true;
        m_sessionStartSeconds = (m_mode == PomodoroMode) ? m_remainingSeconds : m_elapsedSeconds;
        m_timer->start();
        qDebug() << "計時開始";
    }
}

void PomodoroTimer::pause()
{
    if (m_isRunning) {
        m_isRunning = false;
        m_timer->stop();
        
        // 記錄這段工作時間
        if (m_mode == StopwatchMode || (m_mode == PomodoroMode && m_currentPhase == Work)) {
            recordWorkSession();
        }
        
        qDebug() << "計時暫停";
    }
}

void PomodoroTimer::reset()
{
    m_timer->stop();
    m_isRunning = false;
    
    if (m_mode == PomodoroMode) {
        m_currentPhase = Work;
        m_remainingSeconds = m_workDuration;
        m_completedCycles = 0;
        emit phaseChanged(m_currentPhase);
    } else {
        m_elapsedSeconds = 0;
    }
    
    emit tick(m_mode == PomodoroMode ? m_remainingSeconds : m_elapsedSeconds);
    qDebug() << "計時重設";
}

void PomodoroTimer::resetQuiet()
{
    // 重設但不發送 phaseChanged 信號（用於調整設定時避免觸發通知）
    m_timer->stop();
    m_isRunning = false;
    
    if (m_mode == PomodoroMode) {
        m_currentPhase = Work;
        m_remainingSeconds = m_workDuration;
        m_completedCycles = 0;
        // 不發送 phaseChanged 信號
    } else {
        m_elapsedSeconds = 0;
    }
    
    emit tick(m_mode == PomodoroMode ? m_remainingSeconds : m_elapsedSeconds);
    qDebug() << "計時重設（無信號）";
}

void PomodoroTimer::stop()
{
    if (m_isRunning) {
        pause();
    }
    
    // 停止任務計時
    if (m_currentTaskId != -1) {
        stopTaskTimer();
    }
    
    qDebug() << "計時停止";
}

void PomodoroTimer::setWorkDuration(int minutes)
{
    m_workDuration = minutes * 60;
    if (m_currentPhase == Work && !m_isRunning) {
        m_remainingSeconds = m_workDuration;
        emit tick(m_remainingSeconds);
    }
}

void PomodoroTimer::setShortBreakDuration(int minutes)
{
    m_shortBreakDuration = minutes * 60;
}

void PomodoroTimer::setLongBreakDuration(int minutes)
{
    m_longBreakDuration = minutes * 60;
}

void PomodoroTimer::setCyclesBeforeLongBreak(int cycles)
{
    m_cyclesBeforeLongBreak = cycles;
}

int PomodoroTimer::remainingSeconds() const
{
    return m_remainingSeconds;
}

int PomodoroTimer::elapsedSeconds() const
{
    return m_elapsedSeconds;
}

PomodoroTimer::Phase PomodoroTimer::currentPhase() const
{
    return m_currentPhase;
}

bool PomodoroTimer::isRunning() const
{
    return m_isRunning;
}

void PomodoroTimer::startTaskTimer(int taskId)
{
    // 如果有其他任務在計時，先停止
    if (m_currentTaskId != -1 && m_currentTaskId != taskId) {
        stopTaskTimer();
    }
    
    m_currentTaskId = taskId;
    
    // 如果這個任務沒有記錄，初始化為0
    if (!m_taskElapsedSeconds.contains(taskId)) {
        m_taskElapsedSeconds[taskId] = 0;
    }
    
    qDebug() << "開始任務計時，任務ID:" << taskId;
}

void PomodoroTimer::stopTaskTimer()
{
    if (m_currentTaskId != -1) {
        qDebug() << "停止任務計時，任務ID:" << m_currentTaskId 
                 << "，累計時間:" << formatDuration(m_taskElapsedSeconds[m_currentTaskId]);
    }
    m_currentTaskId = -1;
}

int PomodoroTimer::getTaskElapsedSeconds(int taskId) const
{
    return m_taskElapsedSeconds.value(taskId, 0);
}

QString PomodoroTimer::formatTime(int totalSeconds)
{
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

QString PomodoroTimer::formatDuration(int totalSeconds)
{
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;
    
    if (hours > 0) {
        return QString("%1:%2:%3")
            .arg(hours)
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
    } else {
        return QString("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
    }
}

void PomodoroTimer::onTick()
{
    if (m_mode == PomodoroMode) {
        // 番茄鐘模式：倒數
        if (m_remainingSeconds > 0) {
            m_remainingSeconds--;
            
            // 如果是工作階段，累加工作時間
            if (m_currentPhase == Work) {
                m_todayWorkSeconds++;
                m_totalWorkSeconds++;
                
                // 如果有任務在計時
                if (m_currentTaskId != -1) {
                    m_taskElapsedSeconds[m_currentTaskId]++;
                }
            }
            
            emit tick(m_remainingSeconds);
        } else {
            // 時間到，切換階段
            switchToNextPhase();
        }
    } else {
        // 碼錶模式：正數
        m_elapsedSeconds++;
        m_todayWorkSeconds++;
        m_totalWorkSeconds++;
        
        // 如果有任務在計時
        if (m_currentTaskId != -1) {
            m_taskElapsedSeconds[m_currentTaskId]++;
        }
        
        emit tick(m_elapsedSeconds);
    }
}

void PomodoroTimer::switchToNextPhase()
{
    if (m_currentPhase == Work) {
        // 工作結束
        m_completedCycles++;
        m_todayPomodoroCount++;
        emit pomodoroCompleted();
        
        // 通知工作統計系統
        if (m_workStats) {
            m_workStats->completePomodoroSession();
        }
        
        qDebug() << "完成一個番茄鐘！今日完成:" << m_todayPomodoroCount;
        
        // 決定是短休息還是長休息
        if (m_completedCycles >= m_cyclesBeforeLongBreak) {
            m_currentPhase = LongBreak;
            m_remainingSeconds = m_longBreakDuration;
            m_completedCycles = 0;
            qDebug() << "進入長休息";
        } else {
            m_currentPhase = ShortBreak;
            m_remainingSeconds = m_shortBreakDuration;
            qDebug() << "進入短休息";
        }
    } else {
        // 休息結束，回到工作
        m_currentPhase = Work;
        m_remainingSeconds = m_workDuration;
        qDebug() << "休息結束，開始工作";
    }
    
    emit phaseChanged(m_currentPhase);
    emit tick(m_remainingSeconds);
}

void PomodoroTimer::recordWorkSession()
{
    int worked = 0;
    
    if (m_mode == PomodoroMode) {
        worked = m_sessionStartSeconds - m_remainingSeconds;
    } else {
        worked = m_elapsedSeconds - m_sessionStartSeconds;
    }
    
    if (worked > 0) {
        emit workSessionRecorded(worked);
        
        // 通知工作統計系統
        if (m_workStats) {
            m_workStats->addWorkSeconds(worked);
        }
        
        qDebug() << "記錄工作時段:" << formatDuration(worked);
    }
}
