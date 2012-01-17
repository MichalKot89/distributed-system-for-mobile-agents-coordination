/********************************************************************************
** Form generated from reading UI file 'agentwindow.ui'
**
** Created: Tue Jan 17 19:07:09 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGENTWINDOW_H
#define UI_AGENTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AgentWindow
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPushButton *pushButtonReset;
    QLabel *label;
    QLineEdit *lineEditNum;
    QPushButton *pushButtonOk;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBoxAgent;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonAgent;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBoxMethod;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonMethod;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonStartPos;
    QPushButton *pushButtonStopPos;
    QPushButton *pushButtonPath;
    QPushButton *pushButtonSaveAgentPath;
    QPushButton *pushButtonGen;
    QGroupBox *groupBox_3;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *AgentWindow)
    {
        if (AgentWindow->objectName().isEmpty())
            AgentWindow->setObjectName(QString::fromUtf8("AgentWindow"));
        AgentWindow->resize(712, 431);
        groupBox = new QGroupBox(AgentWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 301, 111));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 281, 81));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        pushButtonReset = new QPushButton(layoutWidget);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));

        gridLayout->addWidget(pushButtonReset, 0, 3, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEditNum = new QLineEdit(layoutWidget);
        lineEditNum->setObjectName(QString::fromUtf8("lineEditNum"));
        lineEditNum->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout->addWidget(lineEditNum, 1, 1, 1, 1);

        pushButtonOk = new QPushButton(layoutWidget);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));

        gridLayout->addWidget(pushButtonOk, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        groupBox_2 = new QGroupBox(AgentWindow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 301, 281));
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(11, 22, 281, 251));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBoxAgent = new QComboBox(widget);
        comboBoxAgent->setObjectName(QString::fromUtf8("comboBoxAgent"));
        comboBoxAgent->setEnabled(true);

        horizontalLayout->addWidget(comboBoxAgent);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Ignored, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonAgent = new QPushButton(widget);
        pushButtonAgent->setObjectName(QString::fromUtf8("pushButtonAgent"));

        horizontalLayout->addWidget(pushButtonAgent);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        comboBoxMethod = new QComboBox(widget);
        comboBoxMethod->setObjectName(QString::fromUtf8("comboBoxMethod"));

        horizontalLayout_2->addWidget(comboBoxMethod);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Ignored, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButtonMethod = new QPushButton(widget);
        pushButtonMethod->setObjectName(QString::fromUtf8("pushButtonMethod"));

        horizontalLayout_2->addWidget(pushButtonMethod);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonStartPos = new QPushButton(widget);
        pushButtonStartPos->setObjectName(QString::fromUtf8("pushButtonStartPos"));

        horizontalLayout_3->addWidget(pushButtonStartPos);

        pushButtonStopPos = new QPushButton(widget);
        pushButtonStopPos->setObjectName(QString::fromUtf8("pushButtonStopPos"));

        horizontalLayout_3->addWidget(pushButtonStopPos);

        pushButtonPath = new QPushButton(widget);
        pushButtonPath->setObjectName(QString::fromUtf8("pushButtonPath"));

        horizontalLayout_3->addWidget(pushButtonPath);


        gridLayout_3->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        pushButtonSaveAgentPath = new QPushButton(widget);
        pushButtonSaveAgentPath->setObjectName(QString::fromUtf8("pushButtonSaveAgentPath"));

        verticalLayout->addWidget(pushButtonSaveAgentPath);

        pushButtonGen = new QPushButton(widget);
        pushButtonGen->setObjectName(QString::fromUtf8("pushButtonGen"));

        verticalLayout->addWidget(pushButtonGen);

        groupBox_3 = new QGroupBox(AgentWindow);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(320, 10, 391, 401));
        graphicsView = new QGraphicsView(groupBox_3);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 20, 371, 371));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        retranslateUi(AgentWindow);

        QMetaObject::connectSlotsByName(AgentWindow);
    } // setupUi

    void retranslateUi(QWidget *AgentWindow)
    {
        AgentWindow->setWindowTitle(QApplication::translate("AgentWindow", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AgentWindow", "Liczba agent\303\263w", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AgentWindow", "Wprowad\305\272 liczb\304\231 agent\303\263w \n"
"i zatwierd\305\272 przyciskiem Ok.", 0, QApplication::UnicodeUTF8));
        pushButtonReset->setText(QApplication::translate("AgentWindow", "Reset", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AgentWindow", "Liczba agent\303\263w:", 0, QApplication::UnicodeUTF8));
        lineEditNum->setText(QString());
        pushButtonOk->setText(QApplication::translate("AgentWindow", "Ok", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("AgentWindow", "Parametry Agent\303\263w", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AgentWindow", "Wybierz Agenta:", 0, QApplication::UnicodeUTF8));
        pushButtonAgent->setText(QApplication::translate("AgentWindow", "Ok", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AgentWindow", "Wybierz spos\303\263b generowania wsp\303\263\305\202rz\304\231dnych \n"
"pocz\304\205tkowych i \305\233cie\305\274ki Agenta:", 0, QApplication::UnicodeUTF8));
        comboBoxMethod->clear();
        comboBoxMethod->insertItems(0, QStringList()
         << QApplication::translate("AgentWindow", "R\304\231cznie", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AgentWindow", "Losowo", 0, QApplication::UnicodeUTF8)
        );
        pushButtonMethod->setText(QApplication::translate("AgentWindow", "Ok", 0, QApplication::UnicodeUTF8));
        pushButtonStartPos->setText(QApplication::translate("AgentWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButtonStopPos->setText(QApplication::translate("AgentWindow", "Stop", 0, QApplication::UnicodeUTF8));
        pushButtonPath->setText(QApplication::translate("AgentWindow", "\305\232cie\305\274ka", 0, QApplication::UnicodeUTF8));
        pushButtonSaveAgentPath->setText(QApplication::translate("AgentWindow", "Zapisz: Generuj tras\304\231 agenta", 0, QApplication::UnicodeUTF8));
        pushButtonGen->setText(QApplication::translate("AgentWindow", "Zapisz trasy agent\303\263w: Generuj zadanie", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("AgentWindow", "Podgl\304\205d", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AgentWindow: public Ui_AgentWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGENTWINDOW_H
