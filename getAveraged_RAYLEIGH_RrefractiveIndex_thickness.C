/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Jun 10 10:51:42 JST 2018                                         *
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

Int_t getAveraged_RAYLEIGH_RrefractiveIndex_thickness(){

  TString outPutRootFile="averaged_RAYLEIGH_RrefractiveIndex_thickness.root";

  TString fnameInfo = "./aerogelDataFromDB/aerogelInfo.dat";
  TString fnameMap = "./aerogelDataFromDB/aerogelMap.dat";
  const vector<aerogelInfoMap> &aimv = xmlarichdata::readAerogelInfoMap( fnameInfo, fnameMap);

  TH1D *h1_n_A = new TH1D("h1_n_A", "n A",100,1.04,1.06);
  TH1D *h1_n_B = new TH1D("h1_n_B", "n B",100,1.04,1.06);
  TH1D *h1_transmL_A = new TH1D("h1_transmL_A", "transmL A",100,2.0,6.0);
  TH1D *h1_transmL_B = new TH1D("h1_transmL_B", "transmL B",100,2.0,6.0);
  TH1D *h1_thick_A = new TH1D("h1_thick_A", "thickness A",15,1.85,2.05);
  TH1D *h1_thick_B = new TH1D("h1_thick_B", "thickness B",15,1.85,2.05);

  for( unsigned i=0; i<aimv.size(); i++){
    if(aimv.at(i).layer == "up"){
      h1_n_A->Fill(aimv.at(i).n);
      h1_transmL_A->Fill(aimv.at(i).transmL);
      h1_thick_A->Fill(aimv.at(i).thick);
    }
    if(aimv.at(i).layer == "down"){
      h1_n_B->Fill(aimv.at(i).n);
      h1_transmL_B->Fill(aimv.at(i).transmL);
      h1_thick_B->Fill(aimv.at(i).thick);
    }
  }

  TFile* rootFile = new TFile(outPutRootFile.Data(), "RECREATE", " Histograms", 1);
  h1_n_A->Write();
  h1_transmL_A->Write();
  h1_thick_A->Write();  
  h1_n_B->Write();
  h1_transmL_B->Write();
  h1_thick_B->Write();  

  h1_n_A->SetLineColor(kBlack);
  h1_n_A->SetLineWidth(3.0);
  h1_n_A->SetMaximum(30.0);
  h1_n_A->SetTitle("");
  h1_n_A->GetXaxis()->SetTitle("n");
  h1_n_B->SetLineColor(kRed);
  h1_n_B->SetLineWidth(3.0);

  h1_transmL_A->SetLineColor(kBlack);
  h1_transmL_A->SetLineWidth(3.0);
  h1_transmL_A->SetMaximum(20.0);
  h1_transmL_A->SetTitle("");
  h1_transmL_A->GetXaxis()->SetTitle("Rayleigh scattering length (@ 400 nm), cm");
  h1_transmL_B->SetLineColor(kRed);
  h1_transmL_B->SetLineWidth(3.0);

  h1_thick_A->SetLineColor(kBlack);
  h1_thick_A->SetLineWidth(3.0);
  h1_thick_A->SetMaximum(65.0);
  h1_thick_A->SetTitle("");
  h1_thick_A->GetXaxis()->SetTitle("Thickness, cm");
  h1_thick_B->SetLineColor(kRed);
  h1_thick_B->SetLineWidth(3.0);
  h1_thick_B->SetMaximum(65.0);
  h1_thick_B->SetTitle("");
  h1_thick_B->GetXaxis()->SetTitle("Thickness, cm");
  
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  
  TCanvas *c1 = new TCanvas("c1","n",10,10,800,800);
  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.09);
  c1->SetTopMargin(0.09);
  c1->SetBottomMargin(0.09);
  h1_n_A->Draw();
  h1_n_B->Draw("sames");
  TLegend *leg1 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg1->AddEntry(h1_n_A, "Up (A)","l");
  leg1->AddEntry(h1_n_B, "Down (B)","l");
  leg1->Draw();

  TCanvas *c2 = new TCanvas("c2","RAYLEIGH",20,20,800,800);
  c2->SetRightMargin(0.03);
  c2->SetLeftMargin(0.09);
  c2->SetTopMargin(0.09);
  c2->SetBottomMargin(0.09);
  h1_transmL_A->Draw();
  h1_transmL_B->Draw("sames");
  TLegend *leg2 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg2->AddEntry(h1_transmL_A, "Up (A)","l");
  leg2->AddEntry(h1_transmL_B, "Down (B)","l");
  leg2->Draw();

  TCanvas *c3 = new TCanvas("c3","Thickness",30,30,800,800);
  c3->SetRightMargin(0.03);
  c3->SetLeftMargin(0.09);
  c3->SetTopMargin(0.09);
  c3->SetBottomMargin(0.09);
  h1_thick_A->Draw();
  TLegend *leg3 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg3->AddEntry(h1_thick_A, "Up (A)","l");
  leg3->Draw();

  TCanvas *c4 = new TCanvas("c4","Thickness",40,40,800,800);
  c4->SetRightMargin(0.03);
  c4->SetLeftMargin(0.09);
  c4->SetTopMargin(0.09);
  c4->SetBottomMargin(0.09);
  h1_thick_B->Draw();
  TLegend *leg4 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg4->AddEntry(h1_thick_B, "Down (B)","l");
  leg4->Draw();




  return 0;
}

/*
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
*/
