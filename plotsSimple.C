/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Oct 16 15:51:21 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>

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

Int_t plotsSimple(){

  TString fileN;
  TString histN1;
  TString histN2;
  fileN = "./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root";
  //histN1 = "h1_deltaTrL_A"; 
  //histN2 = "h1_deltaTrL_B"; 
  //histN1 = "h1_TrL_A_400"; 
  //histN2 = "h1_TrLre_A_400"; 
  //histN1 = "h1_TrL_B_400"; 
  //histN2 = "h1_TrLre_B_400"; 
  //histN1 = "h1_TrLre_A_400"; 
  //histN2 = "h1_TrLre_B_400"; 
  histN1 = "h1_n_A";
  histN2 = "h1_n_B";

  TFile *f1 = new TFile(fileN.Data());

  TH1D *h1_1 = (TH1D*)f1->Get(histN1.Data());
  TH1D *h1_2 = (TH1D*)f1->Get(histN2.Data());

  h1_1->SetTitle("");
  h1_2->SetTitle("");

  //h1_1->Rebin(4);

  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);

  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.09);
  c1->SetTopMargin(0.09);
  c1->SetBottomMargin(0.09);

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  gPad->SetGridx();
  gPad->SetGridy();

  h1_1->SetLineColor(kBlack);
  h1_1->SetLineWidth(3.0);
  h1_2->SetLineColor(kRed);
  h1_2->SetLineWidth(3.0);

  //h1_1->SetLineWidth(3.0);
  //h1_1->SetMarkerStyle(21);

  h1_1->SetMinimum(0.0);
  h1_1->SetMaximum(40.0);

  h1_1->Draw();
  h1_2->Draw("sames");

  //h1_1->GetXaxis()->SetTitle("#Delta Transmittance lenght, mm");
  //h1_1->GetXaxis()->SetTitle("Transmittance lenght (@ 400 nm), mm");
  h1_1->GetXaxis()->SetTitle("Refractive index (@ 400 nm)");

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_1, "Up (A)","l");
  leg->AddEntry(h1_2, "Down (B)","l");
  //leg->AddEntry(h1_1, "From xml","l");
  //leg->AddEntry(h1_2, "Retrieved","l");
  leg->Draw();

  return 0;
}
