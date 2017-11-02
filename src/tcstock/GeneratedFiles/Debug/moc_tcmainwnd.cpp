/****************************************************************************
** Meta object code from reading C++ file 'tcmainwnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/tcmainwnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcmainwnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tcMainWindow_t {
    QByteArrayData data[14];
    char stringdata[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tcMainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tcMainWindow_t qt_meta_stringdata_tcMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 14),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 16),
QT_MOC_LITERAL(4, 46, 20),
QT_MOC_LITERAL(5, 67, 17),
QT_MOC_LITERAL(6, 85, 6),
QT_MOC_LITERAL(7, 92, 15),
QT_MOC_LITERAL(8, 108, 16),
QT_MOC_LITERAL(9, 125, 7),
QT_MOC_LITERAL(10, 133, 6),
QT_MOC_LITERAL(11, 140, 15),
QT_MOC_LITERAL(12, 156, 16),
QT_MOC_LITERAL(13, 173, 14)
    },
    "tcMainWindow\0DoModifyMarket\0\0"
    "DoInputStockData\0DoEditFavouriteStock\0"
    "DoImportStockData\0DoExit\0DoViewStockList\0"
    "DoViewWeeklyView\0DoAbout\0mytest\0"
    "DoStockSelected\0tcStockInfoList*\0"
    "pStockInfoList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tcMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x09 /* Protected */,
       3,    0,   65,    2, 0x09 /* Protected */,
       4,    0,   66,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x09 /* Protected */,
       6,    0,   68,    2, 0x09 /* Protected */,
       7,    0,   69,    2, 0x09 /* Protected */,
       8,    0,   70,    2, 0x09 /* Protected */,
       9,    0,   71,    2, 0x09 /* Protected */,
      10,    0,   72,    2, 0x09 /* Protected */,
      11,    1,   73,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void tcMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tcMainWindow *_t = static_cast<tcMainWindow *>(_o);
        switch (_id) {
        case 0: _t->DoModifyMarket(); break;
        case 1: _t->DoInputStockData(); break;
        case 2: _t->DoEditFavouriteStock(); break;
        case 3: _t->DoImportStockData(); break;
        case 4: _t->DoExit(); break;
        case 5: _t->DoViewStockList(); break;
        case 6: _t->DoViewWeeklyView(); break;
        case 7: _t->DoAbout(); break;
        case 8: _t->mytest(); break;
        case 9: _t->DoStockSelected((*reinterpret_cast< tcStockInfoList*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< tcStockInfoList* >(); break;
            }
            break;
        }
    }
}

const QMetaObject tcMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_tcMainWindow.data,
      qt_meta_data_tcMainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *tcMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tcMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcMainWindow.stringdata))
        return static_cast<void*>(const_cast< tcMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int tcMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
