#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <QObject>
#include "NIDAQmx.h"
#include "vector"
#include "fstream"
#include <QtConcurrent/QtConcurrent>
#include "cbw.h"

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
    void read_daq_MC();
    void cont_acq_MC();
    void thread_cont_acq_MC();
    void thread_cont_acq_stop_MC();

    static int32 CVICALLBACK EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
    static int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData);
    static vector <float64> data;



   static long datasize;
   static string devices;
   static double maxVolt;
   static double minVolt;
   static long rate;
   static long samp_per_chan;
   static bool stop;

   static int BoardNum;
   static int ULStat;
   static int LowChan;
   static int HighChan;
   static int Gain;
   static vector <WORD> ADData;
   static unsigned Options;
   static long Count;
   static long Rate;
   static HANDLE MemHandle;
   static int total_num_chan;
   static bool acquisition::NI;

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
