/****************************************************************************
** Meta object code from reading C++ file 'qgscomposermap.h'
**
** Created: Mon Sep 7 22:35:31 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/core/composer/qgscomposermap.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qgscomposermap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_QgsComposerMap[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QgsComposerMap[] = {
    "QgsComposerMap\0\0extentChanged()\0"
    "mapCanvasChanged()\0"
};

const QMetaObject QgsComposerMap::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QgsComposerMap,
      qt_meta_data_QgsComposerMap, 0 }
};

const QMetaObject *QgsComposerMap::metaObject() const
{
    return &staticMetaObject;
}

void *QgsComposerMap::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QgsComposerMap))
	return static_cast<void*>(const_cast< QgsComposerMap*>(this));
    if (!strcmp(_clname, "QgsComposerItem"))
	return static_cast< QgsComposerItem*>(const_cast< QgsComposerMap*>(this));
    return QObject::qt_metacast(_clname);
}

int QgsComposerMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: extentChanged(); break;
        case 1: mapCanvasChanged(); break;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QgsComposerMap::extentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
