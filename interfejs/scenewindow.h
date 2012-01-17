#ifndef SCENEWINDOW_H
#define SCENEWINDOW_H

#include <QWidget>
#include <QGraphicsWidget>
#include "common.h"
#include <QMessageBox>
//#include <QDialog>

namespace Ui {
    class SceneWindow;
}

class SceneWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SceneWindow(QWidget *parent = 0);
    ~SceneWindow();
    void DrawScene(double size, int segments);

signals:
    void scene_status(bool status);
    void scene_parameters(double size, int segments);

private slots:
    void on_pushButtonsceneSize_clicked();

    void on_pushButtonsceneSeg_clicked();

    void on_pushButtonsceneGen_clicked();

    void on_pushButtonReset_clicked();

private:
    Ui::SceneWindow *ui;
    double _SceneSize;
    int _Segments;
    QGraphicsScene *_Scene; //!!
    //bool sceneIsSet;
};

#endif // SCENEWINDOW_H
