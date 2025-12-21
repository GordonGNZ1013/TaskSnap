// ========================================
// 任務對話框類實現 (taskdialog.cpp)
// 功能: 提供創建、編輯任務的對話框UI
// 特性: 支持優先級設置、提醒時間、標籤管理
// ========================================

#include "taskdialog.h"           // 任務對話框頭文件
#include "ui_taskdialog.h"        // 自動生成的UI文件
#include <QMessageBox>            // 消息框

/**
 * 構造函數 - TaskDialog()
 * 參數: parent - 父窗口指針
 * 功能: 初始化任務對話框
 *  1. 設置UI布局
 *  2. 設置默認的截止日期（明天）
 *  3. 連接複選框信號以啟用/禁用日期時間編輯
 */
TaskDialog::TaskDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaskDialog)
{
    ui->setupUi(this);  // 從UI文件加載界面

    // 設定預設日期時間為現在加一天
    QDateTime now = QDateTime::currentDateTime();
    ui->editDueDateTime->setDateTime(now.addDays(1));  // 預設截止日期為明天
    ui->editReminderDateTime->setDateTime(now.addDays(1));

    // 連接勾選框信號到槽函數
    // 當"無截止日期"複選框被切換時，啟用或禁用日期編輯框
    connect(ui->chkNoDueDate, &QCheckBox::toggled, this, [this](bool checked) {
        ui->editDueDateTime->setEnabled(!checked);  // checked時禁用，未checked時啟用
    });

    // 當"無提醒"複選框被切換時，啟用或禁用提醒時間編輯框
    connect(ui->chkNoReminder, &QCheckBox::toggled, this, [this](bool checked) {
        ui->editReminderDateTime->setEnabled(!checked);
    });

    // 預設提醒時間編輯框是禁用的（因為通常用戶不需要提醒）
    ui->editReminderDateTime->setEnabled(false);
}

TaskDialog::~TaskDialog()
{
    delete ui;
}

void TaskDialog::setTask(const Task &task)
{
    m_taskId = task.id;

    // 更新標題
    ui->dialogTitle->setText("編輯任務");
    setWindowTitle("編輯任務");

    // 填入任務資料
    ui->editTitle->setText(task.title);
    ui->editDescription->setPlainText(task.description);

    // 截止日期
    if (task.dueDateTime.isValid()) {
        ui->editDueDateTime->setDateTime(task.dueDateTime);
        ui->chkNoDueDate->setChecked(false);
    } else {
        ui->chkNoDueDate->setChecked(true);
    }

    // 提醒時間
    if (task.reminderAt.isValid()) {
        ui->editReminderDateTime->setDateTime(task.reminderAt);
        ui->chkNoReminder->setChecked(false);
        ui->editReminderDateTime->setEnabled(true);
    } else {
        ui->chkNoReminder->setChecked(true);
    }

    // 優先級
    ui->comboPriority->setCurrentIndex(task.priority);

    // 標籤
    ui->editTags->setText(task.tags);
}

Task TaskDialog::getTask() const
{
    Task task;
    task.id = m_taskId;
    task.title = ui->editTitle->text().trimmed();
    task.description = ui->editDescription->toPlainText().trimmed();

    // 截止日期
    if (!ui->chkNoDueDate->isChecked()) {
        task.dueDateTime = ui->editDueDateTime->dateTime();
    }

    // 提醒時間
    if (!ui->chkNoReminder->isChecked()) {
        task.reminderAt = ui->editReminderDateTime->dateTime();
    }

    // 優先級
    task.priority = ui->comboPriority->currentIndex();

    // 標籤
    task.tags = ui->editTags->text().trimmed();

    return task;
}

void TaskDialog::accept()
{
    // 驗證必填欄位
    if (ui->editTitle->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "提示", "請輸入任務標題！");
        ui->editTitle->setFocus();
        return;
    }

    // 驗證截止時間邏輯
    if (!ui->chkNoDueDate->isChecked()) {
        QDateTime dueTime = ui->editDueDateTime->dateTime();
        if (dueTime <= QDateTime::currentDateTime()) {
            QMessageBox::warning(this, "提示", "截止時間不能早於現在！");
            ui->editDueDateTime->setFocus();
            return;
        }
    }

    // 驗證提醒時間邏輯
    if (!ui->chkNoReminder->isChecked()) {
        QDateTime reminderTime = ui->editReminderDateTime->dateTime();
        if (reminderTime <= QDateTime::currentDateTime()) {
            QMessageBox::warning(this, "提示", "提醒時間不能早於現在！");
            ui->editReminderDateTime->setFocus();
            return;
        }
        // 提醒時間應該早於截止時間
        if (!ui->chkNoDueDate->isChecked()) {
            QDateTime dueTime = ui->editDueDateTime->dateTime();
            if (reminderTime >= dueTime) {
                QMessageBox::warning(this, "提示", "提醒時間應該早於截止時間！");
                ui->editReminderDateTime->setFocus();
                return;
            }
        }
    }

    QDialog::accept();
}
