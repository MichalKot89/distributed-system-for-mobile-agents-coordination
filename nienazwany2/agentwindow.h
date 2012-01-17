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

//public:
    //void mousePressEvent(QMouseEvent *);
    //void mouseReleaseEvent(QMouseEvent *);
signals:
    void btn_pressed_mode_set(mode btn);
    void btn_pressed_paths_save(ViewScene *sc);

private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonAgent_clicked();

    void on_pushButtonMethod_clicked();

    void on_pushButtonReset_clicked();

    void on_pushButtonStartPos_clicked();

    void on_pushButtonStopPos_clicked();

    void on_pushButtonPath_clicked();

    void on_pushButtonSavePaths_clicked();

private:
    Ui::AgentWindow *ui;
    int _NumberOfAgents;
    ViewScene *_Scene; //!!
    mode buttonMode;
};

#endif // AGENTWINDOW_H
