// ========================================
// 行事曆對話框實現 (calendardialog.cpp)
// 功能: 顯示任務的月曆視圖，同步顯示截止日期
// ========================================

#include "calendardialog.h"
#include <QTextCharFormat>
#include <QPushButton>
#include <QSplitter>

CalendarDialog::CalendarDialog(QWidget *parent)
    : QDialog(parent)
    , m_calendar(nullptr)
    , m_taskList(nullptr)
    , m_dateLabel(nullptr)
    , m_infoLabel(nullptr)
{
    setupUI();
}

CalendarDialog::~CalendarDialog()
{
}

void CalendarDialog::setupUI()
{
    setWindowTitle("📅 行事曆 - 任務總覽");
    setMinimumSize(900, 600);
    resize(1000, 700);
    
    // 主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    
    // 左側：行事曆
    QWidget *leftWidget = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *calendarTitle = new QLabel("📅 月曆視圖");
    calendarTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; padding: 10px 0;");
    leftLayout->addWidget(calendarTitle);
    
    m_calendar = new QCalendarWidget;
    m_calendar->setGridVisible(true);
    m_calendar->setMinimumDate(QDate(2020, 1, 1));
    m_calendar->setMaximumDate(QDate(2030, 12, 31));
    m_calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    m_calendar->setStyleSheet(R"(
        QCalendarWidget {
            background-color: white;
            border: 1px solid #bdc3c7;
            border-radius: 8px;
        }
        QCalendarWidget QToolButton {
            color: #2c3e50;
            background-color: transparent;
            border: none;
            border-radius: 4px;
            padding: 8px;
            font-size: 14px;
            font-weight: bold;
        }
        QCalendarWidget QToolButton:hover {
            background-color: #ecf0f1;
        }
        QCalendarWidget QMenu {
            background-color: white;
        }
        QCalendarWidget QSpinBox {
            font-size: 14px;
            background-color: white;
            border: 1px solid #bdc3c7;
            border-radius: 4px;
            padding: 4px;
        }
        QCalendarWidget QTableView {
            selection-background-color: #3498db;
            selection-color: white;
            font-size: 14px;
        }
        QCalendarWidget QTableView::item {
            padding: 8px;
        }
        QCalendarWidget QTableView::item:hover {
            background-color: #e8f4fc;
        }
    )");
    leftLayout->addWidget(m_calendar);
    
    // 圖例
    QLabel *legendLabel = new QLabel("📌 圖例: 🔴 高優先級  🟡 中優先級  🔵 有任務  ⚫ 逾期");
    legendLabel->setStyleSheet("color: #7f8c8d; font-size: 12px; padding: 10px 0;");
    leftLayout->addWidget(legendLabel);
    
    // 右側：任務列表
    QWidget *rightWidget = new QWidget;
    rightWidget->setMinimumWidth(350);
    rightWidget->setMaximumWidth(450);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    
    m_dateLabel = new QLabel("選擇日期查看任務");
    m_dateLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; padding: 10px 0;");
    rightLayout->addWidget(m_dateLabel);
    
    m_infoLabel = new QLabel("");
    m_infoLabel->setStyleSheet("color: #7f8c8d; font-size: 13px;");
    rightLayout->addWidget(m_infoLabel);
    
    m_taskList = new QListWidget;
    m_taskList->setStyleSheet(R"(
        QListWidget {
            background-color: white;
            border: 1px solid #bdc3c7;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
        }
        QListWidget::item {
            padding: 12px;
            border-bottom: 1px solid #ecf0f1;
            border-radius: 4px;
            margin: 2px 0;
        }
        QListWidget::item:selected {
            background-color: #e8f4fc;
            color: #2c3e50;
        }
        QListWidget::item:hover {
            background-color: #f8f9fa;
        }
    )");
    rightLayout->addWidget(m_taskList);
    
    // 提示標籤
    QLabel *tipLabel = new QLabel("💡 雙擊任務可跳轉到詳情");
    tipLabel->setStyleSheet("color: #95a5a6; font-size: 12px; padding: 8px 0;");
    rightLayout->addWidget(tipLabel);
    
    // 按鈕區域
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    
    // 新增任務按鈕
    m_addTaskBtn = new QPushButton("➕ 新增任務");
    m_addTaskBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #27ae60;
            color: white;
            border: none;
            padding: 12px 20px;
            font-size: 14px;
            border-radius: 6px;
        }
        QPushButton:hover {
            background-color: #219a52;
        }
    )");
    connect(m_addTaskBtn, &QPushButton::clicked, this, &CalendarDialog::onAddTaskClicked);
    buttonLayout->addWidget(m_addTaskBtn);
    
    // 關閉按鈕
    QPushButton *closeBtn = new QPushButton("關閉");
    closeBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #3498db;
            color: white;
            border: none;
            padding: 12px 20px;
            font-size: 14px;
            border-radius: 6px;
        }
        QPushButton:hover {
            background-color: #2980b9;
        }
    )");
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    buttonLayout->addWidget(closeBtn);
    
    rightLayout->addLayout(buttonLayout);
    
    mainLayout->addWidget(leftWidget, 2);
    mainLayout->addWidget(rightWidget, 1);
    
    // 連接信號
    connect(m_calendar, &QCalendarWidget::clicked, this, &CalendarDialog::onDateSelected);
    connect(m_taskList, &QListWidget::itemDoubleClicked, this, &CalendarDialog::onTaskDoubleClicked);
    
    // 設置對話框樣式
    setStyleSheet("QDialog { background-color: #f5f5f5; }");
}

