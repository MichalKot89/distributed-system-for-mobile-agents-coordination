#include "scenewindow.h"
#include "ui_scenewindow.h"

SceneWindow::SceneWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneWindow)
{
    ui->setupUi(this);

    ui->lineEditSize->setValidator(new QDoubleValidator(this));
    ui->lineEditSeg->setValidator(new QIntValidator(this));
    ui->label_4->setEnabled(false);
    ui->lineEditSeg->setEnabled(false);
    ui->pushButtonsceneSeg->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    _Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_Scene);

}

SceneWindow::~SceneWindow()
{
    delete ui;
}

void SceneWindow::on_pushButtonsceneSize_clicked()
{
    if(!ui->lineEditSize->text().isEmpty())
    {
        _SceneSize = ui->lineEditSize->text().toDouble();
       // _Size *= 10;
    //QMessageBox::information(this,"bla",QString::number(_Size));
    ui->label_4->setEnabled(true);
    ui->lineEditSeg->setEnabled(true);
    ui->pushButtonsceneSeg->setEnabled(true);
    }
}

void SceneWindow::on_pushButtonsceneSeg_clicked()
{
    if(!ui->lineEditSeg->text().isEmpty())
    {
        _Segments = ui->lineEditSeg->text().toInt();
        ui->groupBox_2->setEnabled(true);
    }
}

void SceneWindow::on_pushButtonsceneGen_clicked()
{
   // _Scene = new QGraphicsScene(this);
   // ui->graphicsView->setScene(_Scene);
    //ui->graphicsView->setSceneRect(0,0,_Size,_Size);
    //ui->graphicsView->setBaseSize(_Size,_Size);

    //ui->graphicsView->setBackgroundBrush(QBrush(Qt::lightGray));
    _Scene->setSceneRect(0,0,_SceneSize,_SceneSize);
    _Scene->addRect(0,0,_SceneSize,_SceneSize,QPen(Qt::gray),QBrush(Qt::lightGray));
    //dodaæ warunek o liczbie segmentów
    for (double x=0; x<=_SceneSize; x+=_SceneSize/_Segments)
        _Scene->addLine(x,0,x,_SceneSize, QPen(Qt::gray));


    for (double y=0; y<=_SceneSize; y+=_SceneSize/_Segments)
        _Scene->addLine(0,y,_SceneSize,y, QPen(Qt::gray));

    //SaveSceneToSimulator();

}

void SceneWindow::on_pushButtonReset_clicked()
{
    _SceneSize = 0.0;
    _Segments = 0;
    ui->lineEditSize->clear();
    ui->lineEditSeg->clear();
    ui->lineEditSeg->setEnabled(false);
    ui->pushButtonsceneSeg->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    ui->graphicsView->scene()->clear();
    /*if(_Scene == NULL)
        if(!_Scene->items().empty())
        //delete _Scene;
            _Scene->clear();*/
  /*  _Scene->clear();

            QList<QGraphicsItem *> list = gScene.items();
            QList<QGraphicsItem *>::Iterator it = list.begin();
            for ( ; it != list.end(); ++it )
            {
                    if ( *it )
                    {
                            gScene.removeItem(*it);
                            delete *it;
                    }
            }
*/
}
