/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Oct 15 16:09:59 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TKey.h>
#include <TClass.h>
#include <TMultiGraph.h>

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

// histOption = "-v"  <--- Transmitance
// histOption = "!-v" <--- Transmitance Length
void list_TGraph(TString hname = "./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root",  
		 TString histOption = "-v", TString plotsOption = "yes", Int_t verboseLevel = 0){

  cout<<"hname        = "<<hname<<endl
      <<"histOption   = "<<histOption<<endl
      <<"plotsOption  = "<<plotsOption<<endl
      <<"verboseLevel = "<<verboseLevel<<endl;

  TGraph *grColl[1000];

  TString grTitle;

  TGraph *gr_A_norm;
  TGraph *gr_A_L_norm;
  TGraph *gr_B_norm;
  TGraph *gr_B_L_norm;
  
  const char *fname = hname;
  TKey *key;
  TFile *f = TFile::Open(fname, "READ");
  if (!f || f->IsZombie()) {
    cout << "Unable to open " << fname << " for reading..." <<endl;
    return;
  }
  Int_t total = 0;
  TIter next((TList *)f->GetListOfKeys());
  while (key = (TKey *)next()) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (cl->InheritsFrom("TGraph")) {
      // the following line is not needed if you only want 
      // to count the histograms
      TGraph *h = (TGraph *)key->ReadObj();
      grTitle = h->GetTitle();
      //gr_version_2.0_serial_B179_id_CAd16-30_index_1.0565_translength_36.0_thick_20.1
      //gr_version_2.0_serial_B179_id_CAd16-30_index_1.0565_translength_36.0_thick_20.1_trLength

      //680 Histo fles ound: gr_A_norm - gr_A_norm
      //681 Histo fles ound: gr_A_L_norm - gr_A_L_norm
      //682 Histo fles ound: gr_B_norm - gr_B_norm
      //683 Histo fles ound: gr_B_L_norm - gr_B_L_norm

      if(grTitle.Contains("gr_A_norm"))
	gr_A_norm = new TGraph(*h);
      if(grTitle.Contains("gr_A_L_norm"))
	gr_A_L_norm = new TGraph(*h);
      if(grTitle.Contains("gr_B_norm"))
	gr_B_norm = new TGraph(*h);
      if(grTitle.Contains("gr_B_L_norm"))
	gr_B_L_norm = new TGraph(*h);  
      if(verboseLevel>0)
	cout << " Histo files found: " << h->GetName() << " - " << h->GetTitle() << endl;
      if(grTitle.Contains("version")){
	if(histOption=="-v"){
	  if(!grTitle.Contains("_trLength")){
	    grColl[total] = new TGraph(*h);
	    total++;
	  }
	}
	else{
	  if(grTitle.Contains("_trLength")){
	    grColl[total] = new TGraph(*h);
	    //grColl[total]->Draw();
	    total++;
	  }
	}
      }
    }
  }

  //grColl[0]->Draw();
  //grColl[1]->Draw("sames");
  
  cout << "Found " << total << " TGraph" << endl;
  
  if(plotsOption == "yes"){
  
    TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,800);
    
    c1->SetRightMargin(0.03);
    c1->SetLeftMargin(0.09);
    c1->SetTopMargin(0.09);
    c1->SetBottomMargin(0.09);
    
    gStyle->SetPalette(1);
    gStyle->SetFrameBorderMode(0);
    gROOT->ForceStyle();
    gStyle->SetStatColor(kWhite);
    //gStyle->SetOptStat(kFALSE);
    
    gPad->SetGridx();
    gPad->SetGridy();
    
    TString gtitle;
    TMultiGraph *mg = new TMultiGraph();
    for(Int_t j = 0;j<total;j++){
      grColl[j]->SetLineWidth(2.0);
      gtitle = grColl[j]->GetTitle();
      if(gtitle.Contains("B"))
	grColl[j]->SetLineColor(kRed);
      mg->Add(grColl[j]);
    }
    
    if(histOption=="-v"){
      gr_A_norm->SetLineWidth(6.0);
      gr_A_norm->SetLineColor(kBlue);
      gr_B_norm->SetLineWidth(6.0);
      gr_B_norm->SetLineColor(kBlue);
      mg->SetMaximum(100.0);
    }
    else{
      gr_A_L_norm->SetLineWidth(6.0);
      gr_A_L_norm->SetLineColor(kBlue);
      gr_B_L_norm->SetLineWidth(6.0);
      gr_B_L_norm->SetLineColor(kBlue);
      mg->SetMaximum(500.0);
    }
    
    mg->SetMinimum(0.0);
    if(histOption=="-v")
      mg->SetMaximum(100.0);
    else
      mg->SetMaximum(500.0);
    
    mg->Draw("AL");
    
    if(histOption=="-v"){
      gr_A_norm->Draw("same");
      gr_B_norm->Draw("same");
    }
    else{
      gr_A_L_norm->Draw("same");
      gr_B_L_norm->Draw("same");
    }

    mg->GetXaxis()->SetTitle("#lambda, nm");
    if(histOption=="-v")
      mg->GetYaxis()->SetTitle("Transmittance, %");
    else
      mg->GetYaxis()->SetTitle("Transmittance lenght, mm");
    
  }

}

#ifdef LIST_TGRAPH_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 5){
    TString hname = argv[1];
    TString histOption = argv[2];
    TString plotsOption = argv[3];
    Int_t verboseLevel = atoi(argv[4]);
    list_TGraph(hname,histOption,plotsOption,verboseLevel);
    return 0;
  }
  list_TGraph();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef LIST_TGRAPH_MAIN
