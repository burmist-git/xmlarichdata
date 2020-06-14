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

Int_t plotsGL840csv_Power(){

  TString fileN;
  TString objectName;
  TString mgTitle;
  Float_t waterFluxXXXX = 0.0;
  Float_t waterTemperatureXXXX = 0.0;
  //Mon Nov  5 10:34:24 JST 2018
  //fileN = "./dataGL840/181104-113624.CSV.CV.root_hist.root";
  // Wed Nov  7 10:46:13 JST 2018
  //fileN = "./dataGL840/181106-124017.CSV.CV.root_hist.root";
  //Thu Nov  8 10:04:36 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181107-102520.CSV.CV.root_hist.root";
  //Fri Nov  9 11:32:13 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181108-104031.CSV.CV.root_hist.root";    
  //Sat Nov 10 11:28:01 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181109-114941.CSV.CV.root_hist.root";
  //Sun Nov 11 13:55:50 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181110-112429.CSV.CV.root_hist.root";
  // Mon Nov 12 10:07:31 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181111-115956.CSV.CV.root_hist.root";
  //Tue Nov 13 11:10:07 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181112-095812.CSV.CV.root_hist.root";
  //Wed Nov 14 10:24:14 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181113-110656.CSV.CV.root_hist.root";
  //Thu Nov 15 10:31:27 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181114-105537.CSV.CV.root_hist.root";
  //Fri Nov 16 11:28:41 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -df 3.2
  //fileN = "./dataGL840/181115-103156.CSV.CV.root_hist.root";
  //Fri Nov 16 16:44:37 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -df 4.2
  //fileN = "./dataGL840/181116-112357.CSV.CV.root_hist.root";
  //Sat Nov 17 11:36:48 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
  //fileN = "./dataGL840/181116-155044.CSV.CV.root_hist.root";
  //Sun Nov 18 14:31:52 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
  //fileN = "./dataGL840/181117-113241.CSV.CV.root_hist.root";
  //Mon Nov 19 10:00:07 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
  //fileN = "./dataGL840/181118-134000.CSV.CV.root_hist.root";
  //Mon Nov 19 16:10:00 JST 2018
  //source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
  //fileN = "./dataGL840/181116-155044_181118-134000.CSV.CV.root_hist.root";
  //Tue Nov 20 11:52:27 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
  //fileN = "./dataGL840/181119-095824.CSV.CV.root_hist.root";
  //Wed Nov 21 15:59:15 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181120-111524.CSV.CV.root_hist.root";
  //Thu Nov 22 11:43:41 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181121-160847.CSV.CV.root_hist.root";
  //Thu Nov 22 16:01:38 JST 2018
  fileN = "./dataGL840/18xxxx-xxxxxx.CSV.CV.root_hist.root";
  waterFluxXXXX=4.2;
  TString waterFluxXXXXstr = "";
  waterFluxXXXXstr += waterFluxXXXX;
  waterTemperatureXXXX=20.0;
  mgTitle="Total water flux : ";
  //mgTitle += waterFluxXXXX;
  mgTitle += waterFluxXXXXstr[0];
  mgTitle += waterFluxXXXXstr[1];
  mgTitle += waterFluxXXXXstr[2];
  mgTitle += waterFluxXXXXstr[3];
  mgTitle += "L/min, water @ ";
  mgTitle += waterTemperatureXXXX;
  mgTitle += " ^{o}C";
  //mgTitle="Total water flux : 4.2 L/min, water @ 20 ^{o}C";
  //mgTitle="Total water flux : 4.4 L/min";
  //mgTitle="Total water flux : 2.4 L/min";
  //mgTitle="Total water flux : 3.2 L/min";
  //mgTitle="Total water flux : 4.1 L/min, water @ 20 ^{o}C";
  
  cout<<"fileN = "<<fileN<<endl;
  
  TFile *f1 = new TFile(fileN.Data());

  TGraph *gr_extractedPower_vs_time_sec6 = (TGraph*)f1->Get("gr_extractedPower_vs_time_sec6");
  TGraph *gr_extractedPower_vs_time_sec5 = (TGraph*)f1->Get("gr_extractedPower_vs_time_sec5");
  TGraph *gr_extractedPower_vs_time_sec4 = (TGraph*)f1->Get("gr_extractedPower_vs_time_sec4");
  TGraph *gr_extractedPower_vs_time_sec3 = (TGraph*)f1->Get("gr_extractedPower_vs_time_sec3");
  TGraph *gr_extractedPower_vs_time_sec2 = (TGraph*)f1->Get("gr_extractedPower_vs_time_sec2");
  TGraph *gr_extractedPower_vs_time_sec1 = (TGraph*)f1->Get("gr_extractedPower_vs_time_sec1");
  TGraph *gr_delta_extractedPower_sec6_m_sec2 = (TGraph*)f1->Get("gr_delta_extractedPower_sec6_m_sec2");
  TGraph *gr_delta_temp_sec6_m_sec2_vs_time = (TGraph*)f1->Get("gr_delta_temp_sec6_m_sec2_vs_time");
  TGraph *gr_elePower_vs_time = (TGraph*)f1->Get("gr_elePower_vs_time");
  
  TH1D *h1_extractedPower_sec6 = (TH1D*)f1->Get("h1_extractedPower_sec6");
  TH1D *h1_extractedPower_sec5 = (TH1D*)f1->Get("h1_extractedPower_sec5");
  TH1D *h1_extractedPower_sec4 = (TH1D*)f1->Get("h1_extractedPower_sec4");
  TH1D *h1_extractedPower_sec3 = (TH1D*)f1->Get("h1_extractedPower_sec3");
  TH1D *h1_extractedPower_sec2 = (TH1D*)f1->Get("h1_extractedPower_sec2");
  TH1D *h1_extractedPower_sec1 = (TH1D*)f1->Get("h1_extractedPower_sec1");
    
  const Int_t nChannels = 10;
  //const Int_t colorArr[10] = {    kBlack,     kRed,  kGreen + 3, kCyan - 3, kBlue + 1,
  //				        kGray+1, kMagenta, kYellow + 2,  kRed - 2, kBlue - 6};
  const Int_t colorArr[nChannels] = {    kBlack,     kRed,  kGreen + 3, kCyan - 3, kBlue + 1,
  				        kGray+1, kMagenta, kYellow + 2,  kRed - 2, kBlue - 6};

  //const Int_t markerArr[10] = { 20, 20, 20, 20, 20,
  //				       21, 21, 21, 21, 21};
  const Int_t markerArr[nChannels] = { 20, 20, 20, 21, 21,
  				       21, 21, 21, 21, 21};
  
  //h1_1->Rebin(4);
  //h1_1->SetTitle("");

  Int_t screen_height = 1080;
  Int_t screen_width = 1920;
  
  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,screen_width,screen_height);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
 
  TMultiGraph *mg = new TMultiGraph("mg", mgTitle.Data());
  
  gr_extractedPower_vs_time_sec6->SetLineColor(colorArr[0]);
  gr_extractedPower_vs_time_sec6->SetLineWidth(3.0);
  gr_extractedPower_vs_time_sec6->SetMarkerColor(colorArr[0]);
  gr_extractedPower_vs_time_sec6->SetMarkerStyle(markerArr[0]);
  gr_extractedPower_vs_time_sec5->SetLineColor(colorArr[1]);
  gr_extractedPower_vs_time_sec5->SetLineWidth(3.0);
  gr_extractedPower_vs_time_sec5->SetMarkerColor(colorArr[1]);
  gr_extractedPower_vs_time_sec5->SetMarkerStyle(markerArr[1]);
  gr_extractedPower_vs_time_sec4->SetLineColor(colorArr[2]);
  gr_extractedPower_vs_time_sec4->SetLineWidth(3.0);
  gr_extractedPower_vs_time_sec4->SetMarkerColor(colorArr[2]);
  gr_extractedPower_vs_time_sec4->SetMarkerStyle(markerArr[2]);
  gr_extractedPower_vs_time_sec3->SetLineColor(colorArr[3]);
  gr_extractedPower_vs_time_sec3->SetLineWidth(3.0);
  gr_extractedPower_vs_time_sec3->SetMarkerColor(colorArr[3]);
  gr_extractedPower_vs_time_sec3->SetMarkerStyle(markerArr[3]);
  gr_extractedPower_vs_time_sec2->SetLineColor(colorArr[4]);
  gr_extractedPower_vs_time_sec2->SetLineWidth(3.0);
  gr_extractedPower_vs_time_sec2->SetMarkerColor(colorArr[4]);
  gr_extractedPower_vs_time_sec2->SetMarkerStyle(markerArr[4]);
  gr_extractedPower_vs_time_sec1->SetLineColor(colorArr[5]);
  gr_extractedPower_vs_time_sec1->SetLineWidth(3.0);
  gr_extractedPower_vs_time_sec1->SetMarkerColor(colorArr[5]);
  gr_extractedPower_vs_time_sec1->SetMarkerStyle(markerArr[5]);  
  gr_elePower_vs_time->SetLineColor(colorArr[9]);
  gr_elePower_vs_time->SetLineWidth(3.0);
  gr_elePower_vs_time->SetMarkerColor(colorArr[9]);
  gr_elePower_vs_time->SetMarkerStyle(markerArr[9]);

  gr_delta_extractedPower_sec6_m_sec2->SetLineColor(colorArr[0]);
  gr_delta_extractedPower_sec6_m_sec2->SetLineWidth(3.0);
  gr_delta_extractedPower_sec6_m_sec2->SetMarkerColor(colorArr[0]);
  gr_delta_extractedPower_sec6_m_sec2->SetMarkerStyle(markerArr[0]);

  gr_delta_temp_sec6_m_sec2_vs_time->SetLineColor(colorArr[0]);
  gr_delta_temp_sec6_m_sec2_vs_time->SetLineWidth(3.0);
  gr_delta_temp_sec6_m_sec2_vs_time->SetMarkerColor(colorArr[0]);
  gr_delta_temp_sec6_m_sec2_vs_time->SetMarkerStyle(markerArr[0]);
 
  mg->Add(gr_extractedPower_vs_time_sec6);
  mg->Add(gr_extractedPower_vs_time_sec5);
  mg->Add(gr_extractedPower_vs_time_sec4);
  mg->Add(gr_extractedPower_vs_time_sec3);
  mg->Add(gr_extractedPower_vs_time_sec2);
  mg->Add(gr_extractedPower_vs_time_sec1);
  mg->Add(gr_elePower_vs_time);
  mg->SetMinimum(0.0);
  mg->Draw("apl");
  
  mg->GetXaxis()->SetTitle("Time, h");
  mg->GetYaxis()->SetTitle("Power, W");
  mg->GetXaxis()->SetTimeDisplay(1);  
  
  TString legInfo;
  //TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  TLegend *leg = new TLegend(0.905,0.09,0.995,0.97,"","brNDC");
  leg->AddEntry(gr_extractedPower_vs_time_sec6, "sec6", "apl");
  leg->AddEntry(gr_extractedPower_vs_time_sec5, "sec5", "apl");
  leg->AddEntry(gr_extractedPower_vs_time_sec4, "sec4", "apl");
  leg->AddEntry(gr_extractedPower_vs_time_sec3, "sec3", "apl");
  leg->AddEntry(gr_extractedPower_vs_time_sec2, "sec2", "apl");
  leg->AddEntry(gr_extractedPower_vs_time_sec1, "sec1", "apl");
  leg->AddEntry(gr_elePower_vs_time, "elec", "apl");
  leg->Draw();


  //////////// 1D histo ////////////
  h1_extractedPower_sec6->SetLineColor(colorArr[0]);
  h1_extractedPower_sec6->SetLineWidth(3.0);
  h1_extractedPower_sec5->SetLineColor(colorArr[1]);
  h1_extractedPower_sec5->SetLineWidth(3.0);
  h1_extractedPower_sec4->SetLineColor(colorArr[2]);
  h1_extractedPower_sec4->SetLineWidth(3.0);
  h1_extractedPower_sec3->SetLineColor(colorArr[3]);
  h1_extractedPower_sec3->SetLineWidth(3.0);
  h1_extractedPower_sec2->SetLineColor(colorArr[4]);
  h1_extractedPower_sec2->SetLineWidth(3.0);
  h1_extractedPower_sec1->SetLineColor(colorArr[5]);
  h1_extractedPower_sec1->SetLineWidth(3.0);
  //////////////////////////////////
  //h1_1->Draw();
  //h1_1->GetXaxis()->SetTitle("Value, Unit");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);

  TCanvas *c2 = new TCanvas("c2",fileN.Data(),20,20,screen_width,screen_height);
  h1_extractedPower_sec6->SetTitle(mgTitle.Data());
  h1_extractedPower_sec6->SetMaximum(10000);
  h1_extractedPower_sec6->Draw("");
  h1_extractedPower_sec6->GetXaxis()->SetTitle("Power, W");
  //h1_extractedPower_sec4->GetXaxis()->SetRangeUser(-0.13,-0.12);
  h1_extractedPower_sec5->Draw("sames");
  h1_extractedPower_sec4->Draw("sames");
  h1_extractedPower_sec3->Draw("sames");
  h1_extractedPower_sec2->Draw("sames");
  h1_extractedPower_sec1->Draw("sames");
  
  TCanvas *c3 = new TCanvas("c3",fileN.Data(),30,30,screen_width,screen_height);
  //gr_delta_extractedPower_sec6_m_sec2->Draw("apl");
  gr_delta_temp_sec6_m_sec2_vs_time->Draw("apl");
  gr_delta_temp_sec6_m_sec2_vs_time->GetXaxis()->SetTitle("Time, h");
  gr_delta_temp_sec6_m_sec2_vs_time->GetYaxis()->SetTitle("#Delta t, C^{o}");
  gr_delta_temp_sec6_m_sec2_vs_time->GetXaxis()->SetTimeDisplay(1);
  //h1_extractedPower_sec6->GetXaxis()->SetTitle("Time, h");
  //h1_extractedPower_sec6->GetYaxis()->SetTitle("#Delta power, W");
  
  return 0;
}
