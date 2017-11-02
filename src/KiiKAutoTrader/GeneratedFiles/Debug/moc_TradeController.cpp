/****************************************************************************
** Meta object code from reading C++ file 'TradeController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TradeController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TradeController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TradeController_t {
    QByteArrayData data[18];
    char stringdata[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TradeController_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TradeController_t qt_meta_stringdata_TradeController = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 14),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 14),
QT_MOC_LITERAL(4, 47, 4),
QT_MOC_LITERAL(5, 52, 9),
QT_MOC_LITERAL(6, 62, 11),
QT_MOC_LITERAL(7, 74, 15),
QT_MOC_LITERAL(8, 90, 41),
QT_MOC_LITERAL(9, 132, 9),
QT_MOC_LITERAL(10, 142, 7),
QT_MOC_LITERAL(11, 150, 9),
QT_MOC_LITERAL(12, 160, 20),
QT_MOC_LITERAL(13, 181, 12),
QT_MOC_LITERAL(14, 194, 10),
QT_MOC_LITERAL(15, 205, 15),
QT_MOC_LITERAL(16, 221, 9),
QT_MOC_LITERAL(17, 231, 11)
    },
    "TradeController\0connect_status\0\0"
    "wdConnectInfo*\0info\0error_msg\0const char*\0"
    "instruments_rsp\0"
    "const std::map<std::string,wdInstrument>*\0"
    "order_rsp\0wdOrder\0trade_rsp\0"
    "const wdTradeTicket*\0position_rsp\0"
    "wdPosition\0connectTdServer\0SendOrder\0"
    "CancelOrder"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TradeController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    1,   72,    2, 0x06 /* Public */,
       7,    1,   75,    2, 0x06 /* Public */,
       9,    2,   78,    2, 0x06 /* Public */,
      11,    1,   83,    2, 0x06 /* Public */,
      13,    2,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   91,    2, 0x0a /* Public */,
      16,    2,   92,    2, 0x0a /* Public */,
      16,    1,   97,    2, 0x2a /* Public | MethodCloned */,
      16,    0,  100,    2, 0x2a /* Public | MethodCloned */,
      17,    2,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    2,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,

       0        // eod
};

void TradeController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TradeController *_t = static_cast<TradeController *>(_o);
        switch (_id) {
        case 0: _t->connect_status((*reinterpret_cast< wdConnectInfo*(*)>(_a[1]))); break;
        case 1: _t->error_msg((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->instruments_rsp((*reinterpret_cast< const std::map<std::string,wdInstrument>*(*)>(_a[1]))); break;
        case 3: _t->order_rsp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const wdOrder(*)>(_a[2]))); break;
        case 4: _t->trade_rsp((*reinterpret_cast< const wdTradeTicket*(*)>(_a[1]))); break;
        case 5: _t->position_rsp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const wdPosition(*)>(_a[2]))); break;
        case 6: _t->connectTdServer(); break;
        case 7: _t->SendOrder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->SendOrder((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->SendOrder(); break;
        case 10: _t->CancelOrder((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TradeController::*_t)(wdConnectInfo * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TradeController::connect_status)) {
                *result = 0;
            }
        }
        {
            typedef void (TradeController::*_t)(const char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TradeController::error_msg)) {
                *result = 1;
            }
        }
        {
            typedef void (TradeController::*_t)(const std::map<std::string,wdInstrument> * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TradeController::instruments_rsp)) {
                *result = 2;
            }
        }
        {
            typedef void (TradeController::*_t)(int , const wdOrder & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TradeController::order_rsp)) {
                *result = 3;
            }
        }
        {
            typedef void (TradeController::*_t)(const wdTradeTicket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TradeController::trade_rsp)) {
                *result = 4;
            }
        }
        {
            typedef void (TradeController::*_t)(int , const wdPosition & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TradeController::position_rsp)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject TradeController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TradeController.data,
      qt_meta_data_TradeController,  qt_static_metacall, 0, 0}
};


const QMetaObject *TradeController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TradeController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TradeController.stringdata))
        return static_cast<void*>(const_cast< TradeController*>(this));
    return QObject::qt_metacast(_clname);
}

int TradeController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void TradeController::connect_status(wdConnectInfo * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TradeController::error_msg(const char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TradeController::instruments_rsp(const std::map<std::string,wdInstrument> * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TradeController::order_rsp(int _t1, const wdOrder & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TradeController::trade_rsp(const wdTradeTicket * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TradeController::position_rsp(int _t1, const wdPosition & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
