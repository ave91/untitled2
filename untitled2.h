#ifndef UNTITLED2_H
#define UNTITLED2_H

#include <QtWidgets/QMainWindow>
#include "ui_untitled2.h"
#include "NIDAQmx.h"
#include <fstream>
#include <vector>
#include "calibration.h"
#include "acquisition.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "plot.h"
#include "gpib.h"
#include "matrix_inv.h"



class untitled2 : public QMainWindow
{
	Q_OBJECT

public:
	untitled2(QWidget *parent = 0);
	~untitled2();
	void setlabel1(double val);
	void setlabel2(double val);
	void setlabel3(double val);
	void setlabel4(double val);
	void setlabel5(double val);
	void setlabel6(double val);
	void setlabel7(double val);
    std::vector <float64> internal_data;

    acquisition * daq_internal_pointer;
    calibration * calib_internal_pointer;
    gpib * gpib_int_pointer;

    static vector < vector <double>> temp_data;
    vector <double> S0fit;
    static double untitled2::Q(const double *xx);
    int NumericalMinimization(double avg,int nparam,const char * minName = "Minuit2",
                              const char *algoName = "" ,
                              int randomSeed = -1);

private:
	Ui::untitled2Class ui;
    QStandardItemModel *model;
    QStandardItemModel *model_matrix;
    QStandardItemModel *model_stokes;

    vector< vector <QStandardItem*>> calibmatrix_qs;
    vector <QStandardItem*> stokesvect_qs;

    QStandardItem * T_H1;
    QStandardItem * T_H2;
    QStandardItem * T_H3;
    QStandardItem * T_H4;
    QStandardItem * T_H5;
    QStandardItem * T_H6;
    QStandardItem * T_H7;

    QStandardItem * T_V1;
    QStandardItem * T_V2;
    QStandardItem * T_V3;
    QStandardItem * T_V4;
    QStandardItem * T_V5;
    QStandardItem * T_V6;
    QStandardItem * T_V7;

    QStandardItem * T_P1;
    QStandardItem * T_P2;
    QStandardItem * T_P3;
    QStandardItem * T_P4;
    QStandardItem * T_P5;
    QStandardItem * T_P6;
    QStandardItem * T_P7;

    QStandardItem * T_M1;
    QStandardItem * T_M2;
    QStandardItem * T_M3;
    QStandardItem * T_M4;
    QStandardItem * T_M5;
    QStandardItem * T_M6;
    QStandardItem * T_M7;

    QStandardItem * T_L1;
    QStandardItem * T_L2;
    QStandardItem * T_L3;
    QStandardItem * T_L4;
    QStandardItem * T_L5;
    QStandardItem * T_L6;
    QStandardItem * T_L7;

    QStandardItem * T_R1;
    QStandardItem * T_R2;
    QStandardItem * T_R3;
    QStandardItem * T_R4;
    QStandardItem * T_R5;
    QStandardItem * T_R6;
    QStandardItem * T_R7;

    Plot *wdg;

    void closeEvent(QCloseEvent *event);
    void threaded_save_stokes(const QString &filename_out);
    void keyPressEvent(QKeyEvent* event);
    string create_command(int i,double value);
    double minimization_stabiliz(int waw, double &ang, double * reference);
    void untitled2::stabilization_thread();
    bool stabilizatio_loop;
    double matrix_NI_temp[4][6];
    double matrix_MC_temp[4][4];
void dumpMatrixValues(matrix<double> &M);


	public slots: void on_pushButton_clicked();

private slots:
    void on_H_Button_clicked();
    void on_V_Button_clicked();
    void on_P_Button_clicked();
    void on_M_Button_clicked();
    void on_L_Button_clicked();
    void on_R_Button_clicked();
    void on_CalibrateButton_clicked();
    void on_stokesButton_clicked();
    void on_exportButton_clicked();
    void on_importButton_clicked();
    void on_plotButton_clicked();
    void on_contAcqButton_clicked();
    void on_stopacqButton_clicked();
    void on_plotStokesButton_clicked();

    void on_contStokesaveButton_clicked();
    void on_polmodButton_clicked();
    void on_fideltyButton_clicked();
    void on_setfidelButton_clicked();
    void on_polContCalButton_clicked();
    void on_stabilizationButton_clicked();
    void on_stabstopButton_clicked();
    void on_referenceButton_clicked();
};

#endif // UNTITLED2_H
