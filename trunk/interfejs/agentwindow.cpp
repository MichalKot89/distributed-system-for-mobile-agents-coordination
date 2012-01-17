#include "agentwindow.h"
#include "ui_agentwindow.h"
#include "simulationwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <vector>

AgentWindow::AgentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AgentWindow)
{
    ui->setupUi(this);

    ui->lineEditNum->setValidator(new QIntValidator(this));
    ui->groupBox_2->setEnabled(false);
    _Scene = new ViewScene(this);
    ui->graphicsView->setScene(_Scene);
    //this->setMouseTracking(true);
    //QWidget * nowy = this->parent();
    //this->parentWidget()->findChild<QWidget *>("simulationWindow")

    sceneStatus = false;

    connect(this,SIGNAL(btn_pressed_mode_set(mode)),_Scene,SLOT(mode_changed(mode)));
    connect(this,SIGNAL(agent_path_saved()),this,SLOT(clear_scene()));

    connect(this,SIGNAL(btn_pressed_paths_save()),
            _Scene,SLOT(scene_reset()));

    connect(this,SIGNAL(send_real_scene_size(double)),
            _Scene,SLOT(set_real_scene_size(double)));
   // connect(this,SIGNAL(btn_pressed_paths_save(ViewScene*)),parentWidget(),SLOT(paths_saved_to_main(ViewScene*)));
//parentWidget->findChild<QPushButton *>("button1");
}//this->parent()->findChild<SimulationWindow *>()/*parentWidget()->findChild<SimulationWindow *>("simulationWindow")*/

AgentWindow::~AgentWindow()
{
    delete ui;
}

void AgentWindow::DrawScene(double size, int segments)
{
    ui->graphicsView->setSceneRect(0,0,size,size);

    _Scene->addRect(0,0,size,size,QPen(Qt::gray),QBrush(Qt::lightGray));
    //dodaæ warunek o liczbie segmentów
    for (double x=0; x<=size; x+=size/segments)
        _Scene->addLine(x,0,x,size, QPen(Qt::gray));


    for (double y=0; y<=size; y+=size/segments)
        _Scene->addLine(0,y,size,y, QPen(Qt::gray));
}

