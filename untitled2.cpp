#include "untitled2.h"
#include "NIDAQmx.h"
#include "qmessagebox.h"
#include <fstream>
#include "QStandardItemModel"
#include <memory>
#include "QFileDialog"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else



untitled2::untitled2(QWidget *parent)
	: QMainWindow(parent)
{	
    //Configure pointers reference not initialized yet
    daq_internal_pointer=0;
    calib_internal_pointer=0;
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

    daq_internal_pointer->read_daq();

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

    daq_internal_pointer->read_daq();

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

    daq_internal_pointer->read_daq();

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

    daq_internal_pointer->read_daq();

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

    daq_internal_pointer->read_daq();

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

    daq_internal_pointer->read_daq();

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

    daq_internal_pointer->read_daq();

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
        calib_internal_pointer->compute_calibration();

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

      daq_internal_pointer->read_daq();

      double itot=daq_internal_pointer->mean(7);
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