void CalendarDialog::setTasks(const QList<Task> &tasks)
{
    m_tasks = tasks;
    m_tasksByDate.clear();
    
    // 按日期分組任務
    for (const Task &task : tasks) {
        if (task.dueDateTime.isValid()) {
            QDate date = task.dueDateTime.date();
            m_tasksByDate[date].append(task);
        }
    }
    
    // 高亮有任務的日期
    highlightDatesWithTasks();
    
    // 選擇今天
    m_calendar->setSelectedDate(QDate::currentDate());
    onDateSelected(QDate::currentDate());
}

void CalendarDialog::refreshTasks(const QList<Task> &tasks)
{
    m_tasks = tasks;
    m_tasksByDate.clear();
    
    // 按日期分組任務
    for (const Task &task : tasks) {
        if (task.dueDateTime.isValid()) {
            QDate date = task.dueDateTime.date();
            m_tasksByDate[date].append(task);
        }
    }
    
    // 重置日曆格式並重新高亮
    // 先清除所有日期格式
    QTextCharFormat defaultFormat;
    for (auto it = m_tasksByDate.constBegin(); it != m_tasksByDate.constEnd(); ++it) {
        m_calendar->setDateTextFormat(it.key(), defaultFormat);
    }
    
    // 重新高亮有任務的日期
    highlightDatesWithTasks();
    
    // 更新當前選中日期的任務列表
    if (m_selectedDate.isValid()) {
        updateTaskList(m_selectedDate);
    }
}

