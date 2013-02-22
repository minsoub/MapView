/****************************************************************************
** Meta object code from reading C++ file 'TrackReportOption.h'
**
** Created: Fri Feb 1 10:13:00 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../trackrpt/TrackReportOption.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrackReportOption.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrackReportOption[] = {

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
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   18,   18,   18, 0x08,
      48,   18,   18,   18, 0x08,
      60,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TrackReportOption[] = {
    "TrackReportOption\0\0setReportOption()\0"
    "listLeft()\0listRight()\0optionSave()\0"
};

const QMetaObject TrackReportOption::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TrackReportOption,
      qt_meta_data_TrackReportOption, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TrackReportOption::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TrackReportOption::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TrackReportOption::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrackReportOption))
        return static_cast<void*>(const_cast< TrackReportOption*>(this));
    if (!strcmp(_clname, "Ui::TrackReportOptionClass"))
        return static_cast< Ui::TrackReportOptionClass*>(const_cast< TrackReportOption*>(this));
    return QWidget::qt_metacast(_clname);
}

int TrackReportOption::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setReportOption(); break;
        case 1: listLeft(); break;
        case 2: listRight(); break;
        case 3: optionSave(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TrackReportOption::setReportOption()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
