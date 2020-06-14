//my
#include "anaGL840.h"
#include "libxmlarichdata.h"

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

void anaGL840::Loop(TString histOut, Int_t dataDivision, TString parametersFileIn){
  Int_t i = 0;
  //TRandom3 *rnd = new TRandom3();
  TH1D *h1_dummyHisto = new TH1D("h1_dummyHisto","dummyHisto",100,0.0,100);
  TGraph *gr_dummyGraph[nChannels];
  tGraphInit(gr_dummyGraph, "gr_dummyGraph", "dummyGraph");
  TH1D *h1_dummyHistoArr[nChannels];
  h1D1Init(h1_dummyHistoArr,"h1_dummyHistoArr","h1_dummyHistoArr",100,-10.0,10);
  TH2D *h2_dummyHistoArr[nChannels];
  h2D2Init(h2_dummyHistoArr,"h2_dummyHistoArr", "dummyHistoArr", 100, -10.0, 10.0, 100, -10.0, 10.0);
  TProfile *pr_dummyArr[nChannels];
  tProfInit(pr_dummyArr,"pr_dummyArr", "dummyArr", 100, 0.0, 10.0);
  ////////////////////////////////////////
  TGraph *gr_t_vs_time[nChannels];
  tGraphInit(gr_t_vs_time, "gr_t_vs_time", "t vs time");
  ////////////////////////////////////////

  TGraph *gr_extractedPower_vs_time = new TGraph();
  gr_extractedPower_vs_time->SetTitle("gr_extractedPower_vs_time");
  gr_extractedPower_vs_time->SetName("gr_extractedPower_vs_time");    

  TGraph *gr_extractedPower_vs_time_sec6 = new TGraph();
  gr_extractedPower_vs_time_sec6->SetTitle("gr_extractedPower_vs_time_sec6");
  gr_extractedPower_vs_time_sec6->SetName("gr_extractedPower_vs_time_sec6");    
  TGraph *gr_extractedPower_vs_time_sec5 = new TGraph();
  gr_extractedPower_vs_time_sec5->SetTitle("gr_extractedPower_vs_time_sec5");
  gr_extractedPower_vs_time_sec5->SetName("gr_extractedPower_vs_time_sec5");    
  TGraph *gr_extractedPower_vs_time_sec4 = new TGraph();
  gr_extractedPower_vs_time_sec4->SetTitle("gr_extractedPower_vs_time_sec4");
  gr_extractedPower_vs_time_sec4->SetName("gr_extractedPower_vs_time_sec4");    
  TGraph *gr_extractedPower_vs_time_sec3 = new TGraph();
  gr_extractedPower_vs_time_sec3->SetTitle("gr_extractedPower_vs_time_sec3");
  gr_extractedPower_vs_time_sec3->SetName("gr_extractedPower_vs_time_sec3");    
  TGraph *gr_extractedPower_vs_time_sec2 = new TGraph();
  gr_extractedPower_vs_time_sec2->SetTitle("gr_extractedPower_vs_time_sec2");
  gr_extractedPower_vs_time_sec2->SetName("gr_extractedPower_vs_time_sec2");    
  TGraph *gr_extractedPower_vs_time_sec1 = new TGraph();
  gr_extractedPower_vs_time_sec1->SetTitle("gr_extractedPower_vs_time_sec1");
  gr_extractedPower_vs_time_sec1->SetName("gr_extractedPower_vs_time_sec1");    

  TGraph *gr_delta_extractedPower_sec6_m_sec2 = new TGraph();
  gr_delta_extractedPower_sec6_m_sec2->SetTitle("gr_delta_extractedPower_sec6_m_sec2");
  gr_delta_extractedPower_sec6_m_sec2->SetName("gr_delta_extractedPower_sec6_m_sec2");

  TGraph *gr_delta_temp_sec6_m_sec2_vs_time = new TGraph();
  gr_delta_temp_sec6_m_sec2_vs_time->SetTitle("gr_delta_temp_sec6_m_sec2_vs_time");
  gr_delta_temp_sec6_m_sec2_vs_time->SetName("gr_delta_temp_sec6_m_sec2_vs_time");
  
  TGraph *gr_elePower_vs_time = new TGraph();
  gr_elePower_vs_time->SetTitle("gr_elePower_vs_time");
  gr_elePower_vs_time->SetName("gr_elePower_vs_time");    
  
  TGraph *gr_extractedPower_vs_temperature = new TGraph();
  gr_extractedPower_vs_temperature->SetTitle("gr_extractedPower_vs_temperature");
  gr_extractedPower_vs_temperature->SetName("gr_extractedPower_vs_temperature");    

  TProfile *pr_extractedPower_vs_temperature = new TProfile("pr_extractedPower_vs_temperature","pr_extractedPower_vs_temperature",30,24,32,"");

  tProfInit(pr_dummyArr,"pr_dummyArr", "dummyArr", 100, 0.0, 10.0);
  
  Double_t normVal = 7;
  TGraph *gr_elePower_vs_time_norm = new TGraph();
  gr_elePower_vs_time_norm->SetTitle("gr_elePower_vs_time_norm");
  gr_elePower_vs_time_norm->SetName("gr_elePower_vs_time_norm");

  TGraph *gr_extractedPower_vs_time_norm = new TGraph();
  gr_extractedPower_vs_time_norm->SetTitle("gr_extractedPower_vs_time_norm");
  gr_extractedPower_vs_time_norm->SetName("gr_extractedPower_vs_time_norm");

  TH1D *h1_extractedPower = new TH1D("h1_extractedPower","extractedPower",200,0,200);

  TH1D *h1_extractedPower_sec6 = new TH1D("h1_extractedPower_sec6","extractedPower sec6",200,0,200);
  TH1D *h1_extractedPower_sec5 = new TH1D("h1_extractedPower_sec5","extractedPower sec5",200,0,200);
  TH1D *h1_extractedPower_sec4 = new TH1D("h1_extractedPower_sec4","extractedPower sec4",200,0,200);  
  TH1D *h1_extractedPower_sec3 = new TH1D("h1_extractedPower_sec3","extractedPower sec3",200,0,200);
  TH1D *h1_extractedPower_sec2 = new TH1D("h1_extractedPower_sec2","extractedPower sec2",200,0,200);
  TH1D *h1_extractedPower_sec1 = new TH1D("h1_extractedPower_sec1","extractedPower sec1",200,0,200);

  double unixtimeStart;
  double unixtimeStop;
  //unixtimeStart = getUnixTimeFrom_year_month_day_hour_min_sec( 2000, 10, 1, 11, 15, 0);
  //unixtimeStop  = getUnixTimeFrom_year_month_day_hour_min_sec( 2100, 10, 1, 18, 50, 0);
  //unixtimeStart = getUnixTimeFrom_year_month_day_hour_min_sec( 2018, 10, 1, 11, 15, 0);
  //unixtimeStop  = getUnixTimeFrom_year_month_day_hour_min_sec( 2018, 10, 1, 18, 50, 0);
  //unixtimeStart = getUnixTimeFrom_year_month_day_hour_min_sec( 2018, 10, 1, 12, 15, 0);
  //unixtimeStop  = getUnixTimeFrom_year_month_day_hour_min_sec( 2018, 10, 1, 17, 50, 0);
  //unixtimeStart = getUnixTimeFrom_year_month_day_hour_min_sec( 2018, 10, 1, 14, 49, 0);
  //unixtimeStop  = getUnixTimeFrom_year_month_day_hour_min_sec( 2018, 10, 1, 14, 59, 0);
  //unixtimeStart = getUnixTimeFrom_year_month_day_hour_min_sec( 2000, 10,  1, 14, 49, 0);
  //unixtimeStop  = getUnixTimeFrom_year_month_day_hour_min_sec( 2018, 11, 14,  9,  0, 0);
  double d_year_min, d_month_min, d_day_min, d_hour_min, d_min_min, d_sec_min;
  double d_year_max, d_month_max, d_day_max, d_hour_max, d_min_max, d_sec_max;
  double totflux;
  readInputPar(parametersFileIn,
	       d_year_min, d_month_min, d_day_min, d_hour_min, d_min_min, d_sec_min,
	       d_year_max, d_month_max, d_day_max, d_hour_max, d_min_max, d_sec_max,
	       totflux);
  //cout<<"totflux = "<<totflux<<endl;
  unixtimeStart = getUnixTimeFrom_year_month_day_hour_min_sec( d_year_min, d_month_min, d_day_min, d_hour_min, d_min_min, d_sec_min);
  unixtimeStop  = getUnixTimeFrom_year_month_day_hour_min_sec( d_year_max, d_month_max, d_day_max, d_hour_max, d_min_max, d_sec_max);    
  double extractedPower;
  double extractedPower_sec6;
  double extractedPower_sec5;
  double extractedPower_sec4;
  double extractedPower_sec3;
  double extractedPower_sec2;
  double extractedPower_sec1;

  double waterFlux;
  double waterFlux2;
  //waterFlux = 1.2/60.0;//kg/s
  //waterFlux = 2.20/3.0/60.0;//kg/s
  //waterFlux2 = 1.75/3.0/60.0;//kg/s
  //Tue Nov 13 11:21:32 JST 2018
  //waterFlux = 3.25/6.0/60.0;//kg/s
  //waterFlux2 = 3.24/6.0/60.0;//kg/s
  //Wed Nov 14 10:33:19 JST 2018
  //waterFlux = 4.4/6.0/60.0;//kg/s
  //waterFlux2 = 4.4/6.0/60.0;//kg/s
  waterFlux = totflux/6.0/60.0;//kg/s
  waterFlux2 = totflux/6.0/60.0;//kg/s

  double c_water   = 4180.6;//J/kg/K
  double elePower = 120.0;
  
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if( unixTime > unixtimeStart && unixTime < unixtimeStop){
      h1_dummyHisto->Fill(1);
      if(jentry%dataDivision==0){
	for(i = 0;i<nChannels;i++){
	  //gr_dummyGraph[i]->SetPoint(gr_dummyGraph[i]->GetN(), gr_dummyGraph[i]->GetN(), rnd->Gaus(0.0,1.0));
	  //h1_dummyHistoArr[i]->Fill(rnd->Gaus(0.0,1.0));
	  //h2_dummyHistoArr[i]->Fill(rnd->Gaus(0.0,1.0),rnd->Gaus(0.0,1.0));
	  //pr_dummyArr[i]->Fill(rnd->Uniform(0.0,10.0),rnd->Gaus(1.0,1.0));
	  gr_t_vs_time[i]->SetPoint(gr_t_vs_time[i]->GetN(), unixTime, temperatureGL[i]);
	}
	extractedPower = (temperatureGL[1] - temperatureGL[0]) * waterFlux * c_water;

	extractedPower_sec6 = (temperatureGL[1] - temperatureGL[0]) * waterFlux * c_water;
	extractedPower_sec5 = (temperatureGL[4] - temperatureGL[3]) * waterFlux * c_water;
	extractedPower_sec4 = (temperatureGL[7] - temperatureGL[6]) * waterFlux * c_water;

	extractedPower_sec3 = (temperatureGL[10] - temperatureGL[11]) * waterFlux2 * c_water;
	extractedPower_sec2 = (temperatureGL[13] - temperatureGL[14]) * waterFlux2 * c_water;
	extractedPower_sec1 = (temperatureGL[17] - temperatureGL[16]) * waterFlux2 * c_water;

	h1_extractedPower->Fill(extractedPower);
	h1_extractedPower_sec6->Fill(extractedPower_sec6);
	h1_extractedPower_sec5->Fill(extractedPower_sec5);
	h1_extractedPower_sec4->Fill(extractedPower_sec4);
	h1_extractedPower_sec3->Fill(extractedPower_sec3);
	h1_extractedPower_sec2->Fill(extractedPower_sec2);
	h1_extractedPower_sec1->Fill(extractedPower_sec1);
	gr_extractedPower_vs_time->SetPoint(gr_extractedPower_vs_time->GetN(), unixTime, extractedPower);
	gr_extractedPower_vs_time_sec6->SetPoint(gr_extractedPower_vs_time_sec6->GetN(), unixTime, extractedPower_sec6);
	gr_extractedPower_vs_time_sec5->SetPoint(gr_extractedPower_vs_time_sec5->GetN(), unixTime, extractedPower_sec5);
	gr_extractedPower_vs_time_sec4->SetPoint(gr_extractedPower_vs_time_sec4->GetN(), unixTime, extractedPower_sec4);
	gr_extractedPower_vs_time_sec3->SetPoint(gr_extractedPower_vs_time_sec3->GetN(), unixTime, extractedPower_sec3);
	gr_extractedPower_vs_time_sec2->SetPoint(gr_extractedPower_vs_time_sec2->GetN(), unixTime, extractedPower_sec2);
	gr_extractedPower_vs_time_sec1->SetPoint(gr_extractedPower_vs_time_sec1->GetN(), unixTime, extractedPower_sec1);
	gr_delta_extractedPower_sec6_m_sec2->SetPoint(gr_delta_extractedPower_sec6_m_sec2->GetN(), unixTime, extractedPower_sec6 - extractedPower_sec2);	
	gr_delta_temp_sec6_m_sec2_vs_time->SetPoint(gr_delta_temp_sec6_m_sec2_vs_time->GetN(), unixTime, temperatureGL[1] - temperatureGL[13]);	
	gr_elePower_vs_time->SetPoint(gr_elePower_vs_time->GetN(), unixTime, elePower);
	gr_extractedPower_vs_temperature->SetPoint(gr_extractedPower_vs_temperature->GetN(), temperatureGL[6], extractedPower);
	pr_extractedPower_vs_temperature->Fill(temperatureGL[6], extractedPower);
	gr_elePower_vs_time_norm->SetPoint(gr_elePower_vs_time_norm->GetN(), unixTime, elePower/normVal);
	gr_extractedPower_vs_time_norm->SetPoint(gr_extractedPower_vs_time_norm->GetN(), unixTime, extractedPower/normVal);
      }
    }
  }
  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  for(i = 0;i<nChannels;i++){
    gr_t_vs_time[i]->Write();
    //gr_dummyGraph[i]->Write();
    //h1_dummyHistoArr[i]->Write();
    //h2_dummyHistoArr[i]->Write();
    //pr_dummyArr[i]->Write();
  }
  h1_dummyHisto->Write();
  gr_extractedPower_vs_time->Write();
  gr_extractedPower_vs_time_sec6->Write();
  gr_extractedPower_vs_time_sec5->Write();
  gr_extractedPower_vs_time_sec4->Write();
  gr_extractedPower_vs_time_sec3->Write();
  gr_extractedPower_vs_time_sec2->Write();
  gr_extractedPower_vs_time_sec1->Write();
  gr_delta_extractedPower_sec6_m_sec2->Write();
  gr_delta_temp_sec6_m_sec2_vs_time->Write();
  gr_elePower_vs_time->Write();
  gr_extractedPower_vs_temperature->Write();
  pr_extractedPower_vs_temperature->Write();
  h1_extractedPower->Write();
  h1_extractedPower_sec6->Write();
  h1_extractedPower_sec5->Write();
  h1_extractedPower_sec4->Write();
  h1_extractedPower_sec3->Write();
  h1_extractedPower_sec2->Write();
  h1_extractedPower_sec1->Write();
  gr_elePower_vs_time_norm->Write();
  gr_extractedPower_vs_time_norm->Write();
  rootFile->Close();
}

void anaGL840::readInputPar(TString fileIn,
			    double &d_year_min, double &d_month_min, double &d_day_min, double &d_hour_min, double &d_min_min, double &d_sec_min,
			    double &d_year_max, double &d_month_max, double &d_day_max, double &d_hour_max, double &d_min_max, double &d_sec_max,
			    double &totflux){

  string mot;
  ifstream indata;
  indata.open(fileIn.Data()); 
  assert(indata.is_open());
  //cout<<indata.is_open()<<endl;
  cout<<" Reading of the input parameters ---> "<<fileIn<<endl;
  while (indata >> mot ){
    //cout<<" New word: "<<mot<<endl;
    if(mot == "timeMin:")
      indata  >> d_year_min >> d_month_min >> d_day_min >> d_hour_min >> d_min_min >> d_sec_min;
    if(mot == "timeMax:")
      indata  >> d_year_max >> d_month_max >> d_day_max >> d_hour_max >> d_min_max >> d_sec_max;
    if(mot == "totalWaterFlux:")
      indata  >> totflux;
  }
}
