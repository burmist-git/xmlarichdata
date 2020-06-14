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
#include <TLine.h>
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

namespace xmlarichdata{
  
  Int_t plotsARICHphase2performance(TString plotKey = "all"){
    
    TString fileN;
    TString objectName;
    fileN = "./histograms_ARICH_phase_2_performance.root";
    
    TFile *f1 = new TFile(fileN.Data());
    TH1D *h_chHit = (TH1D*)f1->Get("h_chHit");
    TH1D *h_thetaWoNoise = (TH1D*)f1->Get("h_thetaWoNoise");
    
    if(plotKey == "all" || plotKey == "hapd"){
      
      int nMod=0;
      double aveHit=0;
      for(int i=1;i<421;i++){
	for(int j=1;j<144;j++){
	  int ch = (i-1)*144 + j;
	  if(h_chHit->GetBinContent(ch+1)!=0){
	    aveHit+=(h_chHit->GetBinContent(ch+1));
	    nMod+=1;
	  }
	}
      }
      aveHit/=nMod;
      Belle2::ARICHChannelHist* chHits = new Belle2::ARICHChannelHist("chHits","Distribution of hits");
      for(int i=1;i<421;i++){
	for(int j=1;j<145;j++){
	  int ch = (i-1)*144 + j;
	  if(h_chHit->GetBinContent(ch)<aveHit*5){
	    chHits->setBinContent(i,j,h_chHit->GetBinContent(ch));
	  }
	}
      }
      
      //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
      TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,600,600);
      gStyle->SetPalette(1);
      gStyle->SetFrameBorderMode(0);
      gROOT->ForceStyle();
      gStyle->SetStatColor(kWhite);
      //gStyle->SetOptStat(kFALSE);
      
      chHits->GetZaxis()->SetRangeUser(1.0,1000);
      chHits->SetStats(0);
      chHits->Draw();
      c1->Update();
      
    }
    
    if(plotKey == "all" || plotKey == "theta"){

      h_thetaWoNoise->GetYaxis()->SetTitle("");
      h_thetaWoNoise->SetTitle("Cherenkov photon angle distribution");
      
      TCanvas *c2 = new TCanvas("c2",fileN.Data(),10,10,600,600);
      gStyle->SetPalette(1);
      gStyle->SetFrameBorderMode(0);
      gROOT->ForceStyle();
      gStyle->SetStatColor(kWhite);
      //gStyle->SetOptStat(kFALSE);
      
      TF1* chFitter = new TF1("chFitter","pol1(0)+gaus(2)+gaus(5)");
      chFitter->SetParameters(400,500,5000,0.3,0.015,1000,0.3,0.02);
      h_thetaWoNoise->Fit("chFitter","","",0.1,0.5);
      
      TF1* l1 = new TF1("l1","pol1",0.1,0.5);
      l1->SetParameters(chFitter->GetParameter(0),chFitter->GetParameter(1));
      l1->SetLineColor(kBlue);
      l1->Draw("same");
      
      /*
      TF1* signal = new TF1("signal","gaus(0)+gaus(3)");
      signal->SetParameters(chFitter->GetParameter(2),chFitter->GetParameter(3),chFitter->GetParameter(4),
			    chFitter->GetParameter(5),chFitter->GetParameter(6),chFitter->GetParameter(7));
      signal->SetLineColor(kRed);
      signal->Draw("same");
      */

      TF1* signal1 = new TF1("signal","gaus");
      signal1->SetParameters(chFitter->GetParameter(2),chFitter->GetParameter(3),chFitter->GetParameter(4));
      signal1->SetLineColor(kRed);
      signal1->Draw("same");

      TF1* signal2 = new TF1("signal","gaus");
      signal2->SetParameters(chFitter->GetParameter(5),chFitter->GetParameter(6),chFitter->GetParameter(7));
      signal2->SetLineColor(kRed);
      signal2->Draw("same");
      
      c2->Update();
      
    }
    return 0;
  }
  
}//namespace xmlarichdata{
