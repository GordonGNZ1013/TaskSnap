/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionNewTask;
    QAction *actionAbout;
    QAction *actionTestNotification;
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
    QWidget *leftPanel;
    QVBoxLayout *leftLayout;
    QLabel *logoLabel;
    QPushButton *btnAllTasks;
    QPushButton *btnToday;
    QPushButton *btnOverdue;
    QPushButton *btnCompleted;
    QSpacerItem *leftSpacer;
    QLabel *pomodoroTitle;
    QWidget *modeButtons;
    QHBoxLayout *modeButtonsLayout;
    QPushButton *btnPomodoroMode;
    QPushButton *btnStopwatchMode;
    QLabel *pomodoroPhaseLabel;
    QLabel *pomodoroTimeLabel;
    QWidget *pomodoroButtons;
    QGridLayout *pomodoroButtonsLayout;
    QPushButton *btnPomodoroStart;
    QPushButton *btnPomodoroPause;
    QPushButton *btnPomodoroReset;
    QPushButton *btnPomodoroSettings;
    QLabel *statsTitle;
    QLabel *lblTodayPomodoros;
    QLabel *lblTodayWorkTime;
    QLabel *lblTaskWorkTime;
    QSpacerItem *bottomSpacer;
    QWidget *centerPanel;
    QVBoxLayout *centerLayout;
    QWidget *headerWidget;
    QHBoxLayout *headerLayout;
    QLabel *taskListTitle;
    QSpacerItem *headerSpacer;
    QPushButton *btnAddTask;
    QListWidget *taskListWidget;
    QWidget *rightPanel;
    QVBoxLayout *rightLayout;
    QLabel *detailTitle;
    QLabel *lblDetailTaskTitle;
    QLabel *lblDetailDue;
    QLabel *lblDetailPriority;
    QLabel *lblDescTitle;
    QTextEdit *txtDetailDescription;
    QLabel *lblAttachTitle;
    QListWidget *attachmentListWidget;
    QPushButton *btnAddAttachment;
    QSpacerItem *rightSpacer;
    QWidget *actionButtons;
    QHBoxLayout *actionButtonsLayout;
    QPushButton *btnEditTask;
    QPushButton *btnCompleteTask;
    QPushButton *btnDeleteTask;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"    QMainWindow {\n"
