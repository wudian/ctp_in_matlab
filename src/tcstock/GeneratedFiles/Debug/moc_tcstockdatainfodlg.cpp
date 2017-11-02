/****************************************************************************
** Meta object code from reading C++ file 'tcstockdatainfodlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/stockinfo/tcstockdatainfodlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcstockdatainfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcStockDataInfoDialog_t {
    QByteArrayData data[8];
    char stringdata[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcStockDataInfoDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcStockDataInfoDialog_t qt_meta_stringdata_tcStockDataInfoDialog = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 13),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 5),
QT_MOC_LITERAL(4, 43, 14),
QT_MOC_LITERAL(5, 58, 6),
QT_MOC_LITERAL(6, 65, 19),
QT_MOC_LITERAL(7, 85, 5)
    },
    "tcStockDataInfoDialog\0DoDateChanged\0"
    "\0pDate\0DoGroupChanged\0pIndex\0"
    "DoFilterTextChanged\0pText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcStockDataInfoDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x09 /* Protected */,
       4,    1,   32,    2, 0x09 /* Protected */,
       6,    1,   35,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void tcStockDataInfoDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcStockDataInfoDialog *_t = static_cast<tcStockDataInfoDialog *>(_o);
        switch (_id) {
        case 0: _t->DoDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 1: _t->DoGroupChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->DoFilterTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject tcStockDataInfoDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_tcStockDataInfoDialog.data,
      qt_meta_data_tcStockDataInfoDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcStockDataInfoDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcStockDataInfoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcStockDataInfoDialog.stringdata))
        return static_cast<void*>(const_cast< tcStockDataInfoDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int tcStockDataInfoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
