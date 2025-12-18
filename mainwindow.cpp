#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskdialog.h"
#include "pomodorosettingsdialog.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include <QCloseEvent>
#include <QApplication>
#include <QPainter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QMimeDatabase>
#include <QFileInfo>
#include <QUuid>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_database(new Database(this))
    , m_pomodoroTimer(new PomodoroTimer(this))
    , m_notificationManager(new NotificationManager(this))
    , m_trayIcon(nullptr)
    , m_trayMenu(nullptr)
{
    ui->setupUi(this);

    // 設定全局字體大小（使所有文字和圖示更大更清晰）
    QFont globalFont = this->font();
    globalFont.setPointSize(13);  // 全局字體大小增加到13pt
    this->setFont(globalFont);

    // 單獨調整關鍵組件的字體 - 左邊面板加大
    if (ui->leftPanel) {
        QFont leftFont = globalFont;
        leftFont.setPointSize(16);  // 左邊面板字體加大到16pt
        ui->leftPanel->setFont(leftFont);
    }

    // 調整左邊各個按鈕和標籤的字體 - 16pt
    QFont buttonFont = globalFont;
    buttonFont.setPointSize(16);
    if (ui->btnAllTasks) ui->btnAllTasks->setFont(buttonFont);
    if (ui->btnToday) ui->btnToday->setFont(buttonFont);
    if (ui->btnOverdue) ui->btnOverdue->setFont(buttonFont);
    if (ui->btnCompleted) ui->btnCompleted->setFont(buttonFont);

    // 調整左邊logo標籤
    if (ui->logoLabel) {
        QFont logoFont = buttonFont;
        logoFont.setPointSize(18);  // Logo更大
        ui->logoLabel->setFont(logoFont);
    }

    // 調整番茄鐘區域字體 - 16pt
    if (ui->pomodoroTitle) ui->pomodoroTitle->setFont(buttonFont);
    if (ui->btnPomodoroMode) ui->btnPomodoroMode->setFont(buttonFont);
    if (ui->btnStopwatchMode) ui->btnStopwatchMode->setFont(buttonFont);
    if (ui->btnPomodoroStart) ui->btnPomodoroStart->setFont(buttonFont);
    if (ui->btnPomodoroPause) ui->btnPomodoroPause->setFont(buttonFont);
    if (ui->btnPomodoroReset) ui->btnPomodoroReset->setFont(buttonFont);

    // 調整番茄鐘計時器顯示（特別大）
    if (ui->pomodoroTimeLabel) {
        QFont timeFont = buttonFont;
        timeFont.setPointSize(56);  // 特別大的計時器
        timeFont.setBold(true);
        ui->pomodoroTimeLabel->setFont(timeFont);
    }

    // 調整右邊任務詳情面板 - 16pt
    QFont detailFont = globalFont;
    detailFont.setPointSize(16);
    if (ui->detailTitle) ui->detailTitle->setFont(detailFont);
    if (ui->lblDetailTaskTitle) ui->lblDetailTaskTitle->setFont(detailFont);
    if (ui->lblDetailDue) ui->lblDetailDue->setFont(detailFont);
    if (ui->lblDetailPriority) ui->lblDetailPriority->setFont(detailFont);
    if (ui->lblDescTitle) ui->lblDescTitle->setFont(detailFont);
    
    // 調整描述文字框和附件區域標籤 - 16pt
    if (ui->txtDetailDescription) ui->txtDetailDescription->setFont(detailFont);
    if (ui->lblAttachTitle) ui->lblAttachTitle->setFont(detailFont);
    if (ui->btnAddAttachment) ui->btnAddAttachment->setFont(detailFont);
    
    // 調整底部按鈕 - 16pt
    if (ui->btnEditTask) ui->btnEditTask->setFont(detailFont);
    if (ui->btnCompleteTask) ui->btnCompleteTask->setFont(detailFont);
    if (ui->btnDeleteTask) ui->btnDeleteTask->setFont(detailFont);

    // 調整中間任務列表的標題 - 18pt
    if (ui->taskListTitle) {
        QFont titleFont = globalFont;
        titleFont.setPointSize(18);
        titleFont.setBold(true);
        ui->taskListTitle->setFont(titleFont);
    }

    // 初始化資料庫
    if (!m_database->initialize()) {
        QMessageBox::critical(this, "錯誤", "無法初始化資料庫！");
    }

    // 設定系統匣圖示
    setupTrayIcon();

    // 設定通知管理器
    m_notificationManager->setTrayIcon(m_trayIcon);
    m_notificationManager->startReminderCheck();

    // 設定信號連接
    setupConnections();

    // 載入任務列表
    loadTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    // 新增任務按鈕
    connect(ui->btnAddTask, &QPushButton::clicked, this, &MainWindow::onAddTask);

    // 編輯、刪除、完成按鈕
    connect(ui->btnEditTask, &QPushButton::clicked, this, &MainWindow::onEditTask);
    connect(ui->btnDeleteTask, &QPushButton::clicked, this, &MainWindow::onDeleteTask);
    connect(ui->btnCompleteTask, &QPushButton::clicked, this, &MainWindow::onTaskCompleted);

    // 任務列表選擇變更
    connect(ui->taskListWidget, &QListWidget::currentRowChanged, this, &MainWindow::onTaskSelected);

    // 番茄鐘按鈕
    connect(ui->btnPomodoroStart, &QPushButton::clicked, this, &MainWindow::onPomodoroStart);
    connect(ui->btnPomodoroPause, &QPushButton::clicked, this, &MainWindow::onPomodoroPause);
    connect(ui->btnPomodoroReset, &QPushButton::clicked, this, &MainWindow::onPomodoroReset);

    // 番茄鐘計時器信號
    connect(m_pomodoroTimer, &PomodoroTimer::tick, this, &MainWindow::onPomodoroTick);
    connect(m_pomodoroTimer, &PomodoroTimer::phaseChanged, this, &MainWindow::onPhaseChanged);
    connect(m_pomodoroTimer, &PomodoroTimer::pomodoroCompleted, this, &MainWindow::onPomodoroCompleted);
    connect(m_pomodoroTimer, &PomodoroTimer::modeChanged, this, &MainWindow::onModeChanged);

    // 模式切換按鈕
    connect(ui->btnPomodoroMode, &QPushButton::clicked, this, [this]() {
        m_pomodoroTimer->setMode(PomodoroTimer::PomodoroMode);
    });
    connect(ui->btnStopwatchMode, &QPushButton::clicked, this, [this]() {
        m_pomodoroTimer->setMode(PomodoroTimer::StopwatchMode);
    });

    // 番茄鐘設定按鈕
    connect(ui->btnPomodoroSettings, &QPushButton::clicked, this, &MainWindow::onPomodoroSettings);

    // 篩選按鈕
    connect(ui->btnAllTasks, &QPushButton::clicked, this, &MainWindow::onFilterAll);
    connect(ui->btnToday, &QPushButton::clicked, this, &MainWindow::onFilterToday);
    connect(ui->btnOverdue, &QPushButton::clicked, this, &MainWindow::onFilterOverdue);
    connect(ui->btnCompleted, &QPushButton::clicked, this, &MainWindow::onFilterCompleted);

    // 附件按鈕
    connect(ui->btnAddAttachment, &QPushButton::clicked, this, &MainWindow::onAddAttachment);
    connect(ui->attachmentListWidget, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item) {
        onOpenAttachment(ui->attachmentListWidget->row(item));
    });
    
    // 附件列表右鍵選單
    ui->attachmentListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->attachmentListWidget, &QWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QListWidgetItem *item = ui->attachmentListWidget->itemAt(pos);
        if (item) {
            QMenu menu(this);
            QAction *openAction = menu.addAction("📂 開啟檔案");
            QAction *deleteAction = menu.addAction("🗑️ 刪除附件");
            
            QAction *selected = menu.exec(ui->attachmentListWidget->mapToGlobal(pos));
            if (selected == openAction) {
                onOpenAttachment(ui->attachmentListWidget->row(item));
            } else if (selected == deleteAction) {
                onDeleteAttachment();
            }
        }
    });

    // 選單動作
    connect(ui->actionNewTask, &QAction::triggered, this, &MainWindow::onAddTask);
    connect(ui->actionExit, &QAction::triggered, this, [this]() {
        // 真正退出程式
        m_trayIcon->hide();
        qApp->quit();
    });
    connect(ui->actionAbout, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "關於 專案小幫手", 
            "專案小幫手 - 任務管理工具\n\n版本 1.0.0\n\n幫助您管理任務、提醒與專注時間.");
    });
    
    // 測試通知（可在選單中加入）
    connect(ui->actionTestNotification, &QAction::triggered, this, [this]() {
        m_notificationManager->showNotification(
            NotificationManager::PomodoroComplete,
            "🔔 測試通知",
            "如果您看到這個通知，表示通知功能正常！");
        m_notificationManager->playSound(NotificationManager::PomodoroComplete);
    });
}