"      background-color: #f5f5f5;\n"
"    }\n"
"   "));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionNewTask = new QAction(MainWindow);
        actionNewTask->setObjectName("actionNewTask");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionTestNotification = new QAction(MainWindow);
        actionTestNotification->setObjectName("actionTestNotification");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        leftPanel = new QWidget(centralwidget);
        leftPanel->setObjectName("leftPanel");
        leftPanel->setMinimumSize(QSize(260, 0));
        leftPanel->setMaximumSize(QSize(300, 16777215));
        leftPanel->setStyleSheet(QString::fromUtf8("\n"
"        QWidget#leftPanel {\n"
"          background-color: #2c3e50;\n"
"        }\n"
"        QLabel {\n"
"          color: white;\n"
"          font-size: 18px;\n"
"          padding: 10px;\n"
"        }\n"
"        QPushButton {\n"
"          background-color: transparent;\n"
"          color: white;\n"
"          border: none;\n"
"          text-align: left;\n"
"          padding: 18px 25px;\n"
"          font-size: 18px;\n"
"        }\n"
"        QPushButton:hover {\n"
"          background-color: #34495e;\n"
"        }\n"
"        QPushButton:checked {\n"
"          background-color: #3498db;\n"
"        }\n"
"       "));
        leftLayout = new QVBoxLayout(leftPanel);
        leftLayout->setSpacing(8);
        leftLayout->setObjectName("leftLayout");
        leftLayout->setContentsMargins(8, 0, 8, 8);
        logoLabel = new QLabel(leftPanel);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setStyleSheet(QString::fromUtf8("font-size: 24px; font-weight: bold; padding: 25px 10px;"));

        leftLayout->addWidget(logoLabel);

        btnAllTasks = new QPushButton(leftPanel);
        btnAllTasks->setObjectName("btnAllTasks");
        btnAllTasks->setCheckable(true);
        btnAllTasks->setChecked(true);
        btnAllTasks->setAutoExclusive(true);

        leftLayout->addWidget(btnAllTasks);

        btnToday = new QPushButton(leftPanel);
        btnToday->setObjectName("btnToday");
        btnToday->setCheckable(true);
        btnToday->setAutoExclusive(true);

        leftLayout->addWidget(btnToday);

        btnOverdue = new QPushButton(leftPanel);
        btnOverdue->setObjectName("btnOverdue");
        btnOverdue->setCheckable(true);
        btnOverdue->setAutoExclusive(true);

        leftLayout->addWidget(btnOverdue);

        btnCompleted = new QPushButton(leftPanel);
        btnCompleted->setObjectName("btnCompleted");
        btnCompleted->setCheckable(true);
        btnCompleted->setAutoExclusive(true);

        leftLayout->addWidget(btnCompleted);

        leftSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(leftSpacer);

        pomodoroTitle = new QLabel(leftPanel);
        pomodoroTitle->setObjectName("pomodoroTitle");
        pomodoroTitle->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; padding: 18px 25px 15px 25px; border-top: 1px solid #34495e;"));

        leftLayout->addWidget(pomodoroTitle);

        modeButtons = new QWidget(leftPanel);
        modeButtons->setObjectName("modeButtons");
        modeButtonsLayout = new QHBoxLayout(modeButtons);
        modeButtonsLayout->setSpacing(12);
        modeButtonsLayout->setObjectName("modeButtonsLayout");
        modeButtonsLayout->setContentsMargins(15, 0, 15, 0);
        btnPomodoroMode = new QPushButton(modeButtons);
        btnPomodoroMode->setObjectName("btnPomodoroMode");
        btnPomodoroMode->setCheckable(true);
        btnPomodoroMode->setChecked(true);
        btnPomodoroMode->setAutoExclusive(true);
        btnPomodoroMode->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #34495e; color: white; padding: 12px 15px; border-radius: 4px; font-size: 16px; font-weight: bold; } QPushButton:checked { background-color: #e74c3c; } QPushButton:hover { background-color: #4a6278; } QPushButton:checked:hover { background-color: #ec7063; }"));

        modeButtonsLayout->addWidget(btnPomodoroMode);

        btnStopwatchMode = new QPushButton(modeButtons);
        btnStopwatchMode->setObjectName("btnStopwatchMode");
        btnStopwatchMode->setCheckable(true);
        btnStopwatchMode->setAutoExclusive(true);
        btnStopwatchMode->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #34495e; color: white; padding: 12px 15px; border-radius: 4px; font-size: 16px; font-weight: bold; } QPushButton:checked { background-color: #3498db; } QPushButton:hover { background-color: #4a6278; } QPushButton:checked:hover { background-color: #5dade2; }"));

        modeButtonsLayout->addWidget(btnStopwatchMode);


        leftLayout->addWidget(modeButtons);

        pomodoroPhaseLabel = new QLabel(leftPanel);
        pomodoroPhaseLabel->setObjectName("pomodoroPhaseLabel");
        pomodoroPhaseLabel->setAlignment(Qt::AlignCenter);

        leftLayout->addWidget(pomodoroPhaseLabel);

        pomodoroTimeLabel = new QLabel(leftPanel);
        pomodoroTimeLabel->setObjectName("pomodoroTimeLabel");
        pomodoroTimeLabel->setStyleSheet(QString::fromUtf8("font-size: 56px; font-weight: bold; padding: 15px;"));
        pomodoroTimeLabel->setAlignment(Qt::AlignCenter);

        leftLayout->addWidget(pomodoroTimeLabel);

        pomodoroButtons = new QWidget(leftPanel);
        pomodoroButtons->setObjectName("pomodoroButtons");
        pomodoroButtonsLayout = new QGridLayout(pomodoroButtons);
        pomodoroButtonsLayout->setSpacing(10);
        pomodoroButtonsLayout->setObjectName("pomodoroButtonsLayout");
        pomodoroButtonsLayout->setContentsMargins(15, 0, 15, 0);
        btnPomodoroStart = new QPushButton(pomodoroButtons);
        btnPomodoroStart->setObjectName("btnPomodoroStart");
        btnPomodoroStart->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnPomodoroStart->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #27ae60; color: white; padding: 12px 8px; border-radius: 3px; font-size: 14px; font-weight: bold; } QPushButton:hover { background-color: #2ecc71; } QPushButton:pressed { background-color: #1e8449; }"));

        pomodoroButtonsLayout->addWidget(btnPomodoroStart, 0, 0, 1, 1);

        btnPomodoroPause = new QPushButton(pomodoroButtons);
        btnPomodoroPause->setObjectName("btnPomodoroPause");
        btnPomodoroPause->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnPomodoroPause->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #f39c12; color: white; padding: 12px 8px; border-radius: 3px; font-size: 14px; font-weight: bold; } QPushButton:hover { background-color: #f1c40f; } QPushButton:pressed { background-color: #d68910; }"));

        pomodoroButtonsLayout->addWidget(btnPomodoroPause, 0, 1, 1, 1);

        btnPomodoroReset = new QPushButton(pomodoroButtons);
        btnPomodoroReset->setObjectName("btnPomodoroReset");
        btnPomodoroReset->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnPomodoroReset->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #e74c3c; color: white; padding: 12px 8px; border-radius: 3px; font-size: 14px; font-weight: bold; } QPushButton:hover { background-color: #ec7063; } QPushButton:pressed { background-color: #c0392b; }"));

        pomodoroButtonsLayout->addWidget(btnPomodoroReset, 1, 0, 1, 1);

        btnPomodoroSettings = new QPushButton(pomodoroButtons);
        btnPomodoroSettings->setObjectName("btnPomodoroSettings");
        btnPomodoroSettings->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnPomodoroSettings->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #9b59b6; color: white; padding: 12px 8px; border-radius: 3px; font-size: 14px; font-weight: bold; } QPushButton:hover { background-color: #a569bd; } QPushButton:pressed { background-color: #7d3c98; }"));

        pomodoroButtonsLayout->addWidget(btnPomodoroSettings, 1, 1, 1, 1);


        leftLayout->addWidget(pomodoroButtons);

        statsTitle = new QLabel(leftPanel);
        statsTitle->setObjectName("statsTitle");
        statsTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; padding: 18px 25px 12px 25px; border-top: 1px solid #34495e;"));

        leftLayout->addWidget(statsTitle);

        lblTodayPomodoros = new QLabel(leftPanel);
        lblTodayPomodoros->setObjectName("lblTodayPomodoros");
        lblTodayPomodoros->setStyleSheet(QString::fromUtf8("font-size: 16px; padding: 8px 25px;"));

        leftLayout->addWidget(lblTodayPomodoros);

        lblTodayWorkTime = new QLabel(leftPanel);
        lblTodayWorkTime->setObjectName("lblTodayWorkTime");
        lblTodayWorkTime->setStyleSheet(QString::fromUtf8("font-size: 16px; padding: 8px 25px;"));

        leftLayout->addWidget(lblTodayWorkTime);

        lblTaskWorkTime = new QLabel(leftPanel);
        lblTaskWorkTime->setObjectName("lblTaskWorkTime");
        lblTaskWorkTime->setStyleSheet(QString::fromUtf8("font-size: 16px; padding: 8px 25px;"));

        leftLayout->addWidget(lblTaskWorkTime);

        bottomSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        leftLayout->addItem(bottomSpacer);


        mainLayout->addWidget(leftPanel);

        centerPanel = new QWidget(centralwidget);
        centerPanel->setObjectName("centerPanel");
        centerPanel->setStyleSheet(QString::fromUtf8("\n"
"        QWidget#centerPanel {\n"
"          background-color: #ecf0f1;\n"
"        }\n"
"       "));
        centerLayout = new QVBoxLayout(centerPanel);
        centerLayout->setObjectName("centerLayout");
        centerLayout->setContentsMargins(15, 15, 15, 0);
        headerWidget = new QWidget(centerPanel);
        headerWidget->setObjectName("headerWidget");
        headerLayout = new QHBoxLayout(headerWidget);
        headerLayout->setObjectName("headerLayout");
        headerLayout->setContentsMargins(0, 0, 0, 0);
        taskListTitle = new QLabel(headerWidget);
        taskListTitle->setObjectName("taskListTitle");
        taskListTitle->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #2c3e50;"));

        headerLayout->addWidget(taskListTitle);

        headerSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(headerSpacer);

        btnAddTask = new QPushButton(headerWidget);
        btnAddTask->setObjectName("btnAddTask");
        btnAddTask->setStyleSheet(QString::fromUtf8("\n"
"              QPushButton {\n"
"                background-color: #3498db;\n"
"                color: white;\n"
"                border: none;\n"
"                padding: 10px 20px;\n"
"                font-size: 14px;\n"
"                border-radius: 5px;\n"
"              }\n"
"              QPushButton:hover {\n"
"                background-color: #2980b9;\n"
"              }\n"
"             "));

        headerLayout->addWidget(btnAddTask);


        centerLayout->addWidget(headerWidget);

        taskListWidget = new QListWidget(centerPanel);
        taskListWidget->setObjectName("taskListWidget");
        taskListWidget->setStyleSheet(QString::fromUtf8("\n"
"           QListWidget {\n"
"             background-color: white;\n"
"             border: 1px solid #bdc3c7;\n"
"             border-radius: 5px;\n"
"             padding: 5px;\n"
"           }\n"
"           QListWidget::item {\n"
"             padding: 15px;\n"
"             border-bottom: 1px solid #ecf0f1;\n"
"           }\n"
"           QListWidget::item:selected {\n"
"             background-color: #e8f4fc;\n"
"             color: #2c3e50;\n"
"           }\n"
"           QListWidget::item:hover {\n"
"             background-color: #f8f9fa;\n"
"           }\n"
"          "));
        taskListWidget->setAlternatingRowColors(false);

        centerLayout->addWidget(taskListWidget);


        mainLayout->addWidget(centerPanel);

        rightPanel = new QWidget(centralwidget);
        rightPanel->setObjectName("rightPanel");
        rightPanel->setMinimumSize(QSize(380, 0));
        rightPanel->setMaximumSize(QSize(450, 16777215));
        rightPanel->setStyleSheet(QString::fromUtf8("\n"
"        QWidget#rightPanel {\n"
"          background-color: white;\n"
"          border-left: 1px solid #bdc3c7;\n"
"        }\n"
"        QLabel {\n"
"          color: #2c3e50;\n"
"        }\n"
"       "));
        rightLayout = new QVBoxLayout(rightPanel);
        rightLayout->setObjectName("rightLayout");
        rightLayout->setContentsMargins(15, 15, 15, 0);
        detailTitle = new QLabel(rightPanel);
        detailTitle->setObjectName("detailTitle");
        detailTitle->setStyleSheet(QString::fromUtf8("font-size: 18px; font-weight: bold; padding-bottom: 10px; border-bottom: 1px solid #ecf0f1;"));

        rightLayout->addWidget(detailTitle);

        lblDetailTaskTitle = new QLabel(rightPanel);
        lblDetailTaskTitle->setObjectName("lblDetailTaskTitle");
        lblDetailTaskTitle->setStyleSheet(QString::fromUtf8("font-size: 16px; font-weight: bold; padding-top: 15px;"));
        lblDetailTaskTitle->setWordWrap(true);

        rightLayout->addWidget(lblDetailTaskTitle);

        lblDetailDue = new QLabel(rightPanel);
        lblDetailDue->setObjectName("lblDetailDue");
        lblDetailDue->setStyleSheet(QString::fromUtf8("color: #7f8c8d; padding-top: 5px;"));

        rightLayout->addWidget(lblDetailDue);

        lblDetailPriority = new QLabel(rightPanel);
        lblDetailPriority->setObjectName("lblDetailPriority");
        lblDetailPriority->setStyleSheet(QString::fromUtf8("padding-top: 5px;"));

        rightLayout->addWidget(lblDetailPriority);

        lblDescTitle = new QLabel(rightPanel);
        lblDescTitle->setObjectName("lblDescTitle");
        lblDescTitle->setStyleSheet(QString::fromUtf8("font-weight: bold; padding-top: 15px;"));

        rightLayout->addWidget(lblDescTitle);

        txtDetailDescription = new QTextEdit(rightPanel);
        txtDetailDescription->setObjectName("txtDetailDescription");
        txtDetailDescription->setReadOnly(true);
        txtDetailDescription->setStyleSheet(QString::fromUtf8("\n"
"           QTextEdit {\n"
"             background-color: #f8f9fa;\n"
"             border: 1px solid #ecf0f1;\n"
"             border-radius: 5px;\n"
"             padding: 10px;\n"
"           }\n"
"          "));
        txtDetailDescription->setMaximumSize(QSize(16777215, 120));

        rightLayout->addWidget(txtDetailDescription);

        lblAttachTitle = new QLabel(rightPanel);
        lblAttachTitle->setObjectName("lblAttachTitle");
        lblAttachTitle->setStyleSheet(QString::fromUtf8("font-weight: bold; padding-top: 15px;"));

        rightLayout->addWidget(lblAttachTitle);

        attachmentListWidget = new QListWidget(rightPanel);
        attachmentListWidget->setObjectName("attachmentListWidget");
        attachmentListWidget->setMinimumSize(QSize(0, 120));
        attachmentListWidget->setMaximumSize(QSize(16777215, 250));
        attachmentListWidget->setStyleSheet(QString::fromUtf8("\n"
"           QListWidget {\n"
"             background-color: white;\n"
"             border: 1px solid #bdc3c7;\n"
"             border-radius: 5px;\n"
"             padding: 8px;\n"
"           }\n"
"           QListWidget::item {\n"
"             padding: 15px;\n"
"             border-bottom: 1px solid #ecf0f1;\n"
"             color: #2c3e50;\n"
"             background-color: white;\n"
"           }\n"
"           QListWidget::item:selected {\n"
"             background-color: #e8f4fc;\n"
"             color: #2c3e50;\n"
"           }\n"
"           QListWidget::item:hover {\n"
"             background-color: #f8f9fa;\n"
"           }\n"
"          "));

        rightLayout->addWidget(attachmentListWidget);

        btnAddAttachment = new QPushButton(rightPanel);
        btnAddAttachment->setObjectName("btnAddAttachment");
        btnAddAttachment->setStyleSheet(QString::fromUtf8("\n"
"           QPushButton {\n"
"             background-color: #95a5a6;\n"
"             color: white;\n"
"             border: none;\n"
"             padding: 8px;\n"
"             border-radius: 3px;\n"
"           }\n"
"           QPushButton:hover {\n"
"             background-color: #7f8c8d;\n"
"           }\n"
"          "));

        rightLayout->addWidget(btnAddAttachment);

        rightSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(rightSpacer);

        actionButtons = new QWidget(rightPanel);
        actionButtons->setObjectName("actionButtons");
        actionButtonsLayout = new QHBoxLayout(actionButtons);
        actionButtonsLayout->setObjectName("actionButtonsLayout");
        actionButtonsLayout->setContentsMargins(0, 0, 0, 0);
        btnEditTask = new QPushButton(actionButtons);
        btnEditTask->setObjectName("btnEditTask");
        btnEditTask->setStyleSheet(QString::fromUtf8("\n"
"              QPushButton {\n"
"                background-color: #3498db;\n"
"                color: white;\n"
"                border: none;\n"
"                padding: 10px 15px;\n"
"                border-radius: 5px;\n"
"              }\n"
"              QPushButton:hover {\n"
"                background-color: #2980b9;\n"
"              }\n"
"             "));

        actionButtonsLayout->addWidget(btnEditTask);

        btnCompleteTask = new QPushButton(actionButtons);
        btnCompleteTask->setObjectName("btnCompleteTask");
        btnCompleteTask->setStyleSheet(QString::fromUtf8("\n"
"              QPushButton {\n"
"                background-color: #27ae60;\n"
"                color: white;\n"
"                border: none;\n"
"                padding: 10px 15px;\n"
"                border-radius: 5px;\n"
"              }\n"
"              QPushButton:hover {\n"
"                background-color: #219a52;\n"
"              }\n"
"             "));

        actionButtonsLayout->addWidget(btnCompleteTask);

        btnDeleteTask = new QPushButton(actionButtons);
        btnDeleteTask->setObjectName("btnDeleteTask");
        btnDeleteTask->setStyleSheet(QString::fromUtf8("\n"
"              QPushButton {\n"
"                background-color: #e74c3c;\n"
"                color: white;\n"
"                border: none;\n"
"                padding: 10px 15px;\n"
"                border-radius: 5px;\n"
"              }\n"
"              QPushButton:hover {\n"
"                background-color: #c0392b;\n"
"              }\n"
"             "));

        actionButtonsLayout->addWidget(btnDeleteTask);


        rightLayout->addWidget(actionButtons);


        mainLayout->addWidget(rightPanel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionNewTask);
        menuHelp->addAction(actionAbout);
        menuHelp->addSeparator();
        menuHelp->addAction(actionTestNotification);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\260\210\346\241\210\345\260\217\345\271\253\346\211\213 - \344\273\273\345\213\231\347\256\241\347\220\206", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\233\242\351\226\213(&X)", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNewTask->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\242\236\344\273\273\345\213\231(&N)", nullptr));
