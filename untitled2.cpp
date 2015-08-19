#include <Windows4Root.h>
#include "untitled2.h"
#include "NIDAQmx.h"
#include "qmessagebox.h"
#include <fstream>
#include "QStandardItemModel"
#include <memory>
#include "QFileDialog"
#include "qcustomplot.h"
#include "plot.h"
#include "gnuplot.h"
#include <iomanip>      // std::setw
#include "sstream"
#include <cstdlib>
#include <random>
#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "Math/Minimizer.h"
#include "TMinuitMinimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom2.h"
#include "TError.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "Eigen/Core"
#include "Eigen/LU"
#include "Math/GSLSimAnMinimizer.h"
#include <chrono>
#include <thread>

using namespace Eigen;

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

 TApplication theApp("A",0,0);

vector < vector <double>> untitled2::temp_data;

untitled2::untitled2(QWidget *parent)
	: QMainWindow(parent)
{	

    angle_pol_test=0;
    wdg=0;
    //Configure pointers reference not initialized yet
    daq_internal_pointer=0;
    calib_internal_pointer=0;
    gpib_int_pointer=0;
    ui.setupUi(this);

    //Reserve memory for C-like use of vectors

    calibmatrix_qs.resize(4);
    for(int i=0;i<4;i++){
        (calibmatrix_qs[i]).resize(6);
    }

    stokesvect_qs.resize(4);

    //Initialize the tableview and his model
    model = new QStandardItemModel(7,6,this); //7 Rows and 6 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("|H>")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("|V>")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("|P>")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("|M>")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("|L>")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("|R>")));

    ui.tableView->setModel(model);

    //Initialize the tableview and his model
    model_matrix = new QStandardItemModel(4,6,this); //7 Rows and 6 Columns
    ui.tableView_2->setModel(model_matrix);

    //Initialize the tableview and his model
    model_stokes = new QStandardItemModel(4,1,this); //7 Rows and 6 Columns
    ui.tableView_3->setModel(model_stokes);


    //Initializiation of data pointers to null, needed for memory managment
    for(int i=0;i<4;i++){
        for(int j=0;j<6;j++){
            calibmatrix_qs[i][j]=0;
        }
    }

    for(int i=0;i<4;++i){
        stokesvect_qs[i]=0;
    }

    T_H1=0;
    T_H2=0;
    T_H3=0;
    T_H4=0;
    T_H5=0;
    T_H6=0;
    T_H7=0;
    T_V1=0;
    T_V2=0;
    T_V3=0;
    T_V4=0;
    T_V5=0;
    T_V6=0;
    T_V7=0;
    T_P1=0;
    T_P2=0;
    T_P3=0;
    T_P4=0;
    T_P5=0;
    T_P6=0;
    T_P7=0;
    T_M1=0;
    T_M2=0;
    T_M3=0;
    T_M4=0;
    T_M5=0;
    T_M6=0;
    T_M7=0;
    T_L1=0;
    T_L2=0;
    T_L3=0;
    T_L4=0;
    T_L5=0;
    T_L6=0;
    T_L7=0;
    T_R1=0;
    T_R2=0;
    T_R3=0;
    T_R4=0;
    T_R5=0;
    T_R6=0;
    T_R7=0;

}

untitled2::~untitled2()
{

}

void untitled2::setlabel1(double val){
	ui.label_cvalue_1->setText(QString::number(val));
}

void untitled2::setlabel2(double val){
	ui.label_cvalue_2->setText(QString::number(val));
}

void untitled2::setlabel3(double val){
	ui.label_cvalue_3->setText(QString::number(val));
}
void untitled2::setlabel4(double val){
	ui.label_cvalue_4->setText(QString::number(val));
}
void untitled2::setlabel5(double val){
	ui.label_cvalue_5->setText(QString::number(val));
}
void untitled2::setlabel6(double val){
	ui.label_cvalue_6->setText(QString::number(val));
}
void untitled2::setlabel7(double val){
	ui.label_cvalue_7->setText(QString::number(val));
}

void untitled2::on_pushButton_clicked() {

    if(daq_internal_pointer!=0){

    if(acquisition::stop==true){
      if(acquisition::NI==true){
    daq_internal_pointer->read_daq();
      }
      else{
       daq_internal_pointer->read_daq_MC();
      }
    }
   // cout<<"PASSATALETTURA";
    ui.label_cvalue_1->setText(QString::number(daq_internal_pointer->mean(1)));
    ui.label_cvalue_2->setText(QString::number(daq_internal_pointer->mean(2)));
    ui.label_cvalue_3->setText(QString::number(daq_internal_pointer->mean(3)));
    ui.label_cvalue_4->setText(QString::number(daq_internal_pointer->mean(4)));
    ui.label_cvalue_5->setText(QString::number(daq_internal_pointer->mean(5)));
    ui.label_cvalue_6->setText(QString::number(daq_internal_pointer->mean(6)));
    ui.label_cvalue_7->setText(QString::number(daq_internal_pointer->mean(7)));

    /*QMessageBox msgBox;
    msgBox.setText(QString::number(daq_internal_pointer->data[1]));
    msgBox.exec();
    */
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();

    }
    ui.centralWidget->update();

}

void untitled2::on_H_Button_clicked()
{
    if(daq_internal_pointer!=0 && calib_internal_pointer!=0){
        if(acquisition::stop==true){
          if(acquisition::NI==true){
        daq_internal_pointer->read_daq();
          }
          else{
           daq_internal_pointer->read_daq_MC();
          }
        }

    calib_internal_pointer->H_vector[0]=(daq_internal_pointer->mean(1));
    calib_internal_pointer->H_vector[1]=(daq_internal_pointer->mean(2));
    calib_internal_pointer->H_vector[2]=(daq_internal_pointer->mean(3));
    calib_internal_pointer->H_vector[3]=(daq_internal_pointer->mean(4));
    calib_internal_pointer->H_vector[4]=(daq_internal_pointer->mean(5));
    calib_internal_pointer->H_vector[5]=(daq_internal_pointer->mean(6));
    calib_internal_pointer->H_vector[6]=(daq_internal_pointer->mean(7));


    if(T_H1!=0){
        delete T_H1;
        T_H1=0;
    }
    if(T_H2!=0){
        delete T_H2;
        T_H2=0;
    }
    if(T_H3!=0){
        delete T_H3;
        T_H3=0;
    }
    if(T_H4!=0){
        delete T_H4;
       T_H4=0;
    }
    if(T_H5!=0){
        delete T_H5;
        T_H5=0;
    }
    if(T_H6!=0){
        delete T_H6;
        T_H6=0;
    }
    if(T_H7!=0){
        delete T_H7;
        T_H7=0;
    }



     T_H1= new QStandardItem (QString::number(calib_internal_pointer->H_vector[0]));
     T_H2= new QStandardItem (QString::number(calib_internal_pointer->H_vector[1]));
     T_H3= new QStandardItem (QString::number(calib_internal_pointer->H_vector[2]));
     T_H4= new QStandardItem (QString::number(calib_internal_pointer->H_vector[3]));
     T_H5= new QStandardItem (QString::number(calib_internal_pointer->H_vector[4]));
     T_H6= new QStandardItem (QString::number(calib_internal_pointer->H_vector[5]));
     T_H7= new QStandardItem (QString::number(calib_internal_pointer->H_vector[6]));

    model->setItem(0,0,T_H1);
    model->setItem(1,0,T_H2);
    model->setItem(2,0,T_H3);
    model->setItem(3,0,T_H4);
    model->setItem(4,0,T_H5);
    model->setItem(5,0,T_H6);
    model->setItem(6,0,T_H7);
    ui.tableView->update();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();

    }

}



