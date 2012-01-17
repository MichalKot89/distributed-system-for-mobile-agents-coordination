#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include "viewscene.h"
#include "common.h"
#include "Plansza.hh"
#include <QTimer>

namespace Ui {
    class SimulationWindow;
}

class SimulationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationWindow(QWidget *parent = 0);
    ~SimulationWindow();
    void DrawScene(double size, int segments);

signals:
    void request_scene();
    void is_ready(bool);

public slots:
    void on_pushButtonZakoncz_clicked();

    void on_pushButtonWczytaj_clicked();

    void on_pushButtonZapisz_clicked();

//private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonReset_clicked();

    void paths_saved(ViewScene * sc);

    void dr_sc();

    void get_scene(Plansza * p);

    void get_scene_parameters(double size, int segments);

private:
    Ui::SimulationWindow *ui;
    ViewScene *_Scene;
    std::vector<coord> AgentsVec;
    QTimer *timer;
    static int iter;
    double _SizeToDraw;
    int _SegmentsToDraw;
    Plansza *sceneToDraw;
};

#endif // SIMULATIONWINDOW_H