#if QT_CONFIG(shortcut)
        actionNewTask->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\351\227\234\346\226\274(&A)", nullptr));
        actionTestNotification->setText(QCoreApplication::translate("MainWindow", "\346\270\254\350\251\246\351\200\232\347\237\245(&T)", nullptr));
        logoLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\223\213 \345\260\210\346\241\210\345\260\217\345\271\253\346\211\213", nullptr));
        btnAllTasks->setText(QCoreApplication::translate("MainWindow", "\360\237\223\201 \346\211\200\346\234\211\344\273\273\345\213\231", nullptr));
        btnToday->setText(QCoreApplication::translate("MainWindow", "\360\237\223\205 \344\273\212\345\244\251", nullptr));
        btnOverdue->setText(QCoreApplication::translate("MainWindow", "\342\232\240\357\270\217 \345\267\262\351\201\216\346\234\237", nullptr));
        btnCompleted->setText(QCoreApplication::translate("MainWindow", "\342\234\205 \345\267\262\345\256\214\346\210\220", nullptr));
        pomodoroTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\215\205 \347\225\252\350\214\204\351\220\230", nullptr));
        btnPomodoroMode->setText(QCoreApplication::translate("MainWindow", "\360\237\215\205 \347\225\252\350\214\204\351\220\230", nullptr));
