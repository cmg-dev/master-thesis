/****************************************************************************
** Meta object code from reading C++ file 'MainWidget.h'
**
** Created: Mon Jul 15 09:58:42 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExperimentListModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   21,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ExperimentListModel[] = {
    "ExperimentListModel\0\0experiment\0"
    "AddExperiment(Experiment*)\0"
};

void ExperimentListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExperimentListModel *_t = static_cast<ExperimentListModel *>(_o);
        switch (_id) {
        case 0: _t->AddExperiment((*reinterpret_cast< Experiment*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ExperimentListModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ExperimentListModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_ExperimentListModel,
      qt_meta_data_ExperimentListModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExperimentListModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExperimentListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExperimentListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExperimentListModel))
        return static_cast<void*>(const_cast< ExperimentListModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int ExperimentListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_MainWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      34,   28,   11,   11, 0x0a,
      66,   28,   11,   11, 0x0a,
      97,   28,   11,   11, 0x0a,
     111,   28,   11,   11, 0x0a,
     140,   11,   11,   11, 0x0a,
     157,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWidget[] = {
    "MainWidget\0\0NewExperiment()\0dummy\0"
    "NewExperimentFromTemplate(bool)\0"
    "ViewConfigurationSummary(bool)\0"
    "Discard(bool)\0ExportRecordingsToFile(bool)\0"
    "ComparisonPlot()\0PerformTest()\0"
};

void MainWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWidget *_t = static_cast<MainWidget *>(_o);
        switch (_id) {
        case 0: _t->NewExperiment(); break;
        case 1: _t->NewExperimentFromTemplate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->ViewConfigurationSummary((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->Discard((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->ExportRecordingsToFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->ComparisonPlot(); break;
        case 6: _t->PerformTest(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget,
      qt_meta_data_MainWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
