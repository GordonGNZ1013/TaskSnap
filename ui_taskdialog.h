/********************************************************************************
** Form generated from reading UI file 'taskdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKDIALOG_H
#define UI_TASKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskDialog
{
public:
    QVBoxLayout *mainLayout;
    QLabel *dialogTitle;
    QLabel *lblTitle;
    QLineEdit *editTitle;
    QLabel *lblDescription;
    QTextEdit *editDescription;
    QWidget *dateTimeRow;
    QHBoxLayout *dateTimeLayout;
    QWidget *dueDateWidget;
    QVBoxLayout *dueDateLayout;
    QLabel *lblDueDate;
    QDateTimeEdit *editDueDateTime;
    QCheckBox *chkNoDueDate;
    QWidget *reminderWidget;
    QVBoxLayout *reminderLayout;
    QLabel *lblReminder;
    QDateTimeEdit *editReminderDateTime;
    QCheckBox *chkNoReminder;
    QWidget *priorityTagRow;
    QHBoxLayout *priorityTagLayout;
    QWidget *priorityWidget;
    QVBoxLayout *priorityLayout;
    QLabel *lblPriority;
    QComboBox *comboPriority;
    QWidget *tagWidget;
    QVBoxLayout *tagLayout;
    QLabel *lblTags;
    QLineEdit *editTags;
    QSpacerItem *verticalSpacer;
    QWidget *buttonWidget;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *btnCancel;
    QPushButton *btnSave;

    void setupUi(QDialog *TaskDialog)
    {
        if (TaskDialog->objectName().isEmpty())
            TaskDialog->setObjectName("TaskDialog");
        TaskDialog->resize(500, 500);
        TaskDialog->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"      background-color: #f5f5f5;\n"
"    }\n"
"    QLabel {\n"
"      color: #2c3e50;\n"
"      font-size: 13px;\n"
"    }\n"
"    QLineEdit, QTextEdit, QDateTimeEdit, QComboBox {\n"
"      padding: 8px;\n"
"      border: 1px solid #bdc3c7;\n"
"      border-radius: 5px;\n"
"      background-color: white;\n"
"      color: #2c3e50;\n"
"      font-size: 13px;\n"
"    }\n"
"    QLineEdit:focus, QTextEdit:focus, QDateTimeEdit:focus, QComboBox:focus {\n"
"      border: 2px solid #3498db;\n"
"    }\n"
"    QLineEdit:disabled, QTextEdit:disabled, QDateTimeEdit:disabled {\n"
"      background-color: #ecf0f1;\n"
"      color: #95a5a6;\n"
"    }\n"
"    QCheckBox {\n"
"      color: #2c3e50;\n"
"      font-size: 12px;\n"
"      spacing: 8px;\n"
"    }\n"
"    QCheckBox::indicator {\n"
"      width: 18px;\n"
"      height: 18px;\n"
"    }\n"
"   "));
        mainLayout = new QVBoxLayout(TaskDialog);
        mainLayout->setSpacing(15);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(20, 20, 20, 20);
        dialogTitle = new QLabel(TaskDialog);
        dialogTitle->setObjectName("dialogTitle");
        dialogTitle->setStyleSheet(QString::fromUtf8("font-size: 20px; font-weight: bold; color: #2c3e50; padding-bottom: 10px;"));

        mainLayout->addWidget(dialogTitle);

        lblTitle = new QLabel(TaskDialog);
        lblTitle->setObjectName("lblTitle");
        lblTitle->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        mainLayout->addWidget(lblTitle);

        editTitle = new QLineEdit(TaskDialog);
        editTitle->setObjectName("editTitle");

        mainLayout->addWidget(editTitle);

        lblDescription = new QLabel(TaskDialog);
        lblDescription->setObjectName("lblDescription");
        lblDescription->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        mainLayout->addWidget(lblDescription);

        editDescription = new QTextEdit(TaskDialog);
        editDescription->setObjectName("editDescription");
        editDescription->setMaximumSize(QSize(16777215, 100));

        mainLayout->addWidget(editDescription);

        dateTimeRow = new QWidget(TaskDialog);
        dateTimeRow->setObjectName("dateTimeRow");
        dateTimeLayout = new QHBoxLayout(dateTimeRow);
        dateTimeLayout->setSpacing(20);
        dateTimeLayout->setObjectName("dateTimeLayout");
        dateTimeLayout->setContentsMargins(0, 0, 0, 0);
        dueDateWidget = new QWidget(dateTimeRow);
        dueDateWidget->setObjectName("dueDateWidget");
        dueDateLayout = new QVBoxLayout(dueDateWidget);
        dueDateLayout->setSpacing(5);
        dueDateLayout->setObjectName("dueDateLayout");
        dueDateLayout->setContentsMargins(0, 0, 0, 0);
        lblDueDate = new QLabel(dueDateWidget);
        lblDueDate->setObjectName("lblDueDate");
        lblDueDate->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        dueDateLayout->addWidget(lblDueDate);

        editDueDateTime = new QDateTimeEdit(dueDateWidget);
        editDueDateTime->setObjectName("editDueDateTime");
        editDueDateTime->setCalendarPopup(true);

        dueDateLayout->addWidget(editDueDateTime);

        chkNoDueDate = new QCheckBox(dueDateWidget);
        chkNoDueDate->setObjectName("chkNoDueDate");

        dueDateLayout->addWidget(chkNoDueDate);


        dateTimeLayout->addWidget(dueDateWidget);

        reminderWidget = new QWidget(dateTimeRow);
        reminderWidget->setObjectName("reminderWidget");
        reminderLayout = new QVBoxLayout(reminderWidget);
        reminderLayout->setSpacing(5);
        reminderLayout->setObjectName("reminderLayout");
        reminderLayout->setContentsMargins(0, 0, 0, 0);
        lblReminder = new QLabel(reminderWidget);
        lblReminder->setObjectName("lblReminder");
        lblReminder->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        reminderLayout->addWidget(lblReminder);

        editReminderDateTime = new QDateTimeEdit(reminderWidget);
        editReminderDateTime->setObjectName("editReminderDateTime");
        editReminderDateTime->setCalendarPopup(true);

        reminderLayout->addWidget(editReminderDateTime);

        chkNoReminder = new QCheckBox(reminderWidget);
        chkNoReminder->setObjectName("chkNoReminder");
        chkNoReminder->setChecked(true);

        reminderLayout->addWidget(chkNoReminder);


        dateTimeLayout->addWidget(reminderWidget);


        mainLayout->addWidget(dateTimeRow);

        priorityTagRow = new QWidget(TaskDialog);
        priorityTagRow->setObjectName("priorityTagRow");
        priorityTagLayout = new QHBoxLayout(priorityTagRow);
        priorityTagLayout->setSpacing(20);
        priorityTagLayout->setObjectName("priorityTagLayout");
        priorityTagLayout->setContentsMargins(0, 0, 0, 0);
        priorityWidget = new QWidget(priorityTagRow);
        priorityWidget->setObjectName("priorityWidget");
        priorityLayout = new QVBoxLayout(priorityWidget);
        priorityLayout->setSpacing(5);
        priorityLayout->setObjectName("priorityLayout");
        priorityLayout->setContentsMargins(0, 0, 0, 0);
        lblPriority = new QLabel(priorityWidget);
        lblPriority->setObjectName("lblPriority");
        lblPriority->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        priorityLayout->addWidget(lblPriority);

        comboPriority = new QComboBox(priorityWidget);
        comboPriority->addItem(QString());
        comboPriority->addItem(QString());
        comboPriority->addItem(QString());
        comboPriority->setObjectName("comboPriority");

        priorityLayout->addWidget(comboPriority);


        priorityTagLayout->addWidget(priorityWidget);

        tagWidget = new QWidget(priorityTagRow);
        tagWidget->setObjectName("tagWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tagWidget->sizePolicy().hasHeightForWidth());
        tagWidget->setSizePolicy(sizePolicy);
        tagLayout = new QVBoxLayout(tagWidget);
        tagLayout->setSpacing(5);
        tagLayout->setObjectName("tagLayout");
        tagLayout->setContentsMargins(0, 0, 0, 0);
        lblTags = new QLabel(tagWidget);
        lblTags->setObjectName("lblTags");
        lblTags->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        tagLayout->addWidget(lblTags);

        editTags = new QLineEdit(tagWidget);
        editTags->setObjectName("editTags");

        tagLayout->addWidget(editTags);


        priorityTagLayout->addWidget(tagWidget);


        mainLayout->addWidget(priorityTagRow);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        mainLayout->addItem(verticalSpacer);

        buttonWidget = new QWidget(TaskDialog);
        buttonWidget->setObjectName("buttonWidget");
        buttonLayout = new QHBoxLayout(buttonWidget);
        buttonLayout->setSpacing(10);
        buttonLayout->setObjectName("buttonLayout");
        buttonLayout->setContentsMargins(0, 0, 0, 0);
        buttonSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        btnCancel = new QPushButton(buttonWidget);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setStyleSheet(QString::fromUtf8("\n"
"          QPushButton {\n"
"            background-color: #95a5a6;\n"
"            color: white;\n"
"            border: none;\n"
"            padding: 10px 25px;\n"
"            font-size: 14px;\n"
"            border-radius: 5px;\n"
"          }\n"
"          QPushButton:hover {\n"
"            background-color: #7f8c8d;\n"
"          }\n"
"         "));

        buttonLayout->addWidget(btnCancel);

        btnSave = new QPushButton(buttonWidget);
        btnSave->setObjectName("btnSave");
        btnSave->setStyleSheet(QString::fromUtf8("\n"
"          QPushButton {\n"
"            background-color: #3498db;\n"
"            color: white;\n"
"            border: none;\n"
"            padding: 10px 25px;\n"
"            font-size: 14px;\n"
"            border-radius: 5px;\n"
"          }\n"
"          QPushButton:hover {\n"
"            background-color: #2980b9;\n"
"          }\n"
"         "));

        buttonLayout->addWidget(btnSave);


        mainLayout->addWidget(buttonWidget);


        retranslateUi(TaskDialog);
        QObject::connect(btnCancel, &QPushButton::clicked, TaskDialog, qOverload<>(&QDialog::reject));
        QObject::connect(btnSave, &QPushButton::clicked, TaskDialog, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(TaskDialog);
    } // setupUi

    void retranslateUi(QDialog *TaskDialog)
    {
        TaskDialog->setWindowTitle(QCoreApplication::translate("TaskDialog", "\344\273\273\345\213\231", nullptr));
        dialogTitle->setText(QCoreApplication::translate("TaskDialog", "\346\226\260\345\242\236\344\273\273\345\213\231", nullptr));
        lblTitle->setText(QCoreApplication::translate("TaskDialog", "\346\250\231\351\241\214 *", nullptr));
        editTitle->setPlaceholderText(QCoreApplication::translate("TaskDialog", "\350\274\270\345\205\245\344\273\273\345\213\231\346\250\231\351\241\214...", nullptr));
        lblDescription->setText(QCoreApplication::translate("TaskDialog", "\346\217\217\350\277\260", nullptr));
        editDescription->setPlaceholderText(QCoreApplication::translate("TaskDialog", "\350\274\270\345\205\245\344\273\273\345\213\231\346\217\217\350\277\260...", nullptr));
        lblDueDate->setText(QCoreApplication::translate("TaskDialog", "\360\237\223\205 \346\210\252\346\255\242\346\227\245\346\234\237", nullptr));
        editDueDateTime->setDisplayFormat(QCoreApplication::translate("TaskDialog", "yyyy/MM/dd HH:mm", nullptr));
        chkNoDueDate->setText(QCoreApplication::translate("TaskDialog", "\347\204\241\346\210\252\346\255\242\346\227\245\346\234\237", nullptr));
        lblReminder->setText(QCoreApplication::translate("TaskDialog", "\342\217\260 \346\217\220\351\206\222\346\231\202\351\226\223", nullptr));
        editReminderDateTime->setDisplayFormat(QCoreApplication::translate("TaskDialog", "yyyy/MM/dd HH:mm", nullptr));
        chkNoReminder->setText(QCoreApplication::translate("TaskDialog", "\344\270\215\350\250\255\345\256\232\346\217\220\351\206\222", nullptr));
        lblPriority->setText(QCoreApplication::translate("TaskDialog", "\342\255\220 \345\204\252\345\205\210\347\264\232", nullptr));
        comboPriority->setItemText(0, QCoreApplication::translate("TaskDialog", "\344\275\216", nullptr));
        comboPriority->setItemText(1, QCoreApplication::translate("TaskDialog", "\344\270\255", nullptr));
        comboPriority->setItemText(2, QCoreApplication::translate("TaskDialog", "\351\253\230", nullptr));

        lblTags->setText(QCoreApplication::translate("TaskDialog", "\360\237\217\267\357\270\217 \346\250\231\347\261\244", nullptr));
        editTags->setPlaceholderText(QCoreApplication::translate("TaskDialog", "\345\267\245\344\275\234, \345\255\270\347\277\222, \347\224\237\346\264\273\357\274\210\351\200\227\350\231\237\345\210\206\351\232\224\357\274\211", nullptr));
        btnCancel->setText(QCoreApplication::translate("TaskDialog", "\345\217\226\346\266\210", nullptr));
        btnSave->setText(QCoreApplication::translate("TaskDialog", "\345\204\262\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TaskDialog: public Ui_TaskDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKDIALOG_H
