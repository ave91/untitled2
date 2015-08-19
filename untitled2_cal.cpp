#include <Windows4Root.h>
#include "untitled2.h"
#include "NIDAQmx.h"
#include "qmessagebox.h"
#include <fstream>
#include "QStandardItemModel"
#include <memory>
#include "QFileDialog"
#include <iomanip>      // std::setw
#include "sstream"
#include <cstdlib>
#include <random>
#include "TH1F.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "Math/Minimizer.h"
#include "TMinuitMinimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom2.h"
#include "TError.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "Eigen/Core"
#include "Eigen/LU"
#include "Math/GSLSimAnMinimizer.h"

using namespace Eigen;

void untitled2::on_referenceButton_clicked()
{
    angle_pol_test=0;
    //Set up a source of pseudorandom number generator for taking the measurments
    //I like mt so I'll use that
    std::random_device rd;
       std::mt19937 gen(rd());
       std::uniform_real_distribution<> dis(-99, 99); // Range of the generation= range of PC (I know here range=[-99,99) but i don't care so much Unlikely {-99,-99,-99} will be an eigenstate so...
    int total_data=100;

    if(calib_internal_pointer!=0 && daq_internal_pointer!=0 ){

        if(acquisition::NI==true){

        gpib_int_pointer->init();
        Sleep(60);
        vector <double> temp;
        temp.resize(7);
        string temp_command;
        ofstream fillee("referenceout.txt");
        for(int i=0;i<total_data;++i){
            temp_command=create_command(1,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(60);
            temp_command=create_command(2,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(60);
            temp_command=create_command(3,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(200);

            daq_internal_pointer->read_daq();


            temp[6]=daq_internal_pointer->mean(7);

             temp[0]=daq_internal_pointer->mean(1);
             temp[1]=daq_internal_pointer->mean(2);
             temp[2]=daq_internal_pointer->mean(3);
             temp[3]=daq_internal_pointer->mean(4);
             temp[4]=daq_internal_pointer->mean(5);
             temp[5]=daq_internal_pointer->mean(6);


/*
       for(int j=0;j<6;j++){
            if(i%6==j){
            temp[j]=1;
           }
            else{
                temp[j]=0;
            }
       cout<<temp[j]<<" ";

       }
       cout<<endl;
       temp[6]=1;
*/


             for(int j=0;j<7;j++){

             fillee<<temp[j]<<"\t";

             }
             fillee<<endl;






            temp_data.push_back(temp);
//cout<<"lolo"<<endl;

        }
        fillee.close();
        //Generate First row of calibration
     MatrixXd z(6,6);
     z= MatrixXd::Zero(6,6);
      MatrixXd z1(6,6);
      z1= MatrixXd::Zero(6,6);
     VectorXd c(6);
     VectorXd x(6);
    c=VectorXd::Zero(6);
    x= VectorXd::Zero(6);

    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            for(int k=0;k<total_data;k++){

                z(i,j)=z(i,j)+(temp_data[k][i]*temp_data[k][j]);

            }
          }
         }

    for(int j=0;j<6;j++){
        for(int k=0;k<total_data;k++){

            x(j)=x(j)+(temp_data[k][j]*temp_data[k][6]);

        }
      }

   cout<<z<<endl<<x<<endl;

    z1=z.inverse();
  cout<<z1<<endl;
  c=z1*x;
  // c.settoproduct(z,x);
    bool success=false;
    S0fit.resize(6);
    for(int i=0;i<6;i++){

    S0fit[i]=c(i);
    calib_internal_pointer->matrix[0][i]=c(i);
    //cout<<S0fit[i]<<endl;
    }
    //cout<<"lolo2"<<endl;
    NumericalMinimization(temp_data[0][6],18,"Minuit2","Migrad");
    bool is_ok=false;
    while(!is_ok){
    QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "Test", "Is the minimization OK?",
                                   QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
       qDebug() << "Yes was clicked";
       is_ok=true;
       return;
     } else {
       NumericalMinimization(temp_data[0][6],18,"Minuit2","Migrad",std::rand());
         qDebug() << "Yes was *not* clicked";
     }

    }
    return;

    //Ok so now c is a row vector and goes from 0 to 5 with each entry is the top entry of every column in the calibration matrix
    //Now start the funny part... Need to build the functional to be minimized (20 dim!!!!! hope for it)




}
    }


}

