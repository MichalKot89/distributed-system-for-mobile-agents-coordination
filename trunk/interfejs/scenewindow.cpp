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

    emit scene_status(false);
}

SceneWindow::~SceneWindow()
{
    delete ui;
}

void SceneWindow::DrawScene(double size, int segments)
{
    _Scene->setSceneRect(0,0,size,size);
    _Scene->addRect(0,0,size,size,QPen(Qt::gray),QBrush(Qt::lightGray));
    //dodaæ warunek o liczbie segmentów
    for (double x=0; x<=size; x+=size/segments)
        _Scene->addLine(x,0,x,size, QPen(Qt::gray));


    for (double y=0; y<=size; y+=size/segments)
        _Scene->addLine(0,y,size,y, QPen(Qt::gray));
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
    //sceneIsSet = true;

    //DrawScene(_SceneSize,_Segments);
    DrawScene(SCENE_SIZE_VIEW,_Segments);

    emit scene_status(true);
    emit scene_parameters(_SceneSize,_Segments);
    //SaveSceneToSimulator();

}

void SceneWindow::on_pushButtonReset_clicked()
{
    _SceneSize = 0.0;
    _Segments = 0;
    //sceneIsSet = false;
    ui->lineEditSize->clear();
    ui->lineEditSeg->clear();
    ui->lineEditSeg->setEnabled(false);
    ui->pushButtonsceneSeg->setEnabled(false);
    ui->groupBox_2->setEnabled(false);
    ui->graphicsView->scene()->clear();
    emit scene_status(false);
}
