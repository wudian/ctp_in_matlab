/****************************************************************************
** Meta object code from reading C++ file 'tcmarketmgr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/stockinfo/tcmarketmgr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcmarketmgr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcMarketManager_t {
    QByteArrayData data[7];
    char stringdata[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcMarketManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcMarketManager_t qt_meta_stringdata_tcMarketManager = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 17),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 16),
QT_MOC_LITERAL(4, 52, 9),
QT_MOC_LITERAL(5, 62, 7),
QT_MOC_LITERAL(6, 70, 16)
    },
    "tcMarketManager\0OnMarketsModified\0\0"
    "OnStocksModified\0tcMarket*\0pMarket\0"
    "DoStocksModified"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcMarketManager[] = {

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
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   33,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void tcMarketManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcMarketManager *_t = static_cast<tcMarketManager *>(_o);
        switch (_id) {
        case 0: _t->OnMarketsModified(); break;
        case 1: _t->OnStocksModified((*reinterpret_cast< tcMarket*(*)>(_a[1]))); break;
        case 2: _t->DoStocksModified(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< tcMarket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (tcMarketManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcMarketManager::OnMarketsModified)) {
                *result = 0;
            }
        }
        {
            typedef void (tcMarketManager::*_t)(tcMarket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcMarketManager::OnStocksModified)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject tcMarketManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tcMarketManager.data,
      qt_meta_data_tcMarketManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcMarketManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcMarketManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcMarketManager.stringdata))
        return static_cast<void*>(const_cast< tcMarketManager*>(this));
    return QObject::qt_metacast(_clname);
}

int tcMarketManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void tcMarketManager::OnMarketsModified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void tcMarketManager::OnStocksModified(tcMarket * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
