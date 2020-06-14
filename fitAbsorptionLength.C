/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Nov 27 22:23:08 2017 +0100                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/
//my
#include "libxmlarichdata.h"

#if !defined(__CLING__)
#include "libxmlarichdata.h"
#else 
//my
#include "plots.C"
#include "readAerogelInfoMap.C"
#include "refractiveIndexSilicaAerogel.C"
#include "rayleighScatteringCrossSection.C"
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
using namespace xmlarichdata;

namespace xmlarichdata{

//Usual execution
const Int_t raunKey = 0;
//Execution in cm
//const Int_t raunKey = 1;

Double_t fitFunction(Double_t *x, Double_t *par){
  Double_t lambdaMin = par[5];
  Double_t lambdaMax = par[6];
  //Double_t lam = 400;
  //cout<<"rayleighScatteringCrossSection "<<rayleighScatteringCrossSection( 40, 400, 1.0463)<<endl;
  if( x[0] < lambdaMin )
    return 0;
  if( x[0] > lambdaMax )
    return 0;
  Double_t xx = (x[0] - lambdaMin)/10.0;
  if(raunKey == 0)
    return par[0] + xx*par[1] + xx*xx*par[2] + xx*xx*xx*par[3] + xx*xx*xx*xx*par[4];
  if(raunKey == 1)
    return x[0]*x[0]*x[0]*x[0]*par[4];
  //return par[0] + x[0]*par[1] + x[0]*x[0]*par[2] + x[0]*x[0]*x[0]*par[3] + x[0]*x[0]*x[0]*x[0]*par[4];
  //return xx*xx*xx*xx*par[4];
  //Double_t d  = par[4];
  //TString type = "A";
  //Double_t n = refractiveIndexSilicaAerogel(type,xx);
  //return 1.0/rayleighScatteringCrossSection( d, xx, n) + par[0] + x[0]*par[1];
  //return par[0] + x[0]*par[1] + x[0]*x[0]*x[0]*x[0]*par[4];
}

//Double_t fitOtherFunction(Double_t *x, Double_t *par){
//return par[0]*TMath::Exp(par[1]*x[0]) + par[2]*TMath::Exp(par[3]*x[0]);
//return par[0] + x[0]*par[1] + x[0]*x[0]*par[2] + par[3]*TMath::Exp(par[4]*x[0]);
//return par[0] + x[0]*par[1] + x[0]*x[0]*par[2] + par[3]*TMath::Exp(par[4]*x[0]);
//return par[0] + x[0]*par[1] + x[0]*x[0]*par[2] + par[3]*TMath::Exp(-par[4]*(x[0]*x[0] - par[5]*par[5]));
//}

// histOption = "-v"  <--- Transmitance
// histOption = "!-v" <--- Transmitance Length
TF1 *fitAbsorptionLength(TString fileN = "./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root", 
			 TString histN1 = "gr_A001",
			 TString histN2 = "gr_A001_trLength",
			 TString pdfFolder = "./pdfdata/2nd_measurement/",
			 Double_t dX = 2.03){
  
  cout<<"fileN     "<<fileN<<endl
      <<"histN1    "<<histN1<<endl
      <<"histN2    "<<histN2<<endl
      <<"pdfFolder "<<pdfFolder<<endl;
  cout<<"dX        "<<dX<<endl;
  
  TGraph *gr1 = plots( fileN, histN1, pdfFolder, "-v");
  TGraph *gr2 = plots( fileN, histN2, pdfFolder, "!-v");
  
  Double_t* ex = new Double_t [gr2->GetN()];
  Double_t* ey = new Double_t [gr2->GetN()];

  Double_t* cmlam = new Double_t [gr2->GetN()];
  Double_t* cmAbs = new Double_t [gr2->GetN()];

  Double_t lambdaMin = 1000;
  Double_t lambdaMax = 0.0;
  
  Double_t absorbProbMin;
  Double_t absorbProbMax;
  
  for( Int_t i = 0; i < gr2->GetN() ; i++){
    if(raunKey == 0){
      ex[i] = 1;
      ey[i] = gr2->GetY()[i]/200.0;
      if(gr2->GetY()[i]>0.0){
	if(lambdaMin > gr2->GetX()[i]){
	  lambdaMin = gr2->GetX()[i];
	  absorbProbMin = gr2->GetY()[i];
	}
	if(lambdaMax < gr2->GetX()[i]){
	  lambdaMax = gr2->GetX()[i];
	  absorbProbMax = gr2->GetY()[i];
	}
      }
    }
    if(raunKey == 1){
      cmlam[i] = gr2->GetX()[i]*1.0e-7;
      cmAbs[i] = gr2->GetY()[i]/10.0;
      ex[i] = 1.0e-7;
      ey[i] = gr2->GetY()[i]/200.0;
      if(gr2->GetY()[i]>0.0){
	if(lambdaMin > gr2->GetX()[i]*1.0e-7){
	  lambdaMin = gr2->GetX()[i]*1.0e-7;
	  absorbProbMin = gr2->GetY()[i];
	}
	if(lambdaMax < gr2->GetX()[i]*1.0e-7){
	  lambdaMax = gr2->GetX()[i]*1.0e-7;
	  absorbProbMax = gr2->GetY()[i];
	}
      }
    }
  }
  
  cout<<"lambdaMin     = "<<lambdaMin<<endl;
  cout<<"lambdaMax     = "<<lambdaMax<<endl;
  cout<<"absorbProbMin = "<<absorbProbMin<<endl;
  cout<<"absorbProbMax = "<<absorbProbMax<<endl;

  TGraphErrors *grErr;
  if(raunKey == 0)
    grErr = new TGraphErrors( gr2->GetN(), gr2->GetX(), gr2->GetY(), ex, ey);
  if(raunKey == 1)
    grErr = new TGraphErrors( gr2->GetN(), cmlam, cmAbs, ex, ey);
  
  grErr->SetTitle(gr2->GetTitle());
  
  const Int_t npar = 7;
  //pol4                           0    1    2      3       4           5          6
  Double_t inParameters[npar];
  if(raunKey == 0){
    inParameters[0] = 3.0;
    inParameters[1] = 1.0;
    inParameters[2] = 0.04;
    inParameters[3] = 0.003;
    inParameters[4] = -2.5e-05;
    inParameters[5] = lambdaMin;
    inParameters[6] = lambdaMax;
  }
  if(raunKey == 1){
    inParameters[0] = 0.0;
    inParameters[1] = 0.0;
    inParameters[2] = 0.0;
    inParameters[3] = 0.0;
    inParameters[4] = 1.0e+18;
    inParameters[5] = lambdaMin;
    inParameters[6] = lambdaMax;
  }
  //TF1 *prefitf = new TF1( "prefitf", "pol4", lambdaMin, lambdaMax, npar);
  //grErr->Fit("pol1");
  //Access the fit resuts
  //TF1 *prefitf = grErr->GetFunction("pol4");
  //prefitf->GetParameters(inParameters);  
  
  TF1 *fitf = new TF1( "fitf", fitFunction, lambdaMin, lambdaMax, npar);
  fitf->SetParameters(inParameters);
  //fitf->SetParLimits(4,1.0e-30,1.0e-8);
  //fitf->FixParameter(0,absorbProbMin);
  //fitf->FixParameter(1,0.0);
  //fitf->FixParameter(2,0.0);
  //fitf->FixParameter(3,0.0);
  
  fitf->FixParameter(5,lambdaMin);
  fitf->FixParameter(6,lambdaMax);

  TString tCanvaNamec2 = "c2_"; tCanvaNamec2 += histN2;
  TCanvas *c2 = new TCanvas( tCanvaNamec2.Data(), fileN.Data(), 20, 20, 1200, 800);
  c2->SetRightMargin(0.03);
  c2->SetLeftMargin(0.09);
  c2->SetTopMargin(0.09);
  c2->SetBottomMargin(0.09);

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  gPad->SetGridx();
  gPad->SetGridy();

  grErr->Fit("fitf","q");
  cout<<" 0 "<<fitf->GetParameter(0)<<endl
      <<" 1 "<<fitf->GetParameter(1)<<endl 
      <<" 2 "<<fitf->GetParameter(2)<<endl
      <<" 3 "<<fitf->GetParameter(3)<<endl
      <<" 4 "<<fitf->GetParameter(4)<<endl;
  cout<<" 5 "<<fitf->GetParameter(5)<<endl
      <<" 6 "<<fitf->GetParameter(6)<<endl;


  //refractiveIndexSilicaAerogelPrintTestData();

  //grErr->Fit("pol4");

  grErr->SetLineWidth(3.0);
  grErr->SetMarkerStyle(21);

  grErr->Draw("APL");

  if(raunKey == 0){
    grErr->GetXaxis()->SetTitle("#lambda, nm");
    grErr->GetYaxis()->SetTitle("Transmittance lenght, mm");
  }

  if(raunKey == 1){
    grErr->GetXaxis()->SetTitle("#lambda, cm");
    grErr->GetYaxis()->SetTitle("Transmittance lenght, cm");
  }

  //grErr->SetMaximum(50);
  //grErr->SetMinimum(0);

  /////////////////// Abs Prob ///////////////////
  Double_t* xAbsProb = new Double_t [gr2->GetN()];

  for( Int_t i = 0; i < gr2->GetN() ; i++)
    xAbsProb[i] = 100.0*TMath::Exp(-dX*10/fitf->Eval(gr2->GetX()[i]));

  TGraph *grAbsProb = new TGraph(gr2->GetN(),gr2->GetX(),xAbsProb);

  grAbsProb->SetLineWidth(3.0);
  grAbsProb->SetLineColor(kBlack);
  grAbsProb->SetMarkerStyle(21);

  gr1->SetLineWidth(3.0);
  gr1->SetMarkerStyle(1);
  gr1->SetMarkerColor(kRed);
  gr1->SetLineColor(kRed);

  TString tCanvaNamec3 = "c3_"; tCanvaNamec3 += histN1;
  TCanvas *c3 = new TCanvas( tCanvaNamec3.Data(), fileN.Data(), 20, 20, 1200, 800);
  //grAbsProb->Draw("APL");
  c3->SetRightMargin(0.03);
  c3->SetLeftMargin(0.09);
  c3->SetTopMargin(0.09);
  c3->SetBottomMargin(0.09);

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  gPad->SetGridx();
  gPad->SetGridy();

  TMultiGraph *mg = new TMultiGraph("mg",gr1->GetTitle());
  mg->Add(grAbsProb);
  mg->Add(gr1);
  //mg->SetMaximum(600);

  mg->Draw("APL");

  mg->GetXaxis()->SetTitle("#lambda, nm");
  mg->GetYaxis()->SetTitle("Transmittance, %");

  TLegend *leg = new TLegend(0.6,0.3,0.9,0.6,"","brNDC");
  leg->AddEntry(grAbsProb, "Fit","pl");
  leg->AddEntry(gr1, "Data","l");
  leg->Draw();

  /////////////////// Data save ///////////////////
  if(pdfFolder != ""){
    TString pdfFile2 = pdfFolder;
    pdfFile2 += histN2;
    pdfFile2 += "_fit.pdf";
    TString gifFile2 = pdfFolder;
    gifFile2 += histN2;
    gifFile2 += "_fit.gif";
    
    c2->SaveAs(pdfFile2.Data());
    c2->SaveAs(gifFile2.Data());
    
    TString pdfFile1 = pdfFolder;
    pdfFile1 += histN1;
    pdfFile1 += "_fit.pdf";
    TString gifFile1 = pdfFolder;
    gifFile1 += histN1;
    gifFile1 += "_fit.gif";
    
    c3->SaveAs(pdfFile1.Data());
    c3->SaveAs(gifFile1.Data());
  }
  /////////////////////////////////////////////////

  //////////////// Print test val. ////////////////
  cout<<"fitf->Eval(400.0) = "<<fitf->Eval(400.0)<<endl;
  /////////////////////////////////////////////////

  return fitf;
}
}//namespace xmlarichdata{

#ifdef FITABSORPTIONLENGHT_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 6){
    TString fileN = argv[1];
    TString histN1 = argv[2];
    TString histN2 = argv[3];
    TString pdfFolder = argv[4];
    Double_t dX = atof(argv[5]);
    fitAbsorptionLength(fileN,histN1,histN2,pdfFolder,dX);
    return 0;
  }
  fitAbsorptionLength();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef FITABSORPTIONLENGHT_MAIN