void CalendarDialog::highlightDatesWithTasks()
{
    // 重置所有日期格式
    QTextCharFormat defaultFormat;
    
    QTextCharFormat hasTaskFormat;
    hasTaskFormat.setBackground(QColor("#e8f4fc"));
    hasTaskFormat.setForeground(QColor("#2c3e50"));
    
    QTextCharFormat highPriorityFormat;
    highPriorityFormat.setBackground(QColor("#fadbd8"));
    highPriorityFormat.setForeground(QColor("#c0392b"));
    
    QTextCharFormat mediumPriorityFormat;
    mediumPriorityFormat.setBackground(QColor("#fef9e7"));
    mediumPriorityFormat.setForeground(QColor("#b7950b"));
    
    QTextCharFormat overdueFormat;
    overdueFormat.setBackground(QColor("#e74c3c"));
    overdueFormat.setForeground(QColor("white"));
    
    QDate today = QDate::currentDate();
    
    // 遍歷所有有任務的日期
    for (auto it = m_tasksByDate.constBegin(); it != m_tasksByDate.constEnd(); ++it) {
        QDate date = it.key();
        const QList<Task> &tasksOnDate = it.value();
        
        // 檢查是否有未完成的任務
        bool hasUncompletedTask = false;
        int maxPriority = 0;
        bool isOverdue = false;
        
        for (const Task &task : tasksOnDate) {
            if (!task.isCompleted) {
                hasUncompletedTask = true;
                if (task.priority > maxPriority) {
                    maxPriority = task.priority;
                }
                if (date < today) {
                    isOverdue = true;
                }
            }
        }
        
        if (hasUncompletedTask) {
            if (isOverdue) {
                m_calendar->setDateTextFormat(date, overdueFormat);
            } else if (maxPriority == 2) {
                m_calendar->setDateTextFormat(date, highPriorityFormat);
            } else if (maxPriority == 1) {
                m_calendar->setDateTextFormat(date, mediumPriorityFormat);
            } else {
                m_calendar->setDateTextFormat(date, hasTaskFormat);
            }
        }
    }
}

void CalendarDialog::onDateSelected(const QDate &date)
{
    m_selectedDate = date;  // 記錄選中的日期
    m_dateLabel->setText(QString("📅 %1").arg(date.toString("yyyy年MM月dd日 dddd")));
    updateTaskList(date);
}

void CalendarDialog::updateTaskList(const QDate &date)
{
    m_taskList->clear();
    
    QDate today = QDate::currentDate();
    
    if (!m_tasksByDate.contains(date)) {
        m_infoLabel->setText("這一天沒有任務");
        return;
    }
    
    const QList<Task> &tasksOnDate = m_tasksByDate[date];
    int total = tasksOnDate.size();
    int completed = 0;
    
    for (const Task &task : tasksOnDate) {
        if (task.isCompleted) completed++;
        
        QString displayText;
        
        // 狀態圖示
        if (task.isCompleted) {
            displayText = "✅ ";
        } else if (date < today) {
            displayText = "⚠️ 逾期 ";
        } else {
            displayText = "📋 ";
        }
        
        // 標題
        displayText += task.title;
        
        // 優先級
        if (task.priority == 2) {
            displayText += " 🔴";
        } else if (task.priority == 1) {
            displayText += " 🟡";
        }
        
        // 時間
        displayText += QString(" ⏰ %1").arg(task.dueDateTime.toString("HH:mm"));
        
        // 子任務進度
        if (!task.subTasks.isEmpty()) {
            displayText += QString(" 📝%1").arg(task.subTaskProgress());
        }
        
        QListWidgetItem *item = new QListWidgetItem(displayText);
        item->setData(Qt::UserRole, task.id);
        
        // 設置顏色
        if (task.isCompleted) {
            item->setForeground(QColor("#95a5a6"));
        } else if (date < today) {
            item->setForeground(QColor("#e74c3c"));
        } else if (task.priority == 2) {
            item->setForeground(QColor("#c0392b"));
        }
        
        m_taskList->addItem(item);
    }
    
    m_infoLabel->setText(QString("共 %1 個任務，已完成 %2 個").arg(total).arg(completed));
}

void CalendarDialog::onTaskDoubleClicked(QListWidgetItem *item)
{
    if (item) {
        int taskId = item->data(Qt::UserRole).toInt();
        emit taskSelected(taskId);
        accept();
    }
}

void CalendarDialog::onAddTaskClicked()
{
    // 發送信號請求添加任務，使用當前選中的日期
    QDate targetDate = m_selectedDate.isValid() ? m_selectedDate : QDate::currentDate();
    emit addTaskRequested(targetDate);
}