void untitled2::on_V_Button_clicked()
{
    if(daq_internal_pointer!=0){

        if(acquisition::stop==true){
          if(acquisition::NI==true){
        daq_internal_pointer->read_daq();
          }
          else{
           daq_internal_pointer->read_daq_MC();
          }
        }

    calib_internal_pointer->V_vector[0]=(daq_internal_pointer->mean(1));
    calib_internal_pointer->V_vector[1]=(daq_internal_pointer->mean(2));
    calib_internal_pointer->V_vector[2]=(daq_internal_pointer->mean(3));
    calib_internal_pointer->V_vector[3]=(daq_internal_pointer->mean(4));
    calib_internal_pointer->V_vector[4]=(daq_internal_pointer->mean(5));
    calib_internal_pointer->V_vector[5]=(daq_internal_pointer->mean(6));
    calib_internal_pointer->V_vector[6]=(daq_internal_pointer->mean(7));


    if(T_V1!=0){
        delete T_V1;
        T_V1=0;
    }
    if(T_V2!=0){
        delete T_V2;
        T_V2=0;
    }
    if(T_V3!=0){
        delete T_V3;
        T_V3=0;
    }
    if(T_V4!=0){
        delete T_V4;
       T_V4=0;
    }
    if(T_V5!=0){
        delete T_V5;
        T_V5=0;
    }
    if(T_V6!=0){
        delete T_V6;
        T_V6=0;
    }
    if(T_V7!=0){
        delete T_V7;
        T_V7=0;
    }

     T_V1= new QStandardItem (QString::number(calib_internal_pointer->V_vector[0]));
     T_V2= new QStandardItem (QString::number(calib_internal_pointer->V_vector[1]));
     T_V3= new QStandardItem (QString::number(calib_internal_pointer->V_vector[2]));
     T_V4= new QStandardItem (QString::number(calib_internal_pointer->V_vector[3]));
     T_V5= new QStandardItem (QString::number(calib_internal_pointer->V_vector[4]));
     T_V6= new QStandardItem (QString::number(calib_internal_pointer->V_vector[5]));
     T_V7= new QStandardItem (QString::number(calib_internal_pointer->V_vector[6]));

    model->setItem(0,1,T_V1);
    model->setItem(1,1,T_V2);
    model->setItem(2,1,T_V3);
    model->setItem(3,1,T_V4);
    model->setItem(4,1,T_V5);
    model->setItem(5,1,T_V6);
    model->setItem(6,1,T_V7);
    ui.tableView->update();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();

    }

}

void untitled2::on_P_Button_clicked()
{
    if(daq_internal_pointer!=0){

        if(acquisition::stop==true){
          if(acquisition::NI==true){
        daq_internal_pointer->read_daq();
          }
          else{
           daq_internal_pointer->read_daq_MC();
          }
        }

    calib_internal_pointer->P_vector[0]=(daq_internal_pointer->mean(1));
    calib_internal_pointer->P_vector[1]=(daq_internal_pointer->mean(2));
    calib_internal_pointer->P_vector[2]=(daq_internal_pointer->mean(3));
    calib_internal_pointer->P_vector[3]=(daq_internal_pointer->mean(4));
    calib_internal_pointer->P_vector[4]=(daq_internal_pointer->mean(5));
    calib_internal_pointer->P_vector[5]=(daq_internal_pointer->mean(6));
    calib_internal_pointer->P_vector[6]=(daq_internal_pointer->mean(7));


    if(T_P1!=0){
        delete T_P1;
        T_P1=0;
    }
    if(T_P2!=0){
        delete T_P2;
        T_P2=0;
    }
    if(T_P3!=0){
        delete T_P3;
        T_P3=0;
    }
    if(T_P4!=0){
        delete T_P4;
       T_P4=0;
    }
    if(T_P5!=0){
        delete T_P5;
        T_P5=0;
    }
    if(T_P6!=0){
        delete T_P6;
        T_P6=0;
    }
    if(T_P7!=0){
        delete T_P7;
        T_P7=0;
    }

     T_P1= new QStandardItem (QString::number(calib_internal_pointer->P_vector[0]));
     T_P2= new QStandardItem (QString::number(calib_internal_pointer->P_vector[1]));
     T_P3= new QStandardItem (QString::number(calib_internal_pointer->P_vector[2]));
     T_P4= new QStandardItem (QString::number(calib_internal_pointer->P_vector[3]));
     T_P5= new QStandardItem (QString::number(calib_internal_pointer->P_vector[4]));
     T_P6= new QStandardItem (QString::number(calib_internal_pointer->P_vector[5]));
     T_P7= new QStandardItem (QString::number(calib_internal_pointer->P_vector[6]));

    model->setItem(0,2,T_P1);
    model->setItem(1,2,T_P2);
    model->setItem(2,2,T_P3);
    model->setItem(3,2,T_P4);
    model->setItem(4,2,T_P5);
    model->setItem(5,2,T_P6);
    model->setItem(6,2,T_P7);
    ui.tableView->update();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();

    }

}

void untitled2::on_M_Button_clicked()
{
    if(daq_internal_pointer!=0){
        if(acquisition::stop==true){
          if(acquisition::NI==true){
        daq_internal_pointer->read_daq();
          }
          else{
           daq_internal_pointer->read_daq_MC();
          }
        }
    calib_internal_pointer->M_vector[0]=(daq_internal_pointer->mean(1));
    calib_internal_pointer->M_vector[1]=(daq_internal_pointer->mean(2));
    calib_internal_pointer->M_vector[2]=(daq_internal_pointer->mean(3));
    calib_internal_pointer->M_vector[3]=(daq_internal_pointer->mean(4));
    calib_internal_pointer->M_vector[4]=(daq_internal_pointer->mean(5));
    calib_internal_pointer->M_vector[5]=(daq_internal_pointer->mean(6));
    calib_internal_pointer->M_vector[6]=(daq_internal_pointer->mean(7));


    if(T_M1!=0){
        delete T_M1;
        T_M1=0;
    }
    if(T_M2!=0){
        delete T_M2;
        T_M2=0;
    }
    if(T_M3!=0){
        delete T_M3;
        T_M3=0;
    }
    if(T_M4!=0){
        delete T_M4;
       T_M4=0;
    }
    if(T_M5!=0){
        delete T_M5;
        T_M5=0;
    }
    if(T_M6!=0){
        delete T_M6;
        T_M6=0;
    }
    if(T_M7!=0){
        delete T_M7;
        T_M7=0;
    }

     T_M1= new QStandardItem (QString::number(calib_internal_pointer->M_vector[0]));
     T_M2= new QStandardItem (QString::number(calib_internal_pointer->M_vector[1]));
     T_M3= new QStandardItem (QString::number(calib_internal_pointer->M_vector[2]));
     T_M4= new QStandardItem (QString::number(calib_internal_pointer->M_vector[3]));
     T_M5= new QStandardItem (QString::number(calib_internal_pointer->M_vector[4]));
     T_M6= new QStandardItem (QString::number(calib_internal_pointer->M_vector[5]));
     T_M7= new QStandardItem (QString::number(calib_internal_pointer->M_vector[6]));

    model->setItem(0,3,T_M1);
    model->setItem(1,3,T_M2);
    model->setItem(2,3,T_M3);
    model->setItem(3,3,T_M4);
    model->setItem(4,3,T_M5);
    model->setItem(5,3,T_M6);
    model->setItem(6,3,T_M7);
    ui.tableView->update();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();

    }

}

