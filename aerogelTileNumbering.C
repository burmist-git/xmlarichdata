/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue Oct 17 19:57:56 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

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
// rotating histograms
// http://root.cern.ch/phpBB3/viewtopic.php?t=790

using namespace std;

//https://confluence.desy.de/download/attachments/34029592/09z19-GEL20110124.pdf?api=v2
int aerogelTileNumbering(TString outpdf = "./outplots/aerogelTileNumbering.pdf", TString outeps = "./outplots/aerogelTileNumbering.eps"){

  const Int_t nR = 4; //Number of aerogel rings

  Int_t verboseLevel = 0;

  TRandom3 *rnd = new TRandom3(123124);

  TCanvas *c1 = new TCanvas("c1","aerogel numbering",1000,1000);
  c1->SetRightMargin(0.05);
  c1->SetLeftMargin(0.15);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.1);

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);

  TH2F *frame = new TH2F("h2","h2",40,-1200,1200,40, -1200,1200);
  frame->GetXaxis()->SetTitle("x (mm)");
  frame->GetYaxis()->SetTitle("y (mm)");
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  frame->SetTitle("");
  frame->Draw();

  Int_t i = 0;
  int iR = 0;
  int iPhi = 0;

  //Set aerogel parameters
  Double_t rin = 441;        //mm
  Double_t rout = 1117;      //mm
  Double_t tileGapR = 1;     //mm
  Double_t tileGapPhimm = 1; //mm
  //https://confluence.desy.de/download/attachments/34029592/09z19-GEL20110124.pdf?api=v2
  Double_t tileX[nR] = { 173.5, 175.0, 176.0, 176.6};        //mm
  Double_t tileRmin[nR] = { 441.0, 614.0, 787.0, 960.0}; //mm
  Double_t tileRmax[nR] = { 613.0, 786.0, 959.0, 1117.0}; //mm
  Double_t tileDPhiDeg[nR] = { 16.364, 12.857, 10.588, 9.0}; //deg
  Double_t tileGapdPhiDeg[nR];                               //deg
  Double_t tileY[nR];
  Int_t nTiles[nR];
  for(i = 0;i<nR;i++){
    tileY[i] = tileRmax[i] - tileRmin[i];
    tileGapdPhiDeg[i] = tileGapPhimm/180.0*TMath::Pi()/tileRmax[i]*180/TMath::Pi();
  }
  
  for( iR = 0; iR < nR; iR++)
    nTiles[iR] = TMath::Nint(2*TMath::Pi()/(tileDPhiDeg[iR]/180.0*TMath::Pi() + tileGapdPhiDeg[iR]));
  
  if(verboseLevel>0){
    cout<<setw(10)<<"ring"<<setw(10)<<"tileRmin"<<setw(10)<<"tileRmax"
	<<setw(10)<<"tileX"<<setw(10)<<"tileY"<<setw(15)<<"tileDPhiDeg";
    cout<<setw(10)<<"tileGapR"<<setw(20)<<"tileGapdPhiDeg"
	<<setw(10)<<"nTiles"<<endl;
    for(i = 0;i<nR;i++){
      cout<<setw(10)<<i+1<<setw(10)<<tileRmin[i]<<setw(10)<<tileRmax[i]<<setw(10)<<tileX[i]<<setw(10)<<tileY[i]<<setw(15)<<tileDPhiDeg[i];
      cout<<setw(10)<<tileGapR<<setw(20)<<tileGapdPhiDeg[i]<<setw(10)<<nTiles[i]<<endl;
    }
  }
  
  TCrown *agel;
  Double_t x0 = 0.0;
  Double_t y0 = 0.0;
  Double_t phi0 = 0.0;
  Double_t phi = 0.0;
  Double_t radin;
  Double_t radout;
  Double_t phimin;
  Double_t phimax;
  TString tileAddr;
  TText aa;
  aa.SetTextSize(.015);
  aa.SetTextAlign(22);
  aa.SetTextAngle(5);
  Double_t rc;
  Double_t rx;
  Double_t ry;
  for( iR = 0; iR < nR; iR++){    
    radin = tileRmin[iR];
    radout = tileRmax[iR];
    for( iPhi = 0; iPhi < nTiles[iR]; iPhi++){
      phimin = phi0 + (tileDPhiDeg[iR] + tileGapdPhiDeg[iR])*iPhi;
      phimax = phimin + tileDPhiDeg[iR];
      agel = new TCrown(x0,y0,radin,radout,phimin,phimax);
      agel->SetLineWidth(3);
      //agel->SetFillColor(kAzure+TMath::Nint(rnd->Uniform(-9.1,10.1)));
      agel->SetFillColor(kAzure+7);
      agel->Draw();
      tileAddr="R";tileAddr+=(iR+1);tileAddr+="C";tileAddr+=(iPhi+1);
      rc = (tileRmax[iR] + tileRmin[iR])/2.0;
      phi = (phimax + phimin)/2.0/180.0*TMath::Pi();
      rx = rc*cos(phi);
      ry = rc*sin(phi);
      aa.DrawText(rx, ry, tileAddr.Data());
    }
  }

  c1->SaveAs(outpdf.Data());
  c1->SaveAs(outeps.Data());
  
  return 0;
}
