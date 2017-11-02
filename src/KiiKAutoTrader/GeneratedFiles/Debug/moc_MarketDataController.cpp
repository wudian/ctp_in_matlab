/****************************************************************************
** Meta object code from reading C++ file 'MarketDataController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MarketDataController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MarketDataController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MarketDataController_t {
    QByteArrayData data[16];
    char stringdata[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MarketDataController_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MarketDataController_t qt_meta_stringdata_MarketDataController = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 9),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 18),
QT_MOC_LITERAL(4, 51, 4),
QT_MOC_LITERAL(5, 56, 11),
QT_MOC_LITERAL(6, 68, 6),
QT_MOC_LITERAL(7, 75, 7),
QT_MOC_LITERAL(8, 83, 7),
QT_MOC_LITERAL(9, 91, 8),
QT_MOC_LITERAL(10, 100, 8),
QT_MOC_LITERAL(11, 109, 15),
QT_MOC_LITERAL(12, 125, 9),
QT_MOC_LITERAL(13, 135, 11),
QT_MOC_LITERAL(14, 147, 14),
QT_MOC_LITERAL(15, 162, 1)
    },
    "MarketDataController\0md_status\0\0"
    "wdConnectionStatus\0step\0const char*\0"
    "errMsg\0md_tick\0wdTick*\0md_kline\0"
    "wdKLine*\0connectMdServer\0subscribe\0"
    "unsubscribe\0CheckIsHistory\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MarketDataController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       1,    1,   59,    2, 0x26 /* Public | MethodCloned */,
       7,    2,   62,    2, 0x06 /* Public */,
       9,    2,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   72,    2, 0x0a /* Public */,
      12,    0,   73,    2, 0x0a /* Public */,
      13,    0,   74,    2, 0x0a /* Public */,
      14,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void MarketDataController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MarketDataController *_t = static_cast<MarketDataController *>(_o);
        switch (_id) {
        case 0: _t->md_status((*reinterpret_cast< wdConnectionStatus(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 1: _t->md_status((*reinterpret_cast< wdConnectionStatus(*)>(_a[1]))); break;
        case 2: _t->md_tick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< wdTick*(*)>(_a[2]))); break;
        case 3: _t->md_kline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< wdKLine*(*)>(_a[2]))); break;
        case 4: _t->connectMdServer(); break;
        case 5: _t->subscribe(); break;
        case 6: _t->unsubscribe(); break;
        case 7: _t->CheckIsHistory((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MarketDataController::*_t)(wdConnectionStatus , const char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarketDataController::md_status)) {
                *result = 0;
            }
        }
        {
            typedef void (MarketDataController::*_t)(int , wdTick * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarketDataController::md_tick)) {
                *result = 2;
            }
        }
        {
            typedef void (MarketDataController::*_t)(int , wdKLine * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarketDataController::md_kline)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject MarketDataController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MarketDataController.data,
      qt_meta_data_MarketDataController,  qt_static_metacall, 0, 0}
};


const QMetaObject *MarketDataController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MarketDataController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MarketDataController.stringdata))
        return static_cast<void*>(const_cast< MarketDataController*>(this));
    return QObject::qt_metacast(_clname);
}

int MarketDataController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MarketDataController::md_status(wdConnectionStatus _t1, const char * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void MarketDataController::md_tick(int _t1, wdTick * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MarketDataController::md_kline(int _t1, wdKLine * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
