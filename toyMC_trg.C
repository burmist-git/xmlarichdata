/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Wed Jun 20 14:43:07 JST 2018                                         *
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
#include <TLine.h>
#include <TRandom3.h>
#include <TMath.h>

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

TRandom3 *rnd = new TRandom3(123123);

void toyMC_trg(){
  
  //***************************************
  Double_t dTbunchXing = 10.0613;        //ns
  const Int_t nMemoryCell = 101;         //Hz
  Double_t singleMemoryCellLenght = 500; //ns
  Double_t trigDelayReal = 20000;        //ns
  Double_t dtrigDel = 250.0;               //ns
  Double_t sigTrig  = 18.0;              //ns
  Double_t sigArich = 1.0;               //ns
  Double_t sigTrk   = 2.0;               //ns
  Double_t sigTot   = TMath::Sqrt(sigTrig*sigTrig + sigArich*sigArich + sigTrk*sigTrk);
  //***************************************
  
  Double_t tEv = 0.0;
  Double_t tTrg = 0.0;
  Double_t tArichBit = 0.0;

  TH1D *h1_tEv  = new TH1D("h1_tEv","tEv",100,-5.0,singleMemoryCellLenght+5);
  TH1D *h1_tTrg = new TH1D("h1_tTrg","tTrg",100,trigDelayReal - 3*sigTot, singleMemoryCellLenght + trigDelayReal + 3*sigTot);
  TH1D *h1_dtTrgEv = new TH1D("h1_dtTrgEv","dtTrgEv",100,trigDelayReal - 4*sigTot, trigDelayReal + 4*sigTot);

  TH1D *h1_ARICHbit = new TH1D("h1_ARICHbit","ARICH bit",nMemoryCell,0.0,nMemoryCell*singleMemoryCellLenght);
  TH1D *h1_ARICHbitZoom = new TH1D("h1_ARICHbitZoom","ARICH bit zoom",4,trigDelayReal - singleMemoryCellLenght*2,trigDelayReal + singleMemoryCellLenght*2);

  for(Int_t i = 0;i<10000;i++){
    tEv = ((Int_t)rnd->Uniform(0.0,singleMemoryCellLenght/dTbunchXing))*dTbunchXing;
    h1_tEv->Fill(tEv);
    tTrg = tEv + trigDelayReal + rnd->Gaus(0.0,sigTot);
    h1_tTrg->Fill(tTrg);
    h1_dtTrgEv->Fill(tTrg - tEv);
    tArichBit = tTrg + dtrigDel;
    h1_ARICHbit->Fill(tArichBit);
    h1_ARICHbitZoom->Fill(tArichBit);
  }
  
  TFile* rootFile = new TFile("toyMC_trg.root", "RECREATE", " Histograms", 1);
  h1_tEv->Write();
  h1_tTrg->Write();
  h1_dtTrgEv->Write();
  h1_ARICHbit->Write();
  h1_ARICHbitZoom->Write();
  rootFile->Close();
  
}

#ifdef TOYMC_TRG
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 1){
    toyMC_trg();
    return 0;
  }
  toyMC_trg();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef TOYMC_TRG
