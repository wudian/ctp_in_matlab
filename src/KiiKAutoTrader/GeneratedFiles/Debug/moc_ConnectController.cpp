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
struct qt_meta_stringdata_ConnectController_t {
    QByteArrayData data[9];
    char stringdata[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectController_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectController_t qt_meta_stringdata_ConnectController = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 9),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 18),
QT_MOC_LITERAL(4, 48, 4),
QT_MOC_LITERAL(5, 53, 11),
QT_MOC_LITERAL(6, 65, 6),
QT_MOC_LITERAL(7, 72, 9),
QT_MOC_LITERAL(8, 82, 13)
    },
    "MarketDataController\0md_status\0\0"
    "wdConnectionStatus\0step\0const char*\0"
    "errMsg\0td_status\0connectServer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       7,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void MarketDataController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MarketDataController *_t = static_cast<MarketDataController *>(_o);
        switch (_id) {
        case 0: _t->md_status((*reinterpret_cast< wdConnectionStatus(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 1: _t->td_status((*reinterpret_cast< wdConnectionStatus(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 2: _t->connectServer(); break;
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
            typedef void (MarketDataController::*_t)(wdConnectionStatus , const char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MarketDataController::td_status)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MarketDataController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConnectController.data,
      qt_meta_data_ConnectController,  qt_static_metacall, 0, 0}
};


const QMetaObject *MarketDataController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MarketDataController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectController.stringdata))
        return static_cast<void*>(const_cast< MarketDataController*>(this));
    return QObject::qt_metacast(_clname);
}

int MarketDataController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MarketDataController::md_status(wdConnectionStatus _t1, const char * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MarketDataController::td_status(wdConnectionStatus _t1, const char * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
