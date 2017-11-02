/****************************************************************************
** Meta object code from reading C++ file 'wdMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wdMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wdMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_wdMainWindow_t {
    QByteArrayData data[20];
    char stringdata[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_wdMainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_wdMainWindow_t qt_meta_stringdata_wdMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 10),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 7),
QT_MOC_LITERAL(4, 33, 7),
QT_MOC_LITERAL(5, 41, 8),
QT_MOC_LITERAL(6, 50, 8),
QT_MOC_LITERAL(7, 59, 13),
QT_MOC_LITERAL(8, 73, 14),
QT_MOC_LITERAL(9, 88, 4),
QT_MOC_LITERAL(10, 93, 7),
QT_MOC_LITERAL(11, 101, 11),
QT_MOC_LITERAL(12, 113, 14),
QT_MOC_LITERAL(13, 128, 41),
QT_MOC_LITERAL(14, 170, 8),
QT_MOC_LITERAL(15, 179, 7),
QT_MOC_LITERAL(16, 187, 8),
QT_MOC_LITERAL(17, 196, 20),
QT_MOC_LITERAL(18, 217, 11),
QT_MOC_LITERAL(19, 229, 10)
    },
    "wdMainWindow\0updateTime\0\0Md_Tick\0"
    "wdTick*\0Md_KLine\0wdKLine*\0ConnectStatus\0"
    "wdConnectInfo*\0info\0OnError\0const char*\0"
    "InstrumentsRsp\0const std::map<std::string,wdInstrument>*\0"
    "OrderRsp\0wdOrder\0TradeRsp\0"
    "const wdTradeTicket*\0PositionRsp\0"
    "wdPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_wdMainWindow[] = {

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
       1,    0,   59,    2, 0x08 /* Private */,
       3,    2,   60,    2, 0x08 /* Private */,
       5,    2,   65,    2, 0x08 /* Private */,
       7,    1,   70,    2, 0x08 /* Private */,
      10,    1,   73,    2, 0x08 /* Private */,
      12,    1,   76,    2, 0x08 /* Private */,
      14,    2,   79,    2, 0x08 /* Private */,
      16,    1,   84,    2, 0x08 /* Private */,
      18,    2,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    2,    2,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 15,    2,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 19,    2,    2,

       0        // eod
};

void wdMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        wdMainWindow *_t = static_cast<wdMainWindow *>(_o);
        switch (_id) {
        case 0: _t->updateTime(); break;
        case 1: _t->Md_Tick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< wdTick*(*)>(_a[2]))); break;
        case 2: _t->Md_KLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< wdKLine*(*)>(_a[2]))); break;
        case 3: _t->ConnectStatus((*reinterpret_cast< wdConnectInfo*(*)>(_a[1]))); break;
        case 4: _t->OnError((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 5: _t->InstrumentsRsp((*reinterpret_cast< const std::map<std::string,wdInstrument>*(*)>(_a[1]))); break;
        case 6: _t->OrderRsp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const wdOrder(*)>(_a[2]))); break;
        case 7: _t->TradeRsp((*reinterpret_cast< const wdTradeTicket*(*)>(_a[1]))); break;
        case 8: _t->PositionRsp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const wdPosition(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject wdMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_wdMainWindow.data,
      qt_meta_data_wdMainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *wdMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wdMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_wdMainWindow.stringdata))
        return static_cast<void*>(const_cast< wdMainWindow*>(this));
    if (!strcmp(_clname, "Ui_MainWindow"))
        return static_cast< Ui_MainWindow*>(const_cast< wdMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int wdMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
