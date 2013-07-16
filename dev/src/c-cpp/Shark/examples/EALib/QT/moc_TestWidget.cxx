/****************************************************************************
** Meta object code from reading C++ file 'TestWidget.h'
**
** Created: Mon Jul 15 09:58:43 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TestWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TestWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestListModel[] = {

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

static const char qt_meta_stringdata_TestListModel[] = {
    "TestListModel\0"
};

void TestListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TestListModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TestListModel::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_TestListModel,
      qt_meta_data_TestListModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestListModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestListModel))
        return static_cast<void*>(const_cast< TestListModel*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int TestListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_TestWidget[] = {

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

static const char qt_meta_stringdata_TestWidget[] = {
    "TestWidget\0"
};

void TestWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TestWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TestWidget::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_TestWidget,
      qt_meta_data_TestWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TestWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TestWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TestWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestWidget))
        return static_cast<void*>(const_cast< TestWidget*>(this));
    return QTableView::qt_metacast(_clname);
}

int TestWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
