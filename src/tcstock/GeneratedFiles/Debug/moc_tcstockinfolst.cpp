/****************************************************************************
** Meta object code from reading C++ file 'tcstockinfolst.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/stockinfo/tcstockinfolst.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcstockinfolst.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcStockInfoList_t {
    QByteArrayData data[12];
    char stringdata[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcStockInfoList_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcStockInfoList_t qt_meta_stringdata_tcStockInfoList = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 21),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 21),
QT_MOC_LITERAL(4, 61, 30),
QT_MOC_LITERAL(5, 92, 29),
QT_MOC_LITERAL(6, 122, 9),
QT_MOC_LITERAL(7, 132, 7),
QT_MOC_LITERAL(8, 140, 40),
QT_MOC_LITERAL(9, 181, 32),
QT_MOC_LITERAL(10, 214, 17),
QT_MOC_LITERAL(11, 232, 15)
    },
    "tcStockInfoList\0OnGroupListNeedReload\0"
    "\0OnStockListNeedReload\0"
    "DoMarketManagerMarketsModified\0"
    "DoMarketManagerStocksModified\0tcMarket*\0"
    "pMarket\0DoFavouriteManagerFavouriteGroupModified\0"
    "DoFavouriteManagerStocksModified\0"
    "tcFavouriteGroup*\0pFavouriteGroup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcStockInfoList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x09 /* Protected */,
       5,    1,   47,    2, 0x09 /* Protected */,
       8,    0,   50,    2, 0x09 /* Protected */,
       9,    1,   51,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void tcStockInfoList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcStockInfoList *_t = static_cast<tcStockInfoList *>(_o);
        switch (_id) {
        case 0: _t->OnGroupListNeedReload(); break;
        case 1: _t->OnStockListNeedReload(); break;
        case 2: _t->DoMarketManagerMarketsModified(); break;
        case 3: _t->DoMarketManagerStocksModified((*reinterpret_cast< tcMarket*(*)>(_a[1]))); break;
        case 4: _t->DoFavouriteManagerFavouriteGroupModified(); break;
        case 5: _t->DoFavouriteManagerStocksModified((*reinterpret_cast< tcFavouriteGroup*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (tcStockInfoList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcStockInfoList::OnGroupListNeedReload)) {
                *result = 0;
            }
        }
        {
            typedef void (tcStockInfoList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcStockInfoList::OnStockListNeedReload)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject tcStockInfoList::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tcStockInfoList.data,
      qt_meta_data_tcStockInfoList,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcStockInfoList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcStockInfoList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcStockInfoList.stringdata))
        return static_cast<void*>(const_cast< tcStockInfoList*>(this));
    if (!strcmp(_clname, "QList<tcStockInfo>"))
        return static_cast< QList<tcStockInfo>*>(const_cast< tcStockInfoList*>(this));
    return QObject::qt_metacast(_clname);
}

int tcStockInfoList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void tcStockInfoList::OnGroupListNeedReload()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void tcStockInfoList::OnStockListNeedReload()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
