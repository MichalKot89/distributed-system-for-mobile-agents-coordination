/****************************************************************************
** Meta object code from reading C++ file 'agentwindow.h'
**
** Created: Tue Jan 17 16:11:14 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/agentwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agentwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AgentWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   13,   12,   12, 0x05,
      44,   12,   12,   12, 0x05,
      69,   12,   12,   12, 0x05,
      91,   88,   12,   12, 0x05,
     134,  127,   12,   12, 0x05,
     156,   12,   12,   12, 0x05,
     173,   12,   12,   12, 0x05,
     211,  202,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     246,   12,   12,   12, 0x08,
     272,   12,   12,   12, 0x08,
     301,   12,   12,   12, 0x08,
     331,   12,   12,   12, 0x08,
     360,   12,   12,   12, 0x08,
     392,   12,   12,   12, 0x08,
     423,   12,   12,   12, 0x08,
     451,   12,   12,   12, 0x08,
     488,   12,   12,   12, 0x08,
     509,  502,   12,   12, 0x08,
     546,  532,   12,   12, 0x08,
     584,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AgentWindow[] = {
    "AgentWindow\0\0btn\0btn_pressed_mode_set(mode)\0"
    "btn_pressed_paths_save()\0agent_path_saved()\0"
    "sc\0send_scene_to_simulator(ViewScene*)\0"
    "number\0number_of_agents(int)\0"
    "set_status(bool)\0send_real_scene_size(double)\0"
    "tr,index\0send_agent(std::list<Segment>,int)\0"
    "on_pushButtonOk_clicked()\0"
    "on_pushButtonAgent_clicked()\0"
    "on_pushButtonMethod_clicked()\0"
    "on_pushButtonReset_clicked()\0"
    "on_pushButtonStartPos_clicked()\0"
    "on_pushButtonStopPos_clicked()\0"
    "on_pushButtonPath_clicked()\0"
    "on_pushButtonSaveAgentPath_clicked()\0"
    "clear_scene()\0status\0scene_status_set(bool)\0"
    "size,segments\0scene_parameters_recieved(double,int)\0"
    "on_pushButtonGen_clicked()\0"
};

const QMetaObject AgentWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AgentWindow,
      qt_meta_data_AgentWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AgentWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AgentWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AgentWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AgentWindow))
        return static_cast<void*>(const_cast< AgentWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int AgentWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: btn_pressed_mode_set((*reinterpret_cast< mode(*)>(_a[1]))); break;
        case 1: btn_pressed_paths_save(); break;
        case 2: agent_path_saved(); break;
        case 3: send_scene_to_simulator((*reinterpret_cast< ViewScene*(*)>(_a[1]))); break;
        case 4: number_of_agents((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: set_status((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: send_real_scene_size((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: send_agent((*reinterpret_cast< std::list<Segment>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: on_pushButtonOk_clicked(); break;
        case 9: on_pushButtonAgent_clicked(); break;
        case 10: on_pushButtonMethod_clicked(); break;
        case 11: on_pushButtonReset_clicked(); break;
        case 12: on_pushButtonStartPos_clicked(); break;
        case 13: on_pushButtonStopPos_clicked(); break;
        case 14: on_pushButtonPath_clicked(); break;
        case 15: on_pushButtonSaveAgentPath_clicked(); break;
        case 16: clear_scene(); break;
        case 17: scene_status_set((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: scene_parameters_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: on_pushButtonGen_clicked(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void AgentWindow::btn_pressed_mode_set(mode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AgentWindow::btn_pressed_paths_save()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void AgentWindow::agent_path_saved()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void AgentWindow::send_scene_to_simulator(ViewScene * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AgentWindow::number_of_agents(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AgentWindow::set_status(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AgentWindow::send_real_scene_size(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AgentWindow::send_agent(std::list<Segment> _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
