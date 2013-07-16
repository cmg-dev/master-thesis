/****************************************************************************
** Meta object code from reading C++ file 'Experiment.h'
**
** Created: Mon Jul 15 09:58:42 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Experiment.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Experiment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExperimentThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      32,   26,   17,   17, 0x05,
      45,   17,   17,   17, 0x05,
      55,   17,   17,   17, 0x05,
      89,   78,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     121,   17,   17,   17, 0x0a,
     132,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ExperimentThread[] = {
    "ExperimentThread\0\0reset()\0evals\0"
    "changed(int)\0destroy()\0destroyControlWidget()\0"
    "experiment\0experimentFinished(Experiment*)\0"
    "viewDone()\0viewDestroyed()\0"
};

void ExperimentThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExperimentThread *_t = static_cast<ExperimentThread *>(_o);
        switch (_id) {
        case 0: _t->reset(); break;
        case 1: _t->changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->destroy(); break;
        case 3: _t->destroyControlWidget(); break;
        case 4: _t->experimentFinished((*reinterpret_cast< Experiment*(*)>(_a[1]))); break;
        case 5: _t->viewDone(); break;
        case 6: _t->viewDestroyed(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ExperimentThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ExperimentThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ExperimentThread,
      qt_meta_data_ExperimentThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExperimentThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExperimentThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExperimentThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExperimentThread))
        return static_cast<void*>(const_cast< ExperimentThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ExperimentThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ExperimentThread::reset()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ExperimentThread::changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ExperimentThread::destroy()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ExperimentThread::destroyControlWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ExperimentThread::experimentFinished(Experiment * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
