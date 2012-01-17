/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jan 17 19:07:09 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <agentwindow.h>
#include <scenewindow.h>
#include <simulationwindow.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGjh;
    QWidget *centralWidget;
    QTabWidget *_Tabs;
    SimulationWindow *simulationWindow;
    SceneWindow *sceneWindow;
    AgentWindow *agentWindow;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(731, 497);
        actionGjh = new QAction(MainWindow);
        actionGjh->setObjectName(QString::fromUtf8("actionGjh"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        _Tabs = new QTabWidget(centralWidget);
        _Tabs->setObjectName(QString::fromUtf8("_Tabs"));
        _Tabs->setGeometry(QRect(0, 0, 721, 441));
        simulationWindow = new SimulationWindow();
        simulationWindow->setObjectName(QString::fromUtf8("simulationWindow"));
        _Tabs->addTab(simulationWindow, QString());
        sceneWindow = new SceneWindow();
        sceneWindow->setObjectName(QString::fromUtf8("sceneWindow"));
        _Tabs->addTab(sceneWindow, QString());
        agentWindow = new AgentWindow();
        agentWindow->setObjectName(QString::fromUtf8("agentWindow"));
        _Tabs->addTab(agentWindow, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 731, 25));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        _Tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionGjh->setText(QApplication::translate("MainWindow", "gjh", 0, QApplication::UnicodeUTF8));
        _Tabs->setTabText(_Tabs->indexOf(simulationWindow), QApplication::translate("MainWindow", "Symulacja", 0, QApplication::UnicodeUTF8));
        _Tabs->setTabText(_Tabs->indexOf(sceneWindow), QApplication::translate("MainWindow", "Scena", 0, QApplication::UnicodeUTF8));
        _Tabs->setTabText(_Tabs->indexOf(agentWindow), QApplication::translate("MainWindow", "Agent", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
