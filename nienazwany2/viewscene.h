#ifndef VIEWSCENE_H
#define VIEWSCENE_H

#include <QGraphicsScene>
#include <QList>
#include "common.h"

class ViewScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ViewScene(QObject *parent = 0);
    ~ViewScene(){}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void mode_changed(mode btn);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event){}
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){}
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){}

private:
    QList<QGraphicsItem *> AgentsItems;
    mode buttonMode;
    qreal x_st;
    qreal y_st;
    qreal x_end;
    qreal y_end;
    bool StartCoord;
    bool EndCoord;
};

#endif // VIEWSCENE_H
