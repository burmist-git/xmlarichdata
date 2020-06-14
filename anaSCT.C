//my
#include "anaSCT.h"
#include "libxmlarichdata.h"
#include "ARICHmappingCopperMergerFeb.h"
#include "ARICHMergerHist.h"
#include "mergerStruct.h"
#include "ARICHMergerHist.C"

//root
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TRandom3.h>
#include <TMultiGraph.h>

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;
using namespace xmlarichdata;

void anaSCT::Loop(TString histOut, double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec, double dTimeWindow, double tMin, double tMax){

  ARICHmappingCopperMergerFeb *arichMapping = new ARICHmappingCopperMergerFeb("hapdTemplateMapping.dat");
  //arichMapping->dumpMapping();
  
  TString histTitle = "h2_asic_t1";
  TString histName = "asic t1";
  TString c1histTitle = histTitle;
  TString c1histName = histName;
  Belle2::ARICHChannelHist *h2_asic_t1 = new Belle2::ARICHChannelHist(histTitle.Data(),histName.Data(),1);
  
  histTitle = "h2_asic_t2";
  histName = "asic t2";
  TString c2histTitle = histTitle;
  TString c2histName = histName;
  Belle2::ARICHChannelHist *h2_asic_t2 = new Belle2::ARICHChannelHist(histTitle.Data(),histName.Data(),1);

  histTitle = "h2_asic_dt";
  histName = "asic dt";
  TString c3histTitle = histTitle;
  TString c3histName = histName;
  Belle2::ARICHChannelHist *h2_asic_dt = new Belle2::ARICHChannelHist(histTitle.Data(),histName.Data(),1);
  
  TH1D *h1_febt1 = new TH1D("h1_febt1","febt1", 300,  0.0, 50.0);
  TH1D *h1_febt2 = new TH1D("h1_febt2","febt2", 300,  0.0, 50.0);
  TH1D *h1_febdt = new TH1D("h1_febdt","febdt", 300, -5.0,  5.0);

  TGraph *gr_febt1 =new TGraph(); gr_febt1->SetTitle("gr_febt1"); gr_febt1->SetName("gr_febt1");
  TGraph *gr_febt2 =new TGraph(); gr_febt2->SetTitle("gr_febt2"); gr_febt2->SetName("gr_febt2");
  TGraph *gr_febdt =new TGraph(); gr_febdt->SetTitle("gr_febdt"); gr_febdt->SetName("gr_febdt");

  TGraph *gr_febt1_dT0 =new TGraph(); gr_febt1_dT0->SetTitle("gr_febt1_dT0"); gr_febt1_dT0->SetName("gr_febt1_dT0");
  
  TGraph *gr_mergert =new TGraph(); gr_mergert->SetTitle("gr_mergert"); gr_mergert->SetName("gr_mergert");

  TGraph *gr_mergert_dT0 =new TGraph(); gr_mergert_dT0->SetTitle("gr_mergert_dT0"); gr_mergert_dT0->SetName("gr_mergert_dT0");
  
  ARICHMergerHist *h2_merger_t = new ARICHMergerHist("h2_merger_t", "Merger temperature");
  
  /*
    for(Int_t iR = 1; iR<=arichMapping->GetnHAPDrings(); iR++){
    for(Int_t iP = 1; iP<=arichMapping->gHAPDpositionInRingPerSector_Arr[(iR-1)]; iP++){
    //cout<<"iR "<<iR <<"  iP "<<iP<<"   "<<arichMapping->getHAPD_globalID_from_sec_iR_iP(6, iR,iP)<<endl;
    h2_asic_t->SetBinContent(arichMapping->getHAPD_globalID_from_sec_iR_iP(6, iR, iP),
    arichMapping->getHAPD_globalID_from_sec_iR_iP(6, iR,iP));
    }
    }
  */

  /*
  Int_t sec_i, cop_i, mer_i, feb_i;
  Int_t secID, iR, iP;
  secID = 6;
  for(iR = 1; iR<=arichMapping->GetnHAPDrings(); iR++){
    for(iP = 1; iP<=arichMapping->gHAPDpositionInRingPerSector_Arr[(iR-1)]; iP++){
      arichMapping->findPositionInarichmappingFormSecIDiRingiPosition( secID,  iR,  iP, sec_i, cop_i, mer_i, feb_i);
      h2_asic_t->SetBinContent(arichMapping->getHAPD_globalID_from_sec_iR_iP(6, iR, iP),
			       arichMapping->arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].globalID);
    }
  }
  */

  //Unix time : 1538381201        Time :  2018    10     1    17     6    41
  //Unix time : 1538381406        Time :  2018    10     1    17    10     6
  //Unix time : 1538382859        Time :  2018    10     1    17    34    19
  //Unix time : 1538382918        Time :  2018    10     1    17    35    18
  //Unix time : 1538383812        Time :  2018    10     1    17    50    12
  
  //d_year  = 2018;  d_month = 10;  d_day   = 1;  d_hour  = 11;  d_min   = 37;  d_sec   = 55;
  //d_year  = 2018;  d_month = 10;  d_day   = 1;  d_hour  = 17;  d_min   = 6;  d_sec   = 40;
  double unixtimeStart = getUnixTimeFrom_year_month_day_hour_min_sec(d_year, d_month, d_day, d_hour, d_min, d_sec-dTimeWindow);
  //d_year  = 2018;  d_month = 10;  d_day   = 1;  d_hour  = 11;  d_min   = 38;  d_sec   = 54;
  //d_year  = 2018;  d_month = 10;  d_day   = 1;  d_hour  = 17;  d_min   = 50;  d_sec   = 13;
  double unixtimeStop  = getUnixTimeFrom_year_month_day_hour_min_sec(d_year, d_month, d_day, d_hour, d_min, d_sec+dTimeWindow);
  cout<<"d_year  "<<d_year<<endl
      <<"d_month "<<d_month<<endl
      <<"d_day   "<<d_day<<endl
      <<"d_hour  "<<d_hour<<endl
      <<"d_min   "<<d_min<<endl
      <<"d_sec   "<<d_sec<<endl;
  //xmlarichdata::runARICH_asic_fpga_Temperatures();
  Int_t i = 0;
  TRandom3 *rnd = new TRandom3();
  TH1D *h1_dummyHisto = new TH1D("h1_dummyHisto","dummyHisto",100,0.0,100);
  TGraph *gr_dummyGraph[nChannels];
  tGraphInit(gr_dummyGraph, "gr_dummyGraph", "dummyGraph");
  TH1D *h1_dummyHistoArr[nChannels];
  h1D1Init(h1_dummyHistoArr,"h1_dummyHistoArr","h1_dummyHistoArr",100,-10.0,10);
  TH2D *h2_dummyHistoArr[nChannels];
  h2D2Init(h2_dummyHistoArr,"h2_dummyHistoArr", "dummyHistoArr", 100, -10.0, 10.0, 100, -10.0, 10.0);
  TProfile *pr_dummyArr[nChannels];
  tProfInit(pr_dummyArr,"pr_dummyArr", "dummyArr", 100, 0.0, 10.0);
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  Double_t valOld = 0.0;
  Double_t valNew = 0.0;
  Double_t unixTimeT0 = 0.0;
  Double_t dt;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //////////////////////////
    //Double_t unixTime;
    //Float_t  febt1[420];
    //Float_t  febt2[420];
    //Float_t  mergert[72];
    //////////////////////////
    if(jentry == 0)
      unixTimeT0 = unixTime - 8500;
    for( i = 0; i<arichMapping->GetnHAPD(); i++){
      if(febt1[i]>-10 && febt1[i]<100){
	gr_febt1->SetPoint(gr_febt1->GetN(), unixTime, febt1[i]);
	gr_febt1_dT0->SetPoint(gr_febt1->GetN(), unixTime - unixTimeT0, febt1[i]);
      }
      if(febt2[i]>-10 && febt2[i]<100)
	gr_febt2->SetPoint(gr_febt2->GetN(), unixTime, febt2[i]);
      if(dt>-10 && dt<10)
	gr_febdt->SetPoint(gr_febdt->GetN(), unixTime, dt);
    }

    for( i = 0; i<arichMapping->GetnMergers(); i++){
      //if(mergert[i]>0.0)
      if(mergert[i]<100){
	gr_mergert->SetPoint(gr_mergert->GetN(), unixTime, mergert[i]);
	gr_mergert_dT0->SetPoint(gr_mergert->GetN(), unixTime - unixTimeT0, mergert[i]);
      }
    }
      
    if(unixtimeStart < unixTime && unixTime < unixtimeStop){
      for( i = 0; i<arichMapping->GetnHAPD(); i++){
	h1_febt1->Fill(febt1[i]);
	h1_febt2->Fill(febt2[i]);
	dt = febt1[i] - febt2[i];
	h1_febdt->Fill(dt);

	Int_t febID = i+1;
	//Int_t sec_i, cop_i,  mer_i, feb_i;

	if(febt1[i]>0.0){
	  //arichMapping->findPositionInarichmappingFormGlobalFebID(febID, &sec_i, &cop_i, &mer_i, &feb_i);
	  valOld = h2_asic_t1->GetBinContent(febID);
	  if(valOld>0.0){
	    valNew = (valOld + febt1[i])/2.0;
	    h2_asic_t1->SetBinContent(febID, roundf(valNew * 100) / 100);
	  }
	  else{
	    h2_asic_t1->SetBinContent(febID, roundf(febt1[i] * 100) / 100);
	  }
	}

	if(febt2[i]>0.0){
	  //arichMapping->findPositionInarichmappingFormGlobalFebID(febID, &sec_i, &cop_i, &mer_i, &feb_i);
	  valOld = h2_asic_t2->GetBinContent(febID);
	  if(valOld>0.0){
	    valNew = (valOld + febt2[i])/2.0;
	    h2_asic_t2->SetBinContent(febID, roundf(valNew * 100) / 100);
	  }
	  else{
	    h2_asic_t2->SetBinContent(febID, roundf(febt2[i] * 100) / 100);
	  }
	}
	
      }

      //mergert[72];
      for( Int_t j = 0; j<arichMapping->GetnMergers(); j++){
	//h2_merger_t->SetBinContent(h2_merger_t->GetBinIDFromMergerSlotNumber(j+1),j+1);
	if(mergert[j]>0.0 && mergert[j]<100)
	  h2_merger_t->SetBinContent(h2_merger_t->GetBinIDFromMergerSlotNumber(j+1),roundf(mergert[j] * 100) / 100);
      }
    }
    //////////////////////////
    h1_dummyHisto->Fill(1);
    for(i = 0;i<nChannels;i++){
      gr_dummyGraph[i]->SetPoint(gr_dummyGraph[i]->GetN(), gr_dummyGraph[i]->GetN(), rnd->Gaus(0.0,1.0));
      h1_dummyHistoArr[i]->Fill(rnd->Gaus(0.0,1.0));
      h2_dummyHistoArr[i]->Fill(rnd->Gaus(0.0,1.0),rnd->Gaus(0.0,1.0));
      pr_dummyArr[i]->Fill(rnd->Uniform(0.0,10.0),rnd->Gaus(1.0,1.0));
    }
  }

  Double_t valt1;
  Double_t valt2;
  Double_t valdt;
  for( i = 0; i<arichMapping->GetnHAPD(); i++){
    Int_t febID = i+1;
    valt1 = h2_asic_t1->GetBinContent(febID);
    valt2 = h2_asic_t2->GetBinContent(febID);
    if(valt1>0.0 && valt2>0.0){
      valdt = valt1 - valt2;
      h2_asic_dt->SetBinContent(febID, roundf(valdt * 100) / 100);
    }
  }

  /*
  gStyle->SetPalette(kRainBow);
  //gStyle->SetPalette(0);
  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  c1->SetTitle(histTitle.Data());
  c1->SetName(histName.Data());
  c1->SetRightMargin(0.12);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.15);
  ///////////////////////////////////////////////////////////////
  double envelopeR_min = 43.5;
  double envelopeR_max = 113.2;
  //Double_t l_slot = 29.1;
  Double_t l_slot = 1.0;
  */
  /*
    Double_t frameXmin = -114.0 - l_slot;
    Double_t frameXmax =  114.0 + l_slot;
    Double_t frameYmin = -114.0 - l_slot;
    Double_t frameYmax =  114.0 + l_slot;
  */
  /*
  Double_t frameXmin =  20.0;
  Double_t frameXmax =  114.0 + l_slot + 6;
  Double_t frameYmin = -114.0 - l_slot + 15;
  Double_t frameYmax =  1.0;
  TH2F *frame = new TH2F( "h2", "h2", 40, frameXmin, frameXmax,40, frameYmin, frameYmax);
  frame->GetXaxis()->SetTitle("x (cm)");
  frame->GetYaxis()->SetTitle("y (cm)");
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  frame->SetTitle("");
  frame->Draw();
  //img->Draw("same");
  */
  ///////////////////////////////////////////////////////////////
  h2_asic_t1->SetStats(kFALSE);
  h2_asic_t1->GetXaxis()->SetTitle("x (cm)");
  h2_asic_t1->GetYaxis()->SetTitle("y (cm)");
  h2_asic_t1->GetXaxis()->CenterTitle();
  h2_asic_t1->GetYaxis()->CenterTitle();
  h2_asic_t1->GetYaxis()->SetTitleOffset(1.5);
  h2_asic_t2->SetStats(kFALSE);
  h2_asic_t2->GetXaxis()->SetTitle("x (cm)");
  h2_asic_t2->GetYaxis()->SetTitle("y (cm)");
  h2_asic_t2->GetXaxis()->CenterTitle();
  h2_asic_t2->GetYaxis()->CenterTitle();
  h2_asic_t2->GetYaxis()->SetTitleOffset(1.5);
  h2_asic_dt->SetStats(kFALSE);
  h2_asic_dt->GetXaxis()->SetTitle("x (cm)");
  h2_asic_dt->GetYaxis()->SetTitle("y (cm)");
  h2_asic_dt->GetXaxis()->CenterTitle();
  h2_asic_dt->GetYaxis()->CenterTitle();
  h2_asic_dt->GetYaxis()->SetTitleOffset(1.5);
  //SetLineStyle(1);
  //SetLineWidth(3.0);

  /*
  h2_asic_t1->GetZaxis()->SetRangeUser(25.0,35.0);
  h2_asic_t2->GetZaxis()->SetRangeUser(25.0,35.0);
  h2_merger_t->GetZaxis()->SetRangeUser(25.0,35.0);
  h2_asic_dt->GetZaxis()->SetRangeUser(-1.0,1.0);
  */
  /*
  h2_asic_t1->GetZaxis()->SetRangeUser(30.0,50.0);
  h2_asic_t2->GetZaxis()->SetRangeUser(30.0,50.0);
  h2_merger_t->GetZaxis()->SetRangeUser(30.0,50.0);
  */
  h2_asic_t1->GetZaxis()->SetRangeUser(tMin,tMax);
  h2_asic_t2->GetZaxis()->SetRangeUser(tMin,tMax);
  h2_merger_t->GetZaxis()->SetRangeUser(tMin,tMax);
  h2_asic_dt->GetZaxis()->SetRangeUser(-1.0,1.0);
  
  gStyle->SetPalette(kRainBow);
  //gStyle->SetPalette(0);
  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  c1->SetTitle(c1histTitle.Data());
  c1->SetName(c1histName.Data());
  c1->SetRightMargin(0.12);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.15);
  plot(c1, h2_asic_t1);
  c1->Modified();
  c1->Update();

  TCanvas *c2 = new TCanvas("c2","c2",1000,1000);
  c2->SetTitle(c2histTitle.Data());
  c2->SetName(c2histName.Data());
  c2->SetRightMargin(0.12);
  c2->SetLeftMargin(0.12);
  c2->SetTopMargin(0.1);
  c2->SetBottomMargin(0.15);
  plot(c2, h2_asic_t2);
  c2->Modified();
  c2->Update();
  
  TCanvas *c3 = new TCanvas("c3","c3",1000,1000);
  c3->SetTitle(c3histTitle.Data());
  c3->SetName(c3histName.Data());
  c3->SetRightMargin(0.12);
  c3->SetLeftMargin(0.12);
  c3->SetTopMargin(0.1);
  c3->SetBottomMargin(0.15);
  plot(c3, h2_asic_dt);
  c3->Modified();
  c3->Update();

  TCanvas *c4 = new TCanvas("c4","c4",1000,1000);
  c4->SetTitle("c4");
  c4->SetName("c4");
  c4->SetRightMargin(0.12);
  c4->SetLeftMargin(0.12);
  c4->SetTopMargin(0.1);
  c4->SetBottomMargin(0.15);
  //
  TMultiGraph *mg = new TMultiGraph();
  gr_febt1->SetLineColor(kBlack);
  gr_febt1->SetLineWidth(3.0);
  gr_febt1->SetMarkerColor(kBlack);
  gr_febt1->SetMarkerStyle(20);
  gr_febt2->SetLineColor(kBlue);
  gr_febt2->SetLineWidth(3.0);
  gr_febt2->SetMarkerColor(kBlue);
  gr_febt2->SetMarkerStyle(20);
  gr_febdt->SetLineColor(kRed);
  gr_febdt->SetLineWidth(3.0);
  gr_febdt->SetMarkerColor(kRed);
  gr_febdt->SetMarkerStyle(20);
  mg->Add(gr_febt1);
  mg->Add(gr_febt2);
  mg->Add(gr_febdt);
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("Time, h");
  mg->GetYaxis()->SetTitle("Temperature, C^{o}");
  //
  c4->Modified();
  c4->Update();

  //TCanvas *c5 = new TCanvas("c5","c5",1000,1000);
  //c5->SetTitle("c5");
  //c5->SetName("c5");
  //c5->SetRightMargin(0.12);
  //c5->SetLeftMargin(0.12);
  //c5->SetTopMargin(0.1);
  //c5->SetBottomMargin(0.15);
  h2_merger_t->DrawHisto("ZTEXT ZCOLOR same","","drawLine",tMin,tMax);
  //c5->Modified();
  //c5->Update();


  TCanvas *c6 = new TCanvas("c6","c6",1000,1000);
  c6->SetTitle("c6");
  c6->SetName("c6");
  c6->SetRightMargin(0.12);
  c6->SetLeftMargin(0.12);
  c6->SetTopMargin(0.1);
  c6->SetBottomMargin(0.15);
  gr_mergert->SetLineColor(kBlack);
  gr_mergert->SetLineWidth(3.0);
  gr_mergert->SetMarkerColor(kBlack);
  gr_mergert->SetMarkerStyle(20);
  gr_mergert->Draw("AP");
  gr_mergert->GetXaxis()->SetTitle("Time, h");
  gr_mergert->GetYaxis()->SetTitle("Temperature, C^{o}");
  c6->Modified();
  c6->Update();
  
  //gStyle->SetPalette(1);
  //h2_asic_t->GetZaxis()->SetRangeUser(0.0,420.0);
  //h2_asic_t->Draw("ZCOLOR same");
  //h2_asic_t->GetZaxis()->SetRangeUser(25.0,30.0);
  //h2_asic_t1->Draw("ZTEXT ZCOLOR same");
  /*
  h2_asic_dt->Draw("ZTEXT ZCOLOR same");
  
  vector<TGraph*> m_verticesGraphV;
  vector<TGraph*> m_additionalGraphV;
  vector<TLine*> m_additionalLineV;
  getAdditionalGraphV_and_LineV_for_Plot(m_additionalGraphV, m_additionalLineV, envelopeR_min, envelopeR_max, l_slot);
  
  for (unsigned i=0; i<m_verticesGraphV.size(); i++)
    m_verticesGraphV.at(i)->Draw("same");
  
  for (unsigned i=0; i<m_additionalGraphV.size(); i++)
    m_additionalGraphV.at(i)->Draw("same");
  
  for (unsigned i=0; i<m_additionalLineV.size(); i++)
    m_additionalLineV.at(i)->Draw("same");
  */

  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  
  for(i = 0;i<nChannels;i++){
    gr_dummyGraph[i]->Write();
    h1_dummyHistoArr[i]->Write();
    h2_dummyHistoArr[i]->Write();
    pr_dummyArr[i]->Write();
  }
  h1_dummyHisto->Write();
  h2_asic_t1->Write();
  h2_asic_t2->Write();
  h2_asic_dt->Write();
  h1_febt1->Write();
  h1_febt2->Write();
  h1_febdt->Write();
  gr_febt1->Write();
  gr_febt2->Write();
  gr_febdt->Write();
  gr_febt1_dT0->Write();
  h2_merger_t->Write();
  gr_mergert->Write();
  gr_mergert_dT0->Write();
  
  rootFile->Close();
  
}

