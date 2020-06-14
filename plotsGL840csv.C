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

TString getObjectName(TString namein, Int_t i);
void plotTemperatures(TString fileN,  Int_t shiftCh);


Int_t plotsGL840csv(){

  TString fileN;
  //fileN = "./hist.root";
  //fileN = "./histSingle.root";
  //Old before Tue Oct 16 14:37:12 JST 2018
  //fileN = "./dataGL840/180929-154859.CSV.CV.root_hist.root";
  //fileN = "./dataGL840/180930-173053.CSV.CV.root_hist.root";
  //fileN = "./dataGL840/180929-154859.CSV.CV.root_hist.root";
  //Tue Oct 16 14:37:12 JST 2018
  //fileN = "./dataGL840/181001-205815.CSV.CV.root_hist.root";
  //fileN = "./dataGL840/181009-103656.CSV.CV.root_hist.root";
  //fileN = "./dataGL840/181009-103725.CSV.CV.root_hist.root";
  //Wed Oct 17 13:52:37 JST 2018
  //fileN = "./dataGL840/181016-152600.CSV.CV.root_hist.root";
  //fileN = "./dataGL840/181016-152638.CSV.CV.root_hist.root";
  //Thu Oct 18 11:52:35 JST 2018
  //fileN = "./dataGL840/181017-135745.CSV.CV.root_hist.root";
  //Fri Oct 19 11:41:17 JST 2018
  //fileN = "./dataGL840/181018-114805.CSV.CV.root_hist.root";
  //Sat Oct 20 15:00:00 JST 2018
  //fileN = "./dataGL840/181019-113654.CSV.CV.root_hist.root";
  //Mon Oct 22 10:28:53 JST 2018
  //fileN = "./dataGL840/181021-102515.CSV.CV.root_hist.root";
  //fileN = "./dataGL840/181021-103202.CSV.CV.root_hist.root";
  //Mon Oct 22 21:13:19 JST 2018
  //fileN = "./dataGL840/181017-135745_181018-114805.root_hist.root";
  //Tue Oct 23 11:15:34 JST 2018
  //fileN = "./dataGL840/181022-102002.CSV.CV.root_hist.root";
  //Wed Oct 24 10:18:14 JST 2018
  //fileN = "./dataGL840/181023-114623.CSV.CV.root_hist.root";
  //Mon Oct 29 15:10:20 JST 2018
  //fileN = "./dataGL840/181023-114623.CSV.CV.root_hist.root";
  //Tue Oct 30 10:53:18 JST 2018
  //fileN = "./dataGL840/181028-155231.CSV.CV.root_hist.root";
  //Wed Oct 31 09:42:10 JST 2018
  //fileN = "./dataGL840/181030-103737.CSV.CV.root_hist.root";
  //Thu Nov  1 10:20:20 JST 2018
  //fileN = "./dataGL840/181031-093942.CSV.CV.root_hist.root";
  //Fri Nov  2 10:22:22 JST 2018
  //fileN = "./dataGL840/181101-101800.CSV.CV.root_hist.root";
  //Fri Nov  2 16:35:27 JST 2018
  //fileN = "./dataGL840/181102-103714.CSV.CV.root_hist.root";
  //Sat Nov  3 10:09:51 JST 2018
  //fileN = "./dataGL840/181102-164133.CSV.CV.root_hist.root";
  //Sun Nov  4 11:14:46 JST 2018
  //fileN = "./dataGL840/181103-103418.CSV.CV.root_hist.root";
  //Mon Nov  5 10:34:24 JST 2018
  //fileN = "./dataGL840/181104-113624.CSV.CV.root_hist.root";
  //Mon Nov  5 22:36:08 JST 2018
  //fileN = "./dataGL840/181105-204034.CSV.CV.root_hist.root";
  //Tue Nov  6 16:30:13 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181105-205453.CSV.CV.root_hist.root";
  //fileN = "./dataGL840/181106-101526.CSV.CV.root_hist.root";
  //Wed Nov  7 10:12:54 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181106-124017.CSV.CV.root_hist.root";
  //Thu Nov  8 10:04:36 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181107-102520.CSV.CV.root_hist.root";
  //Fri Nov  9 11:32:13 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181108-104031.CSV.CV.root_hist.root";
  //Sat Nov 10 11:28:01 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181109-114941.CSV.CV.root_hist.root";
  //Sun Nov 11 13:55:50 JST 2018 --> 20 channels
  //fileN = "./dataGL840/181110-112429.CSV.CV.root_hist.root";
  //Mon Nov 12 10:07:31 JST 2018 --> 20 channels
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
  //Mon Nov 19 15:48:13 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
  //fileN = "./dataGL840/181116-155044_181118-134000.CSV.CV.root_hist.root";
  //Tue Nov 20 11:52:27 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
  //fileN = "./dataGL840/181119-095824.CSV.CV.root_hist.root";
  //Wed Nov 21 15:59:15 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
  //fileN = "./dataGL840/181120-111524.CSV.CV.root_hist.root";
  //Thu Nov 22 11:43:41 JST 2018 --> 20 channels
  //source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
  //fileN = "./dataGL840/181121-160847.CSV.CV.root_hist.root";
  //Thu Nov 22 15:44:43 JST 2018
  fileN = "./dataGL840/18xxxx-xxxxxx.CSV.CV.root_hist.root";
  
  Int_t firstSetChannels = 0;
  Int_t secondSetChannels = 10;

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  Int_t screen_height = 1080;
  Int_t screen_width = 1920;

  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,screen_width,screen_height);
  plotTemperatures(fileN,firstSetChannels);
  c1->SetGridx();
  c1->SetGridy();
  //c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.09);
  c1->SetTopMargin(0.03);
  c1->SetBottomMargin(0.09);
  c1->Modified();
  c1->Update();
  
  TCanvas *c2 = new TCanvas("c2",fileN.Data(),20,20,1920,1080);
  plotTemperatures(fileN,secondSetChannels);
  c2->SetGridx();
  c2->SetGridy();
  //c2->SetRightMargin(0.03);
  c2->SetLeftMargin(0.09);
  c2->SetTopMargin(0.03);
  c2->SetBottomMargin(0.09);
  c2->Modified();
  c2->Update();

  return 0;
  
}

