/****************************************************************************
** Meta object code from reading C++ file 'streampolyline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../2RasterProcessing/6StreamPolyline/streampolyline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'streampolyline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StreamPolyline_t {
    QByteArrayData data[15];
    char stringdata0[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StreamPolyline_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StreamPolyline_t qt_meta_stringdata_StreamPolyline = {
    {
QT_MOC_LITERAL(0, 0, 14), // "StreamPolyline"
QT_MOC_LITERAL(1, 15, 32), // "on_pushButtonStreamGrids_clicked"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 33), // "on_pushButtonFlowDirGrids_cli..."
QT_MOC_LITERAL(4, 83, 35), // "on_pushButtonStreamPolyline_c..."
QT_MOC_LITERAL(5, 119, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(6, 144, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(7, 171, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(8, 197, 18), // "pushButtonSetFocus"
QT_MOC_LITERAL(9, 216, 9), // "Clear_Log"
QT_MOC_LITERAL(10, 226, 23), // "Check_StreamGrids_Input"
QT_MOC_LITERAL(11, 250, 4), // "file"
QT_MOC_LITERAL(12, 255, 24), // "Check_FlowDirGrids_Input"
QT_MOC_LITERAL(13, 280, 27), // "Check_StreamPolyline_Output"
QT_MOC_LITERAL(14, 308, 7) // "message"

    },
    "StreamPolyline\0on_pushButtonStreamGrids_clicked\0"
    "\0on_pushButtonFlowDirGrids_clicked\0"
    "on_pushButtonStreamPolyline_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0pushButtonSetFocus\0"
    "Clear_Log\0Check_StreamGrids_Input\0"
    "file\0Check_FlowDirGrids_Input\0"
    "Check_StreamPolyline_Output\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StreamPolyline[] = {

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
       9,    0,   76,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      13,    2,   83,    2, 0x08 /* Private */,

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
    QMetaType::Bool, QMetaType::QString,   11,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,   11,   14,

       0        // eod
};

void StreamPolyline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StreamPolyline *_t = static_cast<StreamPolyline *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonStreamGrids_clicked(); break;
        case 1: _t->on_pushButtonFlowDirGrids_clicked(); break;
        case 2: _t->on_pushButtonStreamPolyline_clicked(); break;
        case 3: _t->on_pushButtonRun_clicked(); break;
        case 4: _t->on_pushButtonClose_clicked(); break;
        case 5: _t->on_pushButtonHelp_clicked(); break;
        case 6: _t->pushButtonSetFocus(); break;
        case 7: _t->Clear_Log(); break;
        case 8: { bool _r = _t->Check_StreamGrids_Input((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->Check_FlowDirGrids_Input((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->Check_StreamPolyline_Output((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StreamPolyline::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StreamPolyline.data,
      qt_meta_data_StreamPolyline,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StreamPolyline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StreamPolyline::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StreamPolyline.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int StreamPolyline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
