/****************************************************************************
** Meta object code from reading C++ file 'sla.h'
**
** Created: Sat Dec 26 20:09:23 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sla.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sla.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SLA[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    5,    4,    4, 0x0a,
      44,   35,    4,    4, 0x0a,
      67,    4,    4,    4, 0x0a,
      87,    4,    4,    4, 0x0a,
     110,    4,    4,    4, 0x0a,
     136,    4,    4,    4, 0x0a,
     164,    4,    4,    4, 0x0a,
     181,    4,    4,    4, 0x0a,
     202,    4,    4,    4, 0x0a,
     224,    4,    4,    4, 0x0a,
     242,    4,    4,    4, 0x0a,
     262,    4,    4,    4, 0x0a,
     275,    4,    4,    4, 0x0a,
     288,    4,    4,    4, 0x0a,
     301,    4,    4,    4, 0x0a,
     314,    4,    4,    4, 0x0a,
     327,    4,    4,    4, 0x0a,
     346,  340,    4,    4, 0x0a,
     367,  340,    4,    4, 0x0a,
     390,    4,    4,    4, 0x0a,
     405,    4,    4,    4, 0x0a,
     422,    4,    4,    4, 0x0a,
     441,    4,    4,    4, 0x0a,
     462,    4,    4,    4, 0x0a,
     479,    4,    4,    4, 0x0a,
     497,    4,    4,    4, 0x0a,
     515,    4,    4,    4, 0x0a,
     532,    4,    4,    4, 0x0a,
     550,    4,    4,    4, 0x0a,
     571,    4,    4,    4, 0x0a,
     598,    4,    4,    4, 0x0a,
     623,    4,    4,    4, 0x0a,
     641,  635,    4,    4, 0x0a,
     662,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SLA[] = {
    "SLA\0\0comName\0cbComChanged(QString)\0"
    "baudName\0cbBaudChanged(QString)\0"
    "btnConnectClicked()\0btnDisconnectClicked()\0"
    "btnSaveParameterClicked()\0"
    "btnCancelParameterClicked()\0"
    "btnLoadClicked()\0btnGenerateClicked()\0"
    "btnLoadModelClicked()\0btnSliceClicked()\0"
    "eScaleRateChecked()\0eRxChecked()\0"
    "eRyChecked()\0eRzChecked()\0eMxChecked()\0"
    "eMyChecked()\0eMzChecked()\0value\0"
    "sliderUpChanged(int)\0sliderDownChanged(int)\0"
    "btnUpClicked()\0btnDownClicked()\0"
    "btnUpHomeClicked()\0btnDownHomeClicked()\0"
    "btnLeftClicked()\0btnRightClicked()\0"
    "btnStartClicked()\0btnStopClicked()\0"
    "btnPauseClicked()\0btnContinueClicked()\0"
    "btnStartProjectorClicked()\0"
    "btnEndProjectorClicked()\0readMyCom()\0"
    "qdata\0writeMyCom(QString&)\0parsingGcode()\0"
};

void SLA::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SLA *_t = static_cast<SLA *>(_o);
        switch (_id) {
        case 0: _t->cbComChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->cbBaudChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->btnConnectClicked(); break;
        case 3: _t->btnDisconnectClicked(); break;
        case 4: _t->btnSaveParameterClicked(); break;
        case 5: _t->btnCancelParameterClicked(); break;
        case 6: _t->btnLoadClicked(); break;
        case 7: _t->btnGenerateClicked(); break;
        case 8: _t->btnLoadModelClicked(); break;
        case 9: _t->btnSliceClicked(); break;
        case 10: _t->eScaleRateChecked(); break;
        case 11: _t->eRxChecked(); break;
        case 12: _t->eRyChecked(); break;
        case 13: _t->eRzChecked(); break;
        case 14: _t->eMxChecked(); break;
        case 15: _t->eMyChecked(); break;
        case 16: _t->eMzChecked(); break;
        case 17: _t->sliderUpChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->sliderDownChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->btnUpClicked(); break;
        case 20: _t->btnDownClicked(); break;
        case 21: _t->btnUpHomeClicked(); break;
        case 22: _t->btnDownHomeClicked(); break;
        case 23: _t->btnLeftClicked(); break;
        case 24: _t->btnRightClicked(); break;
        case 25: _t->btnStartClicked(); break;
        case 26: _t->btnStopClicked(); break;
        case 27: _t->btnPauseClicked(); break;
        case 28: _t->btnContinueClicked(); break;
        case 29: _t->btnStartProjectorClicked(); break;
        case 30: _t->btnEndProjectorClicked(); break;
        case 31: _t->readMyCom(); break;
        case 32: _t->writeMyCom((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->parsingGcode(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SLA::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SLA::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_SLA,
      qt_meta_data_SLA, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SLA::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SLA::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SLA::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SLA))
        return static_cast<void*>(const_cast< SLA*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int SLA::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
