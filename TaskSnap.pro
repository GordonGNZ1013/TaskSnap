QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 應用程式名稱（編譯時用英文避免編碼問題）
TARGET = ProjectHelper

# Windows 專用：連結 winmm 庫（用於 PlaySound）
win32: LIBS += -lwinmm

# 原始碼檔案
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    database.cpp \
    taskdialog.cpp \
    pomodorotimer.cpp \
    pomodorosettingsdialog.cpp \
    notificationmanager.cpp \
    snapshotmanager.cpp \
    workstats.cpp \
    pomodoroconfig.cpp \
    calendardialog.cpp

# 標頭檔
HEADERS += \
    mainwindow.h \
    database.h \
    task.h \
    taskdialog.h \
    pomodorotimer.h \
    pomodorosettingsdialog.h \
    notificationmanager.h \
    snapshotmanager.h \
    workstats.h \
    pomodoroconfig.h \
    calendardialog.h

# UI 表單檔
FORMS += \
    mainwindow.ui \
    taskdialog.ui

# 資源檔
RESOURCES += \
    resources.qrc

# 預設部署規則
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
