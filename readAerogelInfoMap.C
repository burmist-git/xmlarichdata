/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Oct 16 19:33:10 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
//#if !defined(READAEROGELINFOMAP_MAIN)
//#if !defined(__CLING__)
//#include "libxmlarichdata.h"
//#endif
//#endif
#include "aerogelInfoMap.h"

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

#ifdef READAEROGELINFOMAP_MAIN
Int_t readFileInfo( TString fname, TString *serial, TString *serialID, Double_t *version, Double_t *nref, Double_t *transmLength, Double_t *thickness);
Int_t readFileMap( TString fname, TString *id, Double_t *ring, Double_t *column, TString *layer);
#endif //READAEROGELINFOMAP_MAIN

#if defined(__CLING__)
Int_t readFileInfo( TString fname, TString *serial, TString *serialID, Double_t *version, Double_t *nref, Double_t *transmLength, Double_t *thickness);
Int_t readFileMap( TString fname, TString *id, Double_t *ring, Double_t *column, TString *layer);
#endif

const Int_t nnMax = 1000;
Int_t verboseLevel = 1;

std::vector<aerogelInfoMap> readAerogelInfoMap( TString fnameInfo = "./aerogelDataFromDB/aerogelInfo.dat", TString fnameMap = "./aerogelDataFromDB/aerogelMap.dat"){
  std::cout<<"fnameInfo "<<fnameInfo<<std::endl
	   <<"fnameMap  "<<fnameMap<<std::endl;
  std::vector<aerogelInfoMap> aimv;
  Int_t i = 0;
  Int_t j = 0;
  //////////// aerogel info ////////////
  //[INFO] Version = 2  serial = A001  id = CAu1-1  n = 1.0435  transmLength = 5.6  thickness = 2.03
  Int_t nInfo = 0;
  TString serial[nnMax];
  TString serialID[nnMax];
  Double_t version[nnMax];
  Double_t nref[nnMax];
  Double_t transmLength[nnMax];
  Double_t thickness[nnMax];
  //TString fnamerootInfo = fnameInfo; fnamerootInfo += ".root";
  //////////////////////////////////////
  //////////// aerogel map /////////////
  //[INFO] ID = B076  ring = 1  column = 12  layer: down
  Int_t nMap = 0;
  TString id[nnMax];
  Double_t ring[nnMax];
  Double_t column[nnMax];
  TString layer[nnMax];
  //TString fnamerootMap = fnameMap; fnamerootMap += ".root";
  //////////////////////////////////////
  // --> READING FILE <--
  nInfo = readFileInfo( fnameInfo, serial, serialID, version, nref, transmLength, thickness);
  nMap = readFileMap( fnameMap, id, ring, column, layer);
  if(verboseLevel>1){
    std::cout<<fnameInfo<<std::endl;
    for(i = 0;i<nInfo;i++){
      std::cout<<std::setw(10)<<version[i]<<std::setw(10)<<serial[i]<<std::setw(10)<<serialID[i]<<std::setw(10)<<nref[i]<<std::setw(10)<<transmLength[i]<<std::setw(10)<<thickness[i]<<std::endl;
    }
    std::cout<<fnameMap<<std::endl;
    for(i = 0;i<nMap;i++){
      std::cout<<std::setw(10)<<id[i]<<std::setw(10)<<ring[i]<<std::setw(10)<<column[i]<<std::setw(10)<<layer[i]<<std::endl;
    }
  }
  //////////////////////////////////////
  //////////////////////////////////////
  // --> LOOP <--
  Int_t nn = 0;
  if(verboseLevel>0)
    std::cout<<std::setw(10)<<"id_map"<<std::setw(10)<<"number"<<std::setw(10)<<"serial"<<std::setw(10)<<"serialID"<<std::setw(10)<<"ring"<<std::setw(10)<<"column"<<std::setw(10)<<"layer"<<std::setw(10)<<"n"<<std::setw(10)<<"transmL"<<std::setw(10)<<"thick"<<std::endl;
  for(i = 0;i<nMap;i++){
    if(verboseLevel>0)
      std::cout<<std::setw(10)<<id[i];
    for(j = 0;j<nInfo;j++){
      if(id[i] == serial[j]){
	if(verboseLevel>0)
	  std::cout<<std::setw(10)<<nn<<std::setw(10)<<serial[j]<<std::setw(10)<<serialID[j]<<std::setw(10)<<ring[i]<<std::setw(10)<<column[i]<<std::setw(10)<<layer[i]<<std::setw(10)<<nref[j]<<std::setw(10)<<transmLength[j]<<std::setw(10)<<thickness[j];
	aerogelInfoMap aimstr; 
	aimstr.id_map = id[i];
	aimstr.idnumber = nn;
	aimstr.serial = serial[j];
	aimstr.serialID = serialID[j];
	aimstr.ring = ring[i];
	aimstr.column = column[i];
	aimstr.layer = layer[i];
	aimstr.n = nref[j];
	aimstr.transmL = transmLength[j];
	aimstr.thick = thickness[j];
	aimv.push_back(aimstr);
  	nn++;
      }
    }
    if(verboseLevel>0)
      std::cout<<std::endl;
  }
  //////////////////////////////////////
  // --> DISPLAY <--
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);  
  //TCanvas *c1 = new TCanvas("c1","plots",10,10,800,800);
  //c1->Clear();
  //c1->SetFillColor(kWhite);
  //c1->GetPad(0)->SetLeftMargin(0.12);
  //c1->GetPad(0)->SetRightMargin(0.02);
  //c1->GetPad(0)->SetTopMargin(0.07);
  //c1->GetPad(0)->SetBottomMargin(0.02);
  return aimv;
}

