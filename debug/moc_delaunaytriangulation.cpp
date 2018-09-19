/****************************************************************************
** Meta object code from reading C++ file 'delaunaytriangulation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../4DomainDecomposition/2DelaunayTriangulation/delaunaytriangulation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'delaunaytriangulation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DelaunayTriangulation_t {
    QByteArrayData data[15];
    char stringdata0[321];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DelaunayTriangulation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DelaunayTriangulation_t qt_meta_stringdata_DelaunayTriangulation = {
    {
QT_MOC_LITERAL(0, 0, 21), // "DelaunayTriangulation"
QT_MOC_LITERAL(1, 22, 25), // "on_pushButtonPSLG_clicked"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 24), // "on_checkBoxAngle_toggled"
QT_MOC_LITERAL(4, 74, 7), // "checked"
QT_MOC_LITERAL(5, 82, 23), // "on_checkBoxArea_toggled"
QT_MOC_LITERAL(6, 106, 25), // "on_checkBoxOthers_toggled"
QT_MOC_LITERAL(7, 132, 28), // "on_lineEditAngle_textChanged"
QT_MOC_LITERAL(8, 161, 4), // "arg1"
QT_MOC_LITERAL(9, 166, 27), // "on_lineEditArea_textChanged"
QT_MOC_LITERAL(10, 194, 29), // "on_lineEditOthers_textChanged"
QT_MOC_LITERAL(11, 224, 24), // "on_pushButtonRun_clicked"
QT_MOC_LITERAL(12, 249, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(13, 276, 25), // "on_pushButtonHelp_clicked"
QT_MOC_LITERAL(14, 302, 18) // "pushButtonSetFocus"

    },
    "DelaunayTriangulation\0on_pushButtonPSLG_clicked\0"
    "\0on_checkBoxAngle_toggled\0checked\0"
    "on_checkBoxArea_toggled\0"
    "on_checkBoxOthers_toggled\0"
    "on_lineEditAngle_textChanged\0arg1\0"
    "on_lineEditArea_textChanged\0"
    "on_lineEditOthers_textChanged\0"
    "on_pushButtonRun_clicked\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonHelp_clicked\0pushButtonSetFocus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DelaunayTriangulation[] = {

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
       3,    1,   70,    2, 0x08 /* Private */,
       5,    1,   73,    2, 0x08 /* Private */,
       6,    1,   76,    2, 0x08 /* Private */,
       7,    1,   79,    2, 0x08 /* Private */,
       9,    1,   82,    2, 0x08 /* Private */,
      10,    1,   85,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DelaunayTriangulation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DelaunayTriangulation *_t = static_cast<DelaunayTriangulation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonPSLG_clicked(); break;
        case 1: _t->on_checkBoxAngle_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_checkBoxArea_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_checkBoxOthers_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_lineEditAngle_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_lineEditArea_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_lineEditOthers_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_pushButtonRun_clicked(); break;
        case 8: _t->on_pushButtonClose_clicked(); break;
        case 9: _t->on_pushButtonHelp_clicked(); break;
        case 10: _t->pushButtonSetFocus(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DelaunayTriangulation::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DelaunayTriangulation.data,
      qt_meta_data_DelaunayTriangulation,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DelaunayTriangulation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DelaunayTriangulation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DelaunayTriangulation.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DelaunayTriangulation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