void plotTemperatures(TString fileN,  Int_t shiftCh){

  TString objectName;
  
  TString drawPowerAxis = "off";
  
  cout<<"fileN = "<<fileN<<endl;
  
  TFile *f1 = new TFile(fileN.Data());

  TH1D *h1_1 = (TH1D*)f1->Get("h1_dummyHisto");

  //const Int_t nChannels = 2;
  const Int_t nChannels = 10;
  TH1D *h1_Arr[nChannels];
  TGraph *gr_Arr[nChannels];
  Int_t i = 0;

  TGraph *gr_elePower_vs_time_norm = (TGraph*)f1->Get("gr_elePower_vs_time_norm");
  TGraph *gr_extractedPower_vs_time_norm = (TGraph*)f1->Get("gr_extractedPower_vs_time_norm");
    
  //const Int_t colorArr[10] = {    kBlack,     kRed,  kGreen + 3, kCyan - 3, kBlue + 1,
  //				        kGray+1, kMagenta, kYellow + 2,  kRed - 2, kBlue - 6};
  const Int_t colorArr[nChannels] = {    kBlack,     kRed,  kGreen + 3, kCyan - 3, kBlue + 1,
  				        kGray+1, kMagenta, kYellow + 2,  kRed - 2, kBlue - 6};

  //const Int_t markerArr[10] = { 20, 20, 20, 20, 20,
  //				       21, 21, 21, 21, 21};
  const Int_t markerArr[nChannels] = { 20, 20, 20, 20, 20,
  				       21, 21, 21, 21, 21};

  for(i = 0;i<nChannels;i++){
    //objectName=getObjectName("h1_dummyHistoArr",i);
    //cout<<objectName<<endl;
    //h1_Arr[i] = (TH1D*)f1->Get(objectName.Data());
    objectName=getObjectName("gr_t_vs_time",i+shiftCh);
    gr_Arr[i] = (TGraph*)f1->Get(objectName.Data());
  }
  
  //h1_1->Rebin(4);
  //h1_1->SetTitle("");
 
  h1_1->SetLineColor(kBlack);
  h1_1->SetLineWidth(3.0);

  //h1_1->Draw();
  //h1_1->GetXaxis()->SetTitle("Value, Unit");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);

  /*
  for(i = 0;i<nChannels;i++){
    h1_Arr[i]->SetLineColor(colorArr[i]);
    h1_Arr[i]->SetLineWidth(3.0);
    if(i == 0){
      h1_Arr[i]->Draw();
      h1_Arr[i]->GetXaxis()->SetTitle("Value, Unit");
      //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
    }
    else
      h1_Arr[i]->Draw("same");
  }
  
  //h1_1->Fit("gaus");
  TString legInfo;
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  for(i = 0;i<nChannels;i++){
    legInfo = "ch ";legInfo += i;
    leg->AddEntry(h1_Arr[i], legInfo.Data(), "l");
  }
  leg->Draw();
  */

  TMultiGraph *mg = new TMultiGraph();
  
  for(i = 0;i<nChannels;i++){
    gr_Arr[i]->SetLineColor(colorArr[i]);
    gr_Arr[i]->SetLineWidth(3.0);
    gr_Arr[i]->SetMarkerColor(colorArr[i]);
    gr_Arr[i]->SetMarkerStyle(markerArr[i]);
    mg->Add(gr_Arr[i]);
  }
  //mg->Add(gr_elePower_vs_time_norm);
  //mg->Add(gr_extractedPower_vs_time_norm);
  mg->SetMinimum(0.0);
  mg->Draw("apl");
  
  mg->GetXaxis()->SetTitle("Time, h");
  mg->GetYaxis()->SetTitle("Temperature, C^{o}");
  mg->GetXaxis()->SetTimeDisplay(1);
  
  TString legInfo;
  TLegend *leg = new TLegend(0.905,0.09,0.995,0.97,"","brNDC");
  for(i = 0;i<nChannels;i++){
    legInfo = "ch ";legInfo += i+1 + shiftCh;
    leg->AddEntry(gr_Arr[i], legInfo.Data(), "apl");
  }
  //leg->AddEntry(gr_elePower_vs_time_norm, "Electronics power", "al");
  //leg->AddEntry(gr_extractedPower_vs_time_norm, "Extracted power", "ap");
  leg->Draw();

  TAxis * yaxis = mg->GetHistogram()->GetYaxis();
  Double_t ymax = yaxis->GetXmax();
  Double_t ymin = yaxis->GetXmin();
  printf("min %f max %f\n", ymin, ymax);
  
  Double_t scale = 120.0 / 17.14286;
  Double_t rightmax = ymax * scale;

  if(drawPowerAxis == "yes"){
    //draw an axis on the right side
    TGaxis *axis = new TGaxis( gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),0, rightmax, 510, "+L");
    axis->SetLineColor(kRed);
    axis->SetLabelColor(kRed);
    axis->SetTitle("Power, W");
    axis->Draw();
  }
  
  //return 0;
}

TString getObjectName(TString namein, Int_t i){
  TString h1nameh = namein; h1nameh += "_"; h1nameh += "ch_"; h1nameh += i;
  return h1nameh;
}
