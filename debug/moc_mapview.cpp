/****************************************************************************
** Meta object code from reading C++ file 'mapview.h'
**
** Created: Fri Feb 1 10:13:48 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mapview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,    9,    8,    8, 0x08,
      36,    9,    8,    8, 0x08,
      65,   61,    8,    8, 0x08,
      94,    8,    8,    8, 0x08,
     103,    8,    8,    8, 0x08,
     114,    8,    8,    8, 0x08,
     125,    8,    8,    8, 0x08,
     137,    8,    8,    8, 0x08,
     148,    8,    8,    8, 0x08,
     157,    8,    8,    8, 0x08,
     167,    8,    8,    8, 0x08,
     185,    8,    8,    8, 0x08,
     192,    8,    8,    8, 0x08,
     202,    8,    8,    8, 0x08,
     211,    8,    8,    8, 0x08,
     224,    8,    8,    8, 0x08,
     232,    8,    8,    8, 0x0a,
     254,    8,    8,    8, 0x0a,
     282,  278,    8,    8, 0x0a,
     314,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapView[] = {
    "MapView\0\0xy\0changeMousePos(QString)\0"
    "changeLatLonPos(QString)\0msg\0"
    "changeStatusMessage(QString)\0moveUp()\0"
    "moveDown()\0moveLeft()\0moveRight()\0"
    "moveHome()\0zoomIn()\0zoomOut()\0"
    "setSymbolEditor()\0open()\0saveall()\0"
    "saveas()\0savePixmap()\0about()\0"
    "setLeftPanelVisible()\0setObjectPanelVisible()\0"
    "idx\0setObjectPanelVisibleChild(int)\0"
    "setUserDefinedMap()\0"
};

const QMetaObject MapView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MapView,
      qt_meta_data_MapView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapView))
        return static_cast<void*>(const_cast< MapView*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MapView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeMousePos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: changeLatLonPos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: changeStatusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: moveUp(); break;
        case 4: moveDown(); break;
        case 5: moveLeft(); break;
        case 6: moveRight(); break;
        case 7: moveHome(); break;
        case 8: zoomIn(); break;
        case 9: zoomOut(); break;
        case 10: setSymbolEditor(); break;
        case 11: open(); break;
        case 12: saveall(); break;
        case 13: saveas(); break;
        case 14: savePixmap(); break;
        case 15: about(); break;
        case 16: setLeftPanelVisible(); break;
        case 17: setObjectPanelVisible(); break;
        case 18: setObjectPanelVisibleChild((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: setUserDefinedMap(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
