#include "untitled2.h"
#include "acquisition.h"
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <qlabel.h>
#include <stdio.h>
#include "calibration.h"
#include "qstring.h"
#include <iostream>
#include <fstream>


// "Andarci vicino conta solo a bocce" cit Carlo

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    untitled2 w;

	
    acquisition * daq=new acquisition();
    w.daq_internal_pointer=(daq);
    calibration * calib=new calibration();
    w.calib_internal_pointer=calib;
    gpib * communication=new gpib();
    w.gpib_int_pointer=communication;

    w.show();





    return a.exec();
}

