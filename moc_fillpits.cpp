/****************************************************************************
** Meta object code from reading C++ file 'fillpits.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../2RasterProcessing/1FillPits/fillpits.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fillpits.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FillPits_t {
    QByteArrayData data[14];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FillPits_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FillPits_t qt_meta_stringdata_FillPits = {
    {
QT_MOC_LITERAL(0, 0, 8), // "FillPits"
QT_MOC_LITERAL(1, 9, 24), // "on_pushButtonDEM_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 29), // "on_pushButtonFillPits_clicked"
QT_MOC_LITERAL(4, 65, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(5, 90, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(6, 117, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(7, 143, 18), // "pushButtonSetFocus"
QT_MOC_LITERAL(8, 162, 15), // "Check_DEM_Input"
QT_MOC_LITERAL(9, 178, 3), // "dem"
QT_MOC_LITERAL(10, 182, 20), // "Check_Fillpit_Output"
QT_MOC_LITERAL(11, 203, 8), // "fillpits"
QT_MOC_LITERAL(12, 212, 7), // "message"
QT_MOC_LITERAL(13, 220, 9) // "Clear_Log"

    },
    "FillPits\0on_pushButtonDEM_clicked\0\0"
    "on_pushButtonFillPits_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0pushButtonSetFocus\0"
    "Check_DEM_Input\0dem\0Check_Fillpit_Output\0"
    "fillpits\0message\0Clear_Log"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FillPits[] = {

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
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    1,   65,    2, 0x08 /* Private */,
      10,    2,   68,    2, 0x08 /* Private */,
      13,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    9,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,   11,   12,
    QMetaType::Void,

       0        // eod
};

void FillPits::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FillPits *_t = static_cast<FillPits *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonDEM_clicked(); break;
        case 1: _t->on_pushButtonFillPits_clicked(); break;
        case 2: _t->on_pushButtonRun_clicked(); break;
        case 3: _t->on_pushButtonClose_clicked(); break;
        case 4: _t->on_pushButtonHelp_clicked(); break;
        case 5: _t->pushButtonSetFocus(); break;
        case 6: { bool _r = _t->Check_DEM_Input((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->Check_Fillpit_Output((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->Clear_Log(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FillPits::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FillPits.data,
      qt_meta_data_FillPits,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FillPits::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FillPits::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FillPits.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FillPits::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
