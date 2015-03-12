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

using namespace std;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    untitled2 w;
	w.show();
	
    acquisition daq(7000,"Dev1/ai0:6",10.0,-10.0,2000,1000);
    w.daq_internal_pointer=&daq;

    daq.read_daq();

    calibration calib;
    w.calib_internal_pointer=&calib;

    return a.exec();
}

