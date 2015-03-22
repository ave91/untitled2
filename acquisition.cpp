#include "acquisition.h"
#include "NIDAQmx.h"
#include "string"
#include <vector>
#include "qmessagebox.h"
using namespace std;

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

 vector <float64> acquisition::data;
 int acquisition::datasize=7000;
 string acquisition::devices="Dev1/ai0:6";
 double acquisition:: maxVolt=10.;
 double acquisition::minVolt=-10.;
 double acquisition::rate=2000;
 double acquisition::samp_per_chan=1000;
 bool acquisition::stop=true;



acquisition::acquisition( QObject *parent) : QObject(parent)
{
    //Variable init
    skip=50;
    error=0;
    taskHandle=0;
    errBuff=new char[2048]();

    file_err.open("C:\\Users\\Ave\\Desktop\\daq_filerr.txt");
    data.reserve(datasize+1);
    data.resize(datasize+1);

    //Daq init


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
    DAQmxErrChk(DAQmxCreateTask("taksname", &taskHandle));
    DAQmxErrChk(DAQmxCreateAIVoltageChan(taskHandle, devices.c_str(), "", DAQmx_Val_RSE, minVolt, maxVolt, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle, "", rate, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, samp_per_chan));

    DAQmxErrChk(DAQmxStartTask(taskHandle));
    DAQmxErrChk(DAQmxReadAnalogF64(taskHandle, samp_per_chan, 10.0, DAQmx_Val_GroupByChannel, &(data[0]),datasize , &read, NULL));
    DAQmxErrChk(DAQmxStopTask(taskHandle));
    DAQmxClearTask(taskHandle);
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
    for(int i=skip+n*samp_per_chan;i<=(samp_per_chan+n*samp_per_chan-skip);++i){
     mean_temp+=data[i];
    }

    return ((mean_temp)/double(samp_per_chan-2*skip));

}

void acquisition::cont_acq(){

    DAQmxErrChk(DAQmxCreateTask("taksname", &taskHandle));
    DAQmxErrChk(DAQmxCreateAIVoltageChan(taskHandle, devices.c_str(), "", DAQmx_Val_RSE, minVolt, maxVolt, DAQmx_Val_Volts, NULL));
    DAQmxErrChk (DAQmxCfgSampClkTiming(taskHandle,"",rate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,samp_per_chan));

    DAQmxErrChk (DAQmxRegisterEveryNSamplesEvent(taskHandle,DAQmx_Val_Acquired_Into_Buffer,samp_per_chan,0,EveryNCallback,NULL));
    DAQmxErrChk (DAQmxRegisterDoneEvent(taskHandle,0,DoneCallback,NULL));
    DAQmxErrChk (DAQmxStartTask(taskHandle));

    printf("Acquiring samples continuously. Press Enter to interrupt\n");
    Q_FOREVER{

        if(stop==true){
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
        return;
        }
    }

    printf("End of program, press Enter key to quit\n");

Error:
    if( DAQmxFailed(error) )
        DAQmxGetExtendedErrorInfo(errBuff,2048);
    if( taskHandle!=0 ) {
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(taskHandle);

    }
    if( DAQmxFailed(error) ){
        printf("DAQmx Error: %s\n",errBuff);
    }
    printf("End of thread\n");

    return ;



}

int32 CVICALLBACK acquisition::EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData)
{
        int32       error=0;
        char        errBuff[2048]={'\0'};
        static int  totalRead=0;
        int32       read=0;


        /*********************************************/
        // DAQmx Read Code
        /*********************************************/
        DAQmxErrChk (DAQmxReadAnalogF64(taskHandle,samp_per_chan,10.0,DAQmx_Val_GroupByChannel,&(data[0]),datasize,&read,NULL));
        if( read>0 ) {
                printf("Acquired %d samples. Total %d\r",(int)read,(int)(totalRead+=read));
                fflush(stdout);
        }

Error:
        if( DAQmxFailed(error) ) {
                DAQmxGetExtendedErrorInfo(errBuff,2048);
                /*********************************************/
                // DAQmx Stop Code
                /*********************************************/
                DAQmxStopTask(taskHandle);

                printf("DAQmx Error: %s\n",errBuff);
        }


        return 0;
}

int32 CVICALLBACK acquisition::DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData)
{
        int32   error=0;
        char    errBuff[2048]={'\0'};

        // Check to see if an error stopped the task.
        DAQmxErrChk (status);

Error:
        if( DAQmxFailed(error) ) {
                DAQmxGetExtendedErrorInfo(errBuff,2048);

                printf("DAQmx Error: %s\n",errBuff);
        }

        return 0;
}

void acquisition::thread_cont_acq(){
    stop=false;
    newfuture = QtConcurrent::run(this,&acquisition::cont_acq);
}


void acquisition::thread_cont_acq_stop(){
    stop=true;


}

