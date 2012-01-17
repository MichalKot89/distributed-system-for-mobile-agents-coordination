#include "simulationwindow.h"
#include "ui_simulationwindow.h"

SimulationWindow::SimulationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);

    _Scene = new ViewScene(this);
    ui->graphicsView->setScene(_Scene);
}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}

void SimulationWindow::on_pushButtonZakoncz_clicked()
{
    qApp->quit();
}

void SimulationWindow::on_pushButtonWczytaj_clicked()
{
    //LoadFromFile(...);
}

void SimulationWindow::on_pushButtonZapisz_clicked()
{
    //SaveToFile(...);
}

void SimulationWindow::on_pushButtonStart_clicked()
{

    //StartSimulation(...);
}

void SimulationWindow::on_pushButtonStop_clicked()
{
    //StopSimulation(...);
}

void SimulationWindow::on_pushButtonReset_clicked()
{
    //ResetSimulation(...);
}

void SimulationWindow::paths_saved(ViewScene *sc)
{
    _Scene = sc;
    ui->graphicsView->setScene(_Scene);
}
