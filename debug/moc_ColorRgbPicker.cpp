/****************************************************************************
** Meta object code from reading C++ file 'ColorRgbPicker.h'
**
** Created: Fri Feb 1 10:13:27 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../lib/ColorRgbPicker.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColorRgbPicker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColorRgbPicker[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   15,   15,   15, 0x0a,
      43,   37,   15,   15, 0x0a,
      71,   65,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ColorRgbPicker[] = {
    "ColorRgbPicker\0\0changed()\0setColor()\0"
    "r,g,b\0setColor(int,int,int)\0color\0"
    "setColor(QColor)\0"
};

const QMetaObject ColorRgbPicker::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ColorRgbPicker,
      qt_meta_data_ColorRgbPicker, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColorRgbPicker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColorRgbPicker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColorRgbPicker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColorRgbPicker))
        return static_cast<void*>(const_cast< ColorRgbPicker*>(this));
    return QWidget::qt_metacast(_clname);
}

int ColorRgbPicker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changed(); break;
        case 1: setColor(); break;
        case 2: setColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ColorRgbPicker::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
