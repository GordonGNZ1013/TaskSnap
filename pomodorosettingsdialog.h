#ifndef POMODOROSETTINGSDIALOG_H
#define POMODOROSETTINGSDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>

class PomodoroSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PomodoroSettingsDialog(QWidget *parent = nullptr);

    // 設定目前的值
    void setWorkDuration(int minutes);
    void setShortBreakDuration(int minutes);
    void setLongBreakDuration(int minutes);
    void setCyclesBeforeLongBreak(int cycles);

    // 取得設定的值
    int workDuration() const;
    int shortBreakDuration() const;
    int longBreakDuration() const;
    int cyclesBeforeLongBreak() const;

private:
    QSpinBox *m_workSpinBox;
    QSpinBox *m_shortBreakSpinBox;
    QSpinBox *m_longBreakSpinBox;
    QSpinBox *m_cyclesSpinBox;

    void setupUI();
};

#endif // POMODOROSETTINGSDIALOG_H
