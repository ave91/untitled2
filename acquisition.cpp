#include "acquisition.h"
#include "NIDAQmx.h"
#include "string"
#include <vector>
#include "qmessagebox.h"
using namespace std;

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

acquisition::acquisition( int datasize,string devices,double maxVolt,double minVolt, double rate,double samp_per_chan,QObject *parent) : QObject(parent)
{
    //Variable init
    skip=50;
    error=0;
    taskHandle=0;
    errBuff=new char[2048]();
    sample_chan=samp_per_chan;
    file_err.open("C:\\Users\\Ave\\Desktop\\daq_filerr.txt");
    data.reserve(datasize+1);
    data.resize(datasize+1);
    total_sample=datasize;
    //Daq init
    DAQmxErrChk(DAQmxCreateTask("taksname", &taskHandle));
    DAQmxErrChk(DAQmxCreateAIVoltageChan(taskHandle, devices.c_str(), "", DAQmx_Val_RSE, minVolt, maxVolt, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle, "", rate, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, samp_per_chan));

Error:
    if (DAQmxFailed(error))
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
    if (DAQmxFailed(error))
        file_err << "DAQmx Error: " << errBuff << endl;



}
//Destructor
acquisition::~acquisition()
{
    file_err.close();
    if (taskHandle != 0)  {
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }

}
//Reading Method
void acquisition::read_daq(){
   // QMessageBox msgBox;
    DAQmxErrChk(DAQmxStartTask(taskHandle));
    DAQmxErrChk(DAQmxReadAnalogF64(taskHandle, sample_chan, 10.0, DAQmx_Val_GroupByChannel, &(data[0]),total_sample , &read, NULL));
    DAQmxErrChk(DAQmxStopTask(taskHandle));
    //msgBox.setText(QString::number(data[1]));
    //msgBox.exec();

Error:
    if (DAQmxFailed(error))
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
    if (DAQmxFailed(error))
        file_err << "DAQmx Error: " << errBuff << endl;


}

double acquisition::mean( int channel){
    double mean_temp=0.;
    int n=channel-1;
    for(int i=skip+n*sample_chan;i<=(sample_chan+n*sample_chan-skip);++i){
     mean_temp+=data[i];
    }

    return ((mean_temp)/double(sample_chan-2*skip));

}