/*
void untitled2::on_referenceButton_clicked()
{
    angle_pol_test=0;
    //Set up a source of pseudorandom number generator for taking the measurments
    //I like mt so I'll use that
    std::random_device rd;
       std::mt19937 gen(rd());
       std::uniform_real_distribution<> dis(-99, 99); // Range of the generation= range of PC (I know here range=[-99,99) but i don't care so much Unlikely {-99,-99,-99} will be an eigenstate so...
    int total_data=80;

    if(calib_internal_pointer!=0 && daq_internal_pointer!=0 ){

        if(acquisition::NI==false){

        gpib_int_pointer->init();
        Sleep(60);
        vector <double> temp;
        temp.resize(4);
        string temp_command;
        ofstream fillee("referenceout.txt");
        for(int i=0;i<total_data;++i){
            temp_command=create_command(1,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(60);
            temp_command=create_command(2,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(60);
            temp_command=create_command(3,dis(gen));
            gpib_int_pointer->GPIBWrite(&(temp_command[0]));
            Sleep(200);

            daq_internal_pointer->read_daq();




             temp[0]=daq_internal_pointer->mean(1);
             temp[1]=daq_internal_pointer->mean(2);
             temp[2]=daq_internal_pointer->mean(3);
             temp[3]=daq_internal_pointer->mean(4);


/*
       for(int j=0;j<6;j++){
            if(i%6==j){
            temp[j]=1;
           }
            else{
                temp[j]=0;
            }
       cout<<temp[j]<<" ";

       }
       cout<<endl;
       temp[6]=1;






            temp_data.push_back(temp);
//cout<<"lolo"<<endl;

        }
        fillee.close();
        //Generate First row of calibration
     MatrixXd z(6,6);
     z= MatrixXd::Zero(6,6);
      MatrixXd z1(6,6);
      z1= MatrixXd::Zero(6,6);
     VectorXd c(6);
     VectorXd x(6);
    c=VectorXd::Zero(6);
    x= VectorXd::Zero(6);

    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            for(int k=0;k<total_data;k++){

                z(i,j)=z(i,j)+(temp_data[k][i]*temp_data[k][j]);

            }
          }
         }

    for(int j=0;j<6;j++){
        for(int k=0;k<total_data;k++){

            x(j)=x(j)+(temp_data[k][j]*temp_data[k][6]);

        }
      }

   cout<<z<<endl<<x<<endl;

    z1=z.inverse();
  cout<<z1<<endl;
  c=z1*x;
  // c.settoproduct(z,x);
    bool success=false;
    S0fit.resize(6);
    for(int i=0;i<6;i++){

    S0fit[i]=c(i);
    calib_internal_pointer->matrix[0][i]=c(i);
    //cout<<S0fit[i]<<endl;
    }
    //cout<<"lolo2"<<endl;
    NumericalMinimization(temp_data[0][6],18,"Minuit2","Migrad");


    //Ok so now c is a row vector and goes from 0 to 5 with each entry is the top entry of every column in the calibration matrix
    //Now start the funny part... Need to build the functional to be minimized (20 dim!!!!! hope for it)




}
    }


}


*/









