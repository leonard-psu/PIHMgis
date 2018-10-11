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
    QByteArrayData data[16];
    char stringdata0[288];
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
QT_MOC_LITERAL(11, 227, 6), // "column"
QT_MOC_LITERAL(12, 234, 9), // "Clear_Log"
QT_MOC_LITERAL(13, 244, 21), // "Load_Project_Settings"
QT_MOC_LITERAL(14, 266, 16), // "Check_File_Valid"
QT_MOC_LITERAL(15, 283, 4) // "file"

    },
    "SimplifyPolylines\0pushButtonSetFocus\0"
    "\0on_pushButtonAdd_clicked\0"
    "on_pushButtonRemove_clicked\0"
    "on_pushButtonClear_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0"
    "on_tableWidget_cellChanged\0row\0column\0"
    "Clear_Log\0Load_Project_Settings\0"
    "Check_File_Valid\0file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimplifyPolylines[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    2,   76,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   15,

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
        case 8: _t->Clear_Log(); break;
        case 9: { bool _r = _t->Load_Project_Settings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->Check_File_Valid((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
