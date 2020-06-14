/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue Apr 3 17:30:57 2018 +0200                                        *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
#ifdef __CLING__
#include "convert_TrLength_vs_Lambda_2_TrLength_vs_pe.C"
#endif

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TLine.h>
#include <TMath.h>
#include <TF1.h>

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
  
  TGraph *hapdQE(){

    TString fileInFileName = "./qe_vs_lam.dat";
    
    if (FILE *file = fopen(fileInFileName.Data(), "r")) {
      fclose(file);
    } else {
      cout<<" ERROR --> file : "<<fileInFileName<<" not found"<<endl;
    assert(0);
    }   
    
    TGraph * gr = new TGraph(fileInFileName.Data());
    gr->SetName("Q.E.");
    gr->SetTitle("Q.E.");
    
    gr->SetLineWidth(3.0);
    gr->SetLineColor(kBlack);
    gr->SetMarkerStyle(21);
    gr->SetMarkerColor(kBlack);
    gStyle->SetPalette(1);
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetStatColor(kWhite);
    //gStyle->SetOptStat(kFALSE);
    
    TCanvas *c1 = new TCanvas("c1","plots",10,10,1200,800);
    c1->Clear();
    c1->SetFillColor(kWhite);
    c1->GetPad(0)->SetLeftMargin(0.1);
    c1->GetPad(0)->SetRightMargin(0.04);
    c1->GetPad(0)->SetTopMargin(0.07);
    c1->GetPad(0)->SetBottomMargin(0.1);
    
    gr->GetXaxis()->SetTitle("#lambda, nm");
    gr->GetYaxis()->SetTitle("Relative Q.E. ");
    
    gr->Draw("APL");
    
    TCanvas *c2 = new TCanvas("c2","plots",20,20,1200,800);
    c2->GetName();
    // Transmision lenght vs photon energy (p.e.)  
    TGraph *geer = convert_TrLength_vs_Lambda_2_TrLength_vs_pe(gr);
    geer->SetLineWidth(3.0);
    geer->SetMarkerStyle(21);
    geer->Draw("APL");
    
    return gr;
    
  }
}//namespace xmlarichdata {
