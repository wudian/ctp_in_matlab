/****************************************************************************
** Meta object code from reading C++ file 'tcmarketlistdlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/stockinfo/tcmarketlistdlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcmarketlistdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcMarketListDialog_t {
    QByteArrayData data[11];
    char stringdata[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcMarketListDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcMarketListDialog_t qt_meta_stringdata_tcMarketListDialog = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 20),
QT_MOC_LITERAL(2, 40, 0),
QT_MOC_LITERAL(3, 41, 14),
QT_MOC_LITERAL(4, 56, 14),
QT_MOC_LITERAL(5, 71, 14),
QT_MOC_LITERAL(6, 86, 13),
QT_MOC_LITERAL(7, 100, 13),
QT_MOC_LITERAL(8, 114, 13),
QT_MOC_LITERAL(9, 128, 21),
QT_MOC_LITERAL(10, 150, 19)
    },
    "tcMarketListDialog\0DoMarketIndexChanged\0"
    "\0DoAppendMarket\0DoModifyMarket\0"
    "DoRemoveMarket\0DoAppendStock\0DoModifyStock\0"
    "DoRemoveStock\0DoImportStocksFromCSV\0"
    "DoExportStocksToCSV"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcMarketListDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x09 /* Protected */,
       3,    0,   62,    2, 0x09 /* Protected */,
       4,    0,   63,    2, 0x09 /* Protected */,
       5,    0,   64,    2, 0x09 /* Protected */,
       6,    0,   65,    2, 0x09 /* Protected */,
       7,    0,   66,    2, 0x09 /* Protected */,
       8,    0,   67,    2, 0x09 /* Protected */,
       9,    0,   68,    2, 0x09 /* Protected */,
      10,    0,   69,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tcMarketListDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcMarketListDialog *_t = static_cast<tcMarketListDialog *>(_o);
        switch (_id) {
        case 0: _t->DoMarketIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->DoAppendMarket(); break;
        case 2: _t->DoModifyMarket(); break;
        case 3: _t->DoRemoveMarket(); break;
        case 4: _t->DoAppendStock(); break;
        case 5: _t->DoModifyStock(); break;
        case 6: _t->DoRemoveStock(); break;
        case 7: _t->DoImportStocksFromCSV(); break;
        case 8: _t->DoExportStocksToCSV(); break;
        default: ;
        }
    }
}

const QMetaObject tcMarketListDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_tcMarketListDialog.data,
      qt_meta_data_tcMarketListDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcMarketListDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcMarketListDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcMarketListDialog.stringdata))
        return static_cast<void*>(const_cast< tcMarketListDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int tcMarketListDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
