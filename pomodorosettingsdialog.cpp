#include "pomodorosettingsdialog.h"

PomodoroSettingsDialog::PomodoroSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
}

void PomodoroSettingsDialog::setupUI()
{
    setWindowTitle("⚙️ 番茄鐘設定");
    setFixedSize(350, 320);
    setStyleSheet(R"(
        QDialog {
            background-color: #f5f5f5;
        }
        QLabel {
            color: #2c3e50;
            font-size: 13px;
        }
        QSpinBox {
            padding: 8px;
            border: 1px solid #bdc3c7;
            border-radius: 5px;
            background-color: white;
            color: #2c3e50;
            font-size: 14px;
            min-width: 80px;
        }
        QSpinBox:focus {
            border: 2px solid #3498db;
        }
        QGroupBox {
            font-weight: bold;
            border: 1px solid #bdc3c7;
            border-radius: 5px;
            margin-top: 10px;
            padding-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 標題
    QLabel *titleLabel = new QLabel("🍅 番茄鐘時間設定");
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; padding-bottom: 10px;");
    mainLayout->addWidget(titleLabel);

    // 時間設定群組
    QGroupBox *timeGroup = new QGroupBox("時間設定（分鐘）");
    QVBoxLayout *timeLayout = new QVBoxLayout(timeGroup);
    timeLayout->setSpacing(12);

    // 工作時間
    QHBoxLayout *workLayout = new QHBoxLayout();
    QLabel *workLabel = new QLabel("🔴 工作時間：");
    workLabel->setMinimumWidth(120);
    m_workSpinBox = new QSpinBox();
    m_workSpinBox->setRange(1, 120);
    m_workSpinBox->setValue(25);
    m_workSpinBox->setSuffix(" 分鐘");
    workLayout->addWidget(workLabel);
    workLayout->addWidget(m_workSpinBox);
    workLayout->addStretch();
    timeLayout->addLayout(workLayout);

    // 短休息時間
    QHBoxLayout *shortBreakLayout = new QHBoxLayout();
    QLabel *shortBreakLabel = new QLabel("🟢 短休息時間：");
    shortBreakLabel->setMinimumWidth(120);
    m_shortBreakSpinBox = new QSpinBox();
    m_shortBreakSpinBox->setRange(1, 60);
    m_shortBreakSpinBox->setValue(5);
    m_shortBreakSpinBox->setSuffix(" 分鐘");
    shortBreakLayout->addWidget(shortBreakLabel);
    shortBreakLayout->addWidget(m_shortBreakSpinBox);
    shortBreakLayout->addStretch();
    timeLayout->addLayout(shortBreakLayout);

    // 長休息時間
    QHBoxLayout *longBreakLayout = new QHBoxLayout();
    QLabel *longBreakLabel = new QLabel("🔵 長休息時間：");
    longBreakLabel->setMinimumWidth(120);
    m_longBreakSpinBox = new QSpinBox();
    m_longBreakSpinBox->setRange(1, 60);
    m_longBreakSpinBox->setValue(15);
    m_longBreakSpinBox->setSuffix(" 分鐘");
    longBreakLayout->addWidget(longBreakLabel);
    longBreakLayout->addWidget(m_longBreakSpinBox);
    longBreakLayout->addStretch();
    timeLayout->addLayout(longBreakLayout);

    // 循環次數
    QHBoxLayout *cyclesLayout = new QHBoxLayout();
    QLabel *cyclesLabel = new QLabel("🔄 長休息間隔：");
    cyclesLabel->setMinimumWidth(120);
    m_cyclesSpinBox = new QSpinBox();
    m_cyclesSpinBox->setRange(1, 10);
    m_cyclesSpinBox->setValue(4);
    m_cyclesSpinBox->setSuffix(" 個番茄");
    cyclesLayout->addWidget(cyclesLabel);
    cyclesLayout->addWidget(m_cyclesSpinBox);
    cyclesLayout->addStretch();
    timeLayout->addLayout(cyclesLayout);

    mainLayout->addWidget(timeGroup);

    // 說明文字
    QLabel *infoLabel = new QLabel("💡 提示：完成設定的工作次數後會進入長休息");
    infoLabel->setStyleSheet("color: #7f8c8d; font-size: 11px;");
    infoLabel->setWordWrap(true);
    mainLayout->addWidget(infoLabel);

    mainLayout->addStretch();

    // 按鈕
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    QPushButton *cancelButton = new QPushButton("取消");
    cancelButton->setStyleSheet(R"(
        QPushButton {
            background-color: #95a5a6;
            color: white;
            border: none;
            padding: 10px 25px;
            font-size: 14px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #7f8c8d;
        }
        QPushButton:pressed {
            background-color: #6c7a7d;
        }
    )");
    cancelButton->setCursor(Qt::PointingHandCursor);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    QPushButton *saveButton = new QPushButton("儲存");
    saveButton->setStyleSheet(R"(
        QPushButton {
            background-color: #3498db;
            color: white;
            border: none;
            padding: 10px 25px;
            font-size: 14px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #2980b9;
        }
        QPushButton:pressed {
            background-color: #1f618d;
        }
    )");
    saveButton->setCursor(Qt::PointingHandCursor);
    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(saveButton);
    mainLayout->addLayout(buttonLayout);
}

void PomodoroSettingsDialog::setWorkDuration(int minutes)
{
    m_workSpinBox->setValue(minutes);
}

void PomodoroSettingsDialog::setShortBreakDuration(int minutes)
{
    m_shortBreakSpinBox->setValue(minutes);
}

void PomodoroSettingsDialog::setLongBreakDuration(int minutes)
{
    m_longBreakSpinBox->setValue(minutes);
}

void PomodoroSettingsDialog::setCyclesBeforeLongBreak(int cycles)
{
    m_cyclesSpinBox->setValue(cycles);
}

int PomodoroSettingsDialog::workDuration() const
{
    return m_workSpinBox->value();
}

int PomodoroSettingsDialog::shortBreakDuration() const
{
    return m_shortBreakSpinBox->value();
}

int PomodoroSettingsDialog::longBreakDuration() const
{
    return m_longBreakSpinBox->value();
}

int PomodoroSettingsDialog::cyclesBeforeLongBreak() const
{
    return m_cyclesSpinBox->value();
}
