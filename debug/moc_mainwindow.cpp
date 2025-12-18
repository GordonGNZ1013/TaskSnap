/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QTwondor/TaskSnap/mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onAddTask",
        "",
        "onEditTask",
        "onDeleteTask",
        "onTaskCompleted",
        "onTaskSelected",
        "row",
        "onFilterAll",
        "onFilterToday",
        "onFilterOverdue",
        "onFilterCompleted",
        "onAddAttachment",
        "onDeleteAttachment",
        "onOpenAttachment",
        "onPomodoroStart",
        "onPomodoroPause",
        "onPomodoroReset",
        "onPomodoroSettings",
        "onPomodoroTick",
        "seconds",
        "onPhaseChanged",
        "PomodoroTimer::Phase",
        "phase",
        "onPomodoroCompleted",
        "onModeChanged",
        "PomodoroTimer::Mode",
        "mode",
        "onTrayIconActivated",
        "QSystemTrayIcon::ActivationReason",
        "reason",
        "showWindow"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onAddTask'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onEditTask'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDeleteTask'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTaskCompleted'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTaskSelected'
        QtMocHelpers::SlotData<void(int)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Slot 'onFilterAll'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFilterToday'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFilterOverdue'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onFilterCompleted'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddAttachment'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDeleteAttachment'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onOpenAttachment'
        QtMocHelpers::SlotData<void(int)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Slot 'onPomodoroStart'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPomodoroPause'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPomodoroReset'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPomodoroSettings'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPomodoroTick'
        QtMocHelpers::SlotData<void(int)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 20 },
        }}),
        // Slot 'onPhaseChanged'
        QtMocHelpers::SlotData<void(PomodoroTimer::Phase)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 22, 23 },
        }}),
        // Slot 'onPomodoroCompleted'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onModeChanged'
        QtMocHelpers::SlotData<void(PomodoroTimer::Mode)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 26, 27 },
        }}),
        // Slot 'onTrayIconActivated'
        QtMocHelpers::SlotData<void(QSystemTrayIcon::ActivationReason)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 29, 30 },
        }}),
        // Slot 'showWindow'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onAddTask(); break;
        case 1: _t->onEditTask(); break;
        case 2: _t->onDeleteTask(); break;
        case 3: _t->onTaskCompleted(); break;
        case 4: _t->onTaskSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->onFilterAll(); break;
        case 6: _t->onFilterToday(); break;
        case 7: _t->onFilterOverdue(); break;
        case 8: _t->onFilterCompleted(); break;
        case 9: _t->onAddAttachment(); break;
        case 10: _t->onDeleteAttachment(); break;
        case 11: _t->onOpenAttachment((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->onPomodoroStart(); break;
        case 13: _t->onPomodoroPause(); break;
        case 14: _t->onPomodoroReset(); break;
        case 15: _t->onPomodoroSettings(); break;
        case 16: _t->onPomodoroTick((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->onPhaseChanged((*reinterpret_cast< std::add_pointer_t<PomodoroTimer::Phase>>(_a[1]))); break;
        case 18: _t->onPomodoroCompleted(); break;
        case 19: _t->onModeChanged((*reinterpret_cast< std::add_pointer_t<PomodoroTimer::Mode>>(_a[1]))); break;
        case 20: _t->onTrayIconActivated((*reinterpret_cast< std::add_pointer_t<QSystemTrayIcon::ActivationReason>>(_a[1]))); break;
        case 21: _t->showWindow(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
