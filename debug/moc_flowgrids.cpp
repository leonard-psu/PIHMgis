/****************************************************************************
** Meta object code from reading C++ file 'flowgrids.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../2RasterProcessing/2FlowGrids/flowgrids.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flowgrids.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlowGrids_t {
    QByteArrayData data[15];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlowGrids_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlowGrids_t qt_meta_stringdata_FlowGrids = {
    {
QT_MOC_LITERAL(0, 0, 9), // "FlowGrids"
QT_MOC_LITERAL(1, 10, 29), // "on_pushButtonFillPits_clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 33), // "on_pushButtonsFlowDirGrid_cli..."
QT_MOC_LITERAL(4, 75, 32), // "on_pushButtonFlowAccGrid_clicked"
QT_MOC_LITERAL(5, 108, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(6, 133, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(7, 160, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(8, 186, 18), // "pushButtonSetFocus"
QT_MOC_LITERAL(9, 205, 19), // "Check_Fillpit_Input"
QT_MOC_LITERAL(10, 225, 4), // "file"
QT_MOC_LITERAL(11, 230, 20), // "Check_FlowDir_Output"
QT_MOC_LITERAL(12, 251, 7), // "message"
QT_MOC_LITERAL(13, 259, 20), // "Check_FlowAcc_Output"
QT_MOC_LITERAL(14, 280, 9) // "Clear_Log"

    },
    "FlowGrids\0on_pushButtonFillPits_clicked\0"
    "\0on_pushButtonsFlowDirGrid_clicked\0"
    "on_pushButtonFlowAccGrid_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0pushButtonSetFocus\0"
    "Check_Fillpit_Input\0file\0Check_FlowDir_Output\0"
    "message\0Check_FlowAcc_Output\0Clear_Log"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlowGrids[] = {

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
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    1,   76,    2, 0x08 /* Private */,
      11,    2,   79,    2, 0x08 /* Private */,
      13,    2,   84,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,   10,   12,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,   10,   12,
    QMetaType::Void,

       0        // eod
};

void FlowGrids::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlowGrids *_t = static_cast<FlowGrids *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonFillPits_clicked(); break;
        case 1: _t->on_pushButtonsFlowDirGrid_clicked(); break;
        case 2: _t->on_pushButtonFlowAccGrid_clicked(); break;
        case 3: _t->on_pushButtonRun_clicked(); break;
        case 4: _t->on_pushButtonClose_clicked(); break;
        case 5: _t->on_pushButtonHelp_clicked(); break;
        case 6: _t->pushButtonSetFocus(); break;
        case 7: { bool _r = _t->Check_Fillpit_Input((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->Check_FlowDir_Output((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->Check_FlowAcc_Output((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->Clear_Log(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FlowGrids::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FlowGrids.data,
      qt_meta_data_FlowGrids,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FlowGrids::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlowGrids::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlowGrids.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FlowGrids::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
