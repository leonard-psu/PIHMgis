/****************************************************************************
** Meta object code from reading C++ file 'splitlinedialog.h'
**
** Created: Wed Jun 11 19:11:08 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/pihm_gis/VectorProcessing/SplitLine/splitlinedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'splitlinedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_splitLineDialogDlg[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      32,   19,   19,   19, 0x0a,
      47,   19,   19,   19, 0x0a,
      65,   19,   19,   19, 0x0a,
      71,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_splitLineDialogDlg[] = {
    "splitLineDialogDlg\0\0addBrowse()\0"
    "removeBrowse()\0removeAllBrowse()\0run()\0"
    "help()\0"
};

const QMetaObject splitLineDialogDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_splitLineDialogDlg,
      qt_meta_data_splitLineDialogDlg, 0 }
};

const QMetaObject *splitLineDialogDlg::metaObject() const
{
    return &staticMetaObject;
}

void *splitLineDialogDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_splitLineDialogDlg))
	return static_cast<void*>(const_cast< splitLineDialogDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int splitLineDialogDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addBrowse(); break;
        case 1: removeBrowse(); break;
        case 2: removeAllBrowse(); break;
        case 3: run(); break;
        case 4: help(); break;
        }
        _id -= 5;
    }
    return _id;
}