#if QT_CONFIG(tooltip)
        btnPomodoroMode->setToolTip(QCoreApplication::translate("MainWindow", "\347\225\252\350\214\204\351\220\230\346\250\241\345\274\217", nullptr));
#endif // QT_CONFIG(tooltip)
        btnStopwatchMode->setText(QCoreApplication::translate("MainWindow", "\342\217\261 \347\242\274\351\214\266", nullptr));
#if QT_CONFIG(tooltip)
        btnStopwatchMode->setToolTip(QCoreApplication::translate("MainWindow", "\347\242\274\351\214\266\346\250\241\345\274\217", nullptr));
#endif // QT_CONFIG(tooltip)
        pomodoroPhaseLabel->setText(QCoreApplication::translate("MainWindow", "\345\267\245\344\275\234\344\270\255", nullptr));
        pomodoroTimeLabel->setText(QCoreApplication::translate("MainWindow", "25:00", nullptr));
        btnPomodoroStart->setText(QCoreApplication::translate("MainWindow", "\342\226\266 \351\226\213\345\247\213", nullptr));
#if QT_CONFIG(tooltip)
        btnPomodoroStart->setToolTip(QCoreApplication::translate("MainWindow", "\351\226\213\345\247\213\350\250\210\346\231\202", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPomodoroPause->setText(QCoreApplication::translate("MainWindow", "\342\217\270 \346\232\253\345\201\234", nullptr));
#if QT_CONFIG(tooltip)
        btnPomodoroPause->setToolTip(QCoreApplication::translate("MainWindow", "\346\232\253\345\201\234\350\250\210\346\231\202", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPomodoroReset->setText(QCoreApplication::translate("MainWindow", "\342\206\272 \351\207\215\350\250\255", nullptr));
#if QT_CONFIG(tooltip)
        btnPomodoroReset->setToolTip(QCoreApplication::translate("MainWindow", "\351\207\215\350\250\255\350\250\210\346\231\202\345\231\250", nullptr));
#endif // QT_CONFIG(tooltip)
        btnPomodoroSettings->setText(QCoreApplication::translate("MainWindow", "\342\232\231 \350\250\255\345\256\232", nullptr));
#if QT_CONFIG(tooltip)
        btnPomodoroSettings->setToolTip(QCoreApplication::translate("MainWindow", "\350\250\210\346\231\202\345\231\250\350\250\255\345\256\232", nullptr));
#endif // QT_CONFIG(tooltip)
        statsTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 \344\273\212\346\227\245\347\265\261\350\250\210", nullptr));
        lblTodayPomodoros->setText(QCoreApplication::translate("MainWindow", "\360\237\215\205 \345\256\214\346\210\220: 0 \345\200\213", nullptr));
        lblTodayWorkTime->setText(QCoreApplication::translate("MainWindow", "\342\217\261\357\270\217 \345\267\245\346\231\202: 0:00:00", nullptr));
        lblTaskWorkTime->setText(QCoreApplication::translate("MainWindow", "\360\237\223\213 \344\273\273\345\213\231: --", nullptr));
        taskListTitle->setText(QCoreApplication::translate("MainWindow", "\346\211\200\346\234\211\344\273\273\345\213\231", nullptr));
        btnAddTask->setText(QCoreApplication::translate("MainWindow", "+ \346\226\260\345\242\236\344\273\273\345\213\231", nullptr));
        detailTitle->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\213\231\350\251\263\346\203\205", nullptr));
        lblDetailTaskTitle->setText(QCoreApplication::translate("MainWindow", "\351\201\270\346\223\207\344\270\200\345\200\213\344\273\273\345\213\231\346\237\245\347\234\213\350\251\263\346\203\205", nullptr));
        lblDetailDue->setText(QString());
        lblDetailPriority->setText(QString());
        lblDescTitle->setText(QCoreApplication::translate("MainWindow", "\346\217\217\350\277\260", nullptr));
        lblAttachTitle->setText(QCoreApplication::translate("MainWindow", "\360\237\223\216 \351\231\204\344\273\266", nullptr));
        btnAddAttachment->setText(QCoreApplication::translate("MainWindow", "+ \346\226\260\345\242\236\351\231\204\344\273\266", nullptr));
        btnEditTask->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 \347\267\250\350\274\257", nullptr));
        btnCompleteTask->setText(QCoreApplication::translate("MainWindow", "\342\234\205 \345\256\214\346\210\220", nullptr));
        btnDeleteTask->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 \345\210\252\351\231\244", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\252\224\346\241\210(&F)", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "\347\267\250\350\274\257(&E)", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\350\252\252\346\230\216(&H)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
