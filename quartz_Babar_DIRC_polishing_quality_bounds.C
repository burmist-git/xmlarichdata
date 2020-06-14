/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Apr 15 19:37:24 JST 2018                                         *
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

TGraph *quartz_Babar_DIRC_polishing_quality_bounds(){
  
  //from G4
  /* this function simulate the internal reflection probability per one 
     bounce - each time photon bounced this function is called 
     and the reflection is tested if photon reflects or disappear - 
     this function estimates loss of photons during imperfections 
     of bar 
  */

  double opticalPhotonEnergy[36]={
    1.90744901082931,1.93725290162352,1.96800294768103,1.99974493070815,
    2.03252763449025,2.06640309506508,2.10142687633737,2.13765837420526,
    2.17516115270009,2.21400331614116,2.25425792188918,2.29600343896121,
    2.33932425856425,2.38431126353664,2.43106246478245,2.4796837140781,
    2.53028950416133,2.58300386883136,2.63796139795543,2.6953083848675,
    2.75520412675345,2.81782240236148,2.88335315590477,2.95200442152155,
    3.02400452936354,3.09960464259763,3.17908168471551,3.26274172905013,
    3.35092393794338,3.44400515844181,3.54240530582586,3.64659369717368,
    3.75709653648197,3.87450580324703,3.99948986141629,4.13280619013017};
  
  double internalReflectivity[36] =
    {0.999895281,0.999891334,0.999885743,0.999878696,0.999870426,
     0.9998612,0.999851309,0.999841055,0.999830735,0.999820635,0.999811012,
     0.999802084,0.999794018,0.999786917,0.999780807,0.999775625,
     0.999771209,0.999767282,0.999763441,0.999759146,0.999753706,
     0.999746266,0.999735798,0.999721084,0.999700708,0.99967304,
     0.999636227,0.999588178,0.999526552,0.999448747,0.999351887,
     0.999232808,0.99908805,0.998913839,0.998706078,0.998460335};

  Int_t i = 0;

  double wf[36];
  double prob[36];

  for(i = 0;i<36;i++){
    /* because the ratio between peak1 and peak2 did not correspond,
       the reflection probability was change to get the same 
       ration 2.1:1 => the original probability is multiplied by .9992 */
    //probability = probability*.9992;
    prob[i] = TMath::Power(internalReflectivity[i]*0.9992, 20);
    wf[i] = 1239.84/opticalPhotonEnergy[i];
    cout<<prob[i]<<endl;
  }

  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);

  TCanvas *c1 = new TCanvas("c1","canva", 10, 10, 800, 700);
  c1->SetFillColor(kWhite);

  TGraph *gr1_pr1 = new TGraph( 36, wf, prob );
  gr1_pr1->SetName("");
  gr1_pr1->SetTitle("");
  gr1_pr1->SetLineWidth(3.0);
  gr1_pr1->GetXaxis()->SetTitle("#lambda, nm");
  gr1_pr1->GetYaxis()->SetTitle("Reflection coefficient");
  gr1_pr1->Draw("APL");

  TF1 *f1 = new TF1("f1","1239.84/x",1.9,4);
  f1->GetName();
  TGaxis *axis = new TGaxis( 309.4, 0.95, 651.5, 0.95, "f1", 510, "L+", 1);
  //axis->SetLabelColor(kRed);
  axis->SetTitle("h#nu, eV");
  axis->Draw();

  return gr1_pr1;
}
}//namespace xmlarichdata{
