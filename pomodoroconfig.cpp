// ========================================
// 番茄鐘配置類實現 (pomodoroconfig.cpp)
// 功能: 讀取、保存、管理番茄工作法的時間配置
// 存儲方式: JSON格式，保存在data/pomodoroconfig.json
// ========================================

#include "pomodoroconfig.h"       // 番茄鐘配置頭文件
#include <QCoreApplication>       // 應用程序路徑
#include <QDir>                   // 目錄操作
#include <QFile>                  // 文件操作
#include <QJsonDocument>          // JSON文檔
#include <QJsonObject>            // JSON對象
#include <QDebug>                 // 調試輸出

/**
 * 構造函數 - PomodoroConfig()
 * 功能: 初始化番茄鐘配置對象，自動從配置文件加載設置
 */
PomodoroConfig::PomodoroConfig()
{
    loadSettings();  // 從配置文件加載設置
}

void PomodoroConfig::loadSettings()
{
    QString filePath = getSettingsFilePath();
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "未找到番茄鐘設置文件，使用預設值" << filePath;
        resetToDefaults();
        return;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        qWarning() << "設置文件格式錯誤";
        resetToDefaults();
        return;
    }
    
    QJsonObject obj = doc.object();
    m_workDuration = obj.value("workDuration").toInt(DEFAULT_WORK_DURATION);
    m_shortBreakDuration = obj.value("shortBreakDuration").toInt(DEFAULT_SHORT_BREAK);
    m_longBreakDuration = obj.value("longBreakDuration").toInt(DEFAULT_LONG_BREAK);
    m_cyclesBeforeLongBreak = obj.value("cyclesBeforeLongBreak").toInt(DEFAULT_CYCLES_BEFORE_LONG_BREAK);
    m_autoStartNext = obj.value("autoStartNext").toBool(false);
    
    qDebug() << "✓ 番茄鐘設置已加載"
             << "工作:" << m_workDuration << "分"
             << "短休:" << m_shortBreakDuration << "分"
             << "長休:" << m_longBreakDuration << "分"
             << "長休週期:" << m_cyclesBeforeLongBreak << "個";
}

void PomodoroConfig::saveSettings()
{
    QString filePath = getSettingsFilePath();
    
    // 確保目錄存在
    QDir dir(QCoreApplication::applicationDirPath() + "/data");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QJsonObject obj;
    obj.insert("workDuration", m_workDuration);
    obj.insert("shortBreakDuration", m_shortBreakDuration);
    obj.insert("longBreakDuration", m_longBreakDuration);
    obj.insert("cyclesBeforeLongBreak", m_cyclesBeforeLongBreak);
    obj.insert("autoStartNext", m_autoStartNext);
    
    QJsonDocument doc(obj);
    QFile file(filePath);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "無法保存番茄鐘設置:" << filePath;
        return;
    }
    
    file.write(doc.toJson());
    file.close();
    
    qDebug() << "✓ 番茄鐘設置已保存到:" << filePath;
}

void PomodoroConfig::setWorkDuration(int minutes)
{
    if (minutes > 0 && minutes <= 120) {  // 最多120分鐘
        m_workDuration = minutes;
        saveSettings();
        qDebug() << "工作時間已設置為:" << minutes << "分";
    } else {
        qWarning() << "無效的工作時間:" << minutes;
    }
}

void PomodoroConfig::setShortBreakDuration(int minutes)
{
    if (minutes > 0 && minutes <= 60) {  // 最多60分鐘
        m_shortBreakDuration = minutes;
        saveSettings();
        qDebug() << "短休息時間已設置為:" << minutes << "分";
    } else {
        qWarning() << "無效的短休息時間:" << minutes;
    }
}

void PomodoroConfig::setLongBreakDuration(int minutes)
{
    if (minutes > 0 && minutes <= 120) {  // 最多120分鐘
        m_longBreakDuration = minutes;
        saveSettings();
        qDebug() << "長休息時間已設置為:" << minutes << "分";
    } else {
        qWarning() << "無效的長休息時間:" << minutes;
    }
}

void PomodoroConfig::setCyclesBeforeLongBreak(int cycles)
{
    if (cycles > 0 && cycles <= 10) {  // 最多10個
        m_cyclesBeforeLongBreak = cycles;
        saveSettings();
        qDebug() << "長休息週期已設置為:" << cycles << "個";
    } else {
        qWarning() << "無效的長休息週期:" << cycles;
    }
}

void PomodoroConfig::setAutoStartNext(bool enabled)
{
    m_autoStartNext = enabled;
    saveSettings();
    qDebug() << "自動開始下一個番茄已設置為:" << (enabled ? "啟用" : "禁用");
}

void PomodoroConfig::resetToDefaults()
{
    m_workDuration = DEFAULT_WORK_DURATION;
    m_shortBreakDuration = DEFAULT_SHORT_BREAK;
    m_longBreakDuration = DEFAULT_LONG_BREAK;
    m_cyclesBeforeLongBreak = DEFAULT_CYCLES_BEFORE_LONG_BREAK;
    m_autoStartNext = false;
    
    qDebug() << "番茄鐘設置已重置為預設值";
}

QString PomodoroConfig::getSettingsFilePath() const
{
    return QCoreApplication::applicationDirPath() + "/data/pomodoroconfig.json";
}
