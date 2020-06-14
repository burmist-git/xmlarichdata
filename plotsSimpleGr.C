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

Int_t plotsSimpleGr(){

  TString fileN  = "./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root";
  TString histN1 = "gr_A_TrL_vs_DataTrL";
  TString histN2 = "gr_B_TrL_vs_DataTrL";

  TFile *f1 = new TFile(fileN.Data());

  TGraph *gr_1 = (TGraph*)f1->Get(histN1.Data());
  TGraph *gr_2 = (TGraph*)f1->Get(histN2.Data());

  gr_1->SetTitle("");
  gr_2->SetTitle("");

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

  gr_1->SetLineColor(kBlack);
  gr_1->SetLineWidth(3.0);
  gr_1->SetMarkerColor(kBlack);
  gr_1->SetMarkerStyle(22);
  gr_1->SetMarkerSize(1);
  gr_2->SetLineColor(kRed);
  gr_2->SetLineWidth(3.0);
  gr_2->SetMarkerColor(kRed);
  gr_2->SetMarkerStyle(22);
  gr_2->SetMarkerSize(1);

  //h1_1->SetLineWidth(3.0);
  //h1_1->SetMarkerStyle(21);

  //gr_1->SetMinimum(0.0);
  //gr_1->SetMaximum(25.0);

  gr_1->Draw("AP");
  //gr_2->Draw("AP");

  gr_1->GetXaxis()->SetTitle("Transmittance lenght, mm");
  gr_1->GetYaxis()->SetTitle("Transmittance lenght (retrieved), mm");

  gr_2->GetXaxis()->SetTitle("Transmittance lenght, mm");
  gr_2->GetYaxis()->SetTitle("Transmittance lenght (retrieved), mm");

  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_1, "Up (A)","l");
  leg->AddEntry(gr_2, "Down (B)","l");
  leg->Draw();

  return 0;
}
