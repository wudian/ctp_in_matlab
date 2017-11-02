/****************************************************************************
** Meta object code from reading C++ file 'tcfavtinfodlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/stockinfo/tcfavtinfodlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcfavtinfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcFavouriteInfoDialog_t {
    QByteArrayData data[9];
    char stringdata[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcFavouriteInfoDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcFavouriteInfoDialog_t qt_meta_stringdata_tcFavouriteInfoDialog = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 28),
QT_MOC_LITERAL(2, 51, 0),
QT_MOC_LITERAL(3, 52, 6),
QT_MOC_LITERAL(4, 59, 22),
QT_MOC_LITERAL(5, 82, 22),
QT_MOC_LITERAL(6, 105, 22),
QT_MOC_LITERAL(7, 128, 22),
QT_MOC_LITERAL(8, 151, 22)
    },
    "tcFavouriteInfoDialog\0"
    "DoFavouriteGroupIndexChanged\0\0pIndex\0"
    "DoAppendFavouriteGroup\0DoModifyFavouriteGroup\0"
    "DoRemoveFavouriteGroup\0DoAppendFavouriteStock\0"
    "DoRemoveFavouriteStock"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcFavouriteInfoDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x09 /* Protected */,
       4,    0,   47,    2, 0x09 /* Protected */,
       5,    0,   48,    2, 0x09 /* Protected */,
       6,    0,   49,    2, 0x09 /* Protected */,
       7,    0,   50,    2, 0x09 /* Protected */,
       8,    0,   51,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tcFavouriteInfoDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcFavouriteInfoDialog *_t = static_cast<tcFavouriteInfoDialog *>(_o);
        switch (_id) {
        case 0: _t->DoFavouriteGroupIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->DoAppendFavouriteGroup(); break;
        case 2: _t->DoModifyFavouriteGroup(); break;
        case 3: _t->DoRemoveFavouriteGroup(); break;
        case 4: _t->DoAppendFavouriteStock(); break;
        case 5: _t->DoRemoveFavouriteStock(); break;
        default: ;
        }
    }
}

const QMetaObject tcFavouriteInfoDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_tcFavouriteInfoDialog.data,
      qt_meta_data_tcFavouriteInfoDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcFavouriteInfoDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcFavouriteInfoDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcFavouriteInfoDialog.stringdata))
        return static_cast<void*>(const_cast< tcFavouriteInfoDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int tcFavouriteInfoDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
