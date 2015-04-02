/********************************************************************************
** Form generated from reading UI file 'untitled2.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNTITLED2_H
#define UI_UNTITLED2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_untitled2Class
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_cname_1;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_cvalue_1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_cname_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_cvalue_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_cname_3;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_cvalue_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_cname_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_cvalue_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_cname_5;
    QSpacerItem *horizontalSpacer;
    QLabel *label_cvalue_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_cname_6;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_cvalue_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_cname_7;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_cvalue_7;
    QTableView *tableView;
    QPushButton *H_Button;
    QPushButton *V_Button;
    QPushButton *P_Button;
    QPushButton *M_Button;
    QPushButton *L_Button;
    QPushButton *R_Button;
    QTableView *tableView_2;
    QPushButton *CalibrateButton;
    QFrame *line;
    QPushButton *exportButton;
    QPushButton *importButton;
    QTableView *tableView_3;
    QPushButton *stokesButton;
    QPushButton *plotButton;
    QPushButton *contAcqButton;
    QPushButton *stopacqButton;
    QPushButton *plotStokesButton;
    QPushButton *contStokesaveButton;
    QPushButton *polmodButton;
    QPushButton *fideltyButton;
    QPushButton *setfidelButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *untitled2Class)
    {
        if (untitled2Class->objectName().isEmpty())
            untitled2Class->setObjectName(QStringLiteral("untitled2Class"));
        untitled2Class->resize(922, 421);
        centralWidget = new QWidget(untitled2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 220, 75, 23));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 10, 171, 201));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_cname_1 = new QLabel(layoutWidget);
        label_cname_1->setObjectName(QStringLiteral("label_cname_1"));

        horizontalLayout_2->addWidget(label_cname_1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_cvalue_1 = new QLabel(layoutWidget);
        label_cvalue_1->setObjectName(QStringLiteral("label_cvalue_1"));

        horizontalLayout_2->addWidget(label_cvalue_1);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_cname_2 = new QLabel(layoutWidget);
        label_cname_2->setObjectName(QStringLiteral("label_cname_2"));

        horizontalLayout_5->addWidget(label_cname_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        label_cvalue_2 = new QLabel(layoutWidget);
        label_cvalue_2->setObjectName(QStringLiteral("label_cvalue_2"));

        horizontalLayout_5->addWidget(label_cvalue_2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_cname_3 = new QLabel(layoutWidget);
        label_cname_3->setObjectName(QStringLiteral("label_cname_3"));

        horizontalLayout_7->addWidget(label_cname_3);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        label_cvalue_3 = new QLabel(layoutWidget);
        label_cvalue_3->setObjectName(QStringLiteral("label_cvalue_3"));

        horizontalLayout_7->addWidget(label_cvalue_3);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_cname_4 = new QLabel(layoutWidget);
        label_cname_4->setObjectName(QStringLiteral("label_cname_4"));

        horizontalLayout_4->addWidget(label_cname_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_cvalue_4 = new QLabel(layoutWidget);
        label_cvalue_4->setObjectName(QStringLiteral("label_cvalue_4"));

        horizontalLayout_4->addWidget(label_cvalue_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_cname_5 = new QLabel(layoutWidget);
        label_cname_5->setObjectName(QStringLiteral("label_cname_5"));

        horizontalLayout->addWidget(label_cname_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_cvalue_5 = new QLabel(layoutWidget);
        label_cvalue_5->setObjectName(QStringLiteral("label_cvalue_5"));

        horizontalLayout->addWidget(label_cvalue_5);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_cname_6 = new QLabel(layoutWidget);
        label_cname_6->setObjectName(QStringLiteral("label_cname_6"));

        horizontalLayout_6->addWidget(label_cname_6);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        label_cvalue_6 = new QLabel(layoutWidget);
        label_cvalue_6->setObjectName(QStringLiteral("label_cvalue_6"));

        horizontalLayout_6->addWidget(label_cvalue_6);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_cname_7 = new QLabel(layoutWidget);
        label_cname_7->setObjectName(QStringLiteral("label_cname_7"));

        horizontalLayout_3->addWidget(label_cname_7);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_cvalue_7 = new QLabel(layoutWidget);
        label_cvalue_7->setObjectName(QStringLiteral("label_cvalue_7"));

        horizontalLayout_3->addWidget(label_cvalue_7);


        verticalLayout->addLayout(horizontalLayout_3);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(240, 10, 261, 201));
        H_Button = new QPushButton(centralWidget);
        H_Button->setObjectName(QStringLiteral("H_Button"));
        H_Button->setGeometry(QRect(240, 220, 75, 23));
        V_Button = new QPushButton(centralWidget);
        V_Button->setObjectName(QStringLiteral("V_Button"));
        V_Button->setGeometry(QRect(240, 250, 75, 23));
        P_Button = new QPushButton(centralWidget);
        P_Button->setObjectName(QStringLiteral("P_Button"));
        P_Button->setGeometry(QRect(330, 220, 75, 23));
        M_Button = new QPushButton(centralWidget);
        M_Button->setObjectName(QStringLiteral("M_Button"));
        M_Button->setGeometry(QRect(330, 250, 75, 23));
        L_Button = new QPushButton(centralWidget);
        L_Button->setObjectName(QStringLiteral("L_Button"));
        L_Button->setGeometry(QRect(420, 220, 75, 23));
        R_Button = new QPushButton(centralWidget);
        R_Button->setObjectName(QStringLiteral("R_Button"));
        R_Button->setGeometry(QRect(420, 250, 75, 23));
        tableView_2 = new QTableView(centralWidget);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setGeometry(QRect(510, 10, 271, 201));
        CalibrateButton = new QPushButton(centralWidget);
        CalibrateButton->setObjectName(QStringLiteral("CalibrateButton"));
        CalibrateButton->setGeometry(QRect(600, 230, 75, 23));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(40, 270, 761, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        exportButton = new QPushButton(centralWidget);
        exportButton->setObjectName(QStringLiteral("exportButton"));
        exportButton->setGeometry(QRect(20, 300, 75, 23));
        importButton = new QPushButton(centralWidget);
        importButton->setObjectName(QStringLiteral("importButton"));
        importButton->setGeometry(QRect(20, 330, 75, 23));
        tableView_3 = new QTableView(centralWidget);
        tableView_3->setObjectName(QStringLiteral("tableView_3"));
        tableView_3->setGeometry(QRect(800, 10, 101, 201));
        stokesButton = new QPushButton(centralWidget);
        stokesButton->setObjectName(QStringLiteral("stokesButton"));
        stokesButton->setGeometry(QRect(820, 230, 75, 23));
        plotButton = new QPushButton(centralWidget);
        plotButton->setObjectName(QStringLiteral("plotButton"));
        plotButton->setGeometry(QRect(150, 300, 91, 23));
        contAcqButton = new QPushButton(centralWidget);
        contAcqButton->setObjectName(QStringLiteral("contAcqButton"));
        contAcqButton->setGeometry(QRect(280, 300, 101, 23));
        stopacqButton = new QPushButton(centralWidget);
        stopacqButton->setObjectName(QStringLiteral("stopacqButton"));
        stopacqButton->setGeometry(QRect(410, 300, 75, 23));
        plotStokesButton = new QPushButton(centralWidget);
        plotStokesButton->setObjectName(QStringLiteral("plotStokesButton"));
        plotStokesButton->setGeometry(QRect(820, 290, 75, 23));
        contStokesaveButton = new QPushButton(centralWidget);
        contStokesaveButton->setObjectName(QStringLiteral("contStokesaveButton"));
        contStokesaveButton->setGeometry(QRect(530, 300, 111, 23));
        polmodButton = new QPushButton(centralWidget);
        polmodButton->setObjectName(QStringLiteral("polmodButton"));
        polmodButton->setGeometry(QRect(680, 300, 111, 23));
        fideltyButton = new QPushButton(centralWidget);
        fideltyButton->setObjectName(QStringLiteral("fideltyButton"));
        fideltyButton->setGeometry(QRect(150, 330, 91, 23));
        setfidelButton = new QPushButton(centralWidget);
        setfidelButton->setObjectName(QStringLiteral("setfidelButton"));
        setfidelButton->setGeometry(QRect(300, 330, 75, 23));
        untitled2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(untitled2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 922, 21));
        untitled2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(untitled2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        untitled2Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(untitled2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        untitled2Class->setStatusBar(statusBar);

        retranslateUi(untitled2Class);
        QObject::connect(pushButton, SIGNAL(clicked()), centralWidget, SLOT(repaint()));

        QMetaObject::connectSlotsByName(untitled2Class);
    } // setupUi

    void retranslateUi(QMainWindow *untitled2Class)
    {
        untitled2Class->setWindowTitle(QApplication::translate("untitled2Class", "untitled2", 0));
        pushButton->setText(QApplication::translate("untitled2Class", "Update", 0));
        label_cname_1->setText(QApplication::translate("untitled2Class", "Detector1", 0));
        label_cvalue_1->setText(QApplication::translate("untitled2Class", "TextLabel", 0));
        label_cname_2->setText(QApplication::translate("untitled2Class", "Detector2", 0));
        label_cvalue_2->setText(QApplication::translate("untitled2Class", "TextLabel", 0));
        label_cname_3->setText(QApplication::translate("untitled2Class", "Detector 3", 0));
        label_cvalue_3->setText(QApplication::translate("untitled2Class", "TextLabel", 0));
        label_cname_4->setText(QApplication::translate("untitled2Class", "Detector 4", 0));
        label_cvalue_4->setText(QApplication::translate("untitled2Class", "TextLabel", 0));
        label_cname_5->setText(QApplication::translate("untitled2Class", "Detector 5", 0));
        label_cvalue_5->setText(QApplication::translate("untitled2Class", "TextLabel", 0));
        label_cname_6->setText(QApplication::translate("untitled2Class", "Detector 6", 0));
        label_cvalue_6->setText(QApplication::translate("untitled2Class", "TextLabel", 0));
        label_cname_7->setText(QApplication::translate("untitled2Class", "Detector 7", 0));
        label_cvalue_7->setText(QApplication::translate("untitled2Class", "TextLabel", 0));
        H_Button->setText(QApplication::translate("untitled2Class", "|H>", 0));
        V_Button->setText(QApplication::translate("untitled2Class", "|V>", 0));
        P_Button->setText(QApplication::translate("untitled2Class", "|P>", 0));
        M_Button->setText(QApplication::translate("untitled2Class", "|M>", 0));
        L_Button->setText(QApplication::translate("untitled2Class", "|L>", 0));
        R_Button->setText(QApplication::translate("untitled2Class", "|R>", 0));
        CalibrateButton->setText(QApplication::translate("untitled2Class", "Calibrate!", 0));
        exportButton->setText(QApplication::translate("untitled2Class", "Export", 0));
        importButton->setText(QApplication::translate("untitled2Class", "Import", 0));
        stokesButton->setText(QApplication::translate("untitled2Class", "Stokes", 0));
        plotButton->setText(QApplication::translate("untitled2Class", "Continous Plot", 0));
        contAcqButton->setText(QApplication::translate("untitled2Class", "Cont Acquisition", 0));
        stopacqButton->setText(QApplication::translate("untitled2Class", "Stop Acq", 0));
        plotStokesButton->setText(QApplication::translate("untitled2Class", "PlotStokes", 0));
        contStokesaveButton->setText(QApplication::translate("untitled2Class", "Cont Save Stokes", 0));
        polmodButton->setText(QApplication::translate("untitled2Class", "Talk with Pol Mod", 0));
        fideltyButton->setText(QApplication::translate("untitled2Class", "Acquire Fildelty", 0));
        setfidelButton->setText(QApplication::translate("untitled2Class", "Setup Fidelty", 0));
    } // retranslateUi

};

namespace Ui {
    class untitled2Class: public Ui_untitled2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNTITLED2_H