int untitled2::NumericalMinimization(double avg,int nparam,const char * minName, const char *algoName ,
                                     int randomSeed){
  // create minimizer giving a name and a name (optionally) for the specific
  // algorithm
  // possible choices are:
  //     minName                  algoName
  // Minuit /Minuit2             Migrad, Simplex,Combined,Scan  (default is Migrad)
  //  Minuit2                     Fumili2
  //  Fumili
  //  GSLMultiMin                ConjugateFR, ConjugatePR, BFGS,
  //                              BFGS2, SteepestDescent
  //  GSLMultiFit
  //   GSLSimAn
  //   Genetic
    minName="Minuit";
    algoName="Combined";
   // gDebug=1;
    //ROOT::Math::Minimizer* min =ROOT::Math::Factory::CreateMinimizer(minName, algoName);
   ROOT::Minuit2::Minuit2Minimizer* min=new ROOT::Minuit2::Minuit2Minimizer(ROOT::Minuit2::kCombined);
   //ROOT::Math::GSLSimAnMinimizer * min=new ROOT::Math::GSLSimAnMinimizer();
   cout<<min<<endl;
    // set tolerance , etc...



min->SetMaxFunctionCalls(100000000); // for Minuit/Minuit2
       min->SetMaxIterations(10000000);  // for GSL
       min->SetTolerance(0.0000001);
       min->SetPrintLevel(1);

  // create funciton wrapper for minmizer
  // a IMultiGenFunction type

  ROOT::Math::Functor f(&(untitled2::Q_comb),18);

  double stepp=0.000000000001;
  //double stepp=0.0000001;
  double step[18] = {stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp};

  // starting point

  //double variable[18] = {+avg,-avg,0,0,0,0,0,0,avg,-avg,0,0,0,0,0,0,-avg,+avg};
  double mean=0.3;
  //double variable[18]={0.0324577*avg,-0.784184*avg,1.33234*avg,0.70708*avg,-1.33917*avg,-0.784177*avg,0.695335*avg,0.472558*avg,-0.437909*avg,-0.356402*avg,-0.0378962*avg,-0.291313*avg,1.17834*avg,1.61196*avg,-0.488954*avg,-0.048198*avg,-1.55931*avg,-0.91889*avg};
  //double variable[18]={-0.315504018364667,-0.186892227511484,-0.521670627740295,-0.522430703277551,-0.201104949373917,-0.114301207639755,0.00128560378836436,0.380444053158126,-0.272932986603822,-0.245115501182876,1.07162874852352,0.898012052717405,-0.496399130911951,-1.11558977981970,0.0998692053377596,0.108637780836426,-0.545835823855231,-0.495068663821190};
  //double variable[18]={0.30656305479907614,0.03101093492471959,0.6187775551277827,0.5838922287765484,0.19701203673713807,0.15521977861516048,-0.020131089013634015,-0.26595079920106096,0.3172255644450963,0.27852225509126805,-0.05655530787730796,-0.10000209372190863,-0.41952143055767227,-0.6394615506870377,-0.06515818686266675,-0.10069399899431783,-0.38115743371378935,-0.4038838855771517};
  //double variable[18]={-0.613,-0.183,-1.492,2.683,-2.563,1.951,1.288,0.219,-1.129,-0.176,0.610,-0.772,0.209,-2.345,0.022,-1.112,2.055};
  double variable[18]={-0.61616,	0.248457,	-3.40898,	0.818792,	-0.805741,	4.76776,0.409278,	-1.46225,	-0.0866583,	0.942473,	0.569543,	-0.752036,1.77814,	-0.156264,	0.00538577,	-1.15195,	-0.658304,	-0.00931175};
  if (randomSeed >= 0) {
     TRandom2 r(randomSeed);
     variable[0] = r.Uniform(-20,20);
     variable[1] = r.Uniform(-20,20);
     variable[2] = r.Uniform(-20,20);
     variable[3] = r.Uniform(-20,20);
     variable[4] = r.Uniform(-20,20);
     variable[5] = r.Uniform(-20,20);
     variable[6] = r.Uniform(-20,20);
     variable[7] = r.Uniform(-20,20);
     variable[8] = r.Uniform(-20,20);
     variable[9] = r.Uniform(-20,20);
     variable[10] = r.Uniform(-20,20);
     variable[11] = r.Uniform(-20,20);
     variable[12] = r.Uniform(-20,20);
     variable[13] = r.Uniform(-20,20);
     variable[14] = r.Uniform(-20,20);
     variable[15] = r.Uniform(-20,20);
     variable[16] = r.Uniform(-20,20);
     variable[17] = r.Uniform(-20,20);

  }


  min->SetFunction(f);
    cout<<"lolo4"<<endl;
  // Set the free variables to be minimized!

  min->SetVariable(0,"t",variable[0], step[0]);

  min->SetVariable(1,"y",variable[1], step[1]);
  min->SetVariable(2,"z",variable[2], step[2]);
  min->SetVariable(3,"a",variable[3], step[3]);
  min->SetVariable(4,"b",variable[4], step[4]);
  min->SetVariable(5,"c",variable[5], step[5]);
  min->SetVariable(6,"d",variable[6], step[6]);
  min->SetVariable(7,"e",variable[7], step[7]);
  min->SetVariable(8,"f",variable[8], step[8]);
  min->SetVariable(9,"g",variable[9], step[9]);

  min->SetVariable(10,"h",variable[10], step[10]);
  min->SetVariable(11,"j",variable[11], step[11]);
  min->SetVariable(12,"l",variable[12], step[12]);
  min->SetVariable(13,"m",variable[13], step[13]);
  min->SetVariable(14,"n",variable[14], step[14]);
  min->SetVariable(15,"o",variable[15], step[15]);
  min->SetVariable(16,"p",variable[16], step[16]);
  min->SetVariable(17,"q",variable[17], step[17]);

cout<<"lolo3"<<endl;

  // do the minimization
  min->Minimize();
  cout<<"lolo3"<<endl;
  const double *xs = min->X();


  std::cout << "Minimum: f(";
    for(int i=0;i<nparam;i++){
          cout  << xs[i] << ",";
          calib_internal_pointer->matrix[1+int(i/6)][i%6]=xs[i];
    }
            cout << "): " << min->MinValue()  << std::endl;

  // expected minimum is 0
  if ( min->MinValue()  < 1.E-4  && f(xs) < 1.E-4)
     std::cout << "Minimizer " << minName << " - " << algoName
               << "   converged to the right minimum" << std::endl;
  else {
     std::cout << "Minimizer " << minName << " - " << algoName
               << "   failed to converge !!!" << std::endl;
     Error("NumericalMinimization","fail to converge");
  }

  return 0;
}


