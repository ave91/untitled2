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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "../../qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Plot
{
public:
    QGridLayout *gridLayout_2;
    QCustomPlot *customplot;
    QPushButton *startButton;
    QPushButton *stopButton;

    void setupUi(QWidget *Plot)
    {
        if (Plot->objectName().isEmpty())
            Plot->setObjectName(QStringLiteral("Plot"));
        Plot->resize(867, 577);
        gridLayout_2 = new QGridLayout(Plot);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        customplot = new QCustomPlot(Plot);
        customplot->setObjectName(QStringLiteral("customplot"));

        gridLayout_2->addWidget(customplot, 0, 0, 1, 2);

        startButton = new QPushButton(Plot);
        startButton->setObjectName(QStringLiteral("startButton"));

        gridLayout_2->addWidget(startButton, 1, 0, 1, 1);

        stopButton = new QPushButton(Plot);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        gridLayout_2->addWidget(stopButton, 1, 1, 1, 1);


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
