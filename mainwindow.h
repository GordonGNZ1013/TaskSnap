#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include "database.h"
#include "pomodorotimer.h"
#include "notificationmanager.h"
#include "snapshotmanager.h"
#include "workstats.h"
#include "pomodoroconfig.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 篩選類型
    enum FilterType {
        FilterAll,       // 所有任務
        FilterToday,     // 今日任務
        FilterOverdue,   // 逾期任務
        FilterCompleted  // 已完成任務
    };

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // 任務相關
    void onAddTask();
    void onEditTask();
    void onDeleteTask();
    void onTaskCompleted();
    void onTaskSelected(int row);

    // 篩選相關
    void onFilterAll();
    void onFilterToday();
    void onFilterOverdue();
    void onFilterCompleted();

    // 附件相關
    void onAddAttachment();
    void onDeleteAttachment();
    void onOpenAttachment(int row);

    // 番茄鐘相關
    void onPomodoroStart();
    void onPomodoroPause();
    void onPomodoroReset();
    void onPomodoroSettings();
    void onPomodoroTick(int seconds);
    void onPhaseChanged(PomodoroTimer::Phase phase);
    void onPomodoroCompleted();
    void onModeChanged(PomodoroTimer::Mode mode);

    // 系統匣相關
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void showWindow();
    
    // 行事曆相關
    void onShowCalendar();
    void onCalendarTaskSelected(int taskId);
    void onCalendarAddTask(const QDate &date);
    
    // 子任務相關
    void onAddSubTask();
    void onSubTaskToggled(int row);
    void onDeleteSubTask();
    
    // 靈感相關
    void onAddIdea();
    void onDeleteIdea();
    void onToggleIdeaImportant();

private:
    Ui::MainWindow *ui;
    Database *m_database;
    PomodoroTimer *m_pomodoroTimer;
    NotificationManager *m_notificationManager;
    SnapshotManager *m_snapshotManager;
    WorkStats *m_workStats;
    PomodoroConfig *m_pomodoroConfig;
    QList<Task> m_allTasks;    // 所有任務（從資料庫）
    QList<Task> m_tasks;       // 目前顯示的任務（篩選後）
    FilterType m_currentFilter = FilterAll;  // 目前篩選類型

    // 系統匣
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayMenu;

    void setupConnections();
    void setupTrayIcon();
    void loadTasks();
    void applyFilter();        // 套用篩選
    void displayTasks();       // 顯示任務列表
    void clearTaskDetails();
    void updateStatsDisplay();
    void updateAttachmentList(const Task &task);  // 更新附件列表
    void updateSubTaskList(const Task &task);     // 更新子任務列表
    void updateIdeaList(const Task &task);        // 更新靈感列表
    void selectTaskById(int taskId);              // 根據ID選擇任務
    void updateTaskListItem(int row, const Task &task);  // 更新單一任務列表項目
};

#endif // MAINWINDOW_H
