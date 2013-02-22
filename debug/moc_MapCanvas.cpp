/****************************************************************************
** Meta object code from reading C++ file 'MapCanvas.h'
**
** Created: Fri Feb 1 10:13:44 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MapCanvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapCanvas[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   11,   10,   10, 0x05,
      55,   51,   10,   10, 0x05,
      79,   51,   10,   10, 0x05,
     104,   51,   10,   10, 0x05,
     138,  133,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     160,   51,   10,   10, 0x08,
     183,   51,   10,   10, 0x08,
     207,   51,   10,   10, 0x08,
     235,   10,   10,   10, 0x08,
     257,   10,   10,   10, 0x08,
     271,   10,   10,   10, 0x08,
     283,   10,   10,   10, 0x08,
     295,   10,   10,   10, 0x08,
     309,   10,   10,   10, 0x08,
     324,   10,   10,   10, 0x08,
     339,   10,   10,   10, 0x08,
     360,  352,   10,   10, 0x08,
     400,   10,   10,   10, 0x08,
     431,  418,   10,   10, 0x0a,
     482,  456,   10,   10, 0x0a,
     527,  133,   10,   10, 0x0a,
     546,   11,   10,   10, 0x0a,
     568,   10,   10,   10, 0x0a,
     587,  583,   10,   10, 0x0a,
     618,   10,   10,   10, 0x0a,
     638,  583,   10,   10, 0x0a,
     669,  657,   10,   10, 0x0a,
     702,  700,   10,   10, 0x0a,
     719,  700,   10,   10, 0x0a,
     743,  700,   10,   10, 0x0a,
     766,  700,   10,   10, 0x0a,
     792,   10,   10,   10, 0x0a,
     809,   10,   10,   10, 0x0a,
     829,   10,   10,   10, 0x0a,
     850,   10,   10,   10, 0x0a,
     887,   10,   10,   10, 0x0a,
     907,   10,   10,   10, 0x0a,
     924,   10,   10,   10, 0x0a,
     946,   10,   10,   10, 0x0a,
     953,   10,   10,   10, 0x0a,
     975,  966,   10,   10, 0x0a,
     991,   10,   10,   10, 0x0a,
    1005,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapCanvas[] = {
    "MapCanvas\0\0dt\0changeObjectDrawTypeButton(DrawType)\0"
    "msg\0changeMousePos(QString)\0"
    "changeLatLonPos(QString)\0"
    "changeStatusMessage(QString)\0zoom\0"
    "setChangeZoom(double)\0catchMousePos(QString)\0"
    "catchLatLonPos(QString)\0"
    "catchStatusMessage(QString)\0"
    "leftChangedToReload()\0trackCreate()\0"
    "trackSave()\0trackOpen()\0trackOption()\0"
    "trackClTable()\0trackClPanel()\0"
    "trackPrint()\0from,to\0"
    "setCreateTrackReport(QString&,QString&)\0"
    "setReportOption()\0layerVisible\0"
    "setLayerVisible(QString)\0"
    "t,id,layervisible,visible\0"
    "setDrawIdFlag(int,QString,LayerVisible,bool)\0"
    "changeZoom(double)\0setDrawType(DrawType)\0"
    "finishedDraw()\0uid\0findUidAndSetProperty(QString)\0"
    "changeUidProperty()\0deleteUid(QString)\0"
    "oldid,newid\0changeUidName(QString,QString)\0"
    "b\0showLatLon(bool)\0showBearingCircle(bool)\0"
    "onoffLayerIdText(bool)\0onoffDistancBearing(bool)\0"
    "manualEditDone()\0manualEditChanged()\0"
    "manualEditCanceled()\0"
    "trackReport(QVector<TrackDataModel>)\0"
    "dataBlockPrint(int)\0clearTrackData()\0"
    "setProgressValue(int)\0save()\0saveultodb()\0"
    "fileName\0saveas(QString)\0getulfromdb()\0"
    "makeMapFromDb()\0"
};

const QMetaObject MapCanvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MapCanvas,
      qt_meta_data_MapCanvas, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapCanvas))
        return static_cast<void*>(const_cast< MapCanvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int MapCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeObjectDrawTypeButton((*reinterpret_cast< DrawType(*)>(_a[1]))); break;
        case 1: changeMousePos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: changeLatLonPos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: changeStatusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: setChangeZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: catchMousePos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: catchLatLonPos((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: catchStatusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: leftChangedToReload(); break;
        case 9: trackCreate(); break;
        case 10: trackSave(); break;
        case 11: trackOpen(); break;
        case 12: trackOption(); break;
        case 13: trackClTable(); break;
        case 14: trackClPanel(); break;
        case 15: trackPrint(); break;
        case 16: setCreateTrackReport((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: setReportOption(); break;
        case 18: setLayerVisible((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: setDrawIdFlag((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< LayerVisible(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 20: changeZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: setDrawType((*reinterpret_cast< DrawType(*)>(_a[1]))); break;
        case 22: finishedDraw(); break;
        case 23: findUidAndSetProperty((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: changeUidProperty(); break;
        case 25: deleteUid((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: changeUidName((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 27: showLatLon((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: showBearingCircle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: onoffLayerIdText((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: onoffDistancBearing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: manualEditDone(); break;
        case 32: manualEditChanged(); break;
        case 33: manualEditCanceled(); break;
        case 34: trackReport((*reinterpret_cast< QVector<TrackDataModel>(*)>(_a[1]))); break;
        case 35: dataBlockPrint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: clearTrackData(); break;
        case 37: setProgressValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: save(); break;
        case 39: saveultodb(); break;
        case 40: saveas((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: getulfromdb(); break;
        case 42: makeMapFromDb(); break;
        default: ;
        }
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void MapCanvas::changeObjectDrawTypeButton(DrawType _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MapCanvas::changeMousePos(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MapCanvas::changeLatLonPos(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MapCanvas::changeStatusMessage(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MapCanvas::setChangeZoom(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
