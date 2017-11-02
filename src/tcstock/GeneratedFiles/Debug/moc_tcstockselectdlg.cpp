/****************************************************************************
** Meta object code from reading C++ file 'tcstockselectdlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/stockinfo/tcstockselectdlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcstockselectdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcStockSelectDialog_t {
    QByteArrayData data[8];
    char stringdata[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcStockSelectDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcStockSelectDialog_t qt_meta_stringdata_tcStockSelectDialog = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 20),
QT_MOC_LITERAL(2, 41, 0),
QT_MOC_LITERAL(3, 42, 6),
QT_MOC_LITERAL(4, 49, 19),
QT_MOC_LITERAL(5, 69, 5),
QT_MOC_LITERAL(6, 75, 4),
QT_MOC_LITERAL(7, 80, 21)
    },
    "tcStockSelectDialog\0DoMarketIndexChanged\0"
    "\0pIndex\0DoFilterTextChanged\0pText\0"
    "DoOk\0DoStockListNeedReload"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcStockSelectDialog[] = {

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
       4,    1,   37,    2, 0x09 /* Protected */,
       6,    0,   40,    2, 0x09 /* Protected */,
       7,    0,   41,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tcStockSelectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcStockSelectDialog *_t = static_cast<tcStockSelectDialog *>(_o);
        switch (_id) {
        case 0: _t->DoMarketIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->DoFilterTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->DoOk(); break;
        case 3: _t->DoStockListNeedReload(); break;
        default: ;
        }
    }
}

const QMetaObject tcStockSelectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_tcStockSelectDialog.data,
      qt_meta_data_tcStockSelectDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcStockSelectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcStockSelectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcStockSelectDialog.stringdata))
        return static_cast<void*>(const_cast< tcStockSelectDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int tcStockSelectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
