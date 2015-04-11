#ifndef MINIMIZ_ROOT
#define MINIMIZ_ROOT

//  Show usage with all the possible minimizers.
// Minimize the Rosenbrock function (a 2D -function)
// This example is described also in
// http://root.cern.ch/drupal/content/numerical-minimization#multidim_minim
// input : minimizer name + algorithm name
// randomSeed: = <0 : fixed value: 0 random with seed 0; >0 random with given seed
//
//Author: L. Moneta Dec 2010

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TRandom2.h"
#include "TError.h"
#include <iostream>
#include <vector>

using namespace std;



int NumericalMinimization(double (*RosenBrock)(const double *),double avg,int nparam,const char * minName = "Minuit2",
                         const char *algoName = "" ,
                         int randomSeed = -1)
{
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
  ROOT::Math::Minimizer* min =
  ROOT::Math::Factory::CreateMinimizer(minName, algoName);

  // set tolerance , etc...
  min->SetMaxFunctionCalls(1000000); // for Minuit/Minuit2
  min->SetMaxIterations(10000);  // for GSL
  min->SetTolerance(0.001);
  min->SetPrintLevel(1);

  // create funciton wrapper for minmizer
  // a IMultiGenFunction type
  ROOT::Math::Functor f(&(*RosenBrock),18);
  double stepp=0.01;
  double step[18] = {stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp,stepp};
  // starting point

  double variable[18] = {avg,-avg,0,0,0,0,0,0,avg,-avg,0,0,0,0,0,0,avg,-avg};
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

  // Set the free variables to be minimized!
  min->SetVariable(0,"x",variable[0], step[0]);
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


  // do the minimization
  min->Minimize();

  const double *xs = min->X();


  std::cout << "Minimum: f(";
    for(int i=0;i<nparam;i++){
          cout  << xs[i] << ",";}
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
#endif // MINIMIZ_ROOT

