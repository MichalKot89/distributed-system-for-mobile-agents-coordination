/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Jan 17 17:53:26 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      35,   11,   11,   11, 0x0a,
      51,   11,   11,   11, 0x0a,
      74,   67,   11,   11, 0x0a,
     111,   97,   11,   11, 0x0a,
     152,  145,   11,   11, 0x0a,
     182,   11,   11,   11, 0x0a,
     219,  210,   11,   11, 0x0a,
     262,  257,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0p\0send_scene(Plansza*)\0"
    "shSceneWindow()\0shAgentWindow()\0status\0"
    "set_agent_status(bool)\0size,segments\0"
    "ustaw_Plansze_Agentow(double,int)\0"
    "number\0setNumberAndCreateAgents(int)\0"
    "receive_request_for_scene()\0tr,index\0"
    "receive_agent(std::list<Segment>,int)\0"
    "stat\0ready_to_simulate(bool)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: send_scene((*reinterpret_cast< Plansza*(*)>(_a[1]))); break;
        case 1: shSceneWindow(); break;
        case 2: shAgentWindow(); break;
        case 3: set_agent_status((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: ustaw_Plansze_Agentow((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: setNumberAndCreateAgents((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: receive_request_for_scene(); break;
        case 7: receive_agent((*reinterpret_cast< std::list<Segment>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: ready_to_simulate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::send_scene(Plansza * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
