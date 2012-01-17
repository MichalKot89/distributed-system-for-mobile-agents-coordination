#ifndef VIEWSCENE_H
#define VIEWSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <vector>

#include "common.h"

class ViewScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ViewScene(QObject *parent = 0);
    ~ViewScene(){}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    coord getStartPos(){return start;}
    coord getEndPos(){return end;}
    std::vector<coord> getPath(){return path;}

private slots:
    void mode_changed(mode btn);
    void scene_reset();
    void set_real_scene_size(double size) {_RealSize = size;}
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event){}
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){}
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){}

private:
    QList<QGraphicsItem *> AgentsItems;
    mode buttonMode;
    coord start;
    coord end;
    std::vector<coord> path;
    bool StartCoord;
    bool EndCoord;
    bool PathCoord;
    double _RealSize;
};

#endif // VIEWSCENE_H
