/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Oct 16 19:33:10 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
#include "mergerStruct.h"

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
  
  std::vector<mergerStruct> read_merger_positions( TString fnameInfo, float &size_l, float &size_w, int &nMerger){
    Int_t verboseLevel = 0;
    if(verboseLevel>0)
      std::cout<<"fnameInfo "<<fnameInfo<<std::endl;
    std::vector<mergerStruct> merStrV;
    //Int_t i = 0;
    // --> READING FILE <--
    int nMergerii = 0;
    int Sector;
    int MergerSN;
    float center_radius_mm;
    float center_rotation_deg;
    float Board_Rotation_deg;
    float Board_size_l = 0.0;
    float Board_size_w = 0.0;
    std::string mot;
    std::ifstream myfile(fnameInfo.Data());
    if(myfile.is_open()){
      myfile>>mot;//Board_size
      myfile>>Board_size_w;
      myfile>>Board_size_l;
      size_w = Board_size_w;
      size_l = Board_size_l;
      myfile>>mot;//mm2
      myfile>>mot>>mot>>mot>>mot>>mot; //Sector  MergerSN        center_radius_mm        center_rotation_deg     Board_Rotation_deg
      if(verboseLevel>1)
	  std::cout<<std::setw(10)<<"Sector"
		   <<std::setw(10)<<"MergerSN"
		   <<std::setw(10)<<"center_radius_mm"
		   <<std::setw(10)<<"center_rotation_deg"
		   <<std::setw(10)<<"Board_Rotation_deg"<<std::endl;      
      while(myfile>>Sector>>MergerSN>>center_radius_mm>>center_rotation_deg>>Board_Rotation_deg){
	mergerStruct merStr;
	merStr.Sector = Sector;
	merStr.MergerSN = MergerSN;
	merStr.center_radius_mm = center_radius_mm;
	merStr.center_rotation_deg = center_rotation_deg;
	merStr.Board_Rotation_deg = Board_Rotation_deg;
	merStrV.push_back(merStr);
	nMergerii++;
	if(verboseLevel>1)
	  std::cout<<std::setw(25)<<Sector
		   <<std::setw(25)<<MergerSN
		   <<std::setw(25)<<center_radius_mm
		   <<std::setw(25)<<center_rotation_deg
		   <<std::setw(25)<<Board_Rotation_deg<<std::endl;
	//std::cout<<Board_Rotation_deg - center_rotation_deg<<std::endl;
      }
      nMerger = nMergerii;
      myfile.close();
    } 
    else{
      std::cout << "Unable to open file"; 
    }
    if(verboseLevel>0){
      std::cout<<"Merger slot number : "<<std::endl;
      for (unsigned i=0; i<merStrV.size(); i++){
	std::cout<<std::setw(8)<<merStrV[i].MergerSN + 12*(merStrV[i].Sector - 1);
      }
      std::cout<<std::endl;
      std::cout<<"Distance from the center in mm : "<<std::endl;
      for (unsigned i=0; i<merStrV.size(); i++){
	std::cout<<std::setw(8)<<merStrV[i].center_radius_mm;
	/*
	std::cout<<"<mergerSlotID slotID='"
		 <<(merStrV[i].MergerSN + 12*(merStrV[i].Sector - 1))<<"'>"
		 <<merStrV[i].center_radius_mm<<"</mergerSlotID>"<<std::endl;	
	*/
      }
      std::cout<<std::endl;
      std::cout<<"Azimuthal angle of the merger PCB center in polar coordinate system in deg"<<std::endl;
      for (unsigned i=0; i<merStrV.size(); i++){
	std::cout<<std::setw(8)<<merStrV[i].center_rotation_deg;	
	/*
	std::cout<<"<mergerSlotID slotID='"
		 <<(merStrV[i].MergerSN + 12*(merStrV[i].Sector - 1))<<"'>"
		 <<merStrV[i].center_rotation_deg<<"</mergerSlotID>"<<std::endl;	
	*/
      }
      std::cout<<std::endl;
    }
    return merStrV;
  }
  
}//namespace xmlarichdata{

#ifdef READMERGERPOSITION_MAIN
# ifndef __CINT__
int main(){
  TString fnameInfo = "./merger_positions.dat"; 
  float size_l, size_w;
  int nMerger;
  std::vector<mergerStruct> merStrV = read_merger_positions( fnameInfo, size_l, size_w, nMerger);

  return 0;
}
# endif // ifndef __CINT__
#endif //ifdef READMERGERPOSITION_MAIN