Int_t readFileInfo( TString fname, TString *serial, TString *serialID, Double_t *version, Double_t *nref, Double_t *transmLength, Double_t *thickness){
  std::string mot;
  std::string mot1;
  std::string mot2;
  std::string mot3;
  std::string mot7;
  std::string mot10;
  std::ifstream myfile(fname.Data());
  Int_t nn = 0;
  Double_t x1v, x2v, x3v, x4v;
  //     1       2 3 4      5 6    7  8 9     10 11 12     13           14 15  16        17 18   19
  //[INFO] Version = 2 serial = A001 id = CAu1-1  n  = 1.0435 transmLength  = 5.6 thickness  = 2.03
  //[INFO] Version = 2 serial = A002 id = CAu1-2  n  = 1.0437 transmLength  = 5.2 thickness  = 2.03
  //[INFO] Version = 2 serial = A003 id = CAu1-3  n  = 1.0433 transmLength  = 5.5 thickness  = 2.02
  //[INFO] Version = 2 serial = A004 id = CAu1-4  n  = 1.0434 transmLength  = 5.7 thickness  = 2.04
  //[INFO] Version = 2 serial = A005 id = CAu1-5  n  = 1.0435 transmLength  = 5.6 thickness  = 2.04
  //[INFO] Version = 2 serial = A006 id = CAu1-6  n  = 1.0437 transmLength  = 5.5 thickness  = 2.03
  //[INFO] Version = 2 serial = A007 id = CAu1-7  n  = 1.0436 transmLength  = 5.5 thickness  = 2.03
  //[INFO] Version = 2 serial = A008 id = CAu1-8  n  = 1.0441 transmLength  = 5.2 thickness  = 2.03
  if(myfile.is_open()){
    while(myfile>>mot1>>mot2>>mot3>>x1v){
      myfile>>mot>>mot>>mot7>>mot>>mot>>mot10>>mot>>mot>>x2v;
      //std::cout<<mot7<<std::endl;
      myfile>>mot>>mot>>x3v;
      myfile>>mot>>mot>>x4v;
      version[nn] = x1v;
      serial[nn] = mot7;
      serialID[nn] = mot10;
      nref[nn] = x2v;
      transmLength[nn] = x3v;
      thickness[nn] = x4v;
      nn++;
      if(verboseLevel>1)
	std::cout<<std::setw(10)<<x1v<<std::setw(10)<<x2v<<std::setw(10)<<x3v<<std::setw(10)<<x4v<<std::endl;
    }
    myfile.close();
  } 
  else{
    std::cout << "Unable to open file"; 
  }
  return nn;
}

Int_t readFileMap(TString fname, TString *id, Double_t *ring, Double_t *column,TString *layer){
  std::string mot;
  std::string mot4;
  std::string mot12;
  std::ifstream myfile(fname.Data());
  Int_t nn = 0;
  Double_t x1v, x2v;
  //     1  2 3    4    5 6 7      8 9 10    11    12
  //[INFO] ID = B076 ring = 1 column = 12 layer: down
  //[INFO] ID = B134 ring = 1 column = 13 layer: down
  //[INFO] ID = B036 ring = 1 column = 14 layer: down
  //[INFO] ID = B027 ring = 1 column = 15 layer: down
  //[INFO] ID = B024 ring = 1 column = 16 layer: down
  //[INFO] ID = B077 ring = 1 column = 17 layer: down
  //[INFO] ID = B084 ring = 1 column = 18 layer: down
  //[INFO] ID = B073 ring = 1 column = 19 layer: down
  //[INFO] ID = B060 ring = 1 column = 20 layer: down
  //[INFO] ID = B074 ring = 1 column = 21 layer: down
  //[INFO] ID = B026 ring = 1 column = 22 layer: down
  if(myfile.is_open()){
    while(myfile>>mot>>mot>>mot>>mot4){
      myfile>>mot>>mot>>x1v;
      myfile>>mot>>mot>>x2v;
      myfile>>mot>>mot12;
      id[nn] = mot4;
      ring[nn] = x1v;
      column[nn] = x2v;
      layer[nn] = mot12;
      nn++;
      if(verboseLevel>1)
	std::cout<<std::setw(10)<<mot4<<std::setw(10)<<x1v<<std::setw(10)<<x2v<<std::setw(10)<<mot12<<std::endl;
    }
    myfile.close();
  } 
  else{
    std::cout << "Unable to open file"; 
  }
  return nn;
}
}//namespace xmlarichdata{

#ifdef READAEROGELINFOMAP_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 3){
    TString fileNInfo = argv[1];
    TString fileNMap = argv[2];
    readAerogelInfoMap( fileNInfo, fileNMap);
    return 0;
  }
  readAerogelInfoMap();
  return 0;
}
# endif // ifndef __CINT__
#endif //ifdef READAEROGELINFOMAP_MAIN
