/****************************************************************************
** Meta object code from reading C++ file 'runtriangle.h'
**
** Created: Wed Jun 11 19:11:09 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/pihm_gis/DomainDecomposition/RunTriangle/runtriangle.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'runtriangle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_runTriangleDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      30,   15,   15,   15, 0x0a,
      40,   15,   15,   15, 0x0a,
      46,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_runTriangleDlg[] = {
    "runTriangleDlg\0\0inputBrowse()\0options()\0"
    "run()\0help()\0"
};

const QMetaObject runTriangleDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_runTriangleDlg,
      qt_meta_data_runTriangleDlg, 0 }
};

const QMetaObject *runTriangleDlg::metaObject() const
{
    return &staticMetaObject;
}

void *runTriangleDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_runTriangleDlg))
	return static_cast<void*>(const_cast< runTriangleDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int runTriangleDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: inputBrowse(); break;
        case 1: options(); break;
        case 2: run(); break;
        case 3: help(); break;
        }
        _id -= 4;
    }
    return _id;
}
