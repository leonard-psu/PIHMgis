/****************************************************************************
** Meta object code from reading C++ file 'qgslabeldialog.h'
**
** Created: Wed Jun 11 19:05:43 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/app/qgslabeldialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qgslabeldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_QgsLabelDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   15,   15,   15, 0x0a,
      41,   15,   15,   15, 0x0a,
      54,   15,   15,   15, 0x0a,
      74,   15,   15,   15, 0x0a,
      92,   15,   15,   15, 0x0a,
      99,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QgsLabelDialog[] = {
    "QgsLabelDialog\0\0labelSourceSet()\0"
    "apply()\0changeFont()\0changeBufferColor()\0"
    "changeFontColor()\0init()\0"
    "on_cboLabelField_activated(int)\0"
};

const QMetaObject QgsLabelDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QgsLabelDialog,
      qt_meta_data_QgsLabelDialog, 0 }
};

const QMetaObject *QgsLabelDialog::metaObject() const
{
    return &staticMetaObject;
}

void *QgsLabelDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QgsLabelDialog))
	return static_cast<void*>(const_cast< QgsLabelDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int QgsLabelDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: labelSourceSet(); break;
        case 1: apply(); break;
        case 2: changeFont(); break;
        case 3: changeBufferColor(); break;
        case 4: changeFontColor(); break;
        case 5: init(); break;
        case 6: on_cboLabelField_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QgsLabelDialog::labelSourceSet()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