void AgentWindow::on_pushButtonOk_clicked()
{
    //double size = 300;
    QString string;

    if (sceneStatus == false)
        QMessageBox::information(this,"Uwaga",trUtf8("Uwaga: Przed wprowadzeniem agentów nale¿y zdefiniowaæ scenê w zak³adce \"Scena\"."));

    else if(!ui->lineEditNum->text().isEmpty())
    {
        _NumberOfAgents = ui->lineEditNum->text().toInt();

        emit number_of_agents(_NumberOfAgents);
        emit set_status(true);
        emit send_real_scene_size(_SceneSize);
//        DODAÆ DO PROGRAMU
//================================================================================
//      _AgentsVec = new AgentCom * [_NumberOfAgents];
//      log(Info) << "**** Creating the 'AgentCom' component ****" <<endlog();
//      for (int i = 0; i < _NumberOfAgents; ++i)
//      {
//          ostringstream AgentsName;     AgentsName << AGENTS_NAME;     AgentsName << i + 1;
//          _AgentsVec[i] = new AgentCom(AgentsName.str());
//      }

//        log(Info) << "**** Setting parameters to the Agent's components'    ****" <<endlog();
//        for (int i = 0; i < _NumberOfAgents; ++i)
//            if ( !_AgentsVec[i]->SetParameters(i + 1, 0.01, 4)  )
//            {
//                ErrorMesg("Error during setting parameters for ", _AgentsVec[i]->getName().c_str());
//                return -1;
//            }

//        log(Info) << "**** Configuring Agents ****" <<endlog();
//        for (int i = 0; i < _NumberOfAgents; ++i)
//            if ( !_AgentsVec[i]->configure() )
//            {
//                ErrorMesg("Error during configure of ", _AgentsVec[i]->getName().c_str());
//                return -1;
//            }
//        DODAÆ DO PROGRAMU
//================================================================================

    //QMessageBox::information(this,"bla",QString::number(_NumberOfAgents));
        ui->groupBox_2->setEnabled(true);
        ui->label_4->setEnabled(false);
        ui->comboBoxMethod->setEnabled(false);
        ui->pushButtonMethod->setEnabled(false);
        ui->pushButtonStartPos->setEnabled(false);
        ui->pushButtonStopPos->setEnabled(false);
        ui->pushButtonPath->setEnabled(false);
        ui->pushButtonSaveAgentPath->setEnabled(false);

        //wyczyœæ listê agentów
        ui->comboBoxAgent->clear();
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //w Spectator dodaæ to samo
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //utworzenie listy agentów
        for(int i=0; i<_NumberOfAgents; i++)
        {
            string = "Agent nr " + QString::number(i);
            ui->comboBoxAgent->addItem(string);

            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //w Spectator dodaæ to samo
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
        //ui->label_4->setEnabled(false);
        //ui->comboBoxMethod->setEnabled(false);
        //ui->pushButtonMethod->setEnabled(false);

        //////////////////RYSUJ PLANSZE
        DrawScene(SCENE_SIZE_VIEW, _Segments);
    }

}

void AgentWindow::on_pushButtonAgent_clicked()
{
    ui->label_4->setEnabled(true);
    ui->comboBoxMethod->setEnabled(true);
    ui->pushButtonMethod->setEnabled(true);
    ui->pushButtonStartPos->setEnabled(true);
    ui->pushButtonStopPos->setEnabled(true);
    ui->pushButtonPath->setEnabled(true);
    ui->pushButtonSaveAgentPath->setEnabled(true);

    _agentIndex = ui->comboBoxAgent->currentIndex();
    //QMessageBox::information(this,"bla",QString::number(_agentIndex));

}

void AgentWindow::on_pushButtonMethod_clicked()
{

}

void AgentWindow::on_pushButtonReset_clicked()
{
    _NumberOfAgents = 0;
    ui->lineEditNum->clear();
    ui->comboBoxAgent->clear();
    ui->groupBox_2->setEnabled(false);
    ui->graphicsView->scene()->clear();

    emit set_status(false);
    /*if(_Scene == NULL)
        if(!_Scene->items().empty())
        //delete _Scene;
            _Scene->clear();*/
}

void AgentWindow::on_pushButtonStartPos_clicked()
{
   emit btn_pressed_mode_set(Start);
   //SetAgentStartingPosition(...);
}

void AgentWindow::on_pushButtonStopPos_clicked()
{
    emit btn_pressed_mode_set(Stop);
//        //SetAgentEndingPosition(...);
}

void AgentWindow::on_pushButtonPath_clicked()
{
    emit btn_pressed_mode_set(Path);
//        //AddAgentPathPoints(...);

}

void AgentWindow::on_pushButtonSaveAgentPath_clicked()
{

    emit agent_path_saved();
    emit btn_pressed_paths_save(); // do poprawy

    /* dodaæ do czêœci Zwyklego:
      dla _agentIndex wykonaj przypisanie pozycji start, end oraz œcie¿ki
*/
    std::list<Segment> Trasa;
//if()
    if(_Scene->getPath().size() == 0)
        Trasa.push_back(Segment( Coordinates(_Scene->getStartPos().x,_Scene->getStartPos().y), Coordinates(_Scene->getEndPos().x,_Scene->getEndPos().y)) );
    else
    {
        Trasa.push_back(Segment( Coordinates(_Scene->getStartPos().x,_Scene->getStartPos().y), Coordinates(_Scene->getPath().at(0).x,_Scene->getPath().at(0).y)) );
        for(int i = 0; i < _Scene->getPath().size()-1; ++i)
            Trasa.push_back(Segment( Coordinates(_Scene->getPath().at(i).x,_Scene->getPath().at(i).y), Coordinates(_Scene->getPath().at(i+1).x,_Scene->getPath().at(i+1).y)) );
        Trasa.push_back(Segment( Coordinates(_Scene->getPath().at(_Scene->getPath().size()-1).x,_Scene->getPath().at(_Scene->getPath().size()-1).y), Coordinates(_Scene->getEndPos().x,_Scene->getEndPos().y)) );
    }

    emit send_agent(Trasa, _agentIndex);

    //AgentsVec.push_back(A1);
  /*  */
    //emit agent_path_saved();

}

void AgentWindow::on_pushButtonGen_clicked()
{
    DrawScene(SCENE_SIZE_VIEW, _Segments);
    /*for(int i = 0; i <= AgentsVec.size(); ++i)
    {
        _Scene->addEllipse(AgentsVec.at(i).x-5,AgentsVec.at(i).y-5,10,10,QPen(Qt::green),QBrush(Qt::darkGreen));
        QGraphicsTextItem label = _Scene->addItem(new QGraphicsTextItem(QString::number(i)));
        label.setPos(AgentsVec.at(i).x,AgentsVec.at(i).y);
    }*/

    emit send_scene_to_simulator(_Scene);
}

void AgentWindow::clear_scene()
{
    _Scene->clear();
    DrawScene(SCENE_SIZE_VIEW, _Segments);
}

void AgentWindow::scene_status_set(bool status)
{
    sceneStatus = status;
    if(sceneStatus == false)
        on_pushButtonReset_clicked();
}

void AgentWindow::scene_parameters_recieved(double size, int segments)
{
    _SceneSize = size;
    _Segments = segments;
}

//void AgentWindow::mousePressEvent(QMouseEvent *event)
//{
//    int si = _Scene->items().size();
//    if(ui->graphicsView->underMouse())
//    {
//        //if(_Scene->items().size() > 1)
//        //_Scene->items().erase(_Scene->items().begin()++,_Scene->items().end());
//        //QMessageBox::information(this,"bla","bla");
//        //_Scene->addEllipse(event->x()-240.5,event->y()-298,10,10,QPen(Qt::gray),QBrush(Qt::red));
//        if(buttonMode == Start)
//            _Scene->addEllipse(event->x()-ui->graphicsView->pos().x(),event->y()-ui->graphicsView->pos().y(),10,10,QPen(Qt::green),QBrush(Qt::darkGreen));

//        if(buttonMode == Stop)
//            _Scene->addEllipse(event->globalX()-ui->graphicsView->x()-ui->groupBox_2->x(),event->globalY()-ui->graphicsView->y()-ui->groupBox_2->y(),10,10,QPen(Qt::red),QBrush(Qt::darkRed));
//        //SetAgentStartingPosition(...);

//    }

//}

/*
void AgentWindow::mouseReleaseEvent(QMouseEvent *event)
{
if(ui->graphicsView->underMouse())
{
    QMessageBox::information(this,"bla","bla");
    _Scene->addEllipse(event->globalX(),event->globalY(),10,10,QPen(Qt::gray),QBrush(Qt::red));
}
    //    qDebug() << "lklk";
}
*/
    /*
    if((ui->graphicsView->underMouse()) && (event->button() == Qt::LeftButton))
        _Scene->addEllipse(event->x(),event->y(),10,10,QPen(Qt::gray),QBrush(Qt::red));
*/

/*
void AgentWindow::gv_clicked(QMouseEvent *)
{
}


void AgentWindow::paint_clicked(QMouseEvent *)
{

}

     textEdit->installEventFilter(this);
 }

 bool MainWindow::eventFilter(QObject *obj, QEvent *event)
 {
     if (obj == textEdit) {
         if (event->type() == QEvent::KeyPress) {
             QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
             qDebug() << "Ate key press" << keyEvent->key();
             return true;
         } else {
             return false;
         }
     } else {
         // pass the event on to the parent class
         return QMainWindow::eventFilter(obj, event);
     }
 }

*/







