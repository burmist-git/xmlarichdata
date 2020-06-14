/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Apr 15 19:36:34 JST 2018                                         *
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

TGraph *quartzAbsorbtion_vs_wavelength(){

  const int num = 36;
  double WaveLength[num];
  //double Absorption[num];
  //double AirAbsorption[num];
  //double AirRefractiveIndex[num];
  //double PhotonEnergy[num];

  // Absorption of quartz per 1m
  double QuartzAbsorption[num] =
    {0.999572036,0.999544661,0.999515062,0.999483019,0.999448285,
     0.999410586,0.999369611,0.999325013,0.999276402,0.999223336,
     0.999165317,0.999101778,0.999032079,0.998955488,0.998871172,
     0.998778177,0.99867541 ,0.998561611,0.998435332,0.998294892,
     0.998138345,0.997963425,0.997767484,0.997547418,0.99729958 ,
     0.99701966 ,0.99670255 ,0.996342167,0.995931242,0.995461041,
     0.994921022,0.994298396,0.993577567,0.992739402,0.991760297,
     0.990610945};

  //double nanometer = 1.0E-9;
  for (int i=0; i<num; i++) {
    //PhotonEnergy[num - (i+1)] = 2*TMath::Pi()/((300 + i*10)/0.197*1.0e6);
    WaveLength[num - (i+1)] = (300 + i*10);//nm

    /* Absorption is given per length and G4 needs mean free path
       length, calculate it here
       mean free path length - taken as probablility equal 1/e
       that the photon will be absorbed */
    QuartzAbsorption[i] = (-1)/log(QuartzAbsorption[i])/1000.0;
    //EpotekAbsorption[i] = (-1)/log(EpotekAbsorption[i])*
    //epotekBarJoint.thickness;
  }

  /*
  double QuartzRefractiveIndex[num] =
    {1.456535,1.456812,1.4571  ,1.457399,1.457712,1.458038,
     1.458378,1.458735,1.459108,1.4595  ,1.459911,1.460344,
     1.460799,1.46128 ,1.461789,1.462326,1.462897,1.463502,
     1.464146,1.464833,1.465566,1.46635 ,1.46719 ,1.468094,
     1.469066,1.470116,1.471252,1.472485,1.473826,1.475289,
     1.476891,1.478651,1.480592,1.482739,1.485127,1.487793};
  */

  TCanvas *c1 = new TCanvas("c1","canva", 10, 10, 800, 700);
  c1->SetFillColor(kWhite);

  //TGraph *gr1_pr1 = new TGraph( num, PhotonEnergy, QuartzAbsorption );
  TGraph *gr1_pr1 = new TGraph( num, WaveLength, QuartzAbsorption );
  gr1_pr1->SetName("");
  gr1_pr1->SetTitle("");
  gr1_pr1->SetLineWidth(3.0);
  gr1_pr1->GetXaxis()->SetTitle("#lambda, nm");
  gr1_pr1->GetYaxis()->SetTitle("Free path length, km");
  gr1_pr1->Draw("APL");


  TF1 *f1 = new TF1("f1","1239.84/x",1.9,4);
  f1->GetName();
  TGaxis *axis = new TGaxis( 309.4, -0.4, 651.5, -0.4, "f1", 510, "L+", 1);
  //axis->SetLabelColor(kRed);
  axis->SetTitle("h#nu, eV");
  axis->Draw();

  return gr1_pr1;
}
}//namespace xmlarichdata{