void MainWindow::loadTasks()
{
    // 從資料庫載入所有任務
    m_allTasks = m_database->getAllTasks();

    // 更新通知管理器的任務列表
    m_notificationManager->updateTasks(m_allTasks);

    // 套用目前的篩選
    applyFilter();
}

void MainWindow::applyFilter()
{
    // 根據篩選類型過濾任務
    m_tasks.clear();
    QDate today = QDate::currentDate();
    
    for (const Task &task : m_allTasks) {
        bool include = false;
        
        switch (m_currentFilter) {
            case FilterAll:
                include = true;
                break;
            case FilterToday:
                // 今日任務：截止日期 <= 今天，且未完成（包括逾期）
                if (task.dueDateTime.isValid() && 
                    task.dueDateTime.date() <= today && 
                    !task.isCompleted) {
                    include = true;
                }
                break;
            case FilterOverdue:
                // 逾期任務：已過期且未完成
                if (task.isOverdue() && !task.isCompleted) {
                    include = true;
                }
                break;
            case FilterCompleted:
                // 已完成任務
                if (task.isCompleted) {
                    include = true;
                }
                break;
        }
        
        if (include) {
            m_tasks.append(task);
        }
    }
    
    // 顯示篩選後的任務
    displayTasks();
}

void MainWindow::displayTasks()
{
    // 暫時斷開選擇信號，避免在列表重新建立時觸發過時資料
    disconnect(ui->taskListWidget, &QListWidget::currentRowChanged, this, &MainWindow::onTaskSelected);
    
    // 清空列表
    ui->taskListWidget->clear();

    // 設定任務列表的字體大小
    QFont taskFont = ui->taskListWidget->font();
    taskFont.setPointSize(15);  // 增加字體大小到15pt（更大更清晰）
    ui->taskListWidget->setFont(taskFont);

    // 加入列表
    for (const Task &task : m_tasks) {
        // 建立豐富的顯示文字（單行顯示所有信息）
        QString displayText;
        
        // 狀態圖示 + 標題 + 優先級
        if (task.isCompleted) {
            displayText = "✅ ";
        } else if (task.isOverdue()) {
            displayText = "⚠️ ";
        } else {
            displayText = "📋 ";
        }
        displayText += task.title;
        
        // 加上優先級
        if (task.priority == 2) {
            displayText += "  🔴高";
        } else if (task.priority == 1) {
            displayText += "  🟡中";
        }
        
        // 加上剩下多久 + 截止日期時間
        if (task.dueDateTime.isValid()) {
            QString fullDateTime = task.dueDateTime.toString("yyyy/MM/dd HH:mm");
            
            if (task.isCompleted) {
                displayText += QString("  ✓ 已完成");
            } else if (task.isOverdue()) {
                // 計算逾期時間
                qint64 totalSeconds = QDateTime::currentDateTime().secsTo(task.dueDateTime);
                int days = -totalSeconds / (24 * 3600);
                int hours = (-totalSeconds % (24 * 3600)) / 3600;
                displayText += QString("  ⏰ 逾期 %1天%2小時 (%3)").arg(days).arg(hours).arg(fullDateTime);
            } else {
                // 計算剩餘時間
                qint64 totalSeconds = QDateTime::currentDateTime().secsTo(task.dueDateTime);
                int days = totalSeconds / (24 * 3600);
                int hours = (totalSeconds % (24 * 3600)) / 3600;
                int minutes = (totalSeconds % 3600) / 60;
                
                if (days > 0) {
                    displayText += QString("  ⏱️ 還有 %1天%2小時 (%3)").arg(days).arg(hours).arg(fullDateTime);
                } else if (hours > 0) {
                    displayText += QString("  ⏱️ 還有 %1小時%2分鐘 (%3)").arg(hours).arg(minutes).arg(fullDateTime);
                } else {
                    displayText += QString("  ⏱️ 還有 %1分鐘 (%2)").arg(minutes).arg(fullDateTime);
                }
            }
        } else {
            // 沒有設定截止時間時的提示
            displayText += "  📅 未設定截止時間";
        }
        
        // 加上標籤
        if (!task.tags.isEmpty()) {
            displayText += QString("  🏷️ %1").arg(task.tags);
        }

        QListWidgetItem *item = new QListWidgetItem(displayText);
        item->setData(Qt::UserRole, task.id);  // 儲存任務 ID
        
        // 設定項目高度（增加高度使內容更寬敞易讀）
        item->setSizeHint(QSize(0, 75));

        // 設定顏色
        if (task.isCompleted) {
            item->setForeground(QColor("#95a5a6"));  // 灰色
        } else if (task.isOverdue()) {
            item->setForeground(QColor("#e74c3c"));  // 紅色
        } else if (task.priority == 2) {
            item->setForeground(QColor("#c0392b"));  // 深紅色（高優先級）
        }

        ui->taskListWidget->addItem(item);
    }

    // 更新狀態列（顯示篩選結果）
    QString filterName;
    switch (m_currentFilter) {
        case FilterAll: filterName = "所有任務"; break;
        case FilterToday: filterName = "今日任務"; break;
        case FilterOverdue: filterName = "逾期任務"; break;
        case FilterCompleted: filterName = "已完成"; break;
    }
    
    int totalCount = m_allTasks.size();
    int completedCount = 0;
    int overdueCount = 0;
    for (const Task &t : m_allTasks) {
        if (t.isCompleted) completedCount++;
        else if (t.isOverdue()) overdueCount++;
    }
    
    ui->statusbar->showMessage(QString("【%1】顯示 %2 個 / 總共 %3 個任務")
        .arg(filterName)
        .arg(m_tasks.size())
        .arg(totalCount));
    
    // 重新連接信號
    connect(ui->taskListWidget, &QListWidget::currentRowChanged, this, &MainWindow::onTaskSelected);
    
    // 自動選擇第一個任務（如果有的話）
    if (ui->taskListWidget->count() > 0) {
        ui->taskListWidget->setCurrentRow(0);
    } else {
        clearTaskDetails();
    }
}