void untitled2::on_L_Button_clicked()
{
    if(daq_internal_pointer!=0){

        if(acquisition::stop==true){
          if(acquisition::NI==true){
        daq_internal_pointer->read_daq();
          }
          else{
           daq_internal_pointer->read_daq_MC();
          }
        }

    calib_internal_pointer->L_vector[0]=(daq_internal_pointer->mean(1));
    calib_internal_pointer->L_vector[1]=(daq_internal_pointer->mean(2));
    calib_internal_pointer->L_vector[2]=(daq_internal_pointer->mean(3));
    calib_internal_pointer->L_vector[3]=(daq_internal_pointer->mean(4));
    calib_internal_pointer->L_vector[4]=(daq_internal_pointer->mean(5));
    calib_internal_pointer->L_vector[5]=(daq_internal_pointer->mean(6));
    calib_internal_pointer->L_vector[6]=(daq_internal_pointer->mean(7));


    if(T_L1!=0){
        delete T_L1;
        T_L1=0;
    }
    if(T_L2!=0){
        delete T_L2;
        T_L2=0;
    }
    if(T_L3!=0){
        delete T_L3;
        T_L3=0;
    }
    if(T_L4!=0){
        delete T_L4;
       T_L4=0;
    }
    if(T_L5!=0){
        delete T_L5;
        T_L5=0;
    }
    if(T_L6!=0){
        delete T_L6;
        T_L6=0;
    }
    if(T_L7!=0){
        delete T_L7;
        T_L7=0;
    }

     T_L1= new QStandardItem (QString::number(calib_internal_pointer->L_vector[0]));
     T_L2= new QStandardItem (QString::number(calib_internal_pointer->L_vector[1]));
     T_L3= new QStandardItem (QString::number(calib_internal_pointer->L_vector[2]));
     T_L4= new QStandardItem (QString::number(calib_internal_pointer->L_vector[3]));
     T_L5= new QStandardItem (QString::number(calib_internal_pointer->L_vector[4]));
     T_L6= new QStandardItem (QString::number(calib_internal_pointer->L_vector[5]));
     T_L7= new QStandardItem (QString::number(calib_internal_pointer->L_vector[6]));

    model->setItem(0,4,T_L1);
    model->setItem(1,4,T_L2);
    model->setItem(2,4,T_L3);
    model->setItem(3,4,T_L4);
    model->setItem(4,4,T_L5);
    model->setItem(5,4,T_L6);
    model->setItem(6,4,T_L7);
    ui.tableView->update();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();

    }

}

void untitled2::on_R_Button_clicked()
{
    if(daq_internal_pointer!=0){

        if(acquisition::stop==true){
          if(acquisition::NI==true){
        daq_internal_pointer->read_daq();
          }
          else{
           daq_internal_pointer->read_daq_MC();
          }
        }

    calib_internal_pointer->R_vector[0]=(daq_internal_pointer->mean(1));
    calib_internal_pointer->R_vector[1]=(daq_internal_pointer->mean(2));
    calib_internal_pointer->R_vector[2]=(daq_internal_pointer->mean(3));
    calib_internal_pointer->R_vector[3]=(daq_internal_pointer->mean(4));
    calib_internal_pointer->R_vector[4]=(daq_internal_pointer->mean(5));
    calib_internal_pointer->R_vector[5]=(daq_internal_pointer->mean(6));
    calib_internal_pointer->R_vector[6]=(daq_internal_pointer->mean(7));


    if(T_R1!=0){
        delete T_R1;
        T_R1=0;
    }
    if(T_R2!=0){
        delete T_R2;
        T_R2=0;
    }
    if(T_R3!=0){
        delete T_R3;
        T_R3=0;
    }
    if(T_R4!=0){
        delete T_R4;
       T_R4=0;
    }
    if(T_R5!=0){
        delete T_R5;
        T_R5=0;
    }
    if(T_R6!=0){
        delete T_R6;
        T_R6=0;
    }
    if(T_R7!=0){
        delete T_R7;
        T_R7=0;
    }

     T_R1= new QStandardItem (QString::number(calib_internal_pointer->R_vector[0]));
     T_R2= new QStandardItem (QString::number(calib_internal_pointer->R_vector[1]));
     T_R3= new QStandardItem (QString::number(calib_internal_pointer->R_vector[2]));
     T_R4= new QStandardItem (QString::number(calib_internal_pointer->R_vector[3]));
     T_R5= new QStandardItem (QString::number(calib_internal_pointer->R_vector[4]));
     T_R6= new QStandardItem (QString::number(calib_internal_pointer->R_vector[5]));
     T_R7= new QStandardItem (QString::number(calib_internal_pointer->R_vector[6]));

    model->setItem(0,5,T_R1);
    model->setItem(1,5,T_R2);
    model->setItem(2,5,T_R3);
    model->setItem(3,5,T_R4);
    model->setItem(4,5,T_R5);
    model->setItem(5,5,T_R6);
    model->setItem(6,5,T_R7);
    ui.tableView->update();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();

    }

}

void untitled2::on_CalibrateButton_clicked()
{
    if(calib_internal_pointer!=0){
        if(acquisition::NI==true){
        calib_internal_pointer->compute_calibration_Numeric();
        }
        else{
            calib_internal_pointer->compute_calibration_4_det();
        }

        for(int i=0;i<4;i++){
            for(int j=0;j<6;j++){
               if(  calibmatrix_qs[i][j]!=0){
                   delete calibmatrix_qs[i][j];
                   calibmatrix_qs[i][j]=0;
               }
            }
        }

        for(int i=0;i<4;i++){
            for(int j=0;j<6;j++){
                calibmatrix_qs[i][j]=new QStandardItem (QString::number(calib_internal_pointer->matrix[i][j]));
                model_matrix->setItem(i,j,calibmatrix_qs[i][j]);
            }
        }

        ui.tableView_2->update();



    }
}

