#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <QObject>
#include "NIDAQmx.h"
#include "vector"
#include "fstream"

using namespace std;


class acquisition : public QObject
{
    Q_OBJECT
public:
    explicit acquisition(int datasize, std::string devices, double maxVolt, double minVolt, double rate, double samp_per_chan,QObject *parent = 0);
    ~acquisition();
    double mean(int channel);
    void read_daq();
    vector <float64> data;

private:
    int32       error;
    TaskHandle  taskHandle;
    int32       read;
    char    *    errBuff;
    ofstream file_err;
    int32 sample_chan;
    int32 total_sample;
    int skip;

signals:

public slots:
};

#endif // ACQUISITION_H