double untitled2::Q(const double *xx){

  vector <Double_t> S0;
  vector <Double_t> S1;
  vector <Double_t> S2;
  vector <Double_t> S3;

  for (int j=0;j<temp_data.size();j++){
   S0.push_back(temp_data[j][6]);
  }


  for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<6;k++){
        temp=temp+(xx[k]*temp_data[j][k]);

           }
         S1.push_back(temp);
  }

  for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<6;k++){
        temp=temp+(xx[k+6]*temp_data[j][k]);

           }
         S2.push_back(temp);
  }

  for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<6;k++){
        temp=temp+(xx[k+12]*temp_data[j][k]);

           }
         S3.push_back(temp);
  }



  Double_t minimize=0.;

  for(int k=0;k<temp_data.size();k++){
      //minimize=minimize+((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k])/(S0[k]*S0[k]*S0[k]*S0[k]))*((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k])/(S0[k]*S0[k]*S0[k]*S0[k]));
      minimize=minimize+((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k]))*((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k]));
  }

  return minimize;

}


double untitled2::Q_over(const double *xx){

  vector <Double_t> S0;
  vector <Double_t> S1;
  vector <Double_t> S2;
  vector <Double_t> S3;


  vector< vector <Double_t>>S1_tot;
  vector< vector <Double_t>> S2_tot;
  vector< vector <Double_t>> S3_tot;

  for (int j=0;j<temp_data.size();j++){
   S0.push_back(temp_data[j][6]);
  }

  for(int t=0;t<6;t++){

  for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<5;k++){
        temp=temp+(xx[k]*temp_data[j][(k+t)%6]);

           }
         S1.push_back(temp);
  }

  for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<5;k++){
        temp=temp+(xx[k+6]*temp_data[j][(k+t)%6]);

           }
         S2.push_back(temp);
  }

  for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<5;k++){
        temp=temp+(xx[k+12]*temp_data[j][(k+t)%6]);

           }
         S3.push_back(temp);
  }

  S1_tot.push_back(S1);
  S2_tot.push_back(S2);
  S3_tot.push_back(S3);


}

  Double_t minimize=0.;

  for(int k=0;k<temp_data.size();k++){
      for(int x=0;x<6;x++){
        for(int y=0;y<6;y++){

            //minimize=minimize+((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k])/(S0[k]*S0[k]*S0[k]*S0[k]))*((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k])/(S0[k]*S0[k]*S0[k]*S0[k]));
      minimize=minimize+ fabs(S1_tot[x][k]-S1_tot[y][k])+fabs(S2_tot[x][k]-S2_tot[y][k])+fabs(S3_tot[x][k]-S3_tot[y][k]);
  }
      }
}
  return minimize;

}

