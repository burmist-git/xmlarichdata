/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Apr 15 19:07:31 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/
//my
#include "libxmlarichdata.h"

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
#include <TLegend.h>
#include <TMultiGraph.h>

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

  TGraph *quartz_RefractiveIndex_vs_ev(){

    Double_t ev_Min = 1.5;
    Double_t ev_Max = 5.0;
    Double_t lam_Min = ev_2_lambda_nm(ev_Max);
    Double_t lam_Max = ev_2_lambda_nm(ev_Min);
    cout<<"lam_Min "<<lam_Min<<endl
	<<"lam_Max "<<lam_Max<<endl;
    Int_t nSellmeierQuartz = 200;

    Int_t nP = 21;

    Double_t lam;
    Double_t photon_ene_eV;

    TGraph *gr_SellmeierQuartz = new TGraph();

    for(Int_t i = 0;i<nSellmeierQuartz;i++){
      lam = lam_Min + (lam_Max - lam_Min)*i/(nSellmeierQuartz - 1); 
      gr_SellmeierQuartz->SetPoint(gr_SellmeierQuartz->GetN(),lam,getSellmeierQuartz(lam/1000.0));
    }
    
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetOptStat(kFALSE);    

    TCanvas *c1 = new TCanvas("c1","canva", 10, 10, 800, 800);
    c1->SetFillColor(kWhite);

    gr_SellmeierQuartz->Draw("APL");

    TCanvas *c2 = new TCanvas("c2","canva", 20, 20, 800, 800);
    c2->SetFillColor(kWhite);
    
    TGraph *gr_qri_ev = convert_TGraph_Lambda_vs_pe(gr_SellmeierQuartz);
    gr_qri_ev->Draw("APL");

    TCanvas *c3 = new TCanvas("c3","canva", 30, 30, 800, 800);
    c3->SetFillColor(kWhite);
    

    TGraph *gr_qri_norm_ev = new TGraph();
    for(Int_t i = 0;i<nP;i++){
      photon_ene_eV = ev_Min + (ev_Max - ev_Min)*i/(nP - 1); 
      gr_qri_norm_ev->SetPoint(gr_qri_norm_ev->GetN(),photon_ene_eV,gr_qri_ev->Eval(photon_ene_eV));
    }

    gr_qri_norm_ev->Draw("APL");

    gr_qri_norm_ev->GetXaxis()->SetTitle("h#nu, eV");
    gr_qri_norm_ev->GetYaxis()->SetTitle("Refractive index");

    TF1 *f1 = new TF1("f1","1239.84/x", 250.0, 830.0);
    f1->GetName();
    TGaxis *axis = new TGaxis( 1.5, 1.45, 5.0, 1.45, "f1", 510, "L+", 1);
    axis->SetLabelSize(0.03);
    //axis->SetLabelColor(kRed);
    axis->SetTitle("#lambda, nm");
    axis->Draw();

    //cout<<"convert_TGraph_Lambda_vs_pe"<<endl;
    print_TGraph_info(gr_qri_norm_ev, "basf2");
    
    return 0;
  }
  
}//namespace xmlarichdata{
