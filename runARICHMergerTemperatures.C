/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Wed Oct 18 21:02:16 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "ARICHMergerHist.h"
#include "libxmlarichdata.h"
#else 
#include "ARICHMergerHist.C"
#include "read_temperature_meas.C"
#endif //#if !defined(__CLING__)
#include "mergerStruct.h"

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
using namespace xmlarichdata;

Int_t runARICHMergerTemperatures(){
  ARICHMergerHist *h2_merger = new ARICHMergerHist( "h2_merger", "Merger Temperatures");

  TString lineDrawOpt = "drawLine";

  TString fname = "./temperature_merger.txt"; 
  std::vector<double> posR;
  std::vector<double> posPhi;
  std::vector<double> measT;
  read_temperature_meas( fname, posR, posPhi, measT);
  
  double x, y, w;
  
  for (unsigned i=0; i<posR.size(); i++){
    x = posR.at(i) * 10 * TMath::Cos(posPhi.at(i));
    y = posR.at(i) * 10 * TMath::Sin(posPhi.at(i));
    w = measT.at(i);
    //cout<<"x "<<x<<endl;
    //cout<<"y "<<y<<endl;
    //cout<<"w "<<w<<endl;
    h2_merger->Fill(x,y,w);
  }
    
  h2_merger->GetZaxis()->SetRangeUser(50.0,80.0);
  //h2_merger->GetZaxis()->SetRangeUser(50.0,80.0);
  //h2_merger->DrawHisto("ZTEXT same","","drawLine");
  h2_merger->DrawHisto("ZCOLOR text same","","drawLine");

  return 0;
}
