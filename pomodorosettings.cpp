// ========================================
// 番茄鐘設置類實現文件 (pomodorosettings.cpp)
// 功能: 管理番茄工作法的各項參數設置，包括工作時間、休息時間等
// ========================================

#include "pomodorosettings.h"           // 包含番茄鐘設置的頭文件
#include <QCoreApplication>             // Qt核心應用程序支持
#include <QDir>                         // 目錄操作支持
#include <QFile>                        // 文件讀寫支持
#include <QJsonDocument>                // JSON文檔解析支持
#include <QJsonObject>                  // JSON對象支持
#include <QDebug>                       // 調試輸出支持

/**
 * 構造函數 - 初始化PomodoroSettings對象
 * 功能: 創建番茄鐘設置對象並從配置文件加載設置
 */
PomodoroSettings::PomodoroSettings()
{
    loadSettings();  // 從配置文件中加載已保存的設置
}

/**
 * 加載設置函數 - loadSettings()
 * 功能: 從JSON配置文件中讀取番茄鐘的各項設置參數
 * 流程:
 *  1. 獲取配置文件路徑
 *  2. 嘗試打開文件，如果失敗則使用預設值
 *  3. 讀取JSON數據並解析
 *  4. 提取各項設置參數並存儲到成員變量
 */
void PomodoroSettings::loadSettings()
{
    QString filePath = getSettingsFilePath();  // 獲取配置文件的完整路徑
    QFile file(filePath);
    
    // 嘗試以只讀文本模式打開文件
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "未找到番茄鐘設置文件，使用預設值" << filePath;
        resetToDefaults();  // 如果文件不存在，使用預設設置
        return;
    }
    
    QByteArray data = file.readAll();  // 讀取整個文件內容為字節數組
    file.close();                      // 關閉文件
    
    // 將字節數組轉換為JSON文檔對象
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    // 驗證JSON文檔是否為有效的對象格式
    if (!doc.isObject()) {
        qWarning() << "設置文件格式錯誤";
        resetToDefaults();  // 格式錯誤則使用預設設置
        return;
    }
    
    QJsonObject obj = doc.object();  // 獲取JSON根對象
    
    // 從JSON中逐一提取各項設置，若某項不存在則使用預設值
    m_workDuration = obj.value("workDuration").toInt(DEFAULT_WORK_DURATION);
    m_shortBreakDuration = obj.value("shortBreakDuration").toInt(DEFAULT_SHORT_BREAK);
    m_longBreakDuration = obj.value("longBreakDuration").toInt(DEFAULT_LONG_BREAK);
    m_cyclesBeforeLongBreak = obj.value("cyclesBeforeLongBreak").toInt(DEFAULT_CYCLES_BEFORE_LONG_BREAK);
    m_autoStartNext = obj.value("autoStartNext").toBool(false);
    
    // 輸出加載成功的調試信息
    qDebug() << "✓ 番茄鐘設置已加載"
             << "工作:" << m_workDuration << "分"
             << "短休:" << m_shortBreakDuration << "分"
             << "長休:" << m_longBreakDuration << "分"
             << "長休週期:" << m_cyclesBeforeLongBreak << "個";
}

/**
 * 保存設置函數 - saveSettings()
 * 功能: 將當前的番茄鐘設置保存到JSON配置文件中
 * 流程:
 *  1. 獲取配置文件路徑
 *  2. 確保存儲目錄存在（不存在則創建）
 *  3. 創建JSON對象並填入各項設置值
 *  4. 將JSON對象轉換為JSON格式字符串並寫入文件
 */
void PomodoroSettings::saveSettings()
{
    QString filePath = getSettingsFilePath();  // 獲取配置文件路徑
    
    // 確保目錄存在 - 根據應用程序路徑創建data目錄
    QDir dir(QCoreApplication::applicationDirPath() + "/data");
    if (!dir.exists()) {
        dir.mkpath(".");  // 若目錄不存在，則創建所有必需的父目錄
    }
    
    // 創建一個新的JSON對象用於存儲設置
    QJsonObject obj;
    obj.insert("workDuration", m_workDuration);           // 工作時長
    obj.insert("shortBreakDuration", m_shortBreakDuration);  // 短休時長
    obj.insert("longBreakDuration", m_longBreakDuration);    // 長休時長
    obj.insert("cyclesBeforeLongBreak", m_cyclesBeforeLongBreak);  // 長休週期
    obj.insert("autoStartNext", m_autoStartNext);         // 自動開始下一個
    
    // 將JSON對象包裝成JSON文檔
    QJsonDocument doc(obj);
    QFile file(filePath);
    
    // 以只寫文本模式打開文件（若文件存在則覆蓋）
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "無法保存番茄鐘設置:" << filePath;
        return;
    }
    
    file.write(doc.toJson());  // 將JSON文檔轉換為JSON格式字符串並寫入文件
    file.close();              // 關閉文件
    
    // 輸出保存成功的調試信息
    qDebug() << "✓ 番茄鐘設置已保存到:" << filePath;
}

/**
 * 設置工作時間 - setWorkDuration()
 * 參數: minutes - 工作時間（分鐘）
 * 功能: 設置單個番茄工作週期的時長，有效範圍1-120分鐘
 * 驗證: 檢查輸入值是否在有效範圍內，若有效則保存並更新配置文件
 */
void PomodoroSettings::setWorkDuration(int minutes)
{
    // 驗證輸入值：必須大於0且不超過120分鐘
    if (minutes > 0 && minutes <= 120) {  // 最多120分鐘
        m_workDuration = minutes;           // 更新成員變量
        saveSettings();                     // 保存到配置文件
        qDebug() << "工作時間已設置為:" << minutes << "分";
    } else {
        // 若輸入值無效，輸出警告信息
        qWarning() << "無效的工作時間:" << minutes;
    }
}

/**
 * 設置短休時間 - setShortBreakDuration()
 * 參數: minutes - 短休時間（分鐘）
 * 功能: 設置工作間隔短休息的時長，有效範圍1-60分鐘
 * 應用: 通常在完成一個番茄後使用，給用戶短暫的休息
 */
void PomodoroSettings::setShortBreakDuration(int minutes)
{
    // 驗證輸入值：必須大於0且不超過60分鐘
    if (minutes > 0 && minutes <= 60) {  // 最多60分鐘
        m_shortBreakDuration = minutes;     // 更新成員變量
        saveSettings();                     // 保存到配置文件
        qDebug() << "短休息時間已設置為:" << minutes << "分";
    } else {
        // 若輸入值無效，輸出警告信息
        qWarning() << "無效的短休息時間:" << minutes;
    }
}

/**
 * 設置長休時間 - setLongBreakDuration()
 * 參數: minutes - 長休時間（分鐘）
 * 功能: 設置完成多個番茄週期後的長休時長，有效範圍1-120分鐘
 * 應用: 在完成指定數量的工作週期後，給用戶更長的休息時間
 */
void PomodoroSettings::setLongBreakDuration(int minutes)
{
    // 驗證輸入值：必須大於0且不超過120分鐘
    if (minutes > 0 && minutes <= 120) {  // 最多120分鐘
        m_longBreakDuration = minutes;      // 更新成員變量
        saveSettings();                     // 保存到配置文件
        qDebug() << "長休息時間已設置為:" << minutes << "分";
    } else {
        // 若輸入值無效，輸出警告信息
        qWarning() << "無效的長休息時間:" << minutes;
    }
}

/**
 * 設置長休週期 - setCyclesBeforeLongBreak()
 * 參數: cycles - 觸發長休之前的工作週期數
 * 功能: 設置在進行長休息前要完成多少個工作週期，有效範圍1-10個
 * 例如: 若設為4，則每完成4個番茄後進行一次長休息
 */
void PomodoroSettings::setCyclesBeforeLongBreak(int cycles)
{
    // 驗證輸入值：必須大於0且不超過10個
    if (cycles > 0 && cycles <= 10) {  // 最多10個
        m_cyclesBeforeLongBreak = cycles;   // 更新成員變量
        saveSettings();                     // 保存到配置文件
        qDebug() << "長休息週期已設置為:" << cycles << "個";
    } else {
        // 若輸入值無效，輸出警告信息
        qWarning() << "無效的長休息週期:" << cycles;
    }
}

/**
 * 設置自動開始下一個番茄 - setAutoStartNext()
 * 參數: enabled - true表示啟用自動開始，false表示禁用
 * 功能: 控制是否在一個工作/休息週期結束後自動開始下一個週期
 * 用途: 若啟用，用戶無需手動點擊開始按鈕，系統會自動繼續
 */
void PomodoroSettings::setAutoStartNext(bool enabled)
{
    m_autoStartNext = enabled;              // 更新成員變量
    saveSettings();                         // 保存到配置文件
    // 根據狀態輸出相應的調試信息
    qDebug() << "自動開始下一個番茄已設置為:" << (enabled ? "啟用" : "禁用");
}

/**
 * 重置為預設值 - resetToDefaults()
 * 功能: 將所有番茄鐘設置恢復為預設值
 * 預設值來自: 头文件中定义的DEFAULT_*常量
 * 應用場景: 用戶選擇重置設置或配置文件損壞時
 */
void PomodoroSettings::resetToDefaults()
{
    // 將所有設置成員變量重置為預設常量值
    m_workDuration = DEFAULT_WORK_DURATION;
    m_shortBreakDuration = DEFAULT_SHORT_BREAK;
    m_longBreakDuration = DEFAULT_LONG_BREAK;
    m_cyclesBeforeLongBreak = DEFAULT_CYCLES_BEFORE_LONG_BREAK;
    m_autoStartNext = false;  // 預設禁用自動開始
    
    qDebug() << "番茄鐘設置已重置為預設值";
}

/**
 * 獲取設置文件路徑 - getSettingsFilePath()
 * 返回值: QString - 完整的配置文件路徑
 * 功能: 構建並返回番茄鐘配置文件的完整路徑
 * 路徑結構: [應用程序目錄]/data/pomodorosettings.json
 * 說明: 應用程序每次啟動時都會在此路徑查找和保存配置
 */
QString PomodoroSettings::getSettingsFilePath() const
{
    // 構建路徑：應用程序所在目錄 + data文件夾 + pomodorosettings.json文件名
    return QCoreApplication::applicationDirPath() + "/data/pomodorosettings.json";
}