void untitled2::on_stokesButton_clicked()
{
    if(calib_internal_pointer!=0 && daq_internal_pointer!=0 ){

        if(acquisition::stop==true){
          if(acquisition::NI==true){
        daq_internal_pointer->read_daq();
          }
          else{
           daq_internal_pointer->read_daq_MC();
          }
        }

      double itot=daq_internal_pointer->mean(7);
      if(acquisition::NI==false){
          itot=daq_internal_pointer->mean(1)+daq_internal_pointer->mean(2)+daq_internal_pointer->mean(3)+daq_internal_pointer->mean(4);
      }
      itot=1;
      double i1=(daq_internal_pointer->mean(1))/itot;
      double i2=(daq_internal_pointer->mean(2))/itot;
      double i3=(daq_internal_pointer->mean(3))/itot;
      double i4=(daq_internal_pointer->mean(4))/itot;
      double i5=(daq_internal_pointer->mean(5))/itot;
      double i6=(daq_internal_pointer->mean(6))/itot;



      calib_internal_pointer->stokes_dat[0]=i1*calib_internal_pointer->matrix[0][0] + i2*calib_internal_pointer->matrix[0][1] + i3*calib_internal_pointer->matrix[0][2] + i4*calib_internal_pointer->matrix[0][3] + i5*calib_internal_pointer->matrix[0][4] + i6*calib_internal_pointer->matrix[0][5];
      calib_internal_pointer->stokes_dat[1]=i1*calib_internal_pointer->matrix[1][0] + i2*calib_internal_pointer->matrix[1][1] + i3*calib_internal_pointer->matrix[1][2] + i4*calib_internal_pointer->matrix[1][3] + i5*calib_internal_pointer->matrix[1][4] + i6*calib_internal_pointer->matrix[1][5];
      calib_internal_pointer->stokes_dat[2]=i1*calib_internal_pointer->matrix[2][0] + i2*calib_internal_pointer->matrix[2][1] + i3*calib_internal_pointer->matrix[2][2] + i4*calib_internal_pointer->matrix[2][3] + i5*calib_internal_pointer->matrix[2][4] + i6*calib_internal_pointer->matrix[2][5];
      calib_internal_pointer->stokes_dat[3]=i1*calib_internal_pointer->matrix[3][0] + i2*calib_internal_pointer->matrix[3][1] + i3*calib_internal_pointer->matrix[3][2] + i4*calib_internal_pointer->matrix[3][3] + i5*calib_internal_pointer->matrix[3][4] + i6*calib_internal_pointer->matrix[3][5];

      double s0,s1,s2,s3=0.0;
      s0=calib_internal_pointer->stokes_dat[0];
      s1=calib_internal_pointer->stokes_dat[1]/s0;
      s2=calib_internal_pointer->stokes_dat[2]/s0;
      s3=calib_internal_pointer->stokes_dat[3]/s0;

     // cout<<s1<<s2<<s3<<endl;

      calib_internal_pointer->stokes_dat[1]=s1;
      calib_internal_pointer->stokes_dat[2]=s2;
      calib_internal_pointer->stokes_dat[3]=s3;



      for(int i=0;i<4;i++){
             if(  stokesvect_qs[i]!=0){
                 delete stokesvect_qs[i];
                 stokesvect_qs[i]=0;
             }
      }

      for(int i=0;i<4;i++){
              stokesvect_qs[i]=new QStandardItem (QString::number(calib_internal_pointer->stokes_dat[i]));
              model_stokes->setItem(i,0,stokesvect_qs[i]);

      }

      ui.tableView_3->update();

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();
    }
}


void untitled2::on_exportButton_clicked()
{
    QString filename=QFileDialog::getSaveFileName(this, tr("Save File"),"./calibration.txt",tr("Text files (*.txt)"));
    ofstream fileout;
    fileout.open(filename.toUtf8().constData());

    if(calib_internal_pointer!=0){
        for(int i=0;i<4;++i){
            for(int j=0;j<6;++j){
                fileout<<calib_internal_pointer->matrix[i][j]<<"\t";
            }
        fileout<<endl;
        }
    }
    fileout.close();
    return;

}

void untitled2::on_importButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"./calibration.txt",tr("Text files (*.txt)"));
    ifstream filein;
    filein.open(filename.toUtf8().constData());

    double temp0=0;
    double temp1=0;
    double temp2=0;
    double temp3=0;
    double temp4=0;
    double temp5=0;

    if(calib_internal_pointer!=0){
        for(int i=0;i<4;++i){
            filein>>temp0;
            filein>>temp1;
            filein>>temp2;
            filein>>temp3;
            filein>>temp4;
            filein>>temp5;

            calib_internal_pointer->matrix[i][0]=temp0;
            calib_internal_pointer->matrix[i][1]=temp1;
            calib_internal_pointer->matrix[i][2]=temp2;
            calib_internal_pointer->matrix[i][3]=temp3;
            calib_internal_pointer->matrix[i][4]=temp4;
            calib_internal_pointer->matrix[i][5]=temp5;

        }
    }
    filein.close();
    for(int i=0;i<4;i++){
        for(int j=0;j<6;j++){
           if(  calibmatrix_qs[i][j]!=0){
               delete calibmatrix_qs[i][j];
               calibmatrix_qs[i][j]=0;
           }
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<6;j++){
            calibmatrix_qs[i][j]=new QStandardItem (QString::number(calib_internal_pointer->matrix[i][j]));
            model_matrix->setItem(i,j,calibmatrix_qs[i][j]);
        }
    }


    ui.tableView_2->update();

    return;




}

void untitled2::on_plotButton_clicked()
{

    wdg = new Plot(daq_internal_pointer);
    wdg->setAttribute(Qt::WA_DeleteOnClose);

    wdg->show();
    wdg->run();

}

void untitled2::on_contAcqButton_clicked()
{
    if(acquisition::NI==true){
    daq_internal_pointer->thread_cont_acq();
    }
    else{
        daq_internal_pointer->thread_cont_acq_MC();
    }
}

void untitled2::on_stopacqButton_clicked()
{
    acquisition::stop=true;
    daq_internal_pointer->thread_cont_acq_stop();
}

void untitled2::closeEvent(QCloseEvent *event)
{
 acquisition::stop=true;
}

void untitled2::on_plotStokesButton_clicked()
{
    Gnuplot plot;

     string a,b,c;
     a="a=";
     a=a+to_string(calib_internal_pointer->stokes_dat[1]);
     b="b=";
     b=b+to_string(calib_internal_pointer->stokes_dat[2]);
     c="c=";
     c=c+to_string(calib_internal_pointer->stokes_dat[3]);
    // cout<<a<<endl;
     plot(a.c_str());
     plot(b.c_str());
     plot(c.c_str());
     //plot("set arrow from 0,0,0 to a,b,c front nohead ls 2");
     plot("load \"gnuplotscript.txt\"") ;
     //system("pause");
}

void untitled2::on_contStokesaveButton_clicked()
{
    if(daq_internal_pointer!=0){
       QString filename_out=QFileDialog::getSaveFileName(this, tr("Save File"),"./stokesoutput.txt",tr("Text files (*.txt)"));



        daq_internal_pointer->thread_cont_acq();
       QFuture <void> future = QtConcurrent::run(this,&untitled2::threaded_save_stokes,filename_out);

    }

}

