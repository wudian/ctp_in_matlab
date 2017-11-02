/****************************************************************************
** Meta object code from reading C++ file 'tcfavtgrp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/stockinfo/tcfavtgrp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcfavtgrp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcFavouriteGroup_t {
    QByteArrayData data[3];
    char stringdata[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcFavouriteGroup_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcFavouriteGroup_t qt_meta_stringdata_tcFavouriteGroup = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 16),
QT_MOC_LITERAL(2, 34, 0)
    },
    "tcFavouriteGroup\0OnStocksModified\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcFavouriteGroup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void tcFavouriteGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcFavouriteGroup *_t = static_cast<tcFavouriteGroup *>(_o);
        switch (_id) {
        case 0: _t->OnStocksModified(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (tcFavouriteGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcFavouriteGroup::OnStocksModified)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject tcFavouriteGroup::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tcFavouriteGroup.data,
      qt_meta_data_tcFavouriteGroup,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcFavouriteGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcFavouriteGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcFavouriteGroup.stringdata))
        return static_cast<void*>(const_cast< tcFavouriteGroup*>(this));
    return QObject::qt_metacast(_clname);
}

int tcFavouriteGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void tcFavouriteGroup::OnStocksModified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