// 篩選功能
void MainWindow::onFilterAll()
{
    m_currentFilter = FilterAll;
    applyFilter();
}

void MainWindow::onFilterToday()
{
    m_currentFilter = FilterToday;
    applyFilter();
}

void MainWindow::onFilterOverdue()
{
    m_currentFilter = FilterOverdue;
    applyFilter();
}

void MainWindow::onFilterCompleted()
{
    m_currentFilter = FilterCompleted;
    applyFilter();
}

void MainWindow::onAddTask()
{
    TaskDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        Task task = dialog.getTask();

        if (m_database->addTask(task)) {
            loadTasks();  // 重新載入列表
            ui->statusbar->showMessage("任務已新增", 3000);
        } else {
            QMessageBox::warning(this, "錯誤", "無法新增任務！");
        }
    }
}

void MainWindow::onEditTask()
{
    int currentRow = ui->taskListWidget->currentRow();
    if (currentRow < 0 || currentRow >= m_tasks.size()) {
        QMessageBox::information(this, "提示", "請先選擇一個任務！");
        return;
    }

    Task task = m_tasks[currentRow];

    TaskDialog dialog(this);
    dialog.setTask(task);

    if (dialog.exec() == QDialog::Accepted) {
        Task updatedTask = dialog.getTask();
        updatedTask.id = task.id;  // 保留任務 ID
        updatedTask.createdAt = task.createdAt;  // 保留建立時間
        updatedTask.isCompleted = task.isCompleted;
        updatedTask.completedAt = task.completedAt;

        if (m_database->updateTask(updatedTask)) {
            loadTasks();
            ui->statusbar->showMessage("任務已更新", 3000);
        } else {
            QMessageBox::warning(this, "錯誤", "無法更新任務！");
        }
    }
}

void MainWindow::onDeleteTask()
{
    int currentRow = ui->taskListWidget->currentRow();
    if (currentRow < 0 || currentRow >= m_tasks.size()) {
        QMessageBox::information(this, "提示", "請先選擇一個任務！");
        return;
    }

    Task task = m_tasks[currentRow];

    QMessageBox::StandardButton reply = QMessageBox::question(this, "確認刪除",
        QString("確定要刪除任務「%1」嗎？").arg(task.title),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_database->deleteTask(task.id)) {
            loadTasks();
            clearTaskDetails();
            ui->statusbar->showMessage("任務已刪除", 3000);
        } else {
            QMessageBox::warning(this, "錯誤", "無法刪除任務！");
        }
    }
}

void MainWindow::onTaskCompleted()
{
    int currentRow = ui->taskListWidget->currentRow();
    if (currentRow < 0 || currentRow >= m_tasks.size()) {
        QMessageBox::information(this, "提示", "請先選擇一個任務！");
        return;
    }

    Task task = m_tasks[currentRow];
    bool newStatus = !task.isCompleted;

    if (m_database->markTaskCompleted(task.id, newStatus)) {
        loadTasks();
        ui->statusbar->showMessage(newStatus ? "任務已完成 ✅" : "任務標記為未完成", 3000);
    } else {
        QMessageBox::warning(this, "錯誤", "無法更新任務狀態！");
    }
}

