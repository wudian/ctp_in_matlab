/****************************************************************************
** Meta object code from reading C++ file 'MdTable.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MdTable.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MdTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MdTable_t {
    QByteArrayData data[8];
    char stringdata[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MdTable_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MdTable_t qt_meta_stringdata_MdTable = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 12),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 19),
QT_MOC_LITERAL(4, 42, 20),
QT_MOC_LITERAL(5, 63, 18),
QT_MOC_LITERAL(6, 82, 9),
QT_MOC_LITERAL(7, 92, 20)
    },
    "MdTable\0refreshTable\0\0updateTableForUnsub\0"
    "updateTableForSelect\0std::set<QString>&\0"
    "newInstru\0callUnsubUpdateTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MdTable[] = {

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
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    1,   36,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void MdTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MdTable *_t = static_cast<MdTable *>(_o);
        switch (_id) {
        case 0: _t->refreshTable(); break;
        case 1: _t->updateTableForUnsub(); break;
        case 2: _t->updateTableForSelect((*reinterpret_cast< std::set<QString>(*)>(_a[1]))); break;
        case 3: _t->callUnsubUpdateTimer(); break;
        default: ;
        }
    }
}

const QMetaObject MdTable::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_MdTable.data,
      qt_meta_data_MdTable,  qt_static_metacall, 0, 0}
};


const QMetaObject *MdTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MdTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MdTable.stringdata))
        return static_cast<void*>(const_cast< MdTable*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int MdTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
