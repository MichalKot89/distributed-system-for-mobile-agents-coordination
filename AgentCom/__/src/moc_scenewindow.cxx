/****************************************************************************
** Meta object code from reading C++ file 'scenewindow.h'
**
** Created: Tue Jan 17 11:16:46 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/scenewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scenewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SceneWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   13,   12,   12, 0x05,
      53,   39,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,   12,   12,   12, 0x08,
     115,   12,   12,   12, 0x08,
     147,   12,   12,   12, 0x08,
     179,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SceneWindow[] = {
    "SceneWindow\0\0status\0scene_status(bool)\0"
    "size,segments\0scene_parameters(double,int)\0"
    "on_pushButtonsceneSize_clicked()\0"
    "on_pushButtonsceneSeg_clicked()\0"
    "on_pushButtonsceneGen_clicked()\0"
    "on_pushButtonReset_clicked()\0"
};

const QMetaObject SceneWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SceneWindow,
      qt_meta_data_SceneWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SceneWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SceneWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SceneWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SceneWindow))
        return static_cast<void*>(const_cast< SceneWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int SceneWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: scene_status((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: scene_parameters((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: on_pushButtonsceneSize_clicked(); break;
        case 3: on_pushButtonsceneSeg_clicked(); break;
        case 4: on_pushButtonsceneGen_clicked(); break;
        case 5: on_pushButtonReset_clicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SceneWindow::scene_status(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SceneWindow::scene_parameters(double _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
