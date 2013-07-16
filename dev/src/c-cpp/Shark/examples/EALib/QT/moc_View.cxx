/****************************************************************************
** Meta object code from reading C++ file 'View.h'
**
** Created: Mon Jul 15 09:58:43 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "View.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'View.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_View[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,
      13,    5,    5,    5, 0x05,
      25,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,    5,    5,    5, 0x0a,
      55,   49,    5,    5, 0x0a,
      68,    5,    5,    5, 0x0a,
      78,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_View[] = {
    "View\0\0done()\0destroyed()\0delayedDelete()\0"
    "reset()\0evals\0changed(int)\0destroy()\0"
    "onDelete()\0"
};

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        View *_t = static_cast<View *>(_o);
        switch (_id) {
        case 0: _t->done(); break;
        case 1: _t->destroyed(); break;
        case 2: _t->delayedDelete(); break;
        case 3: _t->reset(); break;
        case 4: _t->changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->destroy(); break;
        case 6: _t->onDelete(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData View::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject View::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_View,
      qt_meta_data_View, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &View::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_View))
        return static_cast<void*>(const_cast< View*>(this));
    return QWidget::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void View::done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void View::destroyed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void View::delayedDelete()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
