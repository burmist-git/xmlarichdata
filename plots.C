/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Oct 15 16:09:59 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
#ifdef __CLING__
#include "convert_TrLength_vs_Lambda_2_TrLength_vs_pe.C"
#endif

//my
//#if !defined(__CLING__)
//#include "libxmlarichdata.h"
//#else 
//#include "convert_TrLength_vs_Lambda_2_TrLength_vs_pe.C"
//#endif

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLine.h>

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
using namespace xmlarichdata;

namespace xmlarichdata{

// histOption = "-v"  <--- Transmitance
// histOption = "!-v" <--- Transmitance Length
TGraph *plots(TString fileN = "./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root", 
	      TString histN = "gr_A001", 
	      TString pdfFolder = "./pdfdata/2nd_measurement/",
	      TString histOption = "-v"){

  cout<<"fileN     "<<fileN<<endl
      <<"histN     "<<histN<<endl
      <<"pdfFolder "<<pdfFolder<<endl;

  TFile *f1 = new TFile(fileN.Data());

  TGraph *h1_1 = (TGraph*)f1->Get(histN.Data());
  //h1_1->Rebin(4);

  TString tCanvaName = "c1_"; tCanvaName += histN;

  TCanvas *c1 = new TCanvas(tCanvaName.Data(),fileN.Data(),10,10,1200,800);
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

  /*
  h1_1->SetLineColor(kBlack);
  h1_1->SetLineWidth(3.0);
  */

  h1_1->SetLineWidth(3.0);
  h1_1->SetMarkerStyle(21);

  h1_1->SetMinimum(0.0);
  if(histOption=="-v")
    h1_1->SetMaximum(100.0);
  else
    h1_1->SetMaximum(500.0);

  h1_1->Draw("APL");

  h1_1->GetXaxis()->SetTitle("#lambda, nm");
  if(histOption=="-v")
    h1_1->GetYaxis()->SetTitle("Transmittance, %");
  else
    h1_1->GetYaxis()->SetTitle("Transmittance lenght, mm");
  //h1_1->GetXaxis()->SetTitle("Amplitude, V");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
  //h1_1->GetXaxis()->CenterTitle();
  //h1_1->GetXaxis()->SetTitleSize(0.05);
  //h1_1->GetXaxis()->SetTitleOffset(0.75);

  /*
  h1_1->Fit("gaus");
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_1, "Without corrections","l");
  leg->AddEntry(h1_2, "With corrections","l");
  leg->Draw();
  */

  if(pdfFolder != ""){
    TString pdfFile = pdfFolder;
    pdfFile += histN;
    pdfFile += ".pdf";
    TString gifFile = pdfFolder;
    gifFile += histN;
    gifFile += ".gif";
    c1->SaveAs(pdfFile.Data());
    c1->SaveAs(gifFile.Data());
  }

  TString tCanvaC2Name = "c2_"; tCanvaC2Name += histN;
  TCanvas *c2 = new TCanvas(tCanvaC2Name.Data(),fileN.Data(),20,20,1200,800);
  cout<<c2->GetDISPLAY()<<endl;

  // Transmision lenght vs photon energy (p.e.)  
  TGraph *geer = convert_TrLength_vs_Lambda_2_TrLength_vs_pe(h1_1);
  geer->SetLineWidth(3.0);
  geer->SetMarkerStyle(21);

  geer->Draw("APL");

  geer->GetXaxis()->SetTitle("photon energy, eV");
  geer->GetYaxis()->SetTitle("Transmittance lenght, mm");

  if(histOption=="!-v"){
    Double_t ymax; 
    //ymax = 820.907;
    //TLine *ln_1 = new TLine(1.5, -5,1.5, ymax);
    //ln_1->SetLineWidth(3.0);
    //ln_1->Draw("same");
    if(histN.Contains("A")){
      cout<<"Info : type A - upstream aerogel (n = 1.045)"<<endl;
    }
    if(histN.Contains("B")){
      cout<<"Info : type B - downstream aerogel (n = 1.055)"<<endl;
    }
    if(histN.Contains("A"))
      ymax = 177.406;
    if(histN.Contains("B"))
      ymax = 137.982;
    TLine *ln_2 = new TLine(2.2, -5,2.2, ymax);
    ln_2->SetLineWidth(3.0);
    ln_2->Draw("same");
    if(histN.Contains("A"))
      ymax = 58.758;
    if(histN.Contains("B"))
      ymax = 45.700;
    TLine *ln_3 = new TLine(2.9, -5,2.9, ymax);
    ln_3->SetLineWidth(3.0);
    ln_3->Draw("same");
    if(histN.Contains("A"))
      ymax = 24.743;
    if(histN.Contains("B"))
      ymax = 19.244;
    TLine *ln_4 = new TLine(3.6, -5,3.6, ymax);
    ln_4->SetLineWidth(3.0);
    ln_4->Draw("same");
    if(histN.Contains("A"))
      ymax = 12.155;
    if(histN.Contains("B"))
      ymax = 9.454;
    TLine *ln_5 = new TLine(4.3, -5,4.3, ymax);
    ln_5->SetLineWidth(3.0);
    ln_5->Draw("same");
    if(histN.Contains("A"))
      ymax = 6.649;
    if(histN.Contains("B"))
      ymax = 5.171;
    TLine *ln_6 = new TLine(5.0, -5,5.0, ymax);
    ln_6->SetLineWidth(3.0);
    ln_6->Draw("same");
    //--------------------------------------//
    // n = 1.045                            //
    // type A - (upstream aerogel)          //
    // <value energy="1.5">820.907 </value> //
    // <value energy="2.2">177.406 </value> //
    // <value energy="2.9">58.758  </value> //
    // <value energy="3.6">24.743  </value> //
    // <value energy="4.3">12.155  </value> //
    // <value energy="5.0">6.649   </value> //
    //--------------------------------------//
    // n = 1.055                            //
    // type B - (downstream aerogel)        //
    // <value energy="1.5">638.483 </value> //
    // <value energy="2.2">137.982 </value> //
    // <value energy="2.9">45.700  </value> //
    // <value energy="3.6">19.244  </value> //
    // <value energy="4.3">9.454   </value> //
    // <value energy="5.0">5.171   </value> //
    //--------------------------------------//
  }
  
  return h1_1;
}
}//namespace xmlarichdata {

#ifdef PLOTS_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 5){
    TString fileN = argv[1];
    TString histN = argv[2];
    TString pdfFolder = argv[3];
    TString histOption = argv[4];
    plots(fileN,histN,pdfFolder,histOption);
    return 0;
  }
  plots();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef PLOTS_MAIN
