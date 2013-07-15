/****************************************************************************
** Meta object code from reading C++ file 'ConfigCtrl.h'
**
** Created: Mon Jul 15 09:58:41 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ConfigCtrl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConfigCtrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyComboBox[] = {

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

static const char qt_meta_stringdata_MyComboBox[] = {
    "MyComboBox\0"
};

void MyComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MyComboBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_MyComboBox,
      qt_meta_data_MyComboBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyComboBox))
        return static_cast<void*>(const_cast< MyComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int MyComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_DoubleEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   13,   13,   13, 0x0a,
      62,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DoubleEditor[] = {
    "DoubleEditor\0\0editor\0commitData(QWidget*)\0"
    "OnLineEditChanged()\0OnSliderChanged()\0"
};

void DoubleEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DoubleEditor *_t = static_cast<DoubleEditor *>(_o);
        switch (_id) {
        case 0: _t->commitData((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->OnLineEditChanged(); break;
        case 2: _t->OnSliderChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DoubleEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DoubleEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DoubleEditor,
      qt_meta_data_DoubleEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DoubleEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DoubleEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DoubleEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DoubleEditor))
        return static_cast<void*>(const_cast< DoubleEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int DoubleEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DoubleEditor::commitData(QWidget * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_ConfigurationModel[] = {

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

static const char qt_meta_stringdata_ConfigurationModel[] = {
    "ConfigurationModel\0"
};

void ConfigurationModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ConfigurationModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConfigurationModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_ConfigurationModel,
      qt_meta_data_ConfigurationModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigurationModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigurationModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigurationModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigurationModel))
        return static_cast<void*>(const_cast< ConfigurationModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int ConfigurationModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ConfigurationDelegate[] = {

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
      30,   23,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConfigurationDelegate[] = {
    "ConfigurationDelegate\0\0editor\0"
    "onCommitData(QWidget*)\0"
};

void ConfigurationDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConfigurationDelegate *_t = static_cast<ConfigurationDelegate *>(_o);
        switch (_id) {
        case 0: _t->onCommitData((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConfigurationDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConfigurationDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_ConfigurationDelegate,
      qt_meta_data_ConfigurationDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigurationDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigurationDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigurationDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigurationDelegate))
        return static_cast<void*>(const_cast< ConfigurationDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int ConfigurationDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_ConfigurationView[] = {

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

static const char qt_meta_stringdata_ConfigurationView[] = {
    "ConfigurationView\0"
};

void ConfigurationView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ConfigurationView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConfigurationView::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_ConfigurationView,
      qt_meta_data_ConfigurationView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigurationView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigurationView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigurationView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigurationView))
        return static_cast<void*>(const_cast< ConfigurationView*>(this));
    return QTreeView::qt_metacast(_clname);
}

int ConfigurationView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
