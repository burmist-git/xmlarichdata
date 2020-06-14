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

Int_t runARICHMergerHist(){
  ARICHMergerHist *h2_merger = new ARICHMergerHist( "h2_merger", "Merger slot numbering");

  TString fnameInfo = "./merger_positions.dat";
  float size_l;
  float size_w;
  int nMerger;
  std::vector<mergerStruct> merStrV = read_merger_positions( fnameInfo, size_l, size_w, nMerger);

  for (unsigned i=0; i<merStrV.size(); i++){
    int mergerSlotNumber = merStrV[i].MergerSN + (merStrV[i].Sector-1)*12;
    h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(mergerSlotNumber),mergerSlotNumber);
    //h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(mergerSlotNumber),1);
  }


  /*
  //for (unsigned i=0; i<merStrV.size(); i++){
  //int mergerSlotNumber = merStrV[i].MergerSN + (merStrV[i].Sector-1)*12;
  //h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(mergerSlotNumber),mergerSlotNumber);
  for (unsigned i=0; i<merStrV.size(); i++){
    int mergerSlotNumber = merStrV[i].MergerSN + (merStrV[i].Sector-1)*12;
    h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(mergerSlotNumber),4015);
    //h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(mergerSlotNumber),1);
  }
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(61),4016);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(62),4016);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(63),4016);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(64),4016);

  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(65),4017);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(66),4017);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(67),4017);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(68),4017);

  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(69),4018);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(70),4018);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(71),4018);
  h2_merger->SetBinContent(h2_merger->GetBinIDFromMergerSlotNumber(72),4018);
  //}
  */

  h2_merger->DrawHisto("ZTEXT same","","drawLine");
  //h2_merger->DrawHisto("ZCOLOR ZTEXT same","","drawLine");
  cout<<"h2_merger->GetBinIDFromMergerSlotNumber( Int_t mergerSlotNumber) "<<h2_merger->GetBinIDFromMergerSlotNumber(70)<<endl;
  cout<<"h2_merger->GetMergerSlotNumberFromBinID( Int_t binID) "<<h2_merger->GetMergerSlotNumberFromBinID(70)<<endl;


  //TCanvas *c1 = new TCanvas("roses", "roses", 800, 800);
  //TImage *img = TImage::Open("$ROOTSYS/tutorials/image/rose512.jpg");
  //TImage *img = TImage::Open("./pict061_2.png");
  //if (!img) {
  //printf("Could not create an image... exit\n");
  //return 0;
  //}
  //c1->cd();
  //img->SetConstRatio(kFALSE);
  //img->Draw("");
  //img->Draw("same N");

  //h2_merger->DrawHisto("ZTEXT same","","drawLine");


  return 0;
}
