/****************************************************************************
** Meta object code from reading C++ file 'channelhistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Histograms_v3/channelhistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'channelhistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChannelHistWidget_t {
    QByteArrayData data[11];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChannelHistWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChannelHistWidget_t qt_meta_stringdata_ChannelHistWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ChannelHistWidget"
QT_MOC_LITERAL(1, 18, 23), // "channelIDButton_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 27), // "binWidth_charge_was_changed"
QT_MOC_LITERAL(4, 71, 25), // "binWidth_time_was_changed"
QT_MOC_LITERAL(5, 97, 24), // "nBins_charge_was_changed"
QT_MOC_LITERAL(6, 122, 22), // "nBins_time_was_changed"
QT_MOC_LITERAL(7, 145, 19), // "hist_double_clicked"
QT_MOC_LITERAL(8, 165, 12), // "QMouseEvent*"
QT_MOC_LITERAL(9, 178, 5), // "event"
QT_MOC_LITERAL(10, 184, 21) // "replot_chargeTimeHist"

    },
    "ChannelHistWidget\0channelIDButton_clicked\0"
    "\0binWidth_charge_was_changed\0"
    "binWidth_time_was_changed\0"
    "nBins_charge_was_changed\0"
    "nBins_time_was_changed\0hist_double_clicked\0"
    "QMouseEvent*\0event\0replot_chargeTimeHist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChannelHistWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    1,   50,    2, 0x08 /* Private */,
       4,    1,   53,    2, 0x08 /* Private */,
       5,    1,   56,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       7,    1,   62,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void ChannelHistWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChannelHistWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->channelIDButton_clicked(); break;
        case 1: _t->binWidth_charge_was_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->binWidth_time_was_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->nBins_charge_was_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->nBins_time_was_changed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->hist_double_clicked((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 6: _t->replot_chargeTimeHist(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChannelHistWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ChannelHistWidget.data,
    qt_meta_data_ChannelHistWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChannelHistWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChannelHistWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChannelHistWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChannelHistWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
