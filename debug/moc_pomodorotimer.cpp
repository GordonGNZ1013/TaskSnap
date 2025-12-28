/****************************************************************************
** Meta object code from reading C++ file 'pomodorotimer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pomodorotimer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pomodorotimer.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13PomodoroTimerE_t {};
} // unnamed namespace

template <> constexpr inline auto PomodoroTimer::qt_create_metaobjectdata<qt_meta_tag_ZN13PomodoroTimerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PomodoroTimer",
        "tick",
        "",
        "seconds",
        "phaseChanged",
        "Phase",
        "newPhase",
        "pomodoroCompleted",
        "modeChanged",
        "Mode",
        "newMode",
        "workSessionRecorded",
        "onTick",
        "PomodoroMode",
        "StopwatchMode",
        "Work",
        "ShortBreak",
        "LongBreak"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'tick'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Signal 'phaseChanged'
        QtMocHelpers::SignalData<void(Phase)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Signal 'pomodoroCompleted'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'modeChanged'
        QtMocHelpers::SignalData<void(Mode)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Signal 'workSessionRecorded'
        QtMocHelpers::SignalData<void(int)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'onTick'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Mode'
        QtMocHelpers::EnumData<Mode>(9, 9, QMC::EnumFlags{}).add({
            {   13, Mode::PomodoroMode },
            {   14, Mode::StopwatchMode },
        }),
        // enum 'Phase'
        QtMocHelpers::EnumData<Phase>(5, 5, QMC::EnumFlags{}).add({
            {   15, Phase::Work },
            {   16, Phase::ShortBreak },
            {   17, Phase::LongBreak },
        }),
    };
    return QtMocHelpers::metaObjectData<PomodoroTimer, qt_meta_tag_ZN13PomodoroTimerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PomodoroTimer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PomodoroTimerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PomodoroTimerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13PomodoroTimerE_t>.metaTypes,
    nullptr
} };

void PomodoroTimer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PomodoroTimer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->tick((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->phaseChanged((*reinterpret_cast< std::add_pointer_t<Phase>>(_a[1]))); break;
        case 2: _t->pomodoroCompleted(); break;
        case 3: _t->modeChanged((*reinterpret_cast< std::add_pointer_t<Mode>>(_a[1]))); break;
        case 4: _t->workSessionRecorded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->onTick(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PomodoroTimer::*)(int )>(_a, &PomodoroTimer::tick, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PomodoroTimer::*)(Phase )>(_a, &PomodoroTimer::phaseChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PomodoroTimer::*)()>(_a, &PomodoroTimer::pomodoroCompleted, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (PomodoroTimer::*)(Mode )>(_a, &PomodoroTimer::modeChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (PomodoroTimer::*)(int )>(_a, &PomodoroTimer::workSessionRecorded, 4))
            return;
    }
}

const QMetaObject *PomodoroTimer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PomodoroTimer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13PomodoroTimerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PomodoroTimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PomodoroTimer::tick(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void PomodoroTimer::phaseChanged(Phase _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void PomodoroTimer::pomodoroCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PomodoroTimer::modeChanged(Mode _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void PomodoroTimer::workSessionRecorded(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
