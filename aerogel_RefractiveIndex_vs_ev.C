/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue Jun  5 19:54:05 JST 2018                                         *
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

  TGraph *aerogel_RefractiveIndex_vs_ev(TString type = "A", Double_t dn_at_405nm = 0.0){

    Double_t ev_Min = 1.5;
    Double_t ev_Max = 5.0;
    Double_t lam_Min = ev_2_lambda_nm(ev_Max);
    Double_t lam_Max = ev_2_lambda_nm(ev_Min);
    Int_t nSellmeierAerogel = 200;

    Int_t nP = 21;

    Double_t lam;
    Double_t photon_ene_eV;

    TGraph *gr_SellmeierAerogel = new TGraph();

    for(Int_t i = 0;i<nSellmeierAerogel;i++){
      lam = lam_Min + (lam_Max - lam_Min)*i/(nSellmeierAerogel - 1); 
      gr_SellmeierAerogel->SetPoint(gr_SellmeierAerogel->GetN(),lam,(refractiveIndexSilicaAerogel( type, lam) + dn_at_405nm));
    }
    
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetOptStat(kFALSE);    

    TCanvas *c1 = new TCanvas("c1","canva", 10, 10, 800, 800);
    c1->SetFillColor(kWhite);

    gr_SellmeierAerogel->Draw("APL");

    TCanvas *c2 = new TCanvas("c2","canva", 20, 20, 800, 800);
    c2->SetFillColor(kWhite);
    
    TGraph *gr_ari_ev = convert_TGraph_Lambda_vs_pe(gr_SellmeierAerogel);
    gr_ari_ev->Draw("APL");

    TCanvas *c3 = new TCanvas("c3","canva", 30, 30, 800, 800);
    c3->SetFillColor(kWhite);
    
    TGraph *gr_ari_norm_ev = new TGraph();
    for(Int_t i = 0;i<nP;i++){
      photon_ene_eV = ev_Min + (ev_Max - ev_Min)*i/(nP - 1); 
      gr_ari_norm_ev->SetPoint(gr_ari_norm_ev->GetN(),photon_ene_eV,gr_ari_ev->Eval(photon_ene_eV));
    }

    gr_ari_norm_ev->Draw("APL");

    gr_ari_norm_ev->GetXaxis()->SetTitle("h#nu, eV");
    gr_ari_norm_ev->GetYaxis()->SetTitle("Refractive index");

    TF1 *f1 = new TF1("f1","1239.84/x", 247.97, 826.56);
    f1->GetName();
    TGaxis *axis = new TGaxis( 1.5, 1.043, 5.0, 1.043, "f1", 510, "L+", 1);
    axis->SetLabelSize(0.03);
    //axis->SetLabelColor(kRed);
    axis->SetTitle("#lambda, nm");
    axis->Draw();


    //cout<<"convert_TGraph_Lambda_vs_pe"<<endl;
    print_TGraph_info(gr_ari_norm_ev, "basf2");

    refractiveIndexSilicaAerogelPrintTestData();

    return gr_ari_norm_ev;
  }
  
}//namespace xmlarichdata{
