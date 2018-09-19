/****************************************************************************
** Meta object code from reading C++ file 'catchmentgrids.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../2RasterProcessing/5CatchmentGrids/catchmentgrids.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'catchmentgrids.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CatchmentGrids_t {
    QByteArrayData data[9];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CatchmentGrids_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CatchmentGrids_t qt_meta_stringdata_CatchmentGrids = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CatchmentGrids"
QT_MOC_LITERAL(1, 15, 30), // "on_pushButtonLinkGrids_clicked"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 33), // "on_pushButtonFlowDirGrids_cli..."
QT_MOC_LITERAL(4, 81, 35), // "on_pushButtonCatchmentGrids_c..."
QT_MOC_LITERAL(5, 117, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(6, 142, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(7, 169, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(8, 195, 18) // "pushButtonSetFocus"

    },
    "CatchmentGrids\0on_pushButtonLinkGrids_clicked\0"
    "\0on_pushButtonFlowDirGrids_clicked\0"
    "on_pushButtonCatchmentGrids_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0pushButtonSetFocus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CatchmentGrids[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CatchmentGrids::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CatchmentGrids *_t = static_cast<CatchmentGrids *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonLinkGrids_clicked(); break;
        case 1: _t->on_pushButtonFlowDirGrids_clicked(); break;
        case 2: _t->on_pushButtonCatchmentGrids_clicked(); break;
        case 3: _t->on_pushButtonRun_clicked(); break;
        case 4: _t->on_pushButtonClose_clicked(); break;
        case 5: _t->on_pushButtonHelp_clicked(); break;
        case 6: _t->pushButtonSetFocus(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CatchmentGrids::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CatchmentGrids.data,
      qt_meta_data_CatchmentGrids,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CatchmentGrids::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CatchmentGrids::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CatchmentGrids.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CatchmentGrids::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
