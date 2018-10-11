/****************************************************************************
** Meta object code from reading C++ file 'meshspatial.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../7VisualAnalytics/1MeshSpatial/meshspatial.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'meshspatial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MeshSpatial_t {
    QByteArrayData data[16];
    char stringdata0[409];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MeshSpatial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MeshSpatial_t qt_meta_stringdata_MeshSpatial = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MeshSpatial"
QT_MOC_LITERAL(1, 12, 37), // "on_pushButtonOutputDataFolder..."
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 39), // "on_lineEditOutputDataFolder_t..."
QT_MOC_LITERAL(4, 91, 4), // "arg1"
QT_MOC_LITERAL(5, 96, 30), // "on_lineEditDataKey_textChanged"
QT_MOC_LITERAL(6, 127, 43), // "on_comboBoxPlotVariable_curre..."
QT_MOC_LITERAL(7, 171, 5), // "index"
QT_MOC_LITERAL(8, 177, 21), // "verifyInputOutputFile"
QT_MOC_LITERAL(9, 199, 18), // "pushButtonSetFocus"
QT_MOC_LITERAL(10, 218, 40), // "on_comboBoxStartStop_currentI..."
QT_MOC_LITERAL(11, 259, 34), // "on_pushButtonMeshShapeFile_cl..."
QT_MOC_LITERAL(12, 294, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(13, 319, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(14, 346, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(15, 372, 36) // "on_lineEditMeshShapeFile_text..."

    },
    "MeshSpatial\0on_pushButtonOutputDataFolder_clicked\0"
    "\0on_lineEditOutputDataFolder_textChanged\0"
    "arg1\0on_lineEditDataKey_textChanged\0"
    "on_comboBoxPlotVariable_currentIndexChanged\0"
    "index\0verifyInputOutputFile\0"
    "pushButtonSetFocus\0"
    "on_comboBoxStartStop_currentIndexChanged\0"
    "on_pushButtonMeshShapeFile_clicked\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0"
    "on_lineEditMeshShapeFile_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MeshSpatial[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       5,    1,   78,    2, 0x08 /* Private */,
       6,    1,   81,    2, 0x08 /* Private */,
       8,    0,   84,    2, 0x08 /* Private */,
       9,    0,   85,    2, 0x08 /* Private */,
      10,    1,   86,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    1,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void MeshSpatial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MeshSpatial *_t = static_cast<MeshSpatial *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonOutputDataFolder_clicked(); break;
        case 1: _t->on_lineEditOutputDataFolder_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_lineEditDataKey_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_comboBoxPlotVariable_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->verifyInputOutputFile(); break;
        case 5: _t->pushButtonSetFocus(); break;
        case 6: _t->on_comboBoxStartStop_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_pushButtonMeshShapeFile_clicked(); break;
        case 8: _t->on_pushButtonRun_clicked(); break;
        case 9: _t->on_pushButtonClose_clicked(); break;
        case 10: _t->on_pushButtonHelp_clicked(); break;
        case 11: _t->on_lineEditMeshShapeFile_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MeshSpatial::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MeshSpatial.data,
      qt_meta_data_MeshSpatial,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MeshSpatial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MeshSpatial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MeshSpatial.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int MeshSpatial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
