#include "taskdialog.h"
#include "ui_taskdialog.h"
#include <QMessageBox>

TaskDialog::TaskDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TaskDialog)
{
    ui->setupUi(this);

    // 設定預設日期時間為現在
    QDateTime now = QDateTime::currentDateTime();
    ui->editDueDateTime->setDateTime(now.addDays(1));  // 預設明天
    ui->editReminderDateTime->setDateTime(now.addDays(1));

    // 連接勾選框信號
    connect(ui->chkNoDueDate, &QCheckBox::toggled, this, [this](bool checked) {
        ui->editDueDateTime->setEnabled(!checked);
    });

    connect(ui->chkNoReminder, &QCheckBox::toggled, this, [this](bool checked) {
        ui->editReminderDateTime->setEnabled(!checked);
    });

    // 預設提醒時間是停用的
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