void anaSCT::plot(TCanvas *cc, Belle2::ARICHChannelHist *h2_asic){
  /*
  gStyle->SetPalette(kRainBow);
  //gStyle->SetPalette(0);
  TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
  c1->SetTitle(histTitle.Data());
  c1->SetName(histName.Data());
  c1->SetRightMargin(0.12);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.15);
  */
  ///////////////////////////////////////////////////////////////
  double envelopeR_min = 43.5;
  double envelopeR_max = 113.2;
  //Double_t l_slot = 29.1;
  Double_t l_slot = 1.0;

  /*
    Double_t frameXmin = -114.0 - l_slot;
    Double_t frameXmax =  114.0 + l_slot;
    Double_t frameYmin = -114.0 - l_slot;
    Double_t frameYmax =  114.0 + l_slot;
  */

  Double_t frameXmin =  20.0;
  Double_t frameXmax =  114.0 + l_slot + 6;
  Double_t frameYmin = -114.0 - l_slot + 15;
  Double_t frameYmax =  1.0;
  TH2F *frame = new TH2F( "h2", "h2", 40, frameXmin, frameXmax,40, frameYmin, frameYmax);
  frame->GetXaxis()->SetTitle("x (cm)");
  frame->GetYaxis()->SetTitle("y (cm)");
  frame->GetXaxis()->CenterTitle();
  frame->GetYaxis()->CenterTitle();
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->SetStats(kFALSE);
  frame->SetTitle("");
  frame->Draw();
  //img->Draw("same");
  ///////////////////////////////////////////////////////////////

  h2_asic->Draw("ZTEXT ZCOLOR same");
  
  vector<TGraph*> m_verticesGraphV;
  vector<TGraph*> m_additionalGraphV;
  vector<TLine*> m_additionalLineV;
  getAdditionalGraphV_and_LineV_for_Plot(m_additionalGraphV, m_additionalLineV, envelopeR_min, envelopeR_max, l_slot);
  
  for (unsigned i=0; i<m_verticesGraphV.size(); i++)
    m_verticesGraphV.at(i)->Draw("same");
  
  for (unsigned i=0; i<m_additionalGraphV.size(); i++)
    m_additionalGraphV.at(i)->Draw("same");
  
  for (unsigned i=0; i<m_additionalLineV.size(); i++)
    m_additionalLineV.at(i)->Draw("same");

}
