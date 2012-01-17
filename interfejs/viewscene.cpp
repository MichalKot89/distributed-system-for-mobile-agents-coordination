#include "viewscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QAbstractGraphicsShapeItem>
#include <QMessageBox>
ViewScene::ViewScene(QObject *parent): QGraphicsScene(parent)
{
    StartCoord = false;
    EndCoord = false;
    PathCoord = false;
}

void ViewScene::mode_changed(mode btn)
{
    buttonMode = btn;
}

void ViewScene::scene_reset()
{
    StartCoord = false;
    EndCoord = false;
    PathCoord = false;
}

void ViewScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
             return;

    //QAbstractGraphicsShapeItem *item;
    if(buttonMode == Start)
    {
        if (StartCoord == true)
            removeItem(itemAt(start.x*SCENE_SIZE_VIEW/_RealSize,start.y*SCENE_SIZE_VIEW/_RealSize));
        addEllipse(event->scenePos().x()-4,event->scenePos().y()-4,8,8,QPen(Qt::green),QBrush(Qt::darkGreen));
        start.x=event->scenePos().x()*_RealSize/SCENE_SIZE_VIEW ; start.y=event->scenePos().y()*_RealSize/SCENE_SIZE_VIEW;
        StartCoord = true;

      //  addEllipse(event->scenePos().x()-5,event->scenePos().y()-5,10,10,QPen(Qt::green),QBrush(Qt::darkGreen));
    }
    if(buttonMode == Stop)
    {
        //addEllipse(event->scenePos().x()-5,event->scenePos().y()-5,10,10,QPen(Qt::red),QBrush(Qt::darkRed));
        if (EndCoord == true)
            removeItem(itemAt(end.x*SCENE_SIZE_VIEW/_RealSize,end.y*SCENE_SIZE_VIEW/_RealSize));
        addEllipse(event->scenePos().x()-4,event->scenePos().y()-4,8,8,QPen(Qt::red),QBrush(Qt::darkRed));
        end.x=event->scenePos().x()*_RealSize/SCENE_SIZE_VIEW; end.y=event->scenePos().y()*_RealSize/SCENE_SIZE_VIEW;
        EndCoord = true;
        //sygna³ zapisuj¹cy po³o¿enie koñcowe
        //i ustawiaj¹cy flagê ¿e
    }
    if(buttonMode == Path)
    {
        if (PathCoord == true)
            // dodaæ usuwanie po liœcie
        {
            //for(int i = 0, i < path.size(), ++i)
                //removeItem(itemAt(path.at(i).x,path.at(i).y));
            path.clear();
        }
        addEllipse(event->scenePos().x()-3,event->scenePos().y()-3,6,6,QPen(Qt::yellow),QBrush(Qt::darkYellow));
        coord Temp(event->scenePos().x()*_RealSize/SCENE_SIZE_VIEW,event->scenePos().y()*_RealSize/SCENE_SIZE_VIEW);
        path.push_back(Temp);
        PathCoord = true;
    }

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
