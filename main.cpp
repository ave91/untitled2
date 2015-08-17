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


#define DEBUG

#ifdef DEBUG
    #include <windows.h>
    #include <stdio.h>
#endif



// "Andarci vicino conta solo a bocce" cit Carlo

using namespace std;

int main(int argc, char *argv[])
{

#ifdef DEBUG
    // detach from the current console window
    // if launched from a console window, that will still run waiting for the new console (below) to close
    // it is useful to detach from Qt Creator's <Application output> panel
    FreeConsole();

    // create a separate new console window
    AllocConsole();

    // attach the new console to this application's process
    AttachConsole(GetCurrentProcessId());

    // reopen the std I/O streams to redirect I/O to the new console
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    freopen("CON", "r", stdin);
#endif




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

