/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue Apr 3 17:30:57 2018 +0200                                        *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#if !defined(PLOTS_MAIN)
# if !defined(__CLING__)
#include "libxmlarichdata.h"
# endif
#endif

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>

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

  Double_t ev_2_lambda_nm(Double_t ev_val){
    if(ev_val>0.0){
      return 1239.84242126909157/ev_val;
    }
    else{
      assert(0);
      return -999;
    }
    return -999;
  }

  //lambda nm to electron volts         
  Double_t lambda_nm_2_ev(Double_t lam){
    if(lam>0.0){
      return 1239.84242126909157/lam;
    }
    else{
      assert(0);
      return -999;
    }
    return -999;
  }
  
  TGraph *convert_TrLength_vs_Lambda_2_TrLength_vs_pe(TGraph *grTr_vs_Lam){
    return convert_TGraph_Lambda_vs_pe(grTr_vs_Lam);
  }

  TGraph *convert_TGraph_Lambda_vs_pe(TGraph *gr_vs_Lam){
    cout<<"Convert -> "<<gr_vs_Lam->GetTitle()<<endl;
    Double_t *xx = gr_vs_Lam->GetX();
    Double_t *yy = gr_vs_Lam->GetY();
    Double_t *x = new Double_t[gr_vs_Lam->GetN()];
    Double_t *y = new Double_t[gr_vs_Lam->GetN()];
    for(Int_t i = 0;i<gr_vs_Lam->GetN();i++){
      x[i] = lambda_nm_2_ev(xx[gr_vs_Lam->GetN() - i - 1]);
      y[i] = yy[gr_vs_Lam->GetN() - i - 1];
      //x[i] = 1239.84/xx[grTr_vs_Lam->GetN() - i - 1];
      //x[i] = i;
      //y[i] = i;
    }
    TGraph *g_vs_pe = new TGraph(gr_vs_Lam->GetN(),x,y);
    g_vs_pe->SetName(gr_vs_Lam->GetName());
    g_vs_pe->SetTitle(gr_vs_Lam->GetTitle());
    return g_vs_pe;
  }
  
  void print_TGraph_info( TGraph *gr, TString printMod = "g4"){
    Double_t xx;
    Double_t yy;
    //
    if(printMod == "n"){
      cout<<setw(10)<<" x = "<<setw(10)<<" y = "<<endl;
      for(Int_t i = 0;i<gr->GetN();i++){
        gr->GetPoint( i, xx, yy);
	cout<<setw(10)<<i<<setw(10)<<xx<<setw(10)<<yy<<endl;
      }
      cout<<endl;
    }
    //
    if(printMod == "g4"){
      cout<<" x = "<<endl;
      for(Int_t i = 0;i<gr->GetN();i++){
        gr->GetPoint( i, xx, yy);
	cout<<xx<<",";
      }
      cout<<endl;
      cout<<" y = "<<endl;
      for(Int_t i = 0;i<gr->GetN();i++){
	gr->GetPoint( i, xx, yy);
        cout<<yy<<",";
      }
      cout<<endl;
    }
    //    
    if(printMod == "basf2"){
      for(Int_t i = 0;i<gr->GetN();i++){
        gr->GetPoint( i, xx, yy);
	cout<<"<value energy=\""<<xx<<"\">"<<yy<<"</value>"<<endl;
      }
    }
  }

  void printToFile_TGraph_info( ofstream &outFile, TGraph *gr, TString printMod = "basf2"){
    Double_t xx;
    Double_t yy;
    //cout<<"printToFile_TGraph_info"<<endl;
    //
    if(printMod == "n"){
      outFile<<setw(10)<<" x = "<<setw(10)<<" y = "<<endl;
      for(Int_t i = 0;i<gr->GetN();i++){
        gr->GetPoint( i, xx, yy);
	outFile<<setw(10)<<i<<setw(10)<<xx<<setw(10)<<yy<<endl;
      }
      outFile<<endl;
    }
    //
    if(printMod == "g4"){
      outFile<<" x = "<<endl;
      for(Int_t i = 0;i<gr->GetN();i++){
        gr->GetPoint( i, xx, yy);
	outFile<<xx<<",";
      }
      outFile<<endl;
      outFile<<" y = "<<endl;
      for(Int_t i = 0;i<gr->GetN();i++){
	gr->GetPoint( i, xx, yy);
        outFile<<yy<<",";
      }
      outFile<<endl;
    }
    //    
    if(printMod == "basf2"){
      for(Int_t i = 0;i<gr->GetN();i++){
        gr->GetPoint( i, xx, yy);
	outFile<<"      <value energy=\""<<xx<<"\">"<<yy<<"</value>"<<endl;
	//cout<<"<value energy=\""<<xx<<"\">"<<yy<<"</value>"<<endl;
      }
    }
  }

  
}//namespace xmlarichdata{
