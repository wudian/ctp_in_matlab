/****************************************************************************
** Meta object code from reading C++ file 'tcimptsource.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/dataimpt/tcimptsource.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcimptsource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcImportSource_t {
    QByteArrayData data[8];
    char stringdata[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcImportSource_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcImportSource_t qt_meta_stringdata_tcImportSource = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 16),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 9),
QT_MOC_LITERAL(4, 43, 15),
QT_MOC_LITERAL(5, 59, 8),
QT_MOC_LITERAL(6, 68, 8),
QT_MOC_LITERAL(7, 77, 16)
    },
    "tcImportSource\0OnUpdateProgress\0\0"
    "pProgress\0OnAppendMessage\0pMessage\0"
    "pSuccess\0OnImportFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcImportSource[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    2,   32,    2, 0x06 /* Public */,
       7,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    5,    6,
    QMetaType::Void,

       0        // eod
};

void tcImportSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcImportSource *_t = static_cast<tcImportSource *>(_o);
        switch (_id) {
        case 0: _t->OnUpdateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OnAppendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->OnImportFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (tcImportSource::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcImportSource::OnUpdateProgress)) {
                *result = 0;
            }
        }
        {
            typedef void (tcImportSource::*_t)(const QString & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcImportSource::OnAppendMessage)) {
                *result = 1;
            }
        }
        {
            typedef void (tcImportSource::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcImportSource::OnImportFinished)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject tcImportSource::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_tcImportSource.data,
      qt_meta_data_tcImportSource,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcImportSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcImportSource::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcImportSource.stringdata))
        return static_cast<void*>(const_cast< tcImportSource*>(this));
    return QObject::qt_metacast(_clname);
}

int tcImportSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void tcImportSource::OnUpdateProgress(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void tcImportSource::OnAppendMessage(const QString & _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void tcImportSource::OnImportFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
