/****************************************************************************
** Meta object code from reading C++ file 'tcsinawebimptsource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/dataimpt/tcsinawebimptsource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcsinawebimptsource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcSinaWebImportSource_t {
    QByteArrayData data[4];
    char stringdata[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcSinaWebImportSource_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcSinaWebImportSource_t qt_meta_stringdata_tcSinaWebImportSource = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 10),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 6)
    },
    "tcSinaWebImportSource\0DoHttpDone\0\0"
    "pError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcSinaWebImportSource[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void tcSinaWebImportSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcSinaWebImportSource *_t = static_cast<tcSinaWebImportSource *>(_o);
        switch (_id) {
        case 0: _t->DoHttpDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject tcSinaWebImportSource::staticMetaObject = {
    { &tcImportSource::staticMetaObject, qt_meta_stringdata_tcSinaWebImportSource.data,
      qt_meta_data_tcSinaWebImportSource,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcSinaWebImportSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcSinaWebImportSource::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcSinaWebImportSource.stringdata))
        return static_cast<void*>(const_cast< tcSinaWebImportSource*>(this));
    return tcImportSource::qt_metacast(_clname);
}

int tcSinaWebImportSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = tcImportSource::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