void MainWindow::onTaskSelected(int row)
{
    if (row < 0 || row >= m_tasks.size()) {
        clearTaskDetails();
        return;
    }

    Task task = m_tasks[row];

    // 更新右側詳情面板
    ui->lblDetailTaskTitle->setText(task.title);

    // 截止日期
    if (task.dueDateTime.isValid()) {
        ui->lblDetailDue->setText("📅 截止：" + task.dueDateTime.toString("yyyy/MM/dd HH:mm"));
    } else {
        ui->lblDetailDue->setText("");
    }

    // 優先級
    QString priorityText = "⭐ 優先級：" + task.priorityText();
    if (task.priority == 2) {
        priorityText += " 🔴";
    } else if (task.priority == 1) {
        priorityText += " 🟡";
    }
    ui->lblDetailPriority->setText(priorityText);

    // 描述
    ui->txtDetailDescription->setPlainText(task.description.isEmpty() ? "（無描述）" : task.description);

    // 更新完成按鈕文字
    ui->btnCompleteTask->setText(task.isCompleted ? "↩️ 取消完成" : "✅ 完成");
    
    // 更新附件列表
    updateAttachmentList(task);
}

void MainWindow::clearTaskDetails()
{
    ui->lblDetailTaskTitle->setText("選擇一個任務查看詳情");
    ui->lblDetailDue->setText("");
    ui->lblDetailPriority->setText("");
    ui->txtDetailDescription->clear();
    ui->attachmentListWidget->clear();
}

void MainWindow::onPomodoroStart()
{
    // 如果有選擇任務，開始任務計時
    int currentRow = ui->taskListWidget->currentRow();
    if (currentRow >= 0 && currentRow < m_tasks.size()) {
        Task task = m_tasks[currentRow];
        m_pomodoroTimer->startTaskTimer(task.id);
        ui->lblTaskWorkTime->setText(QString("📋 任務: %1").arg(task.title.left(10)));
    }

    m_pomodoroTimer->start();
    ui->statusbar->showMessage("計時開始！專注工作中...", 3000);
}

void MainWindow::onPomodoroPause()
{
    m_pomodoroTimer->pause();
    ui->statusbar->showMessage("計時已暫停", 3000);
}

void MainWindow::onPomodoroReset()
{
    m_pomodoroTimer->reset();
    m_pomodoroTimer->stopTaskTimer();
    
    if (m_pomodoroTimer->currentMode() == PomodoroTimer::PomodoroMode) {
        ui->pomodoroTimeLabel->setText("25:00");
        ui->pomodoroPhaseLabel->setText("工作中");
    } else {
        ui->pomodoroTimeLabel->setText("00:00");
        ui->pomodoroPhaseLabel->setText("碼錶");
    }
    
    ui->lblTaskWorkTime->setText("📋 任務: --");
    ui->statusbar->showMessage("計時已重設", 3000);
}

