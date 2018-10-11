/****************************************************************************
** Meta object code from reading C++ file 'mergevectorlayers.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../3VectorProcessing/5MergeVectorLayers/mergevectorlayers.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mergevectorlayers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MergeVectorLayers_t {
    QByteArrayData data[14];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MergeVectorLayers_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MergeVectorLayers_t qt_meta_stringdata_MergeVectorLayers = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MergeVectorLayers"
QT_MOC_LITERAL(1, 18, 24), // "on_pushButtonAdd_clicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 27), // "on_pushButtonRemove_clicked"
QT_MOC_LITERAL(4, 72, 26), // "on_pushButtonClear_clicked"
QT_MOC_LITERAL(5, 99, 31), // "on_pushButtonMergeLayer_clicked"
QT_MOC_LITERAL(6, 131, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(7, 156, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(8, 183, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(9, 209, 18), // "pushButtonSetFocus"
QT_MOC_LITERAL(10, 228, 9), // "Clear_Log"
QT_MOC_LITERAL(11, 238, 21), // "Load_Project_Settings"
QT_MOC_LITERAL(12, 260, 16), // "Check_File_Valid"
QT_MOC_LITERAL(13, 277, 4) // "file"

    },
    "MergeVectorLayers\0on_pushButtonAdd_clicked\0"
    "\0on_pushButtonRemove_clicked\0"
    "on_pushButtonClear_clicked\0"
    "on_pushButtonMergeLayer_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0pushButtonSetFocus\0"
    "Clear_Log\0Load_Project_Settings\0"
    "Check_File_Valid\0file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MergeVectorLayers[] = {

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
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    1,   79,    2, 0x08 /* Private */,

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
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   13,

       0        // eod
};

void MergeVectorLayers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MergeVectorLayers *_t = static_cast<MergeVectorLayers *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonAdd_clicked(); break;
        case 1: _t->on_pushButtonRemove_clicked(); break;
        case 2: _t->on_pushButtonClear_clicked(); break;
        case 3: _t->on_pushButtonMergeLayer_clicked(); break;
        case 4: _t->on_pushButtonRun_clicked(); break;
        case 5: _t->on_pushButtonClose_clicked(); break;
        case 6: _t->on_pushButtonHelp_clicked(); break;
        case 7: _t->pushButtonSetFocus(); break;
        case 8: _t->Clear_Log(); break;
        case 9: { bool _r = _t->Load_Project_Settings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->Check_File_Valid((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MergeVectorLayers::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MergeVectorLayers.data,
      qt_meta_data_MergeVectorLayers,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MergeVectorLayers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MergeVectorLayers::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MergeVectorLayers.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MergeVectorLayers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
