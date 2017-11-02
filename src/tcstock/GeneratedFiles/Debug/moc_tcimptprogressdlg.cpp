/****************************************************************************
** Meta object code from reading C++ file 'tcimptprogressdlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/dataimpt/tcimptprogressdlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcimptprogressdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcImportProgressDialog_t {
    QByteArrayData data[9];
    char stringdata[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcImportProgressDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcImportProgressDialog_t qt_meta_stringdata_tcImportProgressDialog = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 16),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 9),
QT_MOC_LITERAL(4, 51, 15),
QT_MOC_LITERAL(5, 67, 8),
QT_MOC_LITERAL(6, 76, 8),
QT_MOC_LITERAL(7, 85, 16),
QT_MOC_LITERAL(8, 102, 14)
    },
    "tcImportProgressDialog\0DoUpdateProgress\0"
    "\0pProgress\0DoAppendMessage\0pMessage\0"
    "pSuccess\0DoImportFinished\0DoCancelImport"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcImportProgressDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x09 /* Protected */,
       4,    2,   37,    2, 0x09 /* Protected */,
       7,    0,   42,    2, 0x09 /* Protected */,
       8,    0,   43,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tcImportProgressDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcImportProgressDialog *_t = static_cast<tcImportProgressDialog *>(_o);
        switch (_id) {
        case 0: _t->DoUpdateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->DoAppendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->DoImportFinished(); break;
        case 3: _t->DoCancelImport(); break;
        default: ;
        }
    }
}

const QMetaObject tcImportProgressDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_tcImportProgressDialog.data,
      qt_meta_data_tcImportProgressDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcImportProgressDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcImportProgressDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcImportProgressDialog.stringdata))
        return static_cast<void*>(const_cast< tcImportProgressDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int tcImportProgressDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
