#ifndef AGENTWINDOW_H
#define AGENTWINDOW_H

#include <QWidget>
#include <QGraphicsWidget>
#include "viewscene.h"
#include "common.h"

namespace Ui {
    class AgentWindow;
}

class AgentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AgentWindow(QWidget *parent = 0);
    ~AgentWindow();
    void DrawScene(double size, int segments);

//public:
    //void mousePressEvent(QMouseEvent *);
    //void mouseReleaseEvent(QMouseEvent *);
signals:
    void btn_pressed_mode_set(mode btn);
    void btn_pressed_paths_save();
    void agent_path_saved();
    void send_scene_to_simulator(ViewScene *sc);

private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonAgent_clicked();

    void on_pushButtonMethod_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonStartPos_clicked();

    void on_pushButtonStopPos_clicked();

    void on_pushButtonPath_clicked();

    void on_pushButtonSaveAgentPath_clicked();

    void clear_scene();

    void scene_status_set(bool status);

    void scene_parameters_recieved(double size, int segments);

    void on_pushButtonGen_clicked();

private:
    Ui::AgentWindow *ui;
    int _NumberOfAgents;
    double _SceneSize;
    int _Segments;
    ViewScene *_Scene; //!!
    mode buttonMode;
    int _agentIndex; // index agenta, którego wspó³rzêdne zostan¹ zapisane
    bool sceneStatus;
};

#endif // AGENTWINDOW_H
