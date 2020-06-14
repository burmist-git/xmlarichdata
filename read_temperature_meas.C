/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue May  1 21:26:28 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/
//my
#include "libxmlarichdata.h"

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

//root
#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TVector3.h>
#include <TStyle.h>
#include <TPad.h>
#include <TString.h>
#include <TGraph.h>
#include <TAxis.h>

using namespace xmlarichdata;

namespace xmlarichdata{
  void read_temperature_meas( TString fname, std::vector<double> &posR, std::vector<double> &posPhi, std::vector<double> &measT){
    Int_t verboseLevel = 2;
    std::cout<<"fname : "<<fname<<std::endl;
    // --> READING FILE <--
    double posRv, posPhiv, measTv;
    std::ifstream myfile(fname.Data());
    std::string mot;
    if(verboseLevel>1)
      std::cout<<std::setw(15)<<"posR_cm"
	       <<std::setw(15)<<"posPhi_deg"
	       <<std::setw(15)<<"measT_Cel"<<std::endl;    
    if(myfile.is_open()){
      myfile>>mot>>mot>>mot;
      while(myfile>>posRv>>posPhiv>>measTv){
	if(verboseLevel>1)
	  std::cout<<std::setw(15)<<posRv
		   <<std::setw(15)<<posPhiv
		   <<std::setw(15)<<measTv<<std::endl;
	posR.push_back(posRv);
	posPhi.push_back(posPhiv);
	measT.push_back(measTv);
      }
      myfile.close();
    } 
    else{
      std::cout << "Unable to open file"<<std::endl; 
    }
  }  
}//namespace xmlarichdata{

#ifdef READTEMPERATURE_MEAS
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 2){
    //temperature_asic.txt
    //temperature_fpga.txt
    //TString fname = "./temperature_merger.txt"; 
    TString fname = argv[1];
    std::vector<double> posR;
    std::vector<double> posPhi;
    std::vector<double> measT;
    read_temperature_meas( fname, posR, posPhi, measT);
  }
  return 0;
}
# endif // ifndef __CINT__
#endif //#ifdef READTEMPERATURE_MEAS