void untitled2::threaded_save_stokes(const QString &filename_out){

    ofstream file_out;
    file_out.open(filename_out.toUtf8().constData());
    while(acquisition::stop==false) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        float itot=1.;
        double i1=(daq_internal_pointer->mean(1))/itot;
        double i2=(daq_internal_pointer->mean(2))/itot;
        double i3=(daq_internal_pointer->mean(3))/itot;
        double i4=(daq_internal_pointer->mean(4))/itot;
        double i5=(daq_internal_pointer->mean(5))/itot;
        double i6=(daq_internal_pointer->mean(6))/itot;



        calib_internal_pointer->stokes_dat[0]=i1*calib_internal_pointer->matrix[0][0] + i2*calib_internal_pointer->matrix[0][1] + i3*calib_internal_pointer->matrix[0][2] + i4*calib_internal_pointer->matrix[0][3] + i5*calib_internal_pointer->matrix[0][4] + i6*calib_internal_pointer->matrix[0][5];
        calib_internal_pointer->stokes_dat[1]=i1*calib_internal_pointer->matrix[1][0] + i2*calib_internal_pointer->matrix[1][1] + i3*calib_internal_pointer->matrix[1][2] + i4*calib_internal_pointer->matrix[1][3] + i5*calib_internal_pointer->matrix[1][4] + i6*calib_internal_pointer->matrix[1][5];
        calib_internal_pointer->stokes_dat[2]=i1*calib_internal_pointer->matrix[2][0] + i2*calib_internal_pointer->matrix[2][1] + i3*calib_internal_pointer->matrix[2][2] + i4*calib_internal_pointer->matrix[2][3] + i5*calib_internal_pointer->matrix[2][4] + i6*calib_internal_pointer->matrix[2][5];
        calib_internal_pointer->stokes_dat[3]=i1*calib_internal_pointer->matrix[3][0] + i2*calib_internal_pointer->matrix[3][1] + i3*calib_internal_pointer->matrix[3][2] + i4*calib_internal_pointer->matrix[3][3] + i5*calib_internal_pointer->matrix[3][4] + i6*calib_internal_pointer->matrix[3][5];

        double s0,s1,s2,s3=0.0;
        s0=calib_internal_pointer->stokes_dat[0];
        s1=calib_internal_pointer->stokes_dat[1]/s0;
        s2=calib_internal_pointer->stokes_dat[2]/s0;
        s3=calib_internal_pointer->stokes_dat[3]/s0;

       // cout<<s1<<s2<<s3<<endl;

        calib_internal_pointer->stokes_dat[1]=s1;
        calib_internal_pointer->stokes_dat[2]=s2;
        calib_internal_pointer->stokes_dat[3]=s3;

        file_out<<calib_internal_pointer->stokes_dat[0]<<"\t"<<calib_internal_pointer->stokes_dat[1]<<"\t"<<calib_internal_pointer->stokes_dat[2]<<"\t"<<calib_internal_pointer->stokes_dat[3]<<endl;

    }
    file_out.close();
    return;
}

void untitled2::on_polmodButton_clicked()
{
    if(gpib_int_pointer!=0){
        gpib_int_pointer->init();
         Sleep(60);
        gpib_int_pointer->GPIBWrite((char *)"*IDN?\n");
        Sleep(60);
        cout<<gpib_int_pointer->GPIBRead()<<endl;
    }
}

void untitled2::on_fideltyButton_clicked()
{
    ofstream fileout("fidelty.txt", ios::app);
    double stkNI[4];
    double stkMC[4];
    double fidelty=0.;
    acquisition::NI=true;
    acquisition::datasize=7*acquisition::samp_per_chan;
    acquisition::total_num_chan=7;
    acquisition::data.resize(acquisition::datasize+1);
    daq_internal_pointer->read_daq();
    for(int i=0;i<4;i++){
        for (int j=0;j<6;++j){
            calib_internal_pointer->matrix[i][j]=matrix_NI_temp[i][j];
        }
    }
    untitled2::on_stokesButton_clicked();
    stkNI[0]=calib_internal_pointer->stokes_dat[0];
    stkNI[1]=calib_internal_pointer->stokes_dat[1];
    stkNI[2]=calib_internal_pointer->stokes_dat[2];
    stkNI[3]=calib_internal_pointer->stokes_dat[3];

    acquisition::NI=false;
    acquisition::datasize=acquisition::Count;
    acquisition::total_num_chan=4;
    acquisition::data.resize(acquisition::datasize+1);
    acquisition::ADData.resize(acquisition::datasize+1);
    daq_internal_pointer->read_daq();
    for(int i=0;i<4;i++){
        for (int j=0;j<6;++j){
            calib_internal_pointer->matrix[i][j]=matrix_MC_temp[i][j];
        }
    }
    untitled2::on_stokesButton_clicked();
    stkMC[0]=calib_internal_pointer->stokes_dat[0];
    stkMC[1]=calib_internal_pointer->stokes_dat[1];
    stkMC[2]=calib_internal_pointer->stokes_dat[2];
    stkMC[3]=calib_internal_pointer->stokes_dat[3];

    fidelty=stkNI[1]*stkMC[1]+stkNI[2]*stkMC[2]+stkNI[3]*stkMC[3];

    fileout<<stkMC[0]<<"\t"<<stkNI[0]<<"\t"<<fidelty<<endl;
    fileout<<stkMC[1]<<"\t"<<stkNI[1]<<"\t"<<endl;
    fileout<<stkMC[2]<<"\t"<<stkNI[2]<<"\t"<<endl;
    fileout<<stkMC[3]<<"\t"<<stkNI[3]<<"\t"<<endl;

    fileout.close();


}

void untitled2::on_setfidelButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"./calibration_NI.txt",tr("Text files (*.txt)"));
    ifstream filein;
    filein.open(filename.toUtf8().constData());

    double temp0=0;
    double temp1=0;
    double temp2=0;
    double temp3=0;
    double temp4=0;
    double temp5=0;


        for(int i=0;i<4;++i){
            filein>>temp0;
            filein>>temp1;
            filein>>temp2;
            filein>>temp3;
            filein>>temp4;
            filein>>temp5;

            matrix_NI_temp[i][0]=temp0;
            matrix_NI_temp[i][1]=temp1;
            matrix_NI_temp[i][2]=temp2;
            matrix_NI_temp[i][3]=temp3;
            matrix_NI_temp[i][4]=temp4;
            matrix_NI_temp[i][5]=temp5;


    }
    filein.close();
    QString filename2=QFileDialog::getOpenFileName(this, tr("Open File"),"./calibration_MC.txt",tr("Text files (*.txt)"));
    ifstream filein2;
    filein2.open(filename2.toUtf8().constData());

     temp0=0;
     temp1=0;
     temp2=0;
     temp3=0;
     temp4=0;
     temp5=0;


        for(int i=0;i<4;++i){
            filein2>>temp0;
            filein2>>temp1;
            filein2>>temp2;
            filein2>>temp3;


            matrix_MC_temp[i][0]=temp0;
            matrix_MC_temp[i][1]=temp1;
            matrix_MC_temp[i][2]=temp2;
            matrix_MC_temp[i][3]=temp3;
            matrix_MC_temp[i][4]=0;
            matrix_MC_temp[i][5]=0;


    }
    filein2.close();



}
void untitled2::keyPressEvent(QKeyEvent* event) {
    // If Ctrl-C typed
    // Or use event->matches(QKeySequence::Copy)
    if (event->key() == Qt::Key_C && (event->modifiers() & Qt::ControlModifier))
    {

        QAbstractItemModel * model = ui.tableView_3->model();
        QItemSelectionModel * selection = ui.tableView_3->selectionModel();
        QModelIndexList cells = selection->selectedIndexes();
        qSort(cells); // Necessary, otherwise they are in column order

        QString text;
        int currentRow = 0; // To determine when to insert newlines
        foreach (const QModelIndex& cell, cells) {
            if (text.length() == 0) {
                // First item
            } else if (cell.row() != currentRow) {
                // New row
                text += '\n';
            } else {
                // Next cell
                text += '\t';
            }
            currentRow = cell.row();
            text += cell.data().toString();
        }

        QApplication::clipboard()->setText(text);
    }
}

