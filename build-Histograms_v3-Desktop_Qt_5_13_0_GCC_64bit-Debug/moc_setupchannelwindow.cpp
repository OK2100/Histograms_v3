/****************************************************************************
** Meta object code from reading C++ file 'setupchannelwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Histograms_v3/setupchannelwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setupchannelwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SetupChannelWindow_t {
    QByteArrayData data[7];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetupChannelWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetupChannelWindow_t qt_meta_stringdata_SetupChannelWindow = {
    {
QT_MOC_LITERAL(0, 0, 18), // "SetupChannelWindow"
QT_MOC_LITERAL(1, 19, 23), // "binWidth_charge_changed"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 21), // "binWidth_time_changed"
QT_MOC_LITERAL(4, 66, 20), // "nBins_charge_changed"
QT_MOC_LITERAL(5, 87, 18), // "nBins_time_changed"
QT_MOC_LITERAL(6, 106, 13) // "apply_clicked"

    },
    "SetupChannelWindow\0binWidth_charge_changed\0"
    "\0binWidth_time_changed\0nBins_charge_changed\0"
    "nBins_time_changed\0apply_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetupChannelWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,
       4,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void SetupChannelWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SetupChannelWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->binWidth_charge_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->binWidth_time_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->nBins_charge_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->nBins_time_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->apply_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SetupChannelWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetupChannelWindow::binWidth_charge_changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SetupChannelWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetupChannelWindow::binWidth_time_changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SetupChannelWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetupChannelWindow::nBins_charge_changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SetupChannelWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetupChannelWindow::nBins_time_changed)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SetupChannelWindow::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_SetupChannelWindow.data,
    qt_meta_data_SetupChannelWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SetupChannelWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetupChannelWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SetupChannelWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SetupChannelWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SetupChannelWindow::binWidth_charge_changed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SetupChannelWindow::binWidth_time_changed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SetupChannelWindow::nBins_charge_changed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SetupChannelWindow::nBins_time_changed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
