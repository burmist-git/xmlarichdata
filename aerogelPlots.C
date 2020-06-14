/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Fri Oct 27 15:11:21 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "ARICHAerogelHist.h"
#include "libxmlarichdata.h"
#else 
//my
#include "ARICHAerogelHist.C"
#include "xmlreadfile.C"
#include "readAerogelInfoMap.C"
#endif
//my
#include "aerogelInfoMap.h"

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TList.h>

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>

using namespace std;

Int_t plot(TString layerName = "up", TString parName = "n");

Int_t aerogelPlots(){
  plot( "up", "n");
  plot( "down", "n");
  plot( "up", "transmL");
  plot( "down", "transmL");
  plot( "up", "thick");
  plot( "down", "thick");
  return 0;
}

Int_t plot(TString layerName = "up", TString parName = "n"){
  TString h2name = "h2_aerogel";
  h2name += "_";
  h2name += layerName;
  h2name += "_";
  h2name += parName;
  TString h2title = "aerogel";
  h2title += " ";
  h2title += layerName;
  h2title += " ";
  h2title += parName;
  ARICHAerogelHist *h2_aerogel = new ARICHAerogelHist( h2name.Data(), h2title.Data());
  //TString fnameInfo = "./aerogelDataFromDB/aerogelInfoBis.dat";
  TString fnameInfo = "./aerogelDataFromDB/aerogelInfo.dat";
  TString fnameMap = "./aerogelDataFromDB/aerogelMap.dat";

  const vector<aerogelInfoMap> &aimv = xmlarichdata::readAerogelInfoMap( fnameInfo, fnameMap);
  for( unsigned i=0; i<aimv.size(); i++){
    if ( aimv.at(i).layer == layerName){
      if(parName == "n")
	h2_aerogel->SetBinContent(h2_aerogel->GetBinIDFromRingColumn(aimv.at(i).ring, aimv.at(i).column),aimv.at(i).n);
      if(parName == "transmL")
	h2_aerogel->SetBinContent(h2_aerogel->GetBinIDFromRingColumn(aimv.at(i).ring, aimv.at(i).column),aimv.at(i).transmL);
      if(parName == "thick")
	h2_aerogel->SetBinContent(h2_aerogel->GetBinIDFromRingColumn(aimv.at(i).ring, aimv.at(i).column),aimv.at(i).thick);
    }
  }
  //h2_aerogel->DrawHisto("ZCOLOT text same","./outplots/");
  h2_aerogel->DrawHisto("ZCOLOT text same","");
  return 0;
}

#ifdef AEROGELPLOTS_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 1){
    aerogelPlots();
    return 0;
  }
  aerogelPlots();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef AEROGELPLOTS_MAIN
