/****************************************************************************
** Meta object code from reading C++ file 'GenerateView.h'
**
** Created: Fri Feb 1 10:13:46 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GenerateView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GenerateView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GenerateView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   14,   13,   13, 0x05,
      45,   41,   13,   13, 0x05,
      69,   41,   13,   13, 0x05,
      94,   41,   13,   13, 0x05,
     123,   13,   13,   13, 0x05,
     146,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     170,   14,   13,   13, 0x0a,
     189,   13,   13,   13, 0x0a,
     198,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GenerateView[] = {
    "GenerateView\0\0zoom\0setChangeZoom(double)\0"
    "msg\0changeMousePos(QString)\0"
    "changeLatLonPos(QString)\0"
    "changeStatusMessage(QString)\0"
    "userFinishedDrawCall()\0leftPanelWidgetChange()\0"
    "changeZoom(double)\0zoomIn()\0zoomOut()\0"
};

const QMetaObject GenerateView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GenerateView,
      qt_meta_data_GenerateView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GenerateView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GenerateView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GenerateView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GenerateView))
        return static_cast<void*>(const_cast< GenerateView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GenerateView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setChangeZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: changeMousePos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: changeLatLonPos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: changeStatusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: userFinishedDrawCall(); break;
        case 5: leftPanelWidgetChange(); break;
        case 6: changeZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: zoomIn(); break;
        case 8: zoomOut(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GenerateView::setChangeZoom(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GenerateView::changeMousePos(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GenerateView::changeLatLonPos(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GenerateView::changeStatusMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GenerateView::userFinishedDrawCall()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void GenerateView::leftPanelWidgetChange()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
