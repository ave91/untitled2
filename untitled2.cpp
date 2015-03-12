#include "untitled2.h"
#include "NIDAQmx.h"
#include "qmessagebox.h"
#include <fstream>
#include "QStandardItemModel"
#include <memory>

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else



untitled2::untitled2(QWidget *parent)
	: QMainWindow(parent)
{	
    //Configure pointers reference not initialized yet
    daq_internal_pointer=0;
    calib_internal_pointer=0;
    ui.setupUi(this);

    //Reserve memory for C-like use of vectors
    H_vector.reserve(7);
    H_vector.resize(7);
    V_vector.reserve(7);
    V_vector.resize(7);
    L_vector.reserve(7);
    L_vector.resize(7);
    P_vector.reserve(7);
    P_vector.resize(7);
    M_vector.reserve(7);
    M_vector.resize(7);
    L_vector.reserve(7);
    L_vector.resize(7);
    R_vector.reserve(7);
    R_vector.resize(7);

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


    //Initializiation of data pointers to null, needed for memory managment
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

    ui.label_cvalue_1->setText(QString::number(daq_internal_pointer->data[1]));
    ui.label_cvalue_2->setText(QString::number(daq_internal_pointer->data[2]));
    ui.label_cvalue_3->setText(QString::number(daq_internal_pointer->data[3]));
    ui.label_cvalue_4->setText(QString::number(daq_internal_pointer->data[4]));
    ui.label_cvalue_5->setText(QString::number(daq_internal_pointer->data[5]));
    ui.label_cvalue_6->setText(QString::number(daq_internal_pointer->data[6]));
    ui.label_cvalue_7->setText(QString::number(daq_internal_pointer->data[7]));
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
    if(daq_internal_pointer!=0){

    daq_internal_pointer->read_daq();

    H_vector[0]=(daq_internal_pointer->mean(1));
    H_vector[1]=(daq_internal_pointer->mean(2));
    H_vector[2]=(daq_internal_pointer->mean(3));
    H_vector[3]=(daq_internal_pointer->mean(4));
    H_vector[4]=(daq_internal_pointer->mean(5));
    H_vector[5]=(daq_internal_pointer->mean(6));
    H_vector[6]=(daq_internal_pointer->mean(7));


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

     T_H1= new QStandardItem (QString::number(H_vector[0]));
     T_H2= new QStandardItem (QString::number(H_vector[1]));
     T_H3= new QStandardItem (QString::number(H_vector[2]));
     T_H4= new QStandardItem (QString::number(H_vector[3]));
     T_H5= new QStandardItem (QString::number(H_vector[4]));
     T_H6= new QStandardItem (QString::number(H_vector[5]));
     T_H7= new QStandardItem (QString::number(H_vector[6]));

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

    V_vector[0]=(daq_internal_pointer->mean(1));
    V_vector[1]=(daq_internal_pointer->mean(2));
    V_vector[2]=(daq_internal_pointer->mean(3));
    V_vector[3]=(daq_internal_pointer->mean(4));
    V_vector[4]=(daq_internal_pointer->mean(5));
    V_vector[5]=(daq_internal_pointer->mean(6));
    V_vector[6]=(daq_internal_pointer->mean(7));


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

     T_V1= new QStandardItem (QString::number(V_vector[0]));
     T_V2= new QStandardItem (QString::number(V_vector[1]));
     T_V3= new QStandardItem (QString::number(V_vector[2]));
     T_V4= new QStandardItem (QString::number(V_vector[3]));
     T_V5= new QStandardItem (QString::number(V_vector[4]));
     T_V6= new QStandardItem (QString::number(V_vector[5]));
     T_V7= new QStandardItem (QString::number(V_vector[6]));

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

    P_vector[0]=(daq_internal_pointer->mean(1));
    P_vector[1]=(daq_internal_pointer->mean(2));
    P_vector[2]=(daq_internal_pointer->mean(3));
    P_vector[3]=(daq_internal_pointer->mean(4));
    P_vector[4]=(daq_internal_pointer->mean(5));
    P_vector[5]=(daq_internal_pointer->mean(6));
    P_vector[6]=(daq_internal_pointer->mean(7));


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

     T_P1= new QStandardItem (QString::number(P_vector[0]));
     T_P2= new QStandardItem (QString::number(P_vector[1]));
     T_P3= new QStandardItem (QString::number(P_vector[2]));
     T_P4= new QStandardItem (QString::number(P_vector[3]));
     T_P5= new QStandardItem (QString::number(P_vector[4]));
     T_P6= new QStandardItem (QString::number(P_vector[5]));
     T_P7= new QStandardItem (QString::number(P_vector[6]));

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

    M_vector[0]=(daq_internal_pointer->mean(1));
    M_vector[1]=(daq_internal_pointer->mean(2));
    M_vector[2]=(daq_internal_pointer->mean(3));
    M_vector[3]=(daq_internal_pointer->mean(4));
    M_vector[4]=(daq_internal_pointer->mean(5));
    M_vector[5]=(daq_internal_pointer->mean(6));
    M_vector[6]=(daq_internal_pointer->mean(7));


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

     T_M1= new QStandardItem (QString::number(M_vector[0]));
     T_M2= new QStandardItem (QString::number(M_vector[1]));
     T_M3= new QStandardItem (QString::number(M_vector[2]));
     T_M4= new QStandardItem (QString::number(M_vector[3]));
     T_M5= new QStandardItem (QString::number(M_vector[4]));
     T_M6= new QStandardItem (QString::number(M_vector[5]));
     T_M7= new QStandardItem (QString::number(M_vector[6]));

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

    L_vector[0]=(daq_internal_pointer->mean(1));
    L_vector[1]=(daq_internal_pointer->mean(2));
    L_vector[2]=(daq_internal_pointer->mean(3));
    L_vector[3]=(daq_internal_pointer->mean(4));
    L_vector[4]=(daq_internal_pointer->mean(5));
    L_vector[5]=(daq_internal_pointer->mean(6));
    L_vector[6]=(daq_internal_pointer->mean(7));


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

     T_L1= new QStandardItem (QString::number(L_vector[0]));
     T_L2= new QStandardItem (QString::number(L_vector[1]));
     T_L3= new QStandardItem (QString::number(L_vector[2]));
     T_L4= new QStandardItem (QString::number(L_vector[3]));
     T_L5= new QStandardItem (QString::number(L_vector[4]));
     T_L6= new QStandardItem (QString::number(L_vector[5]));
     T_L7= new QStandardItem (QString::number(L_vector[6]));

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

    R_vector[0]=(daq_internal_pointer->mean(1));
    R_vector[1]=(daq_internal_pointer->mean(2));
    R_vector[2]=(daq_internal_pointer->mean(3));
    R_vector[3]=(daq_internal_pointer->mean(4));
    R_vector[4]=(daq_internal_pointer->mean(5));
    R_vector[5]=(daq_internal_pointer->mean(6));
    R_vector[6]=(daq_internal_pointer->mean(7));


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

     T_R1= new QStandardItem (QString::number(R_vector[0]));
     T_R2= new QStandardItem (QString::number(R_vector[1]));
     T_R3= new QStandardItem (QString::number(R_vector[2]));
     T_R4= new QStandardItem (QString::number(R_vector[3]));
     T_R5= new QStandardItem (QString::number(R_vector[4]));
     T_R6= new QStandardItem (QString::number(R_vector[5]));
     T_R7= new QStandardItem (QString::number(R_vector[6]));

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
        calib_internal_pointer->compute_calibration(&H_vector,&V_vector,&P_vector,&M_vector,&L_vector,&R_vector);
        QMessageBox ms;
        ms.setText(QString::number(calib_internal_pointer->matrix[0][0]));
        ms.exec();

    }
}
