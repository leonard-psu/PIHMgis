/****************************************************************************
** Meta object code from reading C++ file 'polygontopolylines.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../3VectorProcessing/2PolygonToPolylines/polygontopolylines.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'polygontopolylines.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PolygonToPolylines_t {
    QByteArrayData data[13];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PolygonToPolylines_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PolygonToPolylines_t qt_meta_stringdata_PolygonToPolylines = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PolygonToPolylines"
QT_MOC_LITERAL(1, 19, 24), // "on_pushButtonAdd_clicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 27), // "on_pushButtonRemove_clicked"
QT_MOC_LITERAL(4, 73, 26), // "on_pushButtonClear_clicked"
QT_MOC_LITERAL(5, 100, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(6, 125, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(7, 152, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(8, 178, 18), // "pushButtonSetFocus"
QT_MOC_LITERAL(9, 197, 9), // "Clear_Log"
QT_MOC_LITERAL(10, 207, 16), // "Check_File_Valid"
QT_MOC_LITERAL(11, 224, 4), // "file"
QT_MOC_LITERAL(12, 229, 21) // "Load_Project_Settings"

    },
    "PolygonToPolylines\0on_pushButtonAdd_clicked\0"
    "\0on_pushButtonRemove_clicked\0"
    "on_pushButtonClear_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0pushButtonSetFocus\0"
    "Clear_Log\0Check_File_Valid\0file\0"
    "Load_Project_Settings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PolygonToPolylines[] = {

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
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    1,   72,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   11,
    QMetaType::Bool,

       0        // eod
};

void PolygonToPolylines::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PolygonToPolylines *_t = static_cast<PolygonToPolylines *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonAdd_clicked(); break;
        case 1: _t->on_pushButtonRemove_clicked(); break;
        case 2: _t->on_pushButtonClear_clicked(); break;
        case 3: _t->on_pushButtonRun_clicked(); break;
        case 4: _t->on_pushButtonClose_clicked(); break;
        case 5: _t->on_pushButtonHelp_clicked(); break;
        case 6: _t->pushButtonSetFocus(); break;
        case 7: _t->Clear_Log(); break;
        case 8: { bool _r = _t->Check_File_Valid((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->Load_Project_Settings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PolygonToPolylines::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PolygonToPolylines.data,
      qt_meta_data_PolygonToPolylines,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PolygonToPolylines::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PolygonToPolylines::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PolygonToPolylines.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int PolygonToPolylines::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
