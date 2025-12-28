// ========================================
// 行事曆對話框頭文件 (calendardialog.h)
// 功能: 顯示任務的月曆視圖，同步顯示截止日期
// ========================================

#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QCalendarWidget>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMap>
#include <QDate>
#include "task.h"

class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget *parent = nullptr);
    ~CalendarDialog();

    // 設置任務列表
    void setTasks(const QList<Task> &tasks);
    
    // 刷新任務列表（添加任務後使用）
    void refreshTasks(const QList<Task> &tasks);

signals:
    // 當用戶選擇一個任務時發出
    void taskSelected(int taskId);
    
    // 請求在指定日期添加任務
    void addTaskRequested(const QDate &date);
    
    // 任務已添加（通知主視窗刷新）
    void taskAdded();

private slots:
    // 日期被選擇
    void onDateSelected(const QDate &date);
    
    // 任務項目被雙擊
    void onTaskDoubleClicked(QListWidgetItem *item);
    
    // 添加任務按鈕點擊
    void onAddTaskClicked();

private:
    void setupUI();
    void updateTaskList(const QDate &date);
    void highlightDatesWithTasks();

    QCalendarWidget *m_calendar;
    QListWidget *m_taskList;
    QLabel *m_dateLabel;
    QLabel *m_infoLabel;
    QPushButton *m_addTaskBtn;
    
    QList<Task> m_tasks;
    QMap<QDate, QList<Task>> m_tasksByDate;  // 按日期分組的任務
    QDate m_selectedDate;  // 當前選中的日期
};

#endif // CALENDARDIALOG_H
