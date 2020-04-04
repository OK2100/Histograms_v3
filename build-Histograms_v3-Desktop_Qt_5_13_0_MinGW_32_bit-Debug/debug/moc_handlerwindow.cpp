/****************************************************************************
** Meta object code from reading C++ file 'handlerwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Histograms_v3/handlerwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'handlerwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HandlerWindow_t {
    QByteArrayData data[21];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HandlerWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HandlerWindow_t qt_meta_stringdata_HandlerWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "HandlerWindow"
QT_MOC_LITERAL(1, 14, 13), // "showNewWindow"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "firstChannelID"
QT_MOC_LITERAL(4, 44, 12), // "updateScreen"
QT_MOC_LITERAL(5, 57, 8), // "addEvent"
QT_MOC_LITERAL(6, 66, 4), // "chID"
QT_MOC_LITERAL(7, 71, 6), // "adc_id"
QT_MOC_LITERAL(8, 78, 6), // "charge"
QT_MOC_LITERAL(9, 85, 4), // "time"
QT_MOC_LITERAL(10, 90, 9), // "chooseADC"
QT_MOC_LITERAL(11, 100, 14), // "startNewWindow"
QT_MOC_LITERAL(12, 115, 14), // "openSourceFile"
QT_MOC_LITERAL(13, 130, 8), // "readFile"
QT_MOC_LITERAL(14, 139, 10), // "addChannel"
QT_MOC_LITERAL(15, 150, 13), // "removeChannel"
QT_MOC_LITERAL(16, 164, 16), // "removeAllChannel"
QT_MOC_LITERAL(17, 181, 5), // "reset"
QT_MOC_LITERAL(18, 187, 8), // "resetAll"
QT_MOC_LITERAL(19, 196, 12), // "hideZeroBars"
QT_MOC_LITERAL(20, 209, 14) // "showStatWindow"

    },
    "HandlerWindow\0showNewWindow\0\0"
    "firstChannelID\0updateScreen\0addEvent\0"
    "chID\0adc_id\0charge\0time\0chooseADC\0"
    "startNewWindow\0openSourceFile\0readFile\0"
    "addChannel\0removeChannel\0removeAllChannel\0"
    "reset\0resetAll\0hideZeroBars\0showStatWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HandlerWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   87,    2, 0x0a /* Public */,
       5,    4,   88,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    1,   98,    2, 0x08 /* Private */,
      12,    0,  101,    2, 0x08 /* Private */,
      13,    0,  102,    2, 0x08 /* Private */,
      14,    0,  103,    2, 0x08 /* Private */,
      15,    0,  104,    2, 0x08 /* Private */,
      16,    0,  105,    2, 0x08 /* Private */,
      17,    0,  106,    2, 0x08 /* Private */,
      18,    0,  107,    2, 0x08 /* Private */,
      19,    0,  108,    2, 0x08 /* Private */,
      20,    0,  109,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar, QMetaType::Short, QMetaType::Short,    6,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HandlerWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HandlerWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showNewWindow((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->updateScreen(); break;
        case 2: _t->addEvent((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< qint16(*)>(_a[3])),(*reinterpret_cast< qint16(*)>(_a[4]))); break;
        case 3: _t->chooseADC(); break;
        case 4: _t->startNewWindow((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: { bool _r = _t->openSourceFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->readFile(); break;
        case 7: _t->addChannel(); break;
        case 8: _t->removeChannel(); break;
        case 9: _t->removeAllChannel(); break;
        case 10: _t->reset(); break;
        case 11: _t->resetAll(); break;
        case 12: _t->hideZeroBars(); break;
        case 13: _t->showStatWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HandlerWindow::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HandlerWindow::showNewWindow)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HandlerWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_HandlerWindow.data,
    qt_meta_data_HandlerWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HandlerWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HandlerWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HandlerWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int HandlerWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void HandlerWindow::showNewWindow(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
