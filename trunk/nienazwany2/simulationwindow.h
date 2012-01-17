#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include "viewscene.h"
#include "common.h"

namespace Ui {
    class SimulationWindow;
}

class SimulationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationWindow(QWidget *parent = 0);
    ~SimulationWindow();

public slots:
    void on_pushButtonZakoncz_clicked();

    void on_pushButtonWczytaj_clicked();

    void on_pushButtonZapisz_clicked();

//private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_pushButtonReset_clicked();

    void paths_saved(ViewScene * sc);
private:
    Ui::SimulationWindow *ui;
    ViewScene *_Scene;
};

#endif // SIMULATIONWINDOW_H
