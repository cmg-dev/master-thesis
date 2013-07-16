/****************************************************************************
** Meta object code from reading C++ file 'classification.h'
**
** Created: Mon Jul 15 09:58:33 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "classification.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'classification.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClassificationWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_ClassificationWidget[] = {
    "ClassificationWidget\0"
};

void ClassificationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ClassificationWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClassificationWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ClassificationWidget,
      qt_meta_data_ClassificationWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClassificationWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClassificationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClassificationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClassificationWidget))
        return static_cast<void*>(const_cast< ClassificationWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ClassificationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PropertyEdit[] = {

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
      20,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PropertyEdit[] = {
    "PropertyEdit\0\0value\0OnChanged(int)\0"
};

void PropertyEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PropertyEdit *_t = static_cast<PropertyEdit *>(_o);
        switch (_id) {
        case 0: _t->OnChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PropertyEdit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PropertyEdit::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_PropertyEdit,
      qt_meta_data_PropertyEdit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PropertyEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PropertyEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PropertyEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PropertyEdit))
        return static_cast<void*>(const_cast< PropertyEdit*>(this));
    return QSlider::qt_metacast(_clname);
}

int PropertyEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_PropertiesWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_PropertiesWidget[] = {
    "PropertiesWidget\0"
};

void PropertiesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PropertiesWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PropertiesWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PropertiesWidget,
      qt_meta_data_PropertiesWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PropertiesWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PropertiesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PropertiesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PropertiesWidget))
        return static_cast<void*>(const_cast< PropertiesWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PropertiesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PropertiesBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_PropertiesBar[] = {
    "PropertiesBar\0"
};

void PropertiesBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PropertiesBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PropertiesBar::staticMetaObject = {
    { &QScrollArea::staticMetaObject, qt_meta_stringdata_PropertiesBar,
      qt_meta_data_PropertiesBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PropertiesBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PropertiesBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PropertiesBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PropertiesBar))
        return static_cast<void*>(const_cast< PropertiesBar*>(this));
    return QScrollArea::qt_metacast(_clname);
}

int PropertiesBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QScrollArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_FrameWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      30,   12,   12,   12, 0x0a,
      56,   50,   12,   12, 0x0a,
      70,   12,   12,   12, 0x0a,
      82,   12,   12,   12, 0x0a,
      91,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FrameWidget[] = {
    "FrameWidget\0\0OnClearDataset()\0"
    "OnGenerateDataset()\0value\0OnChange(int)\0"
    "OnCompute()\0OnSave()\0OnToggle()\0"
};

void FrameWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FrameWidget *_t = static_cast<FrameWidget *>(_o);
        switch (_id) {
        case 0: _t->OnClearDataset(); break;
        case 1: _t->OnGenerateDataset(); break;
        case 2: _t->OnChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnCompute(); break;
        case 4: _t->OnSave(); break;
        case 5: _t->OnToggle(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FrameWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FrameWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrameWidget,
      qt_meta_data_FrameWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrameWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrameWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrameWidget))
        return static_cast<void*>(const_cast< FrameWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FrameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
