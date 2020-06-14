/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Fri Sep 28 18:20:12 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "ARICHMergerHist.h"
#include "libxmlarichdata.h"
#else 
#include "ARICHMergerHist.C"
#include "read_temperature_meas.C"
#include "testCoolingPlates.C"
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
#include <TMath.h>

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
//using namespace Belle2;
using namespace xmlarichdata;

namespace xmlarichdata{
  
  Belle2::ARICHChannelHist* runARICH_asic_fpga_numbering() {
    
    TString histTitle;
    TString fname;
    TString histName;
    
    histTitle = "h2_feb_numbering";
    histName = "FEB numbering";
    
    Belle2::ARICHChannelHist *h2_asic_t = new Belle2::ARICHChannelHist(histTitle.Data(),histName.Data(),1);
    
    for (unsigned i=0; i<420; i++){
      /*
      if((i+1)>35 && (i+1)<43)
	h2_asic_t->setBinContent(i+1,i+1);
      if((i+1)>82 && (i+1)<91)
	h2_asic_t->setBinContent(i+1,i+1);
      if((i+1)>135 && (i+1)<145)
	h2_asic_t->setBinContent(i+1,i+1);
      if((i+1)>194 && (i+1)<205)
	h2_asic_t->setBinContent(i+1,i+1);
      if((i+1)>259 && (i+1)<271)
	h2_asic_t->setBinContent(i+1,i+1);
      if((i+1)>330 && (i+1)<343)
	h2_asic_t->setBinContent(i+1,i+1);
      if((i+1)>407 && (i+1)<421)
      */
	h2_asic_t->setBinContent(i+1,i+1);
    }    
    
    gStyle->SetPalette(kRainBow);
    TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
    c1->SetTitle(histTitle.Data());
    c1->SetName(histName.Data());
    c1->SetRightMargin(0.12);
    c1->SetLeftMargin(0.12);
    c1->SetTopMargin(0.1);
    c1->SetBottomMargin(0.15);
    ///////////////////////////////////////////////////////////////
    double envelopeR_min = 43.5;
    double envelopeR_max = 113.2;
    //Double_t l_slot = 29.1;
    Double_t l_slot = 1.0;
    Double_t frameXmin = -114.0 - l_slot;
    Double_t frameXmax =  114.0 + l_slot;
    Double_t frameYmin = -114.0 - l_slot;
    Double_t frameYmax =  114.0 + l_slot;
    /*
    Double_t frameXmin =  20.0;
    Double_t frameXmax =  114.0 + l_slot + 6;
    Double_t frameYmin = -114.0 - l_slot + 15;
    Double_t frameYmax =  1.0;
    */
    TH2F *frame = new TH2F( "h2", "h2", 40, frameXmin, frameXmax,40, frameYmin, frameYmax);
    frame->GetXaxis()->SetTitle("x (cm)");
    frame->GetYaxis()->SetTitle("y (cm)");
    frame->GetXaxis()->CenterTitle();
    frame->GetYaxis()->CenterTitle();
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->SetStats(kFALSE);
    frame->SetTitle("");
    frame->Draw();
    //img->Draw("same");
    ///////////////////////////////////////////////////////////////
    h2_asic_t->SetStats(kFALSE);
    h2_asic_t->GetXaxis()->SetTitle("x (cm)");
    h2_asic_t->GetYaxis()->SetTitle("y (cm)");
    h2_asic_t->GetXaxis()->CenterTitle();
    h2_asic_t->GetYaxis()->CenterTitle();
    h2_asic_t->GetYaxis()->SetTitleOffset(1.5);
    //SetLineStyle(1);
    //SetLineWidth(3.0);
    c1->Modified();
    c1->Update();
    
    //gStyle->SetPalette(1);
    //h2_asic_t->GetZaxis()->SetRangeUser(0.0,420.0);
    //h2_asic_t->Draw("ZCOLOR same");
    h2_asic_t->Draw("ZTEXT same");

    vector<TGraph*> m_verticesGraphV;
    vector<TGraph*> m_additionalGraphV;
    vector<TLine*> m_additionalLineV;
    getAdditionalGraphV_and_LineV_for_Plot(m_additionalGraphV, m_additionalLineV, envelopeR_min, envelopeR_max, l_slot);

    for (unsigned i=0; i<m_verticesGraphV.size(); i++)
      m_verticesGraphV.at(i)->Draw("same");
    
    for (unsigned i=0; i<m_additionalGraphV.size(); i++)
      m_additionalGraphV.at(i)->Draw("same");
    
    for (unsigned i=0; i<m_additionalLineV.size(); i++)
      m_additionalLineV.at(i)->Draw("same");
    
    //const Int_t Number = 3;
    //Double_t Red[Number]    = { 1.00, 0.00, 0.00};
    //Double_t Green[Number]  = { 0.00, 1.00, 0.00};
    //Double_t Blue[Number]   = { 1.00, 0.00, 1.00};
    //Double_t Length[Number] = { 30.00, 45.0, 60.00 };
    //Int_t nb=20;
    //TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
    
    //return 0;

    return h2_asic_t;
  }
  
}//namespace xmlarichdata{