void untitled2::on_polContCalButton_clicked()
{
    double angle=0.;
    string command;
    ofstream fileout;
    fileout.open("polarizationcontrollercalibration.txt");
   if(gpib_int_pointer!=0){
        gpib_int_pointer->init();
         Sleep(60);
         gpib_int_pointer->GPIBWrite((char *)"X=-99.00\n");
         Sleep(60);
         gpib_int_pointer->GPIBWrite((char *)"Y=00.00\n");
         Sleep(60);
         gpib_int_pointer->GPIBWrite((char *)"Z=00.00\n");
         Sleep(60);
         for (int i=0;i<=1320;i++){
             angle =-99+ 0.15*i;       // number to be converted to a string
             command="X=";          // string which will contain the result
             ostringstream convert;   // stream used for the conversion
             convert << std::setfill('0') << std::setw(4)<< setiosflags(ios::fixed) << setprecision(2) <<angle;      // insert the textual representation of 'Number' in the characters in the stream
             command = command+convert.str();
             command=command+"\n";
             gpib_int_pointer->GPIBWrite(&(command[0]));
             Sleep(60);
             untitled2::on_stokesButton_clicked();
             fileout<<angle<<"\t"<<calib_internal_pointer->stokes_dat[0]<<"\t"<<calib_internal_pointer->stokes_dat[1]<<"\t"<<calib_internal_pointer->stokes_dat[2]<<"\t"<<calib_internal_pointer->stokes_dat[3]<<endl;

         }
        fileout<<endl;
        gpib_int_pointer->GPIBWrite((char *)"X=00.00\n");
        Sleep(60);
        gpib_int_pointer->GPIBWrite((char *)"Y=-99.00\n");
        Sleep(60);
        for (int i=0;i<=1320;i++){
            angle =-99+ 0.15*i;       // number to be converted to a string
            command="Y=";          // string which will contain the result
            ostringstream convert;   // stream used for the conversion
            convert << std::setfill('0') << std::setw(4)<< setiosflags(ios::fixed) << setprecision(2) <<angle;      // insert the textual representation of 'Number' in the characters in the stream
            command = command+convert.str();
            command=command+"\n";
            gpib_int_pointer->GPIBWrite(&(command[0]));
            Sleep(60);
            untitled2::on_stokesButton_clicked();
            fileout<<angle<<"\t"<<calib_internal_pointer->stokes_dat[0]<<"\t"<<calib_internal_pointer->stokes_dat[1]<<"\t"<<calib_internal_pointer->stokes_dat[2]<<"\t"<<calib_internal_pointer->stokes_dat[3]<<endl;
            }
        fileout<<endl;
        gpib_int_pointer->GPIBWrite((char *)"Y=00.00\n");
        Sleep(60);
        gpib_int_pointer->GPIBWrite((char *)"Z=-99.00\n");
        Sleep(60);
        for (int i=0;i<=1320;i++){
            angle =-99+ 0.15*i;       // number to be converted to a string
            command="Z=";          // string which will contain the result
            ostringstream convert;   // stream used for the conversion
            convert << std::setfill('0') << std::setw(4)<< setiosflags(ios::fixed) << setprecision(2) <<angle;      // insert the textual representation of 'Number' in the characters in the stream
            command = command+convert.str();
            command=command+"\n";
            gpib_int_pointer->GPIBWrite(&(command[0]));
            Sleep(60);
            untitled2::on_stokesButton_clicked();
            fileout<<angle<<"\t"<<calib_internal_pointer->stokes_dat[0]<<"\t"<<calib_internal_pointer->stokes_dat[1]<<"\t"<<calib_internal_pointer->stokes_dat[2]<<"\t"<<calib_internal_pointer->stokes_dat[3]<<endl;
            }
}
    fileout.close();






}

double untitled2::minimization_stabiliz(int waw,double &ang,double * reference){
    double new_angle=ang;
    double initial_difference;
    double forward_difference;
    double backward_difference;
    double temp_difference;
    string temp_command;
    double step=0.15;
    untitled2::on_stokesButton_clicked();
    initial_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );
    if(initial_difference>0.3){
        step=3;
    }
    else if(initial_difference>0.15){
        step=0.45;
    }
    else if(initial_difference>0.1){
        step=0.3;
    }

    new_angle=ang+step;
    temp_command=create_command(waw,new_angle);
    gpib_int_pointer->GPIBWrite(&(temp_command[0]));
    untitled2::on_stokesButton_clicked();
    forward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );

    if(forward_difference<= initial_difference){

        temp_difference=initial_difference;

        while(forward_difference<=temp_difference){

            temp_difference=forward_difference;
            new_angle=new_angle+step;
            if(new_angle>99){new_angle=-90;}
            temp_command=create_command(waw,new_angle);
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            untitled2::on_stokesButton_clicked();
            forward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );


        }

        new_angle=new_angle-step;
        if(new_angle<-99){new_angle=+90;}
        temp_command=create_command(waw,new_angle);
        gpib_int_pointer->GPIBWrite(&(temp_command[0]));

    }
    else{
        new_angle=ang-step;
        temp_command=create_command(waw,new_angle);
        gpib_int_pointer->GPIBWrite(&(temp_command[0]));
        untitled2::on_stokesButton_clicked();
        backward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );
            if(backward_difference<= initial_difference){

            temp_difference=initial_difference;

            while(backward_difference<=temp_difference){

                temp_difference=backward_difference;
                new_angle=new_angle-step;
                if(new_angle<-99){new_angle=99;}
                temp_command=create_command(waw,new_angle);
                gpib_int_pointer->GPIBWrite(&(temp_command[0]));
                untitled2::on_stokesButton_clicked();
                backward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );


            }

            new_angle=new_angle+step;
            if(new_angle>99){new_angle=-99;}
            temp_command=create_command(waw,new_angle);
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));

            }


    }

    ang=new_angle;
    return temp_difference;


}

void untitled2::on_stabilizationButton_clicked(){
    stabilizatio_loop=true;
    bool ok;
       double s1 = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                          tr("S1:"), 1, -1, 1, 2, &ok);
       double s2 = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                          tr("S2:"), 1, -1, 1, 2, &ok);
       double s3 = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                          tr("S3:"), 1, -1, 1, 2, &ok);
    QFuture <void> future = QtConcurrent::run(this,&untitled2::stabilization_thread,s1,s2,s3);


}

