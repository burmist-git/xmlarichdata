/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue May  1 23:40:04 JST 2018                                         *
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

  //Int_t runARICH_asic_fpga_Temperatures(){
  
  Belle2::ARICHChannelHist* runARICH_asic_fpga_Temperatures() {
  //ARICHChannelHist* runARICH_asic_fpga_Temperatures() {
    
    TString histTitle;
    TString fname;
    TString histName;
    TString lineDrawOpt;
    double deltaPhi;
    
    histTitle = "h2_asic_t";
    fname = "./temperature_asic.txt"; 
    histName = "asic temperature";
    
    //histTitle = "h2_fpga_t";
    //fname = "./temperature_fpga.txt"; 
    //histName = "fpga temperature";
    
    lineDrawOpt = "drawLine";
    
    //deltaPhi = -TMath::Pi()/3.0;
    deltaPhi = 0;
    
    Belle2::ARICHChannelHist *h2_asic_t = new Belle2::ARICHChannelHist(histTitle.Data(),histName.Data(),1);
    
    std::vector<double> posR;
    std::vector<double> posPhi;
    std::vector<double> measT;
    read_temperature_meas( fname, posR, posPhi, measT);
    
    double x, y, w;
    
    for (unsigned i=0; i<posR.size(); i++){
      x = posR.at(i) * TMath::Cos(posPhi.at(i) + deltaPhi);
      y = posR.at(i) * TMath::Sin(posPhi.at(i) + deltaPhi);
      w = measT.at(i);
      //cout<<"x "<<x<<endl;
      //cout<<"y "<<y<<endl;
      //cout<<"w "<<w<<endl;
      h2_asic_t->Fill(x,y,w);
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
    Double_t l_slot = 29.1;
    Double_t frameXmin = -114.0 - l_slot;
    Double_t frameXmax =  114.0 + l_slot;
    Double_t frameYmin = -114.0 - l_slot;
    Double_t frameYmax =  114.0 + l_slot;
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
    h2_asic_t->GetZaxis()->SetRangeUser(30.0,60.0);
    //h2_merger->GetZaxis()->SetRangeUser(50.0,80.0);
    //h2_merger->DrawHisto("ZTEXT same","","drawLine");
    //h2_merger->DrawHisto("ZCOLOR same","","drawLine");
    h2_asic_t->Draw("ZCOLOR same");


    TH2Poly *h2poly = new TH2Poly();
    vector<TGraph*> m_verticesGraphV;
    vector<TGraph*> m_additionalGraphV;
    vector<TLine*> m_additionalLineV;
    double normalisationV = 10.0;
    getTestCoolingPlates( h2poly, m_verticesGraphV, "h2poly", "h2poly", frameXmin, frameXmax, frameYmin,  frameYmax, normalisationV);
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
