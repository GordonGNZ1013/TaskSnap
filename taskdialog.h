#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include "task.h"

namespace Ui {
class TaskDialog;
}

class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskDialog(QWidget *parent = nullptr);
    ~TaskDialog();

    // 設定任務（編輯模式）
    void setTask(const Task &task);

    // 取得任務資料
    Task getTask() const;

public slots:
    void accept() override;  // 覆寫以驗證表單

private:
    Ui::TaskDialog *ui;
    int m_taskId = -1;  // -1 表示新任務
};

#endif // TASKDIALOG_H
