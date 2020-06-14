//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

//root
#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TVector3.h>

using namespace std;

Int_t aerogel_thickness_Vertion3(){

  TH1D *h1_thup = new TH1D("h1_thup","thup",17,18.5,20.5);
  TH1D *h1_thdown = new TH1D("h1_thdown","thdown",17,18.5,20.5);
  TH1D *h1_thupdown = new TH1D("h1_thupdown","thupdown",17,18.5,20.5);
  TH1D *h1_tot = new TH1D("h1_tot","h1_tot",17*2,18.5*2,20.5*2);

  string mot;
  double thup;
  double thdown;
  ifstream myfile("aerogel_thickness_Vertion3.dat");
  if(myfile.is_open()){
    //1   QWER         1         1      1.97      1.98
    while(myfile>>mot>>mot>>mot>>mot>>thup>>thdown){
      h1_thup->Fill(thup);
      h1_thdown->Fill(thdown);
      h1_thupdown->Fill(thup);
      h1_thupdown->Fill(thdown);
      h1_tot->Fill(thup + thdown);
    }
  } 
  else{
    cout << "Unable to open file"; 
  }  
  myfile.close();

  TCanvas *c1 = new TCanvas("c1","c1",10,10,600,600);
  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.09);
  c1->SetTopMargin(0.09);
  c1->SetBottomMargin(0.09);

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  //gPad->SetGridx();
  //gPad->SetGridy();


  //h1_thup->Draw();
  //h1_thdown->Draw("same");
  //h1_thupdown->Draw();

  h1_tot->SetTitle("");

  h1_tot->SetLineColor(kBlack);
  h1_tot->SetLineWidth(3.0);
  h1_tot->Draw();
  h1_tot->GetXaxis()->SetTitle("x, mm");


  return 0;
}
