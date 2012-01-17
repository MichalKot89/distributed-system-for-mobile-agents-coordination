#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include "simulationwindow.h"
#include "agentwindow.h"
#include "scenewindow.h"
#include "viewscene.h"
#include "common.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QGraphicsScene * GetScene();
//    int getNumberOfAgents(){return _NumberOfAgents;}
//    double getSceneSize(){return _SceneSize;}
//    int getSegments(){return _Segments;}
//    void setNumberOfAgents(int num){_NumberOfAgents = num;}
//    void setSceneSize(double size){_SceneSize = size;}
//    void setSegments(int num){_Segments=num;}

//signals:
//    void pass_through_paths(ViewScene *);

public slots:
    void shSceneWindow();
    void shAgentWindow();
    //void paths_saved_to_main(ViewScene*);

private:
    Ui::MainWindow *ui;

    QAction *_actStart;
    QAction *_actStop;
    QAction *_actReset;
    QAction *_actSave;
    QAction *_actLoad;
    QAction *_actQuit;

    QAction *_actSceneSet;
    QAction *_actSceneReset;

    QAction *_actAgentSet;
    QAction *_actAgentReset;

    QAction *_actDocumentation;
    QAction *_actAbout;

    QMenu *_SimulationMenu;
    QMenu *_AgentMenu;
    QMenu *_SceneMenu;
    QMenu *_HelpMenu;

    ViewScene *_Scene;
    //static QGraphicsScene *_Scene;
    //static int _NumberOfAgents;
    //static double _SceneSize;
    //static int _Segments;
};

#endif // MAINWINDOW_H
