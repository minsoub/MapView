/****************************************************************************
** Meta object code from reading C++ file 'ManualCoordEdit.h'
**
** Created: Fri Feb 1 10:13:19 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../lib/ManualCoordEdit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ManualCoordEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ManualCoordEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      37,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   16,   16,   16, 0x08,
      68,   16,   16,   16, 0x08,
      82,   16,   16,   16, 0x08,
      96,   16,   16,   16, 0x08,
     110,   16,   16,   16, 0x08,
     117,   16,   16,   16, 0x08,
     137,   16,   16,   16, 0x08,
     156,   16,   16,   16, 0x08,
     184,   16,  179,   16, 0x08,
     192,   16,   16,   16, 0x08,
     217,   16,   16,   16, 0x08,
     241,   16,   16,   16, 0x08,
     264,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ManualCoordEdit[] = {
    "ManualCoordEdit\0\0manualeditchanged()\0"
    "manualeditdone()\0insertPoint()\0"
    "updatePoint()\0deletePoint()\0clearPoints()\0"
    "done()\0onViacomboChanged()\0"
    "currentRowToEdit()\0circleradioclick(bool)\0"
    "bool\0check()\0polylineradioclick(bool)\0"
    "polygonradioclick(bool)\0symbolradioclick(bool)\0"
    "selectSymbol()\0"
};

const QMetaObject ManualCoordEdit::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ManualCoordEdit,
      qt_meta_data_ManualCoordEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ManualCoordEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ManualCoordEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ManualCoordEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ManualCoordEdit))
        return static_cast<void*>(const_cast< ManualCoordEdit*>(this));
    return QDialog::qt_metacast(_clname);
}

int ManualCoordEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: manualeditchanged(); break;
        case 1: manualeditdone(); break;
        case 2: insertPoint(); break;
        case 3: updatePoint(); break;
        case 4: deletePoint(); break;
        case 5: clearPoints(); break;
        case 6: done(); break;
        case 7: onViacomboChanged(); break;
        case 8: currentRowToEdit(); break;
        case 9: circleradioclick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: { bool _r = check();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: polylineradioclick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: polygonradioclick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: symbolradioclick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: selectSymbol(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ManualCoordEdit::manualeditchanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ManualCoordEdit::manualeditdone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
