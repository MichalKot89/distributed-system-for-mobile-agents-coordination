#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //connect(this->ui->sceneWindow,SIGNAL(scene_status(bool)),this->ui->agentWindow,SLOT(scene_status_set(bool)));
    //connect(this->ui->agentWindow,SIGNAL(btn_pressed_paths_save(ViewScene*)),this->ui->simulationWindow,SLOT(paths_saved(ViewScene*)));
    ui->setupUi(this);

    setCentralWidget(ui->_Tabs);
    //ui->simulationWindow->
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

    _actQuit = new QAction(tr("&Zakoñcz"), this);
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

    connect(this->ui->agentWindow,SIGNAL(send_scene_to_simulator(ViewScene*)),
            this->ui->simulationWindow,SLOT(paths_saved(ViewScene*)));

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
