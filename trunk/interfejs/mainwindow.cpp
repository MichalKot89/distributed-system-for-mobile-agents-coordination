#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Spectator-component.hpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->_Tabs);

    sceneStatus = false;
    agentStatus = false;
    _NumberOfAgents = 0;
    isReady = false;
    _pPlansza_Agentow = NULL;

    _actStart = new QAction(tr("&Start"), this);
    connect(_actStart, SIGNAL(triggered()),
            ui->simulationWindow, SLOT(on_pushButtonStart_clicked()));

    _actStop = new QAction(tr("&Stop"), this);
    connect(_actStop, SIGNAL(triggered()),
            ui->simulationWindow, SLOT(on_pushButtonStop_clicked()));

    _actReset = new QAction(tr("&Reset"), this);
    connect(_actReset, SIGNAL(triggered()),
            ui->simulationWindow, SLOT(on_pushButtonReset_clicked()));

    _actSave = new QAction(tr("&Zapisz"), this);
    connect(_actSave, SIGNAL(triggered()),
            ui->simulationWindow, SLOT(on_pushButtonZapisz_clicked()));

    _actLoad = new QAction(tr("&Wczytaj"), this);
    connect(_actLoad, SIGNAL(triggered()),
            ui->simulationWindow, SLOT(on_pushButtonWczytaj_clicked()));

    _actQuit = new QAction(tr("&Zako�cz"), this);
    connect(_actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    _actAgentSet = new QAction(tr("&Ustawienia..."), this);
    connect(_actAgentSet, SIGNAL(triggered()), this, SLOT(shAgentWindow()));

    _actAgentReset = new QAction(tr("&Reset"), this);
    //connect(_actAgentReset, SIGNAL(triggered()), ui->agentWindow, SLOT(on_pushButtonReset_clicked()));
    _actSceneSet = new QAction(tr("&Ustawienia..."), this);
    connect(_actSceneSet, SIGNAL(triggered()), this, SLOT(shSceneWindow()));

    _actSceneReset = new QAction(tr("&Reset"), this);
    //connect(_actSceneReset, SIGNAL(triggered()), ui->sceneWindow, SLOT(on_pushButtonReset_clicked()));
    _actDocumentation = new QAction(tr("&Dokumentacja"), this);

    _actAbout = new QAction(tr("&O programie..."), this);

    _SimulationMenu = menuBar()->addMenu(tr("Symulacja"));
    _SimulationMenu ->addAction(_actStart);
    _SimulationMenu ->addAction(_actStop);
    _SimulationMenu ->addAction(_actReset);
    _SimulationMenu ->addSeparator();
    _SimulationMenu ->addAction(_actSave);
    _SimulationMenu ->addAction(_actLoad);
    _SimulationMenu ->addSeparator();
    _SimulationMenu ->addAction(_actQuit);

    _SceneMenu = menuBar()->addMenu(tr("Scena"));
    _SceneMenu->addAction(_actSceneSet);
    _SceneMenu->addAction(_actSceneReset);

    _AgentMenu = menuBar()->addMenu(tr("Agent"));
    _AgentMenu->addAction(_actAgentSet);
    _AgentMenu->addAction(_actAgentReset);

    _HelpMenu = menuBar()->addMenu(tr("Pomoc"));
    _HelpMenu->addAction(_actDocumentation);
    _HelpMenu->addAction(_actAbout);

    connect(this->ui->sceneWindow,SIGNAL(scene_status(bool)),
            this->ui->agentWindow,SLOT(scene_status_set(bool)));

    connect(this->ui->sceneWindow,SIGNAL(scene_parameters(double,int)),
            this->ui->agentWindow,SLOT(scene_parameters_recieved(double,int)));

    connect(this->ui->sceneWindow,SIGNAL(scene_parameters(double,int)),
            this,SLOT(ustaw_Plansze_Agentow(double, int)));

    connect(this->ui->agentWindow,SIGNAL(send_scene_to_simulator(ViewScene*)),
            this->ui->simulationWindow,SLOT(paths_saved(ViewScene*)));

    connect(this->ui->agentWindow,SIGNAL(number_of_agents(int)),
            this,SLOT(setNumberAndCreateAgents(int)));

    connect(this->ui->agentWindow,SIGNAL(set_status(bool)),
            this,SLOT(set_agent_status(bool)));

    connect(this->ui->simulationWindow,SIGNAL(request_scene()),
            this,SLOT(receive_request_for_scene()));

    connect(this,SIGNAL(send_scene(Plansza*)),
            this->ui->simulationWindow,SLOT(get_scene(Plansza*)));

    connect(this->ui->agentWindow,SIGNAL(send_agent(std::list<Segment>, int)),
            this,SLOT(receive_agent(std::list<Segment>,int)));

    connect(this->ui->simulationWindow,SIGNAL(is_ready(bool)),
            this,SLOT(ready_to_simulate(bool)));

    connect(this->ui->sceneWindow,SIGNAL(scene_parameters(double,int)),
            this->ui->simulationWindow,SLOT(get_scene_parameters(double,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::shSceneWindow()
{
    ui->_Tabs->setCurrentWidget(ui->sceneWindow);
}

void MainWindow::shAgentWindow()
{
    ui->_Tabs->setCurrentWidget(ui->agentWindow);
}

void MainWindow::ustaw_Plansze_Agentow(double size, int segments)
{
    this->_pPlansza_Agentow = new Plansza(size,segments); // tu dodac podzial na segmenty
}

void MainWindow::setNumberAndCreateAgents(int number)
{
    Coordinates Temp(0,0);
    _NumberOfAgents = number;
    std::cout << "number of agents: " << _NumberOfAgents << ". " << std::endl;
    zwrocPlansze_agentow()->_Agenci.clear();
    for(int i = 0; i < number; ++i)
    {
        zwrocPlansze_agentow()->_Agenci.push_back(Temp);
        zwrocPlansze_agentow()->_TrasyAgentow.push_back(*(new std::list<Segment>()));
    }
}

void MainWindow::set_agent_status(bool status)
{
    agentStatus = status;
}

void MainWindow::receive_agent(std::list<Segment> tr ,int index)
{
    for(std::list<Segment>::iterator iter = tr.begin(); iter != tr.end(); ++iter)
        _pPlansza_Agentow->_TrasyAgentow.at(index).push_back(*iter);
    //_pPlansza_Agentow->_TrasyAgentow.at(index) = tr;
    _pPlansza_Agentow->add(index,(*(tr.begin()))._Start._x,(*(tr.begin()))._Start._y);
}

void MainWindow::ready_to_simulate(bool stat)
{
    isReady = stat;
    SpectatorCom* Spect = static_cast<SpectatorCom*>(this);
    if ( !Spect->SetParameters() ) return;
    if ( !Spect->configure() ) return;
    if ( !Spect->add_agent_segments() ) return;
    if ( !Spect->start() ) return;
}
