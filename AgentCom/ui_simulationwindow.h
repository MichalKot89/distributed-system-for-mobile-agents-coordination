/********************************************************************************
** Form generated from reading UI file 'simulationwindow.ui'
**
** Created: Tue Jan 17 19:07:09 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONWINDOW_H
#define UI_SIMULATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationWindow
{
public:
    QGroupBox *groupBox_5;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonReset;
    QFrame *line_5;
    QPushButton *pushButtonWczytaj;
    QPushButton *pushButtonZapisz;
    QFrame *line_6;
    QPushButton *pushButtonZakoncz;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_6;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *SimulationWindow)
    {
        if (SimulationWindow->objectName().isEmpty())
            SimulationWindow->setObjectName(QString::fromUtf8("SimulationWindow"));
        SimulationWindow->resize(712, 431);
        groupBox_5 = new QGroupBox(SimulationWindow);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 10, 132, 401));
        layoutWidget = new QWidget(groupBox_5);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 91, 371));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonStart = new QPushButton(layoutWidget);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));

        gridLayout->addWidget(pushButtonStart, 0, 0, 1, 1);

        pushButtonStop = new QPushButton(layoutWidget);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));

        gridLayout->addWidget(pushButtonStop, 1, 0, 1, 1);

        pushButtonReset = new QPushButton(layoutWidget);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));

        gridLayout->addWidget(pushButtonReset, 2, 0, 1, 1);

        line_5 = new QFrame(layoutWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_5, 3, 0, 1, 1);

        pushButtonWczytaj = new QPushButton(layoutWidget);
        pushButtonWczytaj->setObjectName(QString::fromUtf8("pushButtonWczytaj"));

        gridLayout->addWidget(pushButtonWczytaj, 4, 0, 1, 1);

        pushButtonZapisz = new QPushButton(layoutWidget);
        pushButtonZapisz->setObjectName(QString::fromUtf8("pushButtonZapisz"));

        gridLayout->addWidget(pushButtonZapisz, 5, 0, 1, 1);

        line_6 = new QFrame(layoutWidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_6, 6, 0, 1, 1);

        pushButtonZakoncz = new QPushButton(layoutWidget);
        pushButtonZakoncz->setObjectName(QString::fromUtf8("pushButtonZakoncz"));

        gridLayout->addWidget(pushButtonZakoncz, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 8, 0, 1, 1);

        groupBox_6 = new QGroupBox(SimulationWindow);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(147, 10, 391, 401));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        groupBox_6->setSizeIncrement(QSize(0, 0));
        graphicsView = new QGraphicsView(groupBox_6);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 23, 371, 371));
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(344, 0));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

        retranslateUi(SimulationWindow);

        QMetaObject::connectSlotsByName(SimulationWindow);
    } // setupUi

    void retranslateUi(QWidget *SimulationWindow)
    {
        SimulationWindow->setWindowTitle(QApplication::translate("SimulationWindow", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("SimulationWindow", "Opcje", 0, QApplication::UnicodeUTF8));
        pushButtonStart->setText(QApplication::translate("SimulationWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QApplication::translate("SimulationWindow", "Stop", 0, QApplication::UnicodeUTF8));
        pushButtonReset->setText(QApplication::translate("SimulationWindow", "Reset", 0, QApplication::UnicodeUTF8));
        pushButtonWczytaj->setText(QApplication::translate("SimulationWindow", "Wczytaj", 0, QApplication::UnicodeUTF8));
        pushButtonZapisz->setText(QApplication::translate("SimulationWindow", "Zapisz", 0, QApplication::UnicodeUTF8));
        pushButtonZakoncz->setText(QApplication::translate("SimulationWindow", "Zako\305\204cz", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("SimulationWindow", "Plansza", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SimulationWindow: public Ui_SimulationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONWINDOW_H