void MainWindow::onPomodoroTick(int seconds)
{
    // 更新時間顯示
    ui->pomodoroTimeLabel->setText(PomodoroTimer::formatTime(seconds));
    
    // 更新統計
    updateStatsDisplay();
}

void MainWindow::onPhaseChanged(PomodoroTimer::Phase phase)
{
    QString phaseText;
    switch (phase) {
        case PomodoroTimer::Work:
            phaseText = "工作中";
            // 休息結束，開始工作的通知
            m_notificationManager->playSound(NotificationManager::BreakComplete);
            showWindow();  // 自動彈出視窗
            m_notificationManager->showNotification(
                NotificationManager::BreakComplete,
                "⏰ 休息結束",
                "休息時間結束了，開始工作吧！");
            break;
        case PomodoroTimer::ShortBreak:
            phaseText = "短休息";
            break;
        case PomodoroTimer::LongBreak:
            phaseText = "長休息";
            break;
    }
    ui->pomodoroPhaseLabel->setText(phaseText);
}

void MainWindow::onPomodoroCompleted()
{
    // 一個番茄鐘完成
    updateStatsDisplay();
    
    // 播放提示音
    m_notificationManager->playSound(NotificationManager::PomodoroComplete);
    
    // 自動彈出視窗
    showWindow();
    
    // 發送系統通知
    m_notificationManager->showNotification(
        NotificationManager::PomodoroComplete,
        "🍅 番茄鐘完成",
        QString("太棒了！完成一個番茄鐘！今日已完成 %1 個")
            .arg(m_pomodoroTimer->todayPomodoroCount()));
    
    // 顯示對話框
    QMessageBox::information(this, "🍅 番茄鐘完成", 
        QString("太棒了！完成一個番茄鐘！\n\n今日已完成: %1 個\n今日工時: %2")
        .arg(m_pomodoroTimer->todayPomodoroCount())
        .arg(PomodoroTimer::formatDuration(m_pomodoroTimer->todayWorkSeconds())));
}

void MainWindow::onModeChanged(PomodoroTimer::Mode mode)
{
    if (mode == PomodoroTimer::PomodoroMode) {
        ui->pomodoroPhaseLabel->setText("工作中");
        ui->pomodoroTimeLabel->setText("25:00");
        ui->pomodoroTitle->setText("🍅 番茄鐘");
    } else {
        ui->pomodoroPhaseLabel->setText("碼錶");
        ui->pomodoroTimeLabel->setText("00:00");
        ui->pomodoroTitle->setText("⏱️ 碼錶");
    }
}

void MainWindow::updateStatsDisplay()
{
    // 更新今日完成的番茄鐘數
    ui->lblTodayPomodoros->setText(QString("🍅 完成: %1 個").arg(m_pomodoroTimer->todayPomodoroCount()));
    
    // 更新今日工作時間
    ui->lblTodayWorkTime->setText(QString("⏱️ 工時: %1").arg(
        PomodoroTimer::formatDuration(m_pomodoroTimer->todayWorkSeconds())));
    
    // 更新當前任務工作時間
    int taskId = m_pomodoroTimer->getCurrentTaskId();
    if (taskId != -1) {
        int taskSeconds = m_pomodoroTimer->getTaskElapsedSeconds(taskId);
        // 找到任務名稱
        for (const Task &task : m_tasks) {
            if (task.id == taskId) {
                ui->lblTaskWorkTime->setText(QString("📋 %1: %2")
                    .arg(task.title.left(8))
                    .arg(PomodoroTimer::formatDuration(taskSeconds)));
                break;
            }
        }
    }
}

void MainWindow::onPomodoroSettings()
{
    PomodoroSettingsDialog dialog(this);
    
    // 設定目前的值
    dialog.setWorkDuration(m_pomodoroTimer->getWorkDuration());
    dialog.setShortBreakDuration(m_pomodoroTimer->getShortBreakDuration());
    dialog.setLongBreakDuration(m_pomodoroTimer->getLongBreakDuration());
    dialog.setCyclesBeforeLongBreak(m_pomodoroTimer->getCyclesBeforeLongBreak());
    
    if (dialog.exec() == QDialog::Accepted) {
        // 套用設定
        m_pomodoroTimer->setWorkDuration(dialog.workDuration());
        m_pomodoroTimer->setShortBreakDuration(dialog.shortBreakDuration());
        m_pomodoroTimer->setLongBreakDuration(dialog.longBreakDuration());
        m_pomodoroTimer->setCyclesBeforeLongBreak(dialog.cyclesBeforeLongBreak());
        
        // 重設計時器以套用新設定（不發送信號避免彈出通知）
        m_pomodoroTimer->resetQuiet();
        
        ui->statusbar->showMessage(QString("番茄鐘設定已更新：工作 %1 分鐘，短休息 %2 分鐘，長休息 %3 分鐘")
            .arg(dialog.workDuration())
            .arg(dialog.shortBreakDuration())
            .arg(dialog.longBreakDuration()), 5000);
    }
}

