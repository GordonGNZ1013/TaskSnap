#include "workstats.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDate>
#include <QDebug>

WorkStats::WorkStats()
    : m_todayWorkSeconds(0)
    , m_totalWorkSeconds(0)
    , m_todayPomodoroCount(0)
    , m_totalPomodoroCount(0)
{
    loadStats();
    checkAndResetIfNewDay();
}

void WorkStats::loadStats()
{
    QString filePath = getStatsFilePath();
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "未找到統計文件，使用默認值" << filePath;
        m_todayWorkSeconds = 0;
        m_totalWorkSeconds = 0;
        m_todayPomodoroCount = 0;
        m_totalPomodoroCount = 0;
        m_lastSavedDate = QDate::currentDate();
        return;
    }
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        qWarning() << "統計文件格式錯誤";
        return;
    }
    
    QJsonObject obj = doc.object();
    m_todayWorkSeconds = obj.value("todayWorkSeconds").toInt(0);
    m_totalWorkSeconds = obj.value("totalWorkSeconds").toInt(0);
    m_todayPomodoroCount = obj.value("todayPomodoroCount").toInt(0);
    m_totalPomodoroCount = obj.value("totalPomodoroCount").toInt(0);
    
    QString dateStr = obj.value("lastSavedDate").toString();
    m_lastSavedDate = QDate::fromString(dateStr, Qt::ISODate);
    if (!m_lastSavedDate.isValid()) {
        m_lastSavedDate = QDate::currentDate();
    }
    
    qDebug() << "✓ 統計數據已加載"
             << "今日秒數:" << m_todayWorkSeconds
             << "累計秒數:" << m_totalWorkSeconds
             << "今日番茄:" << m_todayPomodoroCount
             << "累計番茄:" << m_totalPomodoroCount;
}

void WorkStats::saveStats()
{
    QString filePath = getStatsFilePath();
    
    // 確保目錄存在
    QDir dir(QCoreApplication::applicationDirPath() + "/data");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    QJsonObject obj;
    obj.insert("todayWorkSeconds", m_todayWorkSeconds);
    obj.insert("totalWorkSeconds", m_totalWorkSeconds);
    obj.insert("todayPomodoroCount", m_todayPomodoroCount);
    obj.insert("totalPomodoroCount", m_totalPomodoroCount);
    obj.insert("lastSavedDate", QDate::currentDate().toString(Qt::ISODate));
    
    QJsonDocument doc(obj);
    QFile file(filePath);
    
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "無法保存統計文件:" << filePath;
        return;
    }
    
    file.write(doc.toJson());
    file.close();
    
    qDebug() << "✓ 統計數據已保存到:" << filePath;
}

void WorkStats::addWorkSeconds(int seconds)
{
    checkAndResetIfNewDay();
    
    m_todayWorkSeconds += seconds;
    m_totalWorkSeconds += seconds;
    
    qDebug() << "工作時間已更新：今日" << m_todayWorkSeconds
             << "秒, 累計" << m_totalWorkSeconds << "秒";
    
    saveStats();
}

void WorkStats::completePomodoroSession()
{
    checkAndResetIfNewDay();
    
    m_todayPomodoroCount++;
    m_totalPomodoroCount++;
    
    qDebug() << "✓ 番茄鐘已完成：今日" << m_todayPomodoroCount
             << "個, 累計" << m_totalPomodoroCount << "個";
    
    saveStats();
}

int WorkStats::getTodayWorkSeconds() const
{
    return m_todayWorkSeconds;
}

int WorkStats::getTotalWorkSeconds() const
{
    return m_totalWorkSeconds;
}

int WorkStats::getTodayPomodoroCount() const
{
    return m_todayPomodoroCount;
}

int WorkStats::getTotalPomodoroCount() const
{
    return m_totalPomodoroCount;
}

void WorkStats::resetDailyStats()
{
    m_todayWorkSeconds = 0;
    m_todayPomodoroCount = 0;
    m_lastSavedDate = QDate::currentDate();
    
    qDebug() << "========== 今日數據已重置 ==========";
    saveStats();
}

QDate WorkStats::getLastSavedDate() const
{
    return m_lastSavedDate;
}

void WorkStats::checkAndResetIfNewDay()
{
    QDate today = QDate::currentDate();
    
    if (m_lastSavedDate != today) {
        qDebug() << "日期已改變，重置今日數據";
        resetDailyStats();
    }
}

QString WorkStats::getStatsFilePath() const
{
    return QCoreApplication::applicationDirPath() + "/data/workstats.json";
}