void untitled2::stabilization_thread(double s1, double s2,double s3)
{
    qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");
    qRegisterMetaType<QVector<int>>("QVector<int>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");



    double angle1=0.;
    double angle2=0.;
    double angle3=0.;
    double difference;
    double tollerance=0.00000001;
    //bool loop_total=true;




cout<<s1<<s2<<s3;
    double reference_stokes[3]={s1,s2,s3};


   if(gpib_int_pointer!=0){
        gpib_int_pointer->init();
         Sleep(60);
         gpib_int_pointer->GPIBWrite((char *)"X?\n");
         Sleep(60);
         angle1=atof(gpib_int_pointer->GPIBRead());
         Sleep(60);
         gpib_int_pointer->GPIBWrite((char *)"Y?\n");
         Sleep(60);
         angle2=atof(gpib_int_pointer->GPIBRead());
         Sleep(60);
         gpib_int_pointer->GPIBWrite((char *)"Z?\n");
         Sleep(60);
         angle3=atof(gpib_int_pointer->GPIBRead());
         Sleep(60);

         cout<<angle1<<endl<<angle2<<endl<<angle3<<endl;
         while(stabilizatio_loop){
            difference=minimization_stabiliz(1,angle1,reference_stokes);
                if(difference<tollerance){
                    break;}
            difference=minimization_stabiliz(2,angle2,reference_stokes);
                if(difference<tollerance){
                    break;}
            difference=minimization_stabiliz(3,angle3,reference_stokes);
                if(difference<tollerance){
                    break;}
         }


   }

}


   string untitled2::create_command(int i,double value){
      string command;
      if(i==1){
          command="X=";
      }
      else if(i==2){
          command="Y=";
      }
      else if(i==3){
          command="Z=";

      }
      ostringstream convert;   // stream used for the conversion
      convert << std::setfill('0') << std::setw(4)<< setiosflags(ios::fixed) << setprecision(2) <<value;
      command = command+convert.str();
      command=command+"\n";
   return command;
   }

void untitled2::on_stabstopButton_clicked()
{
    stabilizatio_loop=false;
}
/*
void untitled2::on_referenceButton_clicked()
{
    angle_pol_test=0;
    //Set up a source of pseudorandom number generator for taking the measurments
    //I like mt so I'll use that
    std::random_device rd;
       std::mt19937 gen(rd());
       std::uniform_real_distribution<> dis(-99, 99); // Range of the generation= range of PC (I know here range=[-99,99) but i don't care so much Unlikely {-99,-99,-99} will be an eigenstate so...
    int total_data=80;

    if(calib_internal_pointer!=0 && daq_internal_pointer!=0 ){

        if(acquisition::NI==true){

        gpib_int_pointer->init();
        Sleep(60);
        vector <double> temp;
        temp.resize(7);
        string temp_command;
        ofstream fillee("referenceout.txt");
        for(int i=0;i<total_data;++i){
            temp_command=create_command(1,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(60);
            temp_command=create_command(2,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(60);
            temp_command=create_command(3,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(200);

            daq_internal_pointer->read_daq();


            temp[6]=daq_internal_pointer->mean(7);

             temp[0]=daq_internal_pointer->mean(1);
             temp[1]=daq_internal_pointer->mean(2);
             temp[2]=daq_internal_pointer->mean(3);
             temp[3]=daq_internal_pointer->mean(4);
             temp[4]=daq_internal_pointer->mean(5);
             temp[5]=daq_internal_pointer->mean(6);


/*
       for(int j=0;j<6;j++){
            if(i%6==j){
            temp[j]=1;
           }
            else{
                temp[j]=0;
            }
       cout<<temp[j]<<" ";

       }
       cout<<endl;
       temp[6]=1;
/*


             for(int j=0;j<7;j++){

             fillee<<temp[j]<<"\t";

             }
             fillee<<endl;






            temp_data.push_back(temp);
//cout<<"lolo"<<endl;

        }
        fillee.close();
        //Generate First row of calibration
     MatrixXd z(6,6);
     z= MatrixXd::Zero(6,6);
      MatrixXd z1(6,6);
      z1= MatrixXd::Zero(6,6);
     VectorXd c(6);
     VectorXd x(6);
    c=VectorXd::Zero(6);
    x= VectorXd::Zero(6);

    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            for(int k=0;k<total_data;k++){

                z(i,j)=z(i,j)+(temp_data[k][i]*temp_data[k][j]);

            }
          }
         }

    for(int j=0;j<6;j++){
        for(int k=0;k<total_data;k++){

            x(j)=x(j)+(temp_data[k][j]*temp_data[k][6]);

        }
      }

   cout<<z<<endl<<x<<endl;

    z1=z.inverse();
  cout<<z1<<endl;
  c=z1*x;
  // c.settoproduct(z,x);
    bool success=false;
    S0fit.resize(6);
    for(int i=0;i<6;i++){

    S0fit[i]=c(i);
    calib_internal_pointer->matrix[0][i]=c(i);
    //cout<<S0fit[i]<<endl;
    }
    //cout<<"lolo2"<<endl;
    NumericalMinimization(temp_data[0][6],18,"Minuit2","Migrad");


    //Ok so now c is a row vector and goes from 0 to 5 with each entry is the top entry of every column in the calibration matrix
    //Now start the funny part... Need to build the functional to be minimized (20 dim!!!!! hope for it)




}
    }


return;

//

//theApp.Run();
}


*/

void untitled2::dumpMatrixValues(matrix <double>& M)  {
  bool xyz;
  double rv;
  for (int i=0; i < M.getactualsize(); i++)
    {
    cout << "i=" << i << ": ";
    for (int j=0; j<M.getactualsize(); j++)
      {
        M.getvalue(i,j,rv,xyz);
        cout << rv << " ";
      }
    cout << endl;
    }
  return;
}


void untitled2::on_fixreferenceButton_clicked(){
    stabilizatio_loop=true;


    bool ok;
       reference[0] = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                          tr("S1:"), 1, -1, 1, 2, &ok);
       reference[1] = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                          tr("S2:"), 1, -1, 1, 2, &ok);
       reference[2] = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                          tr("S3:"), 1, -1, 1, 2, &ok);

    QFuture <void> future = QtConcurrent::run(this,&untitled2::fixreference_thread);
}


void untitled2::fixreference_thread()
{

    if(calib_internal_pointer!=0 && daq_internal_pointer!=0 ){
    if(acquisition::NI==true){




        double theta=0;
        double phi=0;
        double difference;
        double tollerance=0.01;
        untitled2::on_stokesButton_clicked();

        while(stabilizatio_loop){
           difference=fix_reference(1,theta,phi,reference);
               if(difference<tollerance){
                   break;}
           difference=fix_reference(2,theta,phi,reference);
               if(difference<tollerance){
                   break;}

        }







    }
    }


}

double untitled2::fix_reference(int angle,double &theta,double &phi,double * reference){

    double initial_difference;
    double forward_difference;
    double backward_difference;
    double temp_difference;

    double step=0.0000001;
    bool out=true;


    initial_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );
    untitled2::updatestokes(out);
    if(initial_difference>0.1){
       // step=0.00001;
    }


    if(angle==1) {
    theta=theta+step;
    }
    else if(angle==2){
    phi=phi+step;
    }
    calib_internal_pointer->rotate_calib_matrix(theta,phi);
    untitled2::updatestokes(out);
    forward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );

    if(forward_difference<= initial_difference){

        temp_difference=forward_difference;
    }
    else{
        if(angle==1) {
        theta=theta-2*step;
        }
        else if(angle==2){
        phi=phi-2*step;
        }
        calib_internal_pointer->rotate_calib_matrix(theta,phi);
        untitled2::updatestokes(out);
        backward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );
            if(backward_difference<= initial_difference){

            temp_difference=backward_difference;



            }else{
                if(angle==1) {
                theta=theta+step;
                }
                else if(angle==2){
                phi=phi+step;
                }

                temp_difference=initial_difference;


            }

}

    return temp_difference;


}






