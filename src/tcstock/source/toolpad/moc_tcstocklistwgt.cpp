/****************************************************************************
** Meta object code from reading C++ file 'tcstocklistwgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tcstocklistwgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcstocklistwgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcStockListWidget_t {
    QByteArrayData data[17];
    char stringdata[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcStockListWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcStockListWidget_t qt_meta_stringdata_tcStockListWidget = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 15),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 16),
QT_MOC_LITERAL(4, 52, 14),
QT_MOC_LITERAL(5, 67, 16),
QT_MOC_LITERAL(6, 84, 15),
QT_MOC_LITERAL(7, 100, 9),
QT_MOC_LITERAL(8, 110, 7),
QT_MOC_LITERAL(9, 118, 15),
QT_MOC_LITERAL(10, 134, 20),
QT_MOC_LITERAL(11, 155, 6),
QT_MOC_LITERAL(12, 162, 19),
QT_MOC_LITERAL(13, 182, 5),
QT_MOC_LITERAL(14, 188, 23),
QT_MOC_LITERAL(15, 212, 21),
QT_MOC_LITERAL(16, 234, 21)
    },
    "tcStockListWidget\0OnStockSelected\0\0"
    "tcStockInfoList*\0pStockInfoList\0"
    "DoMarketModified\0DoStockModified\0"
    "tcMarket*\0pMarket\0DoEditFavourite\0"
    "DoMarketIndexChanged\0pIndex\0"
    "DoFilterTextChanged\0pText\0"
    "DoStockSelectionChanged\0DoGroupListNeedReload\0"
    "DoStockListNeedReload"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcStockListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   62,    2, 0x09 /* Protected */,
       6,    1,   63,    2, 0x09 /* Protected */,
       9,    0,   66,    2, 0x09 /* Protected */,
      10,    1,   67,    2, 0x09 /* Protected */,
      12,    1,   70,    2, 0x09 /* Protected */,
      14,    0,   73,    2, 0x09 /* Protected */,
      15,    0,   74,    2, 0x09 /* Protected */,
      16,    0,   75,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void tcStockListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcStockListWidget *_t = static_cast<tcStockListWidget *>(_o);
        switch (_id) {
        case 0: _t->OnStockSelected((*reinterpret_cast< tcStockInfoList*(*)>(_a[1]))); break;
        case 1: _t->DoMarketModified(); break;
        case 2: _t->DoStockModified((*reinterpret_cast< tcMarket*(*)>(_a[1]))); break;
        case 3: _t->DoEditFavourite(); break;
        case 4: _t->DoMarketIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->DoFilterTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->DoStockSelectionChanged(); break;
        case 7: _t->DoGroupListNeedReload(); break;
        case 8: _t->DoStockListNeedReload(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< tcStockInfoList* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< tcMarket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (tcStockListWidget::*_t)(tcStockInfoList * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tcStockListWidget::OnStockSelected)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject tcStockListWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_tcStockListWidget.data,
      qt_meta_data_tcStockListWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcStockListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcStockListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcStockListWidget.stringdata))
        return static_cast<void*>(const_cast< tcStockListWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int tcStockListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void tcStockListWidget::OnStockSelected(tcStockInfoList * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
