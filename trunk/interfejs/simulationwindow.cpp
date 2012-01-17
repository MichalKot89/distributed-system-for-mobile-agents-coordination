#include "simulationwindow.h"
#include "ui_simulationwindow.h"
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QTime>
#include <QList>

int SimulationWindow::iter = 0;
SimulationWindow::SimulationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);

    sceneToDraw = NULL;

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

void SimulationWindow::DrawScene(double size, int segments)
{
    _Scene->setSceneRect(0,0,size,size);
    _Scene->addRect(0,0,size,size,QPen(Qt::gray),QBrush(Qt::lightGray));
    //dodaæ warunek o liczbie segmentów
    for (double x=0; x<=size; x+=size/segments)
        _Scene->addLine(x,0,x,size, QPen(Qt::gray));


    for (double y=0; y<=size; y+=size/segments)
        _Scene->addLine(0,y,size,y, QPen(Qt::gray));
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
    //if( (agentStatus == true) && (sceneStatus == true))
        timer->start(100);
    //else

    //StartSimulation(...);
}

void SimulationWindow::dr_sc()
{
    emit request_scene();
    //QList<QGraphicsItem *> items;
    QGraphicsItemGroup *group = _Scene->createItemGroup(_Scene->selectedItems());
    //czyszczenie listy
   /* QList<QGraphicsItem *> list = _Scene->items();
    QList<QGraphicsItem *>::Iterator it = list.begin();
    for ( ; it != list.end(); ++it )
    {
            if ( *it )
            {
                    _Scene->removeItem(*it);
                    delete *it;
            }
    }*/
    //_Scene->destroyItemGroup(group);
    // Group all selected items together
    //QGraphicsItemGroup *group = scene->createItemGroup(scene->selecteditems());

    DrawScene(SCENE_SIZE_VIEW,_SegmentsToDraw);
    // Destroy the group, and delete the group item
    if( (sceneToDraw != NULL) && (sceneToDraw->_Agenci.size() > 0) && (sceneToDraw->_TrasyAgentow.at(0).size() > 0) )
        emit is_ready(true);
    else
        return;
    //double bla=0;
    //std::cin >> bla;
    for(unsigned int i = 0; i < sceneToDraw->_Agenci.size(); ++i)
    {
        //_Scene->addEllipse(sceneToDraw->_Agenci.at(i)._x-4,sceneToDraw->_Agenci.at(i)._y-4,8,8,QPen(Qt::red),QBrush(Qt::darkRed));
        std::cout << "polozenia agentow x:" << sceneToDraw->_Agenci.at(i)._x-4 << " y: " << sceneToDraw->_Agenci.at(i)._y-4 << std::endl;
        QGraphicsEllipseItem * ell = _Scene->addEllipse(sceneToDraw->_Agenci.at(i)._x-4,sceneToDraw->_Agenci.at(i)._y-4,8,8,QPen(Qt::red),QBrush(Qt::darkRed));
//QGraphicsEllipseItem * ell = _Scene->addEllipse(bla,sceneToDraw->_Agenci.at(i)._y-4,8,8,QPen(Qt::red),QBrush(Qt::darkRed));
        //ell->setSelected(true);
        //group->addToGroup(ell);
        //->setSelected(true)

        QGraphicsTextItem * label = new QGraphicsTextItem(QString::number(i)); //=
        _Scene->addItem(label);
        //group->addToGroup(label);//new QGraphicsTextItem(QString::number(i)));
        label->setPos(sceneToDraw->_Agenci.at(i)._x-15,sceneToDraw->_Agenci.at(i)._y-15);
        label->setSelected(true);
        //group->addToGroup(label);

    }
    //_Scene->destroyItemGroup(group);
//_Scene->addEllipse(sceneToDraw->_Agenci.at(i)._x-4,sceneToDraw->_Agenci.at(i)._y-4,8,8,QPen(Qt::red),QBrush(Qt::darkRed));
//QGraphicsTextItem * label = new QGraphicsTextItem(QString::number(i)); //=
//_Scene->addItem(label);//new QGraphicsTextItem(QString::number(i)));
//label->setPos(sceneToDraw->_Agenci.at(i)._x-10,sceneToDraw->_Agenci.at(i)._y-10);

    /*if(iter<15)
    //for(int i = 0; i <= AgentsVec.size(); ++i)
        {
            QTime midnight(0, 0, 0);
            qsrand(midnight.secsTo(QTime::currentTime()));
            //if(iter>0)
            //    _Scene->removeItem(_Scene->items().last());
            for()
            _Scene->addEllipse(qrand()%333,qrand()%333,10,10,QPen(Qt::red),QBrush(Qt::darkRed));
            _Scene->addEllipse(AgentsVec.at(iter).x-5,AgentsVec.at(iter).y-5,10,10,QPen(Qt::green),QBrush(Qt::darkGreen));
            QGraphicsTextItem * label = new QGraphicsTextItem(QString::number(iter)); //=
            _Scene->addItem(label);//new QGraphicsTextItem(QString::number(i)));
            label->setPos(AgentsVec.at(iter).x-10,AgentsVec.at(iter).y-10);
            iter++;
        }*/

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

void SimulationWindow::get_scene(Plansza *p)
{
    sceneToDraw = p;
}

void SimulationWindow::get_scene_parameters(double size, int segments)
{
    _SizeToDraw = size;
    _SegmentsToDraw = segments;
}
