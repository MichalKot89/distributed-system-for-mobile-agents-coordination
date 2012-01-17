/********************************************************************************
** Form generated from reading UI file 'scenewindow.ui'
**
** Created: Tue Jan 17 19:07:09 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENEWINDOW_H
#define UI_SCENEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SceneWindow
{
public:
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButtonReset;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditSize;
    QPushButton *pushButtonsceneSize;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditSeg;
    QPushButton *pushButtonsceneSeg;
    QPushButton *pushButtonsceneGen;
    QGroupBox *groupBox_2;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *SceneWindow)
    {
        if (SceneWindow->objectName().isEmpty())
            SceneWindow->setObjectName(QString::fromUtf8("SceneWindow"));
        SceneWindow->resize(712, 431);
        groupBox = new QGroupBox(SceneWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(11, 11, 221, 271));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 30, 201, 223));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        pushButtonReset = new QPushButton(widget);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));

        verticalLayout_5->addWidget(pushButtonReset);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEditSize = new QLineEdit(widget);
        lineEditSize->setObjectName(QString::fromUtf8("lineEditSize"));
        lineEditSize->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout_2->addWidget(lineEditSize);

        pushButtonsceneSize = new QPushButton(widget);
        pushButtonsceneSize->setObjectName(QString::fromUtf8("pushButtonsceneSize"));

        horizontalLayout_2->addWidget(pushButtonsceneSize);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        line = new QFrame(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEditSeg = new QLineEdit(widget);
        lineEditSeg->setObjectName(QString::fromUtf8("lineEditSeg"));
        lineEditSeg->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout->addWidget(lineEditSeg);

        pushButtonsceneSeg = new QPushButton(widget);
        pushButtonsceneSeg->setObjectName(QString::fromUtf8("pushButtonsceneSeg"));

        horizontalLayout->addWidget(pushButtonsceneSeg);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_4);

        pushButtonsceneGen = new QPushButton(widget);
        pushButtonsceneGen->setObjectName(QString::fromUtf8("pushButtonsceneGen"));

        verticalLayout_5->addWidget(pushButtonsceneGen);

        groupBox_2 = new QGroupBox(SceneWindow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(240, 10, 391, 401));
        graphicsView = new QGraphicsView(groupBox_2);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 20, 371, 371));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        retranslateUi(SceneWindow);

        QMetaObject::connectSlotsByName(SceneWindow);
    } // setupUi

    void retranslateUi(QWidget *SceneWindow)
    {
        SceneWindow->setWindowTitle(QApplication::translate("SceneWindow", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SceneWindow", "Ustawienia", 0, QApplication::UnicodeUTF8));
        pushButtonReset->setText(QApplication::translate("SceneWindow", "Reset", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SceneWindow", "Wprowad\305\272 wymiary planszy:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SceneWindow", "Szeroko\305\233\304\207/Wysoko\305\233\304\207:", 0, QApplication::UnicodeUTF8));
        pushButtonsceneSize->setText(QApplication::translate("SceneWindow", "OK", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SceneWindow", "Wprowad\305\272 liczb\304\231 segment\303\263w:", 0, QApplication::UnicodeUTF8));
        pushButtonsceneSeg->setText(QApplication::translate("SceneWindow", "OK", 0, QApplication::UnicodeUTF8));
        pushButtonsceneGen->setText(QApplication::translate("SceneWindow", "Generuj podgl\304\205d", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("SceneWindow", "Podgl\304\205d", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SceneWindow: public Ui_SceneWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEWINDOW_H
