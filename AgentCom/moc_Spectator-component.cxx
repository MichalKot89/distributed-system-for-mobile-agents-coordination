/****************************************************************************
** Meta object code from reading C++ file 'Spectator-component.hpp'
**
** Created: Tue Jan 17 21:04:46 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Spectator-component.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Spectator-component.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SpectatorCom[] = {

 // content:
       5,       // revision
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

static const char qt_meta_stringdata_SpectatorCom[] = {
    "SpectatorCom\0"
};

const QMetaObject SpectatorCom::staticMetaObject = {
    { &MainWindow::staticMetaObject, qt_meta_stringdata_SpectatorCom,
      qt_meta_data_SpectatorCom, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpectatorCom::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpectatorCom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpectatorCom::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpectatorCom))
        return static_cast<void*>(const_cast< SpectatorCom*>(this));
    if (!strcmp(_clname, "RTT::TaskContext"))
        return static_cast< RTT::TaskContext*>(const_cast< SpectatorCom*>(this));
    return MainWindow::qt_metacast(_clname);
}

int SpectatorCom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
