#include "iostream"
#include "acquisition.h"
#include "NIDAQmx.h"
#include "string"
#include <vector>
#include "qmessagebox.h"

using namespace std;

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else



 vector <float64> acquisition::data;
 long acquisition::datasize;
 string acquisition::devices="Dev1/ai0:6";
 double acquisition:: maxVolt=10.;
 double acquisition::minVolt=-10.;
 long acquisition::rate=2800;
 long acquisition::samp_per_chan=1000;
 bool acquisition::stop=true;

  int acquisition::BoardNum=0;
  int acquisition::ULStat=0;
  int acquisition::LowChan=0;
  int acquisition::HighChan=3;
  int acquisition::Gain=BIP10VOLTS;
  long acquisition::Count = 32736;
  long acquisition::Rate = 50000;
  vector <WORD> acquisition::ADData;
  HANDLE acquisition::MemHandle = 0;
 unsigned acquisition::Options=CONVERTDATA+BURSTIO;
 int acquisition::total_num_chan;
 bool acquisition::NI;

acquisition::acquisition( QObject *parent) : QObject(parent)
{
     NI=true;
    //Variable init
    if(NI==true){
    datasize=7*samp_per_chan;
    total_num_chan=7;
    }
    else{
     datasize=Count;
     total_num_chan=4;
    }

    for(int i=0;i<7;++i){
        offset_volt_NI[i]=0.;
        offset_volt_MC[i]=0.;
    }

    setOffsetVoltage();
    skip=50;
    error=0;
    taskHandle=0;
    errBuff=new char[2048]();

    file_err.open("C:\\Users\\Ave\\Desktop\\daq_filerr.txt");
    data.resize(datasize+1);
    ADData.resize(datasize+1);
    //Daq init
    cbErrHandling (PRINTALL, DONTSTOP);


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

void acquisition::read_daq_MC(){
     cbErrHandling (PRINTALL, DONTSTOP);

     Options=CONVERTDATA+BURSTIO;
     Rate=50000;
     //MemHandle = cbWinBufAlloc(Count);
    //ADData = (WORD*) MemHandle;
    float EngUnits;
    ULStat = cbAInScan (BoardNum, LowChan, HighChan, Count, &Rate,Gain, &ADData[0], Options);
    int temp=0;
    for (int J = 0; J < 4 && !ULStat; J++)       /* loop through the channels */
        {
        for (int I = 0; I <= ((Count/4)-4); I++)   /* loop through the values & print */
        {
               {
                ULStat = cbToEngUnits (BoardNum, Gain, ADData[I*4+J], &EngUnits);
                data[temp]=EngUnits;
                temp++;
                }
            }

        }



}


double acquisition::mean( int channel){
    double mean_temp=0.;
    double temp_return=0.;
    int n=channel-1;
    int size_chan=(data.size())/total_num_chan;
    if(channel<=total_num_chan && channel>0){
        for(int i=skip+n*size_chan;i<=(size_chan+n*size_chan-skip);++i){
        mean_temp+=data[i];
        }
    }
    else{
        std::cout<<"ERROR: channel out of range"<<std::endl;
        return 0;
    }
    if(acquisition::NI==true){
    temp_return=( ((mean_temp)/double(size_chan-2*skip))-offset_volt_NI[n]);
    }
    else{
    temp_return=( ((mean_temp)/double(size_chan-2*skip))-offset_volt_MC[n]);
    }


                  return temp_return;

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

void acquisition::cont_acq_MC(){
    Options=CONVERTDATA + BACKGROUND + CONTINUOUS + BLOCKIO;
    Rate=25000;
    ULStat = cbAInScan (BoardNum, LowChan, HighChan, Count, &Rate, Gain,
                        &(ADData[0]), Options);
    Q_FOREVER{

        if(stop==true){
          ULStat = cbStopBackground (BoardNum,AIFUNCTION);
          return;
        }
        else{

            int temp=0;
            float EngUnits;
            for (int J = 0; J < 4 && !ULStat; J++)       /* loop through the channels */
                {
                for (int I = 0; I <= ((Count/4)-4); I++)   /* loop through the values & print */
                {
                       {
                        ULStat = cbToEngUnits (BoardNum, Gain, ADData[I*4+J], &EngUnits);
                        data[temp]=EngUnits;
                        temp++;
                        }
                    }

                }

        }

    }
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

void acquisition::thread_cont_acq_MC(){
    stop=false;
    newfuture = QtConcurrent::run(this,&acquisition::cont_acq_MC);
}


void acquisition::thread_cont_acq_stop(){
    stop=true;


}

void acquisition::setOffsetVoltage(){

        offset_volt_NI[0]=0.00814998;
        offset_volt_NI[1]=0.0117947;
        offset_volt_NI[2]=0.00263705;
        offset_volt_NI[3]=0.0056605;
        offset_volt_NI[4]=0.08825019;
        offset_volt_NI[5]=0.00765609;
        offset_volt_NI[6]=0.00923653;



        offset_volt_MC[0]=0.;
        offset_volt_MC[1]=0.;
        offset_volt_MC[2]=0.;
        offset_volt_MC[3]=0.;



}
void acquisition::setsize(int size,int skipp=10){

    skip=skipp;
    if(NI==true){
    acquisition::samp_per_chan=size;
    datasize=7*samp_per_chan;
    total_num_chan=7;
    }
    else{
     acquisition::Count=size;
     datasize=Count;
     total_num_chan=4;
    }
    data.resize(datasize+1);
    ADData.resize(datasize+1);
}
