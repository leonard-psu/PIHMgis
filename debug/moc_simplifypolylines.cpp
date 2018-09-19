/****************************************************************************
** Meta object code from reading C++ file 'simplifypolylines.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../3VectorProcessing/3SimplifyPolylines/simplifypolylines.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simplifypolylines.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimplifyPolylines_t {
    QByteArrayData data[12];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimplifyPolylines_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimplifyPolylines_t qt_meta_stringdata_SimplifyPolylines = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SimplifyPolylines"
QT_MOC_LITERAL(1, 18, 18), // "pushButtonSetFocus"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 24), // "on_pushButtonAdd_clicked"
QT_MOC_LITERAL(4, 63, 27), // "on_pushButtonRemove_clicked"
QT_MOC_LITERAL(5, 91, 26), // "on_pushButtonClear_clicked"
QT_MOC_LITERAL(6, 118, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(7, 143, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(8, 170, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(9, 196, 26), // "on_tableWidget_cellChanged"
QT_MOC_LITERAL(10, 223, 3), // "row"
QT_MOC_LITERAL(11, 227, 6) // "column"

    },
    "SimplifyPolylines\0pushButtonSetFocus\0"
    "\0on_pushButtonAdd_clicked\0"
    "on_pushButtonRemove_clicked\0"
    "on_pushButtonClear_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0"
    "on_tableWidget_cellChanged\0row\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimplifyPolylines[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    2,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,

       0        // eod
};

void SimplifyPolylines::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SimplifyPolylines *_t = static_cast<SimplifyPolylines *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pushButtonSetFocus(); break;
        case 1: _t->on_pushButtonAdd_clicked(); break;
        case 2: _t->on_pushButtonRemove_clicked(); break;
        case 3: _t->on_pushButtonClear_clicked(); break;
        case 4: _t->on_pushButtonRun_clicked(); break;
        case 5: _t->on_pushButtonClose_clicked(); break;
        case 6: _t->on_pushButtonHelp_clicked(); break;
        case 7: _t->on_tableWidget_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SimplifyPolylines::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SimplifyPolylines.data,
      qt_meta_data_SimplifyPolylines,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SimplifyPolylines::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimplifyPolylines::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimplifyPolylines.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SimplifyPolylines::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
