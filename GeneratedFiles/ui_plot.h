/********************************************************************************
** Form generated from reading UI file 'plot.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOT_H
#define UI_PLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "../../qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Plot
{
public:
    QCustomPlot *customplot;
    QPushButton *startButton;
    QPushButton *stopButton;

    void setupUi(QWidget *Plot)
    {
        if (Plot->objectName().isEmpty())
            Plot->setObjectName(QStringLiteral("Plot"));
        Plot->resize(487, 391);
        customplot = new QCustomPlot(Plot);
        customplot->setObjectName(QStringLiteral("customplot"));
        customplot->setGeometry(QRect(20, 10, 451, 331));
        startButton = new QPushButton(Plot);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(60, 350, 75, 23));
        stopButton = new QPushButton(Plot);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(340, 350, 75, 23));

        retranslateUi(Plot);

        QMetaObject::connectSlotsByName(Plot);
    } // setupUi

    void retranslateUi(QWidget *Plot)
    {
        Plot->setWindowTitle(QApplication::translate("Plot", "Form", 0));
        startButton->setText(QApplication::translate("Plot", "Start", 0));
        stopButton->setText(QApplication::translate("Plot", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class Plot: public Ui_Plot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOT_H
