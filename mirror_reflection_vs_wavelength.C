/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Apr 15 19:30:18 JST 2018                                         *
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

TGraph *mirror_reflection_vs_wavelength(){

  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  
  const int num2 = 36;
  double WaveLength[num2];
  //double PhotonEnergy[num2];
  double MirrorReflectivity[num2]=
    {0.87,0.88,0.885,0.89,0.895,0.9,0.905,0.91,0.915,0.92,0.923,0.9245,
     0.926,0.928,0.93,0.935,0.936,0.937,0.938,0.94,0.94,0.939,0.9382,
     0.938,0.937,0.937,0.936,0.935,0.934,0.932,0.93,0.928,0.926,0.924,
     0.922,0.92};
  
  for (int i=0; i<num2; i++) {
    //PhotonEnergy[num2 - (i+1)] = 2*TMath::Pi()/((300 + i*10)/0.197*1.0e6);
    WaveLength[num2 - (i+1)] = (300 + i*10);//nm
  }

  TCanvas *c1 = new TCanvas("c1","canva", 10, 10, 800, 700);
  c1->SetFillColor(kWhite);

  TGraph *gr1_pr1 = new TGraph( num2, WaveLength, MirrorReflectivity);
  gr1_pr1->SetName("");
  gr1_pr1->SetTitle("");
  gr1_pr1->SetLineWidth(3.0);
  gr1_pr1->GetXaxis()->SetTitle("#lambda, nm");
  gr1_pr1->GetYaxis()->SetTitle("Mirror reflectivity");
  gr1_pr1->Draw("APL");
  
  TF1 *f1 = new TF1("f1","1239.84/x",1.9,4);
  f1->GetName();
  TGaxis *axis = new TGaxis( 309.4, 0.855, 651.5, 0.855, "f1", 510, "L+", 1);
  //axis->SetLabelColor(kRed);
  axis->SetTitle("h#nu, eV");
  axis->Draw();

  return gr1_pr1;
}
}//namespace xmlarichdata{


