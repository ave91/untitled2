#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <QObject>
#include "NIDAQmx.h"
#include "vector"
#include "fstream"
#include <QtConcurrent/QtConcurrent>

using namespace std;


class acquisition : public QObject
{
    Q_OBJECT
public:
    explicit acquisition(QObject *parent = 0);
    ~acquisition();
    double mean(int channel);
    void cont_acq();
    void thread_cont_acq();
    void thread_cont_acq_stop();
    void read_daq();
    static int32 CVICALLBACK EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
    static int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData);
    static vector <float64> data;



   static int datasize;
   static string devices;
   static double maxVolt;
   static double minVolt;
   static double rate;
   static double samp_per_chan;
   static bool stop;


   ofstream file_err;

private:
    int32       error;
    TaskHandle  taskHandle;
    int32       read;
    char    *    errBuff;
    QFuture <void> newfuture;

    int skip;

signals:

public slots:
};




#endif // ACQUISITION_H
