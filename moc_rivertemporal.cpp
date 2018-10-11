/****************************************************************************
** Meta object code from reading C++ file 'rivertemporal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../7VisualAnalytics/4RiverTemporal/rivertemporal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rivertemporal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RiverTemporal_t {
    QByteArrayData data[15];
    char stringdata0[380];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RiverTemporal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RiverTemporal_t qt_meta_stringdata_RiverTemporal = {
    {
QT_MOC_LITERAL(0, 0, 13), // "RiverTemporal"
QT_MOC_LITERAL(1, 14, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(4, 67, 37), // "on_pushButtonOutputDataFolder..."
QT_MOC_LITERAL(5, 105, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(6, 131, 44), // "on_comboBoxModelSegments_curr..."
QT_MOC_LITERAL(7, 176, 5), // "index"
QT_MOC_LITERAL(8, 182, 39), // "on_lineEditOutputDataFolder_t..."
QT_MOC_LITERAL(9, 222, 4), // "arg1"
QT_MOC_LITERAL(10, 227, 30), // "on_lineEditDataKey_textChanged"
QT_MOC_LITERAL(11, 258, 21), // "verifyInputOutputFile"
QT_MOC_LITERAL(12, 280, 18), // "pushButtonSetFocus"
QT_MOC_LITERAL(13, 299, 43), // "on_comboBoxPlotVariable_curre..."
QT_MOC_LITERAL(14, 343, 36) // "on_lineEditModelSegments_text..."

    },
    "RiverTemporal\0on_pushButtonRun_clicked\0"
    "\0on_pushButtonClose_clicked\0"
    "on_pushButtonOutputDataFolder_clicked\0"
    "on_pushButtonHelp_clicked\0"
    "on_comboBoxModelSegments_currentIndexChanged\0"
    "index\0on_lineEditOutputDataFolder_textChanged\0"
    "arg1\0on_lineEditDataKey_textChanged\0"
    "verifyInputOutputFile\0pushButtonSetFocus\0"
    "on_comboBoxPlotVariable_currentIndexChanged\0"
    "on_lineEditModelSegments_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RiverTemporal[] = {

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
       6,    1,   73,    2, 0x08 /* Private */,
       8,    1,   76,    2, 0x08 /* Private */,
      10,    1,   79,    2, 0x08 /* Private */,
      11,    0,   82,    2, 0x08 /* Private */,
      12,    0,   83,    2, 0x08 /* Private */,
      13,    1,   84,    2, 0x08 /* Private */,
      14,    1,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void RiverTemporal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RiverTemporal *_t = static_cast<RiverTemporal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonRun_clicked(); break;
        case 1: _t->on_pushButtonClose_clicked(); break;
        case 2: _t->on_pushButtonOutputDataFolder_clicked(); break;
        case 3: _t->on_pushButtonHelp_clicked(); break;
        case 4: _t->on_comboBoxModelSegments_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_lineEditOutputDataFolder_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_lineEditDataKey_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->verifyInputOutputFile(); break;
        case 8: _t->pushButtonSetFocus(); break;
        case 9: _t->on_comboBoxPlotVariable_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_lineEditModelSegments_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RiverTemporal::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RiverTemporal.data,
      qt_meta_data_RiverTemporal,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RiverTemporal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RiverTemporal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RiverTemporal.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int RiverTemporal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
