/****************************************************************************
** Meta object code from reading C++ file 'qgsmaprender.h'
**
** Created: Wed Jun 11 19:03:32 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/core/qgsmaprender.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qgsmaprender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_QgsMapRender[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      28,   14,   13,   13, 0x05,
      58,   53,   13,   13, 0x05,
      83,   13,   13,   13, 0x05,
     107,   13,   13,   13, 0x05,
     119,   13,   13,   13, 0x05,
     137,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     161,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QgsMapRender[] = {
    "QgsMapRender\0\0current,total\0"
    "drawingProgress(int,int)\0flag\0"
    "projectionsEnabled(bool)\0"
    "destinationSrsChanged()\0updateMap()\0"
    "mapUnitsChanged()\0drawError(QgsMapLayer*)\0"
    "onDrawingProgress(int,int)\0"
};

const QMetaObject QgsMapRender::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QgsMapRender,
      qt_meta_data_QgsMapRender, 0 }
};

const QMetaObject *QgsMapRender::metaObject() const
{
    return &staticMetaObject;
}

void *QgsMapRender::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QgsMapRender))
	return static_cast<void*>(const_cast< QgsMapRender*>(this));
    return QObject::qt_metacast(_clname);
}

int QgsMapRender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: drawingProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: projectionsEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: destinationSrsChanged(); break;
        case 3: updateMap(); break;
        case 4: mapUnitsChanged(); break;
        case 5: drawError((*reinterpret_cast< QgsMapLayer*(*)>(_a[1]))); break;
        case 6: onDrawingProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QgsMapRender::drawingProgress(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QgsMapRender::projectionsEnabled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QgsMapRender::destinationSrsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QgsMapRender::updateMap()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QgsMapRender::mapUnitsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QgsMapRender::drawError(QgsMapLayer * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
