/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Jun 24 11:44:22 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLine.h>
#include <TMath.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{

  void printSuperKEKBpar(){
    int nBunches = 2500;
    double circumference = 3016.315;                                    // m
    double rfFrequency = 508887000.0;                                   // hZ
    double singleBunchRotationTime = circumference/TMath::C();          // m
    double singleBunchRotationFrequency = 1.0/singleBunchRotationTime;  // hZ
    double bunchXingTime = singleBunchRotationTime/nBunches;            // m
    double bunchXingFrequency = singleBunchRotationFrequency*nBunches;  // hZ
    cout<<"***************************"<<endl;
    cout<<"nBunches                     "<<nBunches<<endl
	<<"circumference                "<<circumference<<endl
	<<"singleBunchRotationTime      "<<singleBunchRotationTime<<endl
	<<"singleBunchRotationFrequency "<<singleBunchRotationFrequency<<endl
	<<"bunchXingTime                "<<bunchXingTime<<endl
	<<"bunchXingFrequency           "<<bunchXingFrequency<<endl
	<<"rfFrequency                  "<<rfFrequency<<endl;
    cout<<"---------------------------"<<endl;
  }

}//namespace xmlarichdata {

#ifdef PRINTSUPERKEKBPAR_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 1){
    printSuperKEKBpar();
    return 0;
  }
  printSuperKEKBpar();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef PRINTSUPERKEKBPAR_MAIN
