/****************************************************************************
** Meta object code from reading C++ file 'MapLayerPanel.h'
**
** Created: Fri Feb 1 10:13:40 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../leftlayout/MapLayerPanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapLayerPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapLayerPanel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      33,   14,   14,   14, 0x05,
      50,   48,   14,   14, 0x05,
      84,   74,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     107,   74,   14,   14, 0x0a,
     123,   74,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapLayerPanel[] = {
    "MapLayerPanel\0\0checkboxclicked()\0"
    "labelclicked()\0b\0maplayerselectall(bool)\0"
    "layertype\0checkStateChanged(int)\0"
    "checkClick(int)\0labelClick(int)\0"
};

const QMetaObject MapLayerPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MapLayerPanel,
      qt_meta_data_MapLayerPanel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapLayerPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapLayerPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapLayerPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapLayerPanel))
        return static_cast<void*>(const_cast< MapLayerPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int MapLayerPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkboxclicked(); break;
        case 1: labelclicked(); break;
        case 2: maplayerselectall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: checkStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: checkClick((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: labelClick((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MapLayerPanel::checkboxclicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MapLayerPanel::labelclicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MapLayerPanel::maplayerselectall(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MapLayerPanel::checkStateChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
