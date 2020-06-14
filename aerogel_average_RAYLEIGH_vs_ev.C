/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sat Jun  9 22:49:10 JST 2018                                         *
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

  TGraph *aerogel_average_RAYLEIGH_vs_ev(TString type = "A"){

    TString histName;
    TString histNameL;
    Double_t dX;

    Double_t ev_Min = 1.5;
    Double_t ev_Max = 5.0;
    Double_t ev_700nm = lambda_nm_2_ev(700);

    Double_t lam_Min = ev_2_lambda_nm(ev_Max);
    Double_t lam_Max = ev_2_lambda_nm(ev_Min);

    cout<<"lam_Min (5.0 eV) "<<lam_Min<<endl
	<<"lam_Max (1.5 eV) "<<lam_Max<<endl
	<<"700 nm = "<<ev_700nm<<endl;

    TGraph *grOld = new TGraph();
    if(type == "A"){
      //<value energy="1.5">820.907</value>
      //<value energy="2.2">177.406</value>
      //<value energy="2.9">58.758</value>
      //<value energy="3.6">24.743</value>
      //<value energy="4.3">12.155</value>
      //<value energy="5.0">6.649</value>
      grOld->SetPoint(grOld->GetN(),1.5,820.907);
      grOld->SetPoint(grOld->GetN(),2.2,177.406);
      grOld->SetPoint(grOld->GetN(),2.9,58.758);
      grOld->SetPoint(grOld->GetN(),3.6,24.743);
      grOld->SetPoint(grOld->GetN(),4.3,12.155);
      grOld->SetPoint(grOld->GetN(),5.0,6.649);
      histName = "gr_A_L_norm";
      histNameL = "gr_A_L_norm";
      dX = 1.96;
    }
    if(type == "B"){
      histName = "gr_B_L_norm";
      histNameL = "gr_B_L_norm";
      dX = 1.97;
      //<value energy="1.5">638.483</value>
      //<value energy="2.2">137.982</value>
      //<value energy="2.9">45.700</value>
      //<value energy="3.6">19.244</value>
      //<value energy="4.3">9.454</value>
      //<value energy="5.0">5.171</value>
      grOld->SetPoint(grOld->GetN(),1.5,638.483);
      grOld->SetPoint(grOld->GetN(),2.2,137.982);
      grOld->SetPoint(grOld->GetN(),2.9,45.700);
      grOld->SetPoint(grOld->GetN(),3.6,19.244);
      grOld->SetPoint(grOld->GetN(),4.3,9.454);
      grOld->SetPoint(grOld->GetN(),5.0,5.171);
    }
    grOld->SetLineWidth(3.0);
    grOld->SetLineColor(kRed);
    grOld->SetMarkerStyle(20);
    grOld->SetMarkerColor(kRed);
    //////////////    data end    /////////////

    TGraph *gr_norm_ev = aerogel_RAYLEIGH_vs_ev(histName, histNameL, dX);

    gStyle->SetPalette(1);
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetStatColor(kWhite);
    //gStyle->SetOptStat(kFALSE);

    TCanvas *c3 = new TCanvas("c3","Canva3",30,30,800,800);
    c3->SetRightMargin(0.03);
    c3->SetLeftMargin(0.09);
    c3->SetTopMargin(0.09);
    c3->SetBottomMargin(0.09);
    //gr_norm_ev->GetXaxis()->SetTitle("h#nu, eV");
    //gr_norm_ev->SetTitle("gr_norm_ev");
    //gr_norm_ev->Draw("APL");
    gr_norm_ev->SetLineWidth(3.0);
    gr_norm_ev->SetLineColor(kBlack);
    gr_norm_ev->SetMarkerStyle(20);
    gr_norm_ev->SetMarkerColor(kBlack);
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(gr_norm_ev);
    mg->Add(grOld);
    //mg->SetTitle("gr_norm_ev");
    mg->Draw("APL");
    mg->GetXaxis()->SetTitle("h#nu, eV");
    if(type == "A")
      mg->GetYaxis()->SetTitle("Rayleigh scattering length (Type : A), mm");
    if(type == "B")
      mg->GetYaxis()->SetTitle("Rayleigh scattering length (Type : B), mm");
    TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
    leg->AddEntry(gr_norm_ev, "Update","lp");
    leg->AddEntry(grOld, "Old","lp");
    leg->Draw();
    gPad->SetGridx();
    gPad->SetGridy();
    /////////////////////////////////////////////////////////////////////////////////////
    TF1 *f3 = new TF1("f3","1239.84/x", 247.968, 826.562);
    //TF1 *f2 = new TF1("f2","1239.84/x", 1.5, 5.0);
    f3->GetName();
    //TGaxis *axis = new TGaxis( 247.968, -10.0, 826.562, -10.0, "f1", 510, "L+", 1);
    TGaxis *axisf3 = new TGaxis( 1.5, -50, 5.0, -50, "f3", 510, "L+", 1);
    axisf3->SetLabelSize(0.03);
    //axis->SetLabelColor(kRed);
    axisf3->SetTitle("#lambda, nm");
    //axisf2->SetTitle("h#nu, eV");
    axisf3->Draw();
    /////////////////////////////////////////////////////////////////////////////////////

    //print_TGraph_info(gr_norm_ev, "basf2");   
    
    return gr_norm_ev;
  }

  TGraph *aerogel_RAYLEIGH_vs_ev(TString histName, TString histNameL, Double_t dX){

    Double_t ev_Min = 1.5;
    Double_t ev_Max = 5.0;
    Double_t ev_700nm = lambda_nm_2_ev(700);
    Double_t photon_ene_eV;
    Double_t lam;
    Double_t lam_Min = ev_2_lambda_nm(ev_Max);
    Double_t lam_Max = ev_2_lambda_nm(ev_Min);

    cout<<"lam_Min (5.0 eV) "<<lam_Min<<endl
	<<"lam_Max (1.5 eV) "<<lam_Max<<endl
	<<"700 nm = "<<ev_700nm<<endl;

    ////////////// data beginning /////////////
    TString fileN;
    fileN = "./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root";
    TFile *ff1 = new TFile(fileN.Data());
    ///////////////////////////////////////////  

    TGraph *gr = (TGraph*)ff1->Get(histNameL.Data());

    /////////////// Fit beginning /////////////
    TF1 *ff = fitAbsorptionLength( fileN, histName, histNameL, "", dX);
    ff->SetParameter(6,lam_Max);
    ///////////////////////////////////////////

    TGraph *gr_full = new TGraph();

    Int_t nn = 200;
    for(Int_t i = 0; i< nn;i++){
      lam = lam_Min + (lam_Max - lam_Min)*i/(nn - 1);
      if(lam>=700){
	gr_full->SetPoint(gr_full->GetN(),lam,ff->Eval(lam));
      }
      else{
	gr_full->SetPoint(gr_full->GetN(),lam,gr->Eval(lam));
      }
    }

    Int_t nP = 21;
    TGraph *gr_ev = convert_TGraph_Lambda_vs_pe(gr_full);

    TGraph *gr_norm_ev = new TGraph();
    for(Int_t i = 0;i<nP;i++){
      photon_ene_eV = ev_Min + (ev_Max - ev_Min)*i/(nP - 1);
      gr_norm_ev->SetPoint(gr_norm_ev->GetN(),photon_ene_eV,gr_ev->Eval(photon_ene_eV));
    }

    gStyle->SetPalette(1);
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetStatColor(kWhite);
    //gStyle->SetOptStat(kFALSE);

    TCanvas *c1 = new TCanvas("c1","Canva1",10,10,800,800);
    c1->SetRightMargin(0.03);
    c1->SetLeftMargin(0.09);
    c1->SetTopMargin(0.09);
    c1->SetBottomMargin(0.09);
    gr_full->GetXaxis()->SetTitle("#lambda, nm");
    gr_full->SetTitle("gr_full");
    gr_full->Draw("AP");
    /////////////////////////////////////////////////////////////////////////////////////
    //TF1 *f1 = new TF1("f1","1239.84/x", 247.968, 826.562);
    TF1 *f1 = new TF1("f1","1239.84/x", 1.5, 5.0);
    f1->GetName();
    TGaxis *axis = new TGaxis( 247.968, -50.0, 826.562, -50.0, "f1", 510, "L+", 1);
    //TGaxis *axis = new TGaxis( 1.5, 1.045, 5.0, 1.045, "f1", 510, "L+", 1);
    axis->SetLabelSize(0.03);
    //axis->SetLabelColor(kRed);
    //axis->SetTitle("#lambda, nm");
    axis->SetTitle("h#nu, eV");
    axis->Draw();
    /////////////////////////////////////////////////////////////////////////////////////

    TCanvas *c2 = new TCanvas("c2","Canva2",20,20,800,800);
    c2->SetRightMargin(0.03);
    c2->SetLeftMargin(0.09);
    c2->SetTopMargin(0.09);
    c2->SetBottomMargin(0.09);
    gr_ev->GetXaxis()->SetTitle("h#nu, eV");
    gr_ev->SetTitle("gr_ev");
    gr_ev->Draw("APL");
    /////////////////////////////////////////////////////////////////////////////////////
    TF1 *f2 = new TF1("f2","1239.84/x", 247.968, 826.562);
    //TF1 *f2 = new TF1("f2","1239.84/x", 1.5, 5.0);
    f2->GetName();
    //TGaxis *axis = new TGaxis( 247.968, -10.0, 826.562, -10.0, "f1", 510, "L+", 1);
    TGaxis *axisf2 = new TGaxis( 1.5, -50, 5.0, -50, "f2", 510, "L+", 1);
    axisf2->SetLabelSize(0.03);
    //axis->SetLabelColor(kRed);
    axisf2->SetTitle("#lambda, nm");
    //axisf2->SetTitle("h#nu, eV");
    axisf2->Draw();
    /////////////////////////////////////////////////////////////////////////////////////

    TCanvas *ctot = new TCanvas("ctot","CanvaTot",30,30,800,800);
    ctot->SetRightMargin(0.03);
    ctot->SetLeftMargin(0.09);
    ctot->SetTopMargin(0.09);
    ctot->SetBottomMargin(0.09);
    gr_norm_ev->SetLineWidth(3.0);
    gr_norm_ev->SetLineColor(kBlack);
    gr_norm_ev->SetMarkerStyle(20);
    gr_norm_ev->SetMarkerColor(kBlack);
    gr_norm_ev->GetXaxis()->SetTitle("h#nu, eV");
    //gr_norm_ev->SetTitle("gr_norm_ev");
    gr_norm_ev->SetTitle(gr->GetTitle());
    gr_norm_ev->Draw("APL");
    /////////////////////////////////////////////////////////////////////////////////////
    TF1 *f3 = new TF1("f3","1239.84/x", 247.968, 826.562);
    //TF1 *f3 = new TF1("f3","1239.84/x", 1.5, 5.0);
    f3->GetName();
    //TGaxis *axis = new TGaxis( 247.968, -10.0, 826.562, -10.0, "f3", 510, "L+", 1);
    TGaxis *axisf3 = new TGaxis( 1.5, -50, 5.0, -50, "f3", 510, "L+", 1);
    axisf3->SetLabelSize(0.03);
    //axis->SetLabelColor(kRed);
    axisf3->SetTitle("#lambda, nm");
    //axisf2->SetTitle("h#nu, eV");
    axisf3->Draw();
    /////////////////////////////////////////////////////////////////////////////////////

    print_TGraph_info(gr_norm_ev, "basf2");   
    
    return gr_norm_ev;

  }
  
}//namespace xmlarichdata{