/*
double untitled2::fix_reference(int angle,double &theta,double &phi,double * reference){

    double initial_difference;
    double forward_difference;
    double backward_difference;
    double temp_difference;

    double step=0.0000001;
    bool out=true;


    initial_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );
    untitled2::updatestokes(out);
    if(initial_difference>0.1){
       // step=0.00001;
    }


    if(angle==1) {
    theta=theta+step;
    }
    else if(angle==2){
    phi=phi+step;
    }
    calib_internal_pointer->rotate_calib_matrix(theta,phi);
    untitled2::updatestokes(out);
    forward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );

    if(forward_difference<= initial_difference){

        temp_difference=initial_difference;

        while(forward_difference<=temp_difference){

            temp_difference=forward_difference;
            if(angle==1) {
            theta=theta+step;
            }
            else if(angle==2){
            phi=phi+step;
            }
            calib_internal_pointer->rotate_calib_matrix(theta,phi);
            untitled2::updatestokes(out);
            forward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );


        }

        if(angle==1) {
        theta=theta-step;
        }
        if(angle==2){
        phi=phi-step;
        }
        calib_internal_pointer->rotate_calib_matrix(theta,phi);
        untitled2::updatestokes(out);

    }
    else{
        if(angle==1) {
        theta=theta-step;
        }
        else if(angle==2){
        phi=phi-step;
        }
        calib_internal_pointer->rotate_calib_matrix(theta,phi);
        untitled2::updatestokes(out);
        backward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );
            if(backward_difference<= initial_difference){

            temp_difference=initial_difference;

            while(backward_difference<=temp_difference){

                temp_difference=backward_difference;
                if(angle==1) {
                theta=theta-step;
                }
                else if(angle==2){
                phi=phi-step;
                }
                calib_internal_pointer->rotate_calib_matrix(theta,phi);
                untitled2::updatestokes(out);
                backward_difference=(  (reference[0]-calib_internal_pointer->stokes_dat[1])*(reference[0]-calib_internal_pointer->stokes_dat[1])+(reference[1]-calib_internal_pointer->stokes_dat[2])*(reference[1]-calib_internal_pointer->stokes_dat[2])+(reference[2]-calib_internal_pointer->stokes_dat[3])*(reference[2]-calib_internal_pointer->stokes_dat[3]) );


            }

            if(angle==1) {
            theta=theta+step;
            }
            if(angle==2){
            phi=phi+step;
            }
            calib_internal_pointer->rotate_calib_matrix(theta,phi);
            untitled2::updatestokes(out);
            }


    }


    return temp_difference;


}
*/
void untitled2::updatestokes(bool out)
{
    if(calib_internal_pointer!=0 && daq_internal_pointer!=0 ){



      double itot=daq_internal_pointer->mean(7);

      itot=1;
      double i1=(daq_internal_pointer->mean(1))/itot;
      double i2=(daq_internal_pointer->mean(2))/itot;
      double i3=(daq_internal_pointer->mean(3))/itot;
      double i4=(daq_internal_pointer->mean(4))/itot;
      double i5=(daq_internal_pointer->mean(5))/itot;
      double i6=(daq_internal_pointer->mean(6))/itot;



      calib_internal_pointer->stokes_dat[0]=i1*calib_internal_pointer->matrix[0][0] + i2*calib_internal_pointer->matrix[0][1] + i3*calib_internal_pointer->matrix[0][2] + i4*calib_internal_pointer->matrix[0][3] + i5*calib_internal_pointer->matrix[0][4] + i6*calib_internal_pointer->matrix[0][5];
      calib_internal_pointer->stokes_dat[1]=i1*calib_internal_pointer->matrix[1][0] + i2*calib_internal_pointer->matrix[1][1] + i3*calib_internal_pointer->matrix[1][2] + i4*calib_internal_pointer->matrix[1][3] + i5*calib_internal_pointer->matrix[1][4] + i6*calib_internal_pointer->matrix[1][5];
      calib_internal_pointer->stokes_dat[2]=i1*calib_internal_pointer->matrix[2][0] + i2*calib_internal_pointer->matrix[2][1] + i3*calib_internal_pointer->matrix[2][2] + i4*calib_internal_pointer->matrix[2][3] + i5*calib_internal_pointer->matrix[2][4] + i6*calib_internal_pointer->matrix[2][5];
      calib_internal_pointer->stokes_dat[3]=i1*calib_internal_pointer->matrix[3][0] + i2*calib_internal_pointer->matrix[3][1] + i3*calib_internal_pointer->matrix[3][2] + i4*calib_internal_pointer->matrix[3][3] + i5*calib_internal_pointer->matrix[3][4] + i6*calib_internal_pointer->matrix[3][5];

      double s0,s1,s2,s3=0.0;
      s0=calib_internal_pointer->stokes_dat[0];
      s1=calib_internal_pointer->stokes_dat[1]/s0;
      s2=calib_internal_pointer->stokes_dat[2]/s0;
      s3=calib_internal_pointer->stokes_dat[3]/s0;
        if(out){
      cout<<s1<<s2<<s3<<endl;
        }
      calib_internal_pointer->stokes_dat[1]=s1;
      calib_internal_pointer->stokes_dat[2]=s2;
      calib_internal_pointer->stokes_dat[3]=s3;


      if(out){
      for(int i=0;i<4;i++){
             if(  stokesvect_qs[i]!=0){
                 delete stokesvect_qs[i];
                 stokesvect_qs[i]=0;
             }
      }

      for(int i=0;i<4;i++){
              stokesvect_qs[i]=new QStandardItem (QString::number(calib_internal_pointer->stokes_dat[i]));
              model_stokes->setItem(i,0,stokesvect_qs[i]);

      }

      ui.tableView_3->update();
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Error: No reference to daq istance");
        msgBox.exec();
    }
}

void untitled2::on_testButton_clicked()
{
   // calib_internal_pointer->rotate_calib_matrix(1.5,1.5);
    ofstream fileout("polarimeter_perform.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    on_stokesButton_clicked();
   angle_pol_test=angle_pol_test+2;
   fileout<<angle_pol_test<<"\t"<<calib_internal_pointer->stokes_dat[0]<<"\t"<<calib_internal_pointer->stokes_dat[1]<<"\t"<<calib_internal_pointer->stokes_dat[2]<<"\t"<<calib_internal_pointer->stokes_dat[3]<<endl;


}

void untitled2::on_rotateButton_clicked()
{
    angle_pol_test=0;
    bool ok;
       double theta = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                          tr("Theta:"), 0.00, -7.00, 7.22, 5, &ok);
       double phi = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                          tr("phi:"), 0.00,-7.00, 7.22, 5, &ok);

       calib_internal_pointer->rotate_calib_matrix(theta,phi);

}
