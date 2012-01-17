#include "viewscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QAbstractGraphicsShapeItem>
#include <QMessageBox>
ViewScene::ViewScene(QObject *parent): QGraphicsScene(parent)
{
    StartCoord = false;
    EndCoord = false;
}

void ViewScene::mode_changed(mode btn)
{
    buttonMode = btn;
}

void ViewScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
             return;

    QAbstractGraphicsShapeItem *item;
    if(buttonMode == Start)
    {
        if (StartCoord == true)
            removeItem(itemAt(x_st,y_st));
        addEllipse(event->scenePos().x()-5,event->scenePos().y()-5,10,10,QPen(Qt::green),QBrush(Qt::darkGreen));
        x_st=event->scenePos().x(); y_st=event->scenePos().y();
        StartCoord = true;

      //  addEllipse(event->scenePos().x()-5,event->scenePos().y()-5,10,10,QPen(Qt::green),QBrush(Qt::darkGreen));
    }
    if(buttonMode == Stop)
    {
        //addEllipse(event->scenePos().x()-5,event->scenePos().y()-5,10,10,QPen(Qt::red),QBrush(Qt::darkRed));
        if (EndCoord == true)
            removeItem(itemAt(x_end,y_end));
        addEllipse(event->scenePos().x()-5,event->scenePos().y()-5,10,10,QPen(Qt::red),QBrush(Qt::darkRed));
        x_end=event->scenePos().x(); y_end=event->scenePos().y();
        EndCoord = true;
        //sygna³ zapisuj¹cy po³o¿enie koñcowe
        //i ustawiaj¹cy flagê ¿e
    }
    if(buttonMode == Path)
        addEllipse(event->scenePos().x()-5,event->scenePos().y()-5,10,10,QPen(Qt::yellow),QBrush(Qt::darkYellow));

//         DiagramItem *item;
//         switch (myMode) {
//             case InsertItem:
//                 item = new DiagramItem(myItemType, myItemMenu);
//                 item->setBrush(myItemColor);
//                 addItem(item);
//                 item->setPos(mouseEvent->scenePos());
//                 emit itemInserted(item);
//                 break;



    //if(event )
    //if(ui->graphicsView->underMouse())
    //{
        //if(_Scene->items().size() > 1)
        //_Scene->items().erase(_Scene->items().begin()++,_Scene->items().end());
        //QMessageBox::information(this,"bla","bla");
        //_Scene->addEllipse(event->x()-240.5,event->y()-298,10,10,QPen(Qt::gray),QBrush(Qt::red));
 //       if(buttonMode == Start)
  //          _Scene->addEllipse(event->x()-ui->graphicsView->pos().x(),event->y()-ui->graphicsView->pos().y(),10,10,QPen(Qt::green),QBrush(Qt::darkGreen));

  //      if(buttonMode == Stop)
  //          _Scene->addEllipse(event->globalX()-ui->graphicsView->x()-ui->groupBox_2->x(),event->globalY()-ui->graphicsView->y()-ui->groupBox_2->y(),10,10,QPen(Qt::red),QBrush(Qt::darkRed));
        //SetAgentStartingPosition(...);

    //}
}