void MainWindow::setupTrayIcon()
{
    // 建立系統匣圖示
    m_trayIcon = new QSystemTrayIcon(this);
    
    // 使用應用程式圖示，或建立一個簡單的圖示
    QPixmap pixmap(32, 32);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 繪製一個簡單的番茄圖示
    painter.setBrush(QColor("#e74c3c"));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(2, 6, 28, 24);
    
    // 繪製番茄蒂
    painter.setBrush(QColor("#27ae60"));
    painter.drawRect(13, 2, 6, 6);
    
    painter.end();
    
    m_trayIcon->setIcon(QIcon(pixmap));
    m_trayIcon->setToolTip("專案小幫手 - 任務管理工具");

    // 建立右鍵選單
    m_trayMenu = new QMenu(this);
    
    QAction *showAction = m_trayMenu->addAction("📋 顯示主視窗");
    connect(showAction, &QAction::triggered, this, &MainWindow::showWindow);
    
    m_trayMenu->addSeparator();
    
    QAction *newTaskAction = m_trayMenu->addAction("➕ 新增任務");
    connect(newTaskAction, &QAction::triggered, this, &MainWindow::onAddTask);
    
    m_trayMenu->addSeparator();
    
    QAction *startPomodoroAction = m_trayMenu->addAction("🍅 開始番茄鐘");
    connect(startPomodoroAction, &QAction::triggered, this, &MainWindow::onPomodoroStart);
    
    QAction *pausePomodoroAction = m_trayMenu->addAction("⏸️ 暫停");
    connect(pausePomodoroAction, &QAction::triggered, this, &MainWindow::onPomodoroPause);
    
    m_trayMenu->addSeparator();
    
    QAction *exitAction = m_trayMenu->addAction("🚪 結束");
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    
    m_trayIcon->setContextMenu(m_trayMenu);

    // 連接點擊事件
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);

    // 顯示系統匣圖示
    m_trayIcon->show();
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:  // 單擊
        case QSystemTrayIcon::DoubleClick:  // 雙擊
            showWindow();
            break;
        default:
            break;
    }
}

void MainWindow::showWindow()
{
    // 顯示視窗並帶到前景
    showNormal();
    activateWindow();
    raise();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 隱藏系統匣圖示，然後關閉程式
    if (m_trayIcon) {
        m_trayIcon->hide();
    }
    
    // 接受關閉事件，真正關閉程式
    event->accept();
}

// ============ 附件功能 ============

void MainWindow::updateAttachmentList(const Task &task)
{
    ui->attachmentListWidget->clear();
    
    // 設定附件列表的字體大小
    QFont attachFont = ui->attachmentListWidget->font();
    attachFont.setPointSize(16);  // 更大的字體
    attachFont.setBold(true);
    ui->attachmentListWidget->setFont(attachFont);
    
    for (const Attachment &att : task.attachments) {
        // 只顯示檔案名稱，圖示在前面，使用空格分隔
        QString fileName = att.originalName;
        // 如果檔案名太長，縮短顯示
        if (fileName.length() > 30) {
            fileName = fileName.left(27) + "...";
        }
        QString displayText = att.icon() + "  " + fileName;
        
        QListWidgetItem *item = new QListWidgetItem(displayText);
        item->setData(Qt::UserRole, att.id);
        item->setData(Qt::UserRole + 1, att.storedPath);
        item->setToolTip(QString("完整名稱: %1\n路徑: %2\n新增時間: %3")
            .arg(att.originalName)
            .arg(att.storedPath)
            .arg(att.addedAt.toString("yyyy/MM/dd HH:mm")));
        item->setSizeHint(QSize(300, 50));  // 增加寬度和高度
        ui->attachmentListWidget->addItem(item);
    }
    
    // 更新標題顯示附件數量
    if (task.attachments.isEmpty()) {
        ui->lblAttachTitle->setText("📎 附件");
    } else {
        ui->lblAttachTitle->setText(QString("📎 附件 (%1)").arg(task.attachments.size()));
    }
}