double untitled2::Q_sym(const double *xx){

  vector <Double_t> S0;
  vector <Double_t> S1;
  vector <Double_t> S2;
  vector <Double_t> S3;

  MatrixXd corig(3,6);
  MatrixXd rotation(3,3);
  MatrixXd crot(3,6);

  Double_t minimize=0.;
  corig<<xx[1], xx[2], xx[3], xx[4], xx[5], xx[6], xx[7], xx[8], xx[9],xx[10], xx[11], xx[12], xx[13], xx[14], xx[15], xx[16], xx[17], xx[18];

  for (int j=0;j<temp_data.size();j++){
   S0.push_back(temp_data[j][6]);
  }



  for(double theta=0;theta<(2*M_PI);theta=theta+0.5){
    for(double phi=0;phi<(2*M_PI);phi=phi+0.5){

        rotation<<cos(theta),sin(theta),0,(-cos(phi)*sin(theta)),(cos(theta)*cos(phi)),sin(phi),(sin(theta)*sin(phi)),(-cos(theta)*sin(phi)),cos(phi);
        crot=rotation*corig;

        vector<double> xxx;
        xxx.resize(18);

        for(int i=0;i<3;i++){
            for(int j=0;j<6;j++){
                xxx.push_back((crot(i,j)));
            }
        }


   for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<6;k++){
        temp=temp+(xxx[k]*temp_data[j][k]);

           }
         S1.push_back(temp);
  }

  for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<6;k++){
        temp=temp+(xxx[k+6]*temp_data[j][k]);

           }
         S2.push_back(temp);
  }

  for (int j=0;j<temp_data.size();j++) {
      Double_t temp=0.;
      for(int k=0;k<6;k++){
        temp=temp+(xxx[k+12]*temp_data[j][k]);

           }
         S3.push_back(temp);
  }





  for(int k=0;k<temp_data.size();k++){
      //minimize=minimize+((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k])/(S0[k]*S0[k]*S0[k]*S0[k]))*((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k])/(S0[k]*S0[k]*S0[k]*S0[k]));
      minimize=minimize+((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k]))*((S1[k]*S1[k]+S2[k]*S2[k]+S3[k]*S3[k]-S0[k]*S0[k]));
  }




    }
  }
  return (minimize);

}






double untitled2::Q_comb(const double *xx){

    return (Q(xx));//+Q_over(xx));//+Q_sym(xx));

}

