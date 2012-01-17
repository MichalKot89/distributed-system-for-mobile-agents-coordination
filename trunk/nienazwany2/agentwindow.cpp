#include "agentwindow.h"
#include "ui_agentwindow.h"
#include "simulationwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
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
    connect(this,SIGNAL(btn_pressed_mode_set(mode)),_Scene,SLOT(mode_changed(mode)));
   // connect(this,SIGNAL(btn_pressed_paths_save(ViewScene*)),parentWidget(),SLOT(paths_saved_to_main(ViewScene*)));
//parentWidget->findChild<QPushButton *>("button1");
}//this->parent()->findChild<SimulationWindow *>()/*parentWidget()->findChild<SimulationWindow *>("simulationWindow")*/

AgentWindow::~AgentWindow()
{
    delete ui;
}

void AgentWindow::on_pushButtonOk_clicked()
{
    double size = 300;
    QString string;

    if(!ui->lineEditNum->text().isEmpty())
    {
        _NumberOfAgents = ui->lineEditNum->text().toInt();

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
        for(int i=0; i<_NumberOfAgents; i++)
        {
            string = "Agent nr " + QString::number(i);
            ui->comboBoxAgent->addItem(string);
        }
        ui->label_4->setEnabled(false);
        ui->comboBoxMethod->setEnabled(false);
        ui->pushButtonMethod->setEnabled(false);
    //////////////////RYSUJ PLANSZE
        ui->graphicsView->setSceneRect(0,0,size,size);

        _Scene->addRect(0,0,size,size,QPen(Qt::gray),QBrush(Qt::lightGray));
        //dodaæ warunek o liczbie segmentów
        for (double x=0; x<=size; x+=size/4)
            _Scene->addLine(x,0,x,size, QPen(Qt::gray));


        for (double y=0; y<=size; y+=size/4)
            _Scene->addLine(0,y,size,y, QPen(Qt::gray));
       // _Scene->addEllipse(10,10,10,10,QPen(Qt::gray),QBrush(Qt::red));
    }

}

void AgentWindow::on_pushButtonAgent_clicked()
{
    ui->label_4->setEnabled(true);
    ui->comboBoxMethod->setEnabled(true);
    ui->pushButtonMethod->setEnabled(true);
}

void AgentWindow::on_pushButtonMethod_clicked()
{

}

void AgentWindow::on_pushButtonReset_clicked()
{
    _NumberOfAgents = 0;
    ui->lineEditNum->clear();
    ui->groupBox_2->setEnabled(false);
    ui->graphicsView->scene()->clear();
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

void AgentWindow::on_pushButtonSavePaths_clicked()
{
    emit btn_pressed_paths_save(_Scene);
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