void MainWindow::onAddAttachment()
{
    int currentRow = ui->taskListWidget->currentRow();
    if (currentRow < 0 || currentRow >= m_tasks.size()) {
        QMessageBox::information(this, "提示", "請先選擇一個任務！");
        return;
    }
    
    Task &task = m_tasks[currentRow];
    
    // 開啟檔案選擇對話框
    QStringList files = QFileDialog::getOpenFileNames(this, "選擇附件檔案", 
        QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
        "所有檔案 (*);;圖片 (*.png *.jpg *.jpeg *.gif *.bmp);;文件 (*.pdf *.doc *.docx *.txt)");
    
    if (files.isEmpty()) {
        return;
    }
    
    QMimeDatabase mimeDb;
    QString attachDir = Database::attachmentsDir();
    
    for (const QString &filePath : files) {
        QFileInfo fileInfo(filePath);
        
        // 生成唯一的儲存檔名
        QString storedName = QUuid::createUuid().toString(QUuid::WithoutBraces) + "_" + fileInfo.fileName();
        QString storedPath = attachDir + "/" + storedName;
        
        // 複製檔案到附件目錄
        if (QFile::copy(filePath, storedPath)) {
            Attachment att;
            att.taskId = task.id;
            att.originalName = fileInfo.fileName();
            att.storedPath = storedPath;
            att.mimeType = mimeDb.mimeTypeForFile(filePath).name();
            
            if (m_database->addAttachment(att)) {
                task.attachments.append(att);
                ui->statusbar->showMessage(QString("已新增附件: %1").arg(att.originalName), 3000);
            }
        } else {
            QMessageBox::warning(this, "錯誤", QString("無法複製檔案: %1").arg(fileInfo.fileName()));
        }
    }
    
    // 更新附件列表顯示
    updateAttachmentList(task);
    
    // 同步更新 m_allTasks
    for (Task &t : m_allTasks) {
        if (t.id == task.id) {
            t.attachments = task.attachments;
            break;
        }
    }
}

void MainWindow::onDeleteAttachment()
{
    int currentRow = ui->taskListWidget->currentRow();
    if (currentRow < 0 || currentRow >= m_tasks.size()) {
        return;
    }
    
    int attRow = ui->attachmentListWidget->currentRow();
    if (attRow < 0) {
        QMessageBox::information(this, "提示", "請先選擇一個附件！");
        return;
    }
    
    QListWidgetItem *item = ui->attachmentListWidget->currentItem();
    int attachmentId = item->data(Qt::UserRole).toInt();
    QString fileName = item->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "確認刪除",
        QString("確定要刪除附件「%1」嗎？").arg(fileName),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (m_database->deleteAttachment(attachmentId)) {
            // 從任務中移除附件
            Task &task = m_tasks[currentRow];
            for (int i = 0; i < task.attachments.size(); ++i) {
                if (task.attachments[i].id == attachmentId) {
                    task.attachments.removeAt(i);
                    break;
                }
            }
            
            // 同步更新 m_allTasks
            for (Task &t : m_allTasks) {
                if (t.id == task.id) {
                    t.attachments = task.attachments;
                    break;
                }
            }
            
            updateAttachmentList(task);
            ui->statusbar->showMessage("附件已刪除", 3000);
        } else {
            QMessageBox::warning(this, "錯誤", "無法刪除附件！");
        }
    }
}

void MainWindow::onOpenAttachment(int row)
{
    if (row < 0) return;
    
    QListWidgetItem *item = ui->attachmentListWidget->item(row);
    if (!item) return;
    
    QString filePath = item->data(Qt::UserRole + 1).toString();
    
    if (QFile::exists(filePath)) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    } else {
        QMessageBox::warning(this, "錯誤", "找不到附件檔案！\n路徑: " + filePath);
    }
}
