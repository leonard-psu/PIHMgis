/****************************************************************************
** Meta object code from reading C++ file 'qgsnewhttpconnection.h'
**
** Created: Wed Jun 11 19:10:43 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/app/qgsnewhttpconnection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qgsnewhttpconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_QgsNewHttpConnection[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x0a,
      39,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QgsNewHttpConnection[] = {
    "QgsNewHttpConnection\0\0saveConnection()\0"
    "on_btnHelp_clicked()\0"
};

const QMetaObject QgsNewHttpConnection::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QgsNewHttpConnection,
      qt_meta_data_QgsNewHttpConnection, 0 }
};

const QMetaObject *QgsNewHttpConnection::metaObject() const
{
    return &staticMetaObject;
}

void *QgsNewHttpConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QgsNewHttpConnection))
	return static_cast<void*>(const_cast< QgsNewHttpConnection*>(this));
    return QDialog::qt_metacast(_clname);
}

int QgsNewHttpConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: saveConnection(); break;
        case 1: on_btnHelp_clicked(); break;
        }
        _id -= 2;
    }
    return _id;
}
