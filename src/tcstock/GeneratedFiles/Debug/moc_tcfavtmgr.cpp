/****************************************************************************
** Meta object code from reading C++ file 'tcfavtmgr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/stockinfo/tcfavtmgr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcfavtmgr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcFavouriteManager_t {
    QByteArrayData data[7];
    char stringdata[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcFavouriteManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcFavouriteManager_t qt_meta_stringdata_tcFavouriteManager = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 24),
QT_MOC_LITERAL(2, 44, 0),
QT_MOC_LITERAL(3, 45, 16),
QT_MOC_LITERAL(4, 62, 17),
QT_MOC_LITERAL(5, 80, 15),
QT_MOC_LITERAL(6, 96, 16)
    },
    "tcFavouriteManager\0OnFavouriteGroupModified\0"
    "\0OnStocksModified\0tcFavouriteGroup*\0"
    "pFavouriteGroup\0DoStocksModified"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcFavouriteManager[] = {

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

void tcFavouriteManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcFavouriteManager *_t = static_cast<tcFavouriteManager *>(_o);
        switch (_id) {
        case 0: _t->OnFavouriteGroupModified(); break;
        case 1: _t->OnStocksModified((*reinterpret_cast< tcFavouriteGroup*(*)>(_a[1]))); break;
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
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< tcFavouriteGroup* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (tcFavouriteManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcFavouriteManager::OnFavouriteGroupModified)) {
                *result = 0;
            }
        }
        {
            typedef void (tcFavouriteManager::*_t)(tcFavouriteGroup * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcFavouriteManager::OnStocksModified)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject tcFavouriteManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tcFavouriteManager.data,
      qt_meta_data_tcFavouriteManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcFavouriteManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcFavouriteManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcFavouriteManager.stringdata))
        return static_cast<void*>(const_cast< tcFavouriteManager*>(this));
    return QObject::qt_metacast(_clname);
}

int tcFavouriteManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void tcFavouriteManager::OnFavouriteGroupModified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void tcFavouriteManager::OnStocksModified(tcFavouriteGroup * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE