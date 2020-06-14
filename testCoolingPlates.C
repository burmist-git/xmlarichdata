/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue May  1 12:27:24 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <vector>

//root
#include <TVector2.h>
#include <TPolyLine.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TText.h>
#include <TMath.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCrown.h>
#include <TArc.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TPad.h>
#include <TString.h>
#include <TFile.h>
#include <TAxis.h>
#include <TVector2.h>
#include <TImage.h>
#include <TH2Poly.h>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{

  void testCoolingPlates(){

    TString lineDrawOpt = "drawLine";

    TImage *img = TImage::Open("./testCoolingPlates.png");
    img->SetConstRatio(kFALSE);

    TString histTitle = "testCoolingPlates";
    TString histName = "testCoolingPlates";
    TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
    c1->SetTitle(histTitle.Data());
    c1->SetName(histName.Data());
    c1->SetRightMargin(0.12);
    c1->SetLeftMargin(0.12);
    c1->SetTopMargin(0.1);
    c1->SetBottomMargin(0.15);

    double envelopeR_min = 435;
    double envelopeR_max = 1132;
    Double_t frameXmin = -1140;
    Double_t frameXmax =  1140;
    Double_t frameYmin = -1140;
    Double_t frameYmax =  1140;    

    TH2F *frame;
    frame = new TH2F( "h2", "h2", 40, frameXmin, frameXmax,40, frameYmin, frameYmax);
    frame->GetXaxis()->SetTitle("x (mm)");
    frame->GetYaxis()->SetTitle("y (mm)");
    frame->GetXaxis()->CenterTitle();
    frame->GetYaxis()->CenterTitle();
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->SetStats(kFALSE);
    frame->SetTitle("");
    frame->Draw();
    img->Draw("same");

    TH2Poly *h2poly = new TH2Poly();
    vector<TGraph*> m_verticesGraphV;
    vector<TGraph*> m_additionalGraphV;
    vector<TLine*> m_additionalLineV;
    double normalisationV = 1.0;
    getTestCoolingPlates( h2poly, m_verticesGraphV, "h2poly", "h2poly", frameXmin, frameXmax, frameYmin,  frameYmax, normalisationV);
    getAdditionalGraphV_and_LineV_for_Plot(m_additionalGraphV, m_additionalLineV, envelopeR_min, envelopeR_max, 0);

    //ZCOLOT text same
    h2poly->Draw("same");

    //cout<<"m_verticesGraphV.size() "<<m_verticesGraphV.size()<<endl;
    //for (unsigned i=0; i<m_verticesGraphV.size(); i++)
    //m_verticesGraphV[i]->Draw("same");

    if(lineDrawOpt == "drawLine"){

      for (unsigned i=0; i<m_verticesGraphV.size(); i++)
	m_verticesGraphV.at(i)->Draw("same");

      for (unsigned i=0; i<m_additionalGraphV.size(); i++)
	m_additionalGraphV.at(i)->Draw("same");

      for (unsigned i=0; i<m_additionalLineV.size(); i++)
	m_additionalLineV.at(i)->Draw("same");

    }


  }

  void getTestCoolingPlates( TH2Poly *h2poly, 
			     vector<TGraph*> &m_verticesGraphV, 
			     TString h2_name, 
			     TString h2_title, 
			     double frameXmin, 
			     double frameXmax, 
			     double frameYmin,  
			     double frameYmax,
			     double normalisationV) {
    
    //Single pieces
    //Double_t box_lx  = 240;
    //Double_t box_ly  = 150;
    //Double_t rho1    = 900;
    //Double_t phi1    = 100.5;
    Double_t box_lx  = 304.8/normalisationV;
    Double_t box_ly  = 95.3/normalisationV;
    Double_t rho1    = 970/normalisationV;
    //Double_t phi1    = 30;
    Double_t phi1    = 11.25;
    //Two pieces
    //Double_t box_lx2 = 140;
    //Double_t box_ly2 = 150;
    //Double_t rho2    = 720;
    //Double_t phi2    = 43.0;
    //Two pieces
    Double_t box_lx3 = 100/normalisationV;
    Double_t box_ly3 = 150/normalisationV;
    Double_t rho3    = 890/normalisationV;
    Double_t phi3    = 43.0;
    //Single pieces
    //Double_t box_lx2 = 240;
    //Double_t box_ly2 = 150;
    //Double_t rho2    = 720;
    //Double_t phi2    = 43.0;
    Double_t box_lx2 = box_lx;
    Double_t box_ly2 = box_ly;
    Double_t rho2    = rho1;
    //Double_t phi2    = 330;
    Double_t phi2    = 360.0 - 28.125;

    const Int_t nCoolingPoint = 500;
    Double_t rCoolingTorus_min = 705/normalisationV;
    Double_t rCoolingTorus_max = 877/normalisationV;

    const Int_t n = 5;
    Double_t x1[n] = { rho1-box_lx/2.0,  rho1+box_lx/2.0,  rho1+box_lx/2.0, rho1-box_lx/2.0, rho1-box_lx/2.0};
    Double_t y1[n] = {      box_ly/2.0,       box_ly/2.0,      -box_ly/2.0,     -box_ly/2.0,      box_ly/2.0};

    Double_t x2[n] = { rho2-box_lx/2.0, rho2+box_lx2/2.0, rho2+box_lx2/2.0, rho2-box_lx/2.0, rho2-box_lx/2.0};
    Double_t y2[n] = {      box_ly/2.0,      box_ly2/2.0,     -box_ly2/2.0,     -box_ly/2.0,     box_ly2/2.0};

    Double_t x3[n] = {        rho3, rho3+box_lx3, rho3+box_lx3,         rho3,        rho3};
    Double_t y3[n] = { box_ly3/2.0,  box_ly3/2.0, -box_ly3/2.0, -box_ly3/2.0, box_ly3/2.0};

    Double_t xnew[n];
    Double_t ynew[n];

    Double_t xCoolingTorus_min[nCoolingPoint];
    Double_t yCoolingTorus_min[nCoolingPoint];
    Double_t xCoolingTorus_max[nCoolingPoint];
    Double_t yCoolingTorus_max[nCoolingPoint];

    Double_t xpold;
    Double_t ypold;

    Int_t i = 0;

    //h2poly = new TH2Poly( h2_name.Data(), h2_title.Data(), frameXmin, frameXmax, frameYmin,  frameYmax);

    h2poly->SetName(h2_name.Data());
    h2poly->SetTitle(h2_title.Data());
    //
    for(i = 0;i<n;i++){
      xpold = x1[i];
      ypold = y1[i];
      TVector2 v(xpold,ypold);
      TVector2 vrot;
      vrot = v.Rotate(phi1*TMath::Pi()/180.0);
      xnew[i] = vrot.X();
      ynew[i] = vrot.Y();
    }
    h2poly->AddBin(n,xnew,ynew);
    TGraph *gr1 = new TGraph(n,xnew,ynew);
    m_verticesGraphV.push_back(gr1);
    //
    for(i = 0;i<n;i++){
      xpold = x2[i];
      ypold = y2[i];
      TVector2 v(xpold,ypold);
      TVector2 vrot;
      vrot = v.Rotate(phi2*TMath::Pi()/180.0);
      xnew[i] = vrot.X();
      ynew[i] = vrot.Y();
    }
    h2poly->AddBin(n,xnew,ynew);
    TGraph *gr2 = new TGraph(n,xnew,ynew);
    m_verticesGraphV.push_back(gr2);
    //
    for(i = 0;i<n;i++){
      xpold = x3[i];
      ypold = y3[i];
      TVector2 v(xpold,ypold);
      TVector2 vrot;
      vrot = v.Rotate(phi3*TMath::Pi()/180.0);
      xnew[i] = vrot.X();
      ynew[i] = vrot.Y();
    }
    //h2poly->AddBin(n,xnew,ynew);
    //TGraph *gr3 = new TGraph(n,xnew,ynew);
    //m_verticesGraphV.push_back(gr3);


    for(int ii = 0; ii<nCoolingPoint;ii++){
      TVector2 vmin(rCoolingTorus_min,0);
      TVector2 vminrot;
      vminrot = vmin.Rotate(360.0/(nCoolingPoint - 1)*ii*TMath::Pi()/180.0);
      TVector2 vmax(rCoolingTorus_max,0);
      TVector2 vmaxrot;
      vmaxrot = vmax.Rotate(360.0/(nCoolingPoint - 1)*ii*TMath::Pi()/180.0);
      xCoolingTorus_min[ii] = vminrot.X();
      yCoolingTorus_min[ii] = vminrot.Y();
      xCoolingTorus_max[ii] = vmaxrot.X();
      yCoolingTorus_max[ii] = vmaxrot.Y();
    }
    TGraph *gr_CoolingTorus_min = new TGraph(nCoolingPoint,xCoolingTorus_min,yCoolingTorus_min);
    m_verticesGraphV.push_back(gr_CoolingTorus_min);
    TGraph *gr_CoolingTorus_max = new TGraph(nCoolingPoint,xCoolingTorus_max,yCoolingTorus_max);
    m_verticesGraphV.push_back(gr_CoolingTorus_max);

    for (unsigned i=0; i<m_verticesGraphV.size(); i++){
      m_verticesGraphV[i]->SetLineWidth(3);
      m_verticesGraphV[i]->SetLineColor(kBlack);
      //m_verticesGraphV[i]->Draw("same");
    }
    
 
  }

  void getAdditionalGraphV_and_LineV_for_Plot( vector<TGraph*> &m_additionalGraphV, vector<TLine*> &m_additionalLineV, double envelopeR_min, double envelopeR_max, double l_slot){

    /////////////////////////////////
    
    //TLine *ln_0 = new TLine( frameXmin, 0, frameXmax, 0);
    //TLine *ln_1 = new TLine( frameYmin/TMath::Tan(60.0*TMath::Pi()/180.0), frameYmin,  frameYmax/TMath::Tan(60.0*TMath::Pi()/180.0), frameYmax);
    //TLine *ln_2 = new TLine( frameYmin/TMath::Tan(120.0*TMath::Pi()/180.0), frameYmin, frameYmax/TMath::Tan(120.0*TMath::Pi()/180.0), frameYmax);
    //ln_0->SetLineWidth(3.0);
    //ln_1->SetLineWidth(3.0);
    //ln_2->SetLineWidth(3.0);
    //ln_0->Draw("same");
    //ln_1->Draw("same");
    //ln_2->Draw("same");
    
    TVector2 vmin_0(envelopeR_min,0);
    TVector2 vmax_0(envelopeR_max,0);
    TVector2 vminrot_0;
    TVector2 vmaxrot_0;
    // 0
    vminrot_0 = vmin_0.Rotate(60.0*0*TMath::Pi()/180.0);
    vmaxrot_0 = vmax_0.Rotate(60.0*0*TMath::Pi()/180.0);
    TLine *ln_0 = new TLine( vminrot_0.X(), vminrot_0.Y(), vmaxrot_0.X(), vmaxrot_0.Y());
    // 1
    vminrot_0 = vmin_0.Rotate(60.0*1.0*TMath::Pi()/180.0);
    vmaxrot_0 = vmax_0.Rotate(60.0*1.0*TMath::Pi()/180.0);
    TLine *ln_1 = new TLine( vminrot_0.X(), vminrot_0.Y(), vmaxrot_0.X(), vmaxrot_0.Y());
    // 2
    vminrot_0 = vmin_0.Rotate(60.0*2.0*TMath::Pi()/180.0);
    vmaxrot_0 = vmax_0.Rotate(60.0*2.0*TMath::Pi()/180.0);
    TLine *ln_2 = new TLine( vminrot_0.X(), vminrot_0.Y(), vmaxrot_0.X(), vmaxrot_0.Y());
    // 3
    vminrot_0 = vmin_0.Rotate(60.0*3.0*TMath::Pi()/180.0);
    vmaxrot_0 = vmax_0.Rotate(60.0*3.0*TMath::Pi()/180.0);
    TLine *ln_3 = new TLine( vminrot_0.X(), vminrot_0.Y(), vmaxrot_0.X(), vmaxrot_0.Y());
    // 4
    vminrot_0 = vmin_0.Rotate(60.0*4.0*TMath::Pi()/180.0);
    vmaxrot_0 = vmax_0.Rotate(60.0*4.0*TMath::Pi()/180.0);
    TLine *ln_4 = new TLine( vminrot_0.X(), vminrot_0.Y(), vmaxrot_0.X(), vmaxrot_0.Y());
    // 5
    vminrot_0 = vmin_0.Rotate(60.0*5.0*TMath::Pi()/180.0);
    vmaxrot_0 = vmax_0.Rotate(60.0*5.0*TMath::Pi()/180.0);
    TLine *ln_5 = new TLine( vminrot_0.X(), vminrot_0.Y(), vmaxrot_0.X(), vmaxrot_0.Y());

    ln_0->SetLineWidth(3.0);
    ln_1->SetLineWidth(3.0);
    ln_2->SetLineWidth(3.0);
    ln_3->SetLineWidth(3.0);
    ln_4->SetLineWidth(3.0);
    ln_5->SetLineWidth(3.0);
    //ln_0->Draw("same");
    //ln_1->Draw("same");
    //ln_2->Draw("same");
    //ln_3->Draw("same");
    //ln_4->Draw("same");
    //ln_5->Draw("same");
    
    m_additionalLineV.push_back(ln_0);
    m_additionalLineV.push_back(ln_1);
    m_additionalLineV.push_back(ln_2);
    m_additionalLineV.push_back(ln_3);
    m_additionalLineV.push_back(ln_4);
    m_additionalLineV.push_back(ln_5);

    TVector2 vmin_1(envelopeR_max,0);
    TVector2 vmax_1(envelopeR_max + l_slot,0);
    TVector2 vminrot_1;
    TVector2 vmaxrot_1;
    int nSlot = 64;
    double dThetaSlot = 2*TMath::Pi()/nSlot;
    for(Int_t i = 0;i<nSlot;i++){
      vminrot_1 = vmin_1.Rotate(dThetaSlot*i -dThetaSlot/2);
      vmaxrot_1 = vmax_1.Rotate(dThetaSlot*i -dThetaSlot/2);
      TLine *ln = new TLine( vminrot_1.X(), vminrot_1.Y(), vmaxrot_1.X(), vmaxrot_1.Y());
      ln->SetLineWidth(3.0);
      m_additionalLineV.push_back(ln);
    }

    /////////////////////////////////
    //Additional graphs information   
    /////////////////////////////////
    //../arich/data/ARICH-Detectors.xml
    //<outerRadius desc="Outer radius of support plate" unit="mm">1132</outerRadius>
    //<innerRadius desc="Inner radius of support plate" unit="mm">435</innerRadius>    
    const Int_t nEnvelope = 500;
    Double_t xEnvelope_min[nEnvelope];
    Double_t yEnvelope_min[nEnvelope];
    Double_t xEnvelope_max[nEnvelope];
    Double_t yEnvelope_max[nEnvelope];
    Double_t xSlot_max[nEnvelope];
    Double_t ySlot_max[nEnvelope];
    for(int ii = 0; ii<nEnvelope;ii++){
      TVector2 vmin(envelopeR_min,0);
      TVector2 vminrot;
      vminrot = vmin.Rotate(360.0/(nEnvelope - 1)*ii*TMath::Pi()/180.0);
      TVector2 vmax(envelopeR_max,0);
      TVector2 vmaxrot;
      vmaxrot = vmax.Rotate(360.0/(nEnvelope - 1)*ii*TMath::Pi()/180.0);
      xEnvelope_min[ii] = vminrot.X();
      yEnvelope_min[ii] = vminrot.Y();
      xEnvelope_max[ii] = vmaxrot.X();
      yEnvelope_max[ii] = vmaxrot.Y();
      TVector2 vslot(envelopeR_max+l_slot,0);
      TVector2 vslotrot;
      vslotrot = vslot.Rotate(360.0/(nEnvelope - 1)*ii*TMath::Pi()/180.0);
      xSlot_max[ii] = vslotrot.X();
      ySlot_max[ii] = vslotrot.Y();
    }
    TGraph *gr_envelopeR_min = new TGraph(nEnvelope,xEnvelope_min,yEnvelope_min);
    m_additionalGraphV.push_back(gr_envelopeR_min);
    TGraph *gr_envelopeR_max = new TGraph(nEnvelope,xEnvelope_max,yEnvelope_max);
    m_additionalGraphV.push_back(gr_envelopeR_max);  
    TGraph *gr_slot = new TGraph(nEnvelope,xSlot_max,ySlot_max);
    m_additionalGraphV.push_back(gr_slot);  
    /////////////////////////////////

    for (unsigned i=0; i<m_additionalGraphV.size(); i++){
      m_additionalGraphV.at(i)->SetLineWidth(3);
      m_additionalGraphV.at(i)->SetLineColor(kBlack);
      //m_additionalGraphV.at(i)->Draw("same");
    }
  
  }

}//namespace xmlarichdata{
