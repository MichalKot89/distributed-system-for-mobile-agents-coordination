#include "simulationwindow.h"
#include "ui_simulationwindow.h"
#include <QGraphicsTextItem>
#include <QTime>

int SimulationWindow::iter = 0;
SimulationWindow::SimulationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);

    _Scene = new ViewScene(this);
    ui->graphicsView->setScene(_Scene);

    //AgentsVec.resize(15);
    coord Temp;
    for(int i = 0; i <= 15; ++i)
    {
        Temp.x = 10*i+50;
        Temp.y = 60+9*i;
        AgentsVec.push_back(Temp);
    }
    timer = new QTimer(this);
         connect(timer, SIGNAL(timeout()), this, SLOT(dr_sc()));


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
    timer->start(1000);

    //StartSimulation(...);
}

void SimulationWindow::dr_sc()
{
    if(iter<15)
    //for(int i = 0; i <= AgentsVec.size(); ++i)
        {
            QTime midnight(0, 0, 0);
            qsrand(midnight.secsTo(QTime::currentTime()));
            //if(iter>0)
            //    _Scene->removeItem(_Scene->items().last());
            _Scene->addEllipse(qrand()%333,qrand()%333,10,10,QPen(Qt::red),QBrush(Qt::darkRed));
            _Scene->addEllipse(AgentsVec.at(iter).x-5,AgentsVec.at(iter).y-5,10,10,QPen(Qt::green),QBrush(Qt::darkGreen));
            QGraphicsTextItem * label = new QGraphicsTextItem(QString::number(iter)); //=
            _Scene->addItem(label);//new QGraphicsTextItem(QString::number(i)));
            label->setPos(AgentsVec.at(iter).x-10,AgentsVec.at(iter).y-10);
            iter++;
        }
}

void SimulationWindow::on_pushButtonStop_clicked()
{
    timer->stop();
    //StopSimulation(...);
}

void SimulationWindow::on_pushButtonReset_clicked()
{
    iter = 0;
    //ResetSimulation(...);
}

void SimulationWindow::paths_saved(ViewScene *sc)
{
    _Scene = sc;
    ui->graphicsView->setScene(_Scene);

}
