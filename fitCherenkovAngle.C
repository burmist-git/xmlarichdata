/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Thu Jun  7 17:39:28 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "libxmlarichdata.h"
#endif

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TList.h>
#include <TF1.h>
#include <TMath.h>
#include <TMultiGraph.h>
#include <TLegend.h>

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

Double_t fitFunction(Double_t *x, Double_t *par){
  Double_t c1 = par[0];
  Double_t c2 = par[1];
  Double_t A  = par[2];
  Double_t th0 = par[3];     // Mean value of the cherenkov angle
  Double_t sigphot = par[4]; // Single photon resolution
  return c1 + c2*x[0] + A*TMath::Gaus(x[0],th0,sigphot);
}

TF1 *fitCherenkovAngle(){  

  TString fileN1;
  fileN1 = "./ARICHPerformance.root_histo.root";
  TFile *f1 = new TFile(fileN1.Data());
  TString histoName;
  histoName = "h_chK";
  TH1D *h1_1 = (TH1D*)f1->Get(histoName.Data());
  h1_1->SetLineColor(kBlack);
  h1_1->SetLineWidth(3.0);

  const Int_t npar = 5;
  Double_t inParameters[npar];
  Double_t th_min  = 0.20; //Fitting window : value from the left (min) in rad
  Double_t th_max  = 0.32; //Fitting window : value from the right (max) in rad
  Double_t val_min = 30.0; //Fitting window : bin value at the left (min)
  Double_t val_max = 50.0; //Fitting window : bin value at the right (max)

  //c1 + th*c2 + A*Gaus(th,th0,sigphot)
  inParameters[1] = (val_max - val_min)/(th_max - th_min);  //c2
  inParameters[0] = val_max - inParameters[1]*th_max;       //c1
  inParameters[2] = 600.0;                                  //A
  inParameters[3] = 0.265;                                  //th0, rad
  inParameters[4] = 0.016;                                  //sigphot, rad
  
  TF1 *fitf = new TF1( "fitf", fitFunction, th_min, th_max, npar);
  fitf->SetParameters(inParameters);
  fitf->SetParName(0, "c1");
  fitf->SetParName(1, "c2");
  fitf->SetParName(2, "A");
  fitf->SetParName(3, "#theta_{0}");
  fitf->SetParName(4, "#sigma_{photon}");

  TCanvas *c1 = new TCanvas( "c1", "c1", 10, 10, 800, 800);
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

  h1_1->Fit("fitf","","",th_min,th_max);
  cout<<" 0 "<<fitf->GetParameter(0)<<endl
      <<" 1 "<<fitf->GetParameter(1)<<endl 
      <<" 2 "<<fitf->GetParameter(2)<<endl
      <<" 3 "<<fitf->GetParameter(3)<<endl
      <<" 4 "<<fitf->GetParameter(4)<<endl;

  return fitf;
}
