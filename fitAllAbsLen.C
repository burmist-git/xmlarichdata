/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Nov 27 22:23:08 2017 +0100                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "libxmlarichdata.h"
#else 
//my
#include "readAerogelInfoMap.C"
#endif

//my
#include "aerogelInfoMap.h"

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TList.h>
#include <TF1.h>
#include <TMath.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{

std::vector<aerogelInfoMap> fitAllAbsLen(TString fileN = "./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root",
					 TString fnameInfo = "./aerogelDataFromDB/aerogelInfoBis.dat",
					 TString fnameMap = "./aerogelDataFromDB/aerogelMap.dat",
					 TString pdfFolder = "./pdfdataFit/aerogel_xml_ver3/",
					 TString outFname = "./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3_fit.root",
					 TString outXMLfile = "./xmlData/aerogel_xml_ver3/aerogel_xml_ver3_fit.xml",
					 Float_t version = 3.0){
  cout<<"fileN      "<<fileN<<endl
      <<"fnameInfo  "<<fnameInfo<<endl
      <<"fnameMap   "<<fnameMap<<endl
      <<"pdfFolder  "<<pdfFolder<<endl
      <<"outFname   "<<outFname<<endl
      <<"outXMLfile "<<outXMLfile<<endl;
  cout<<"version    "<<version<<endl;

  vector<aerogelInfoMap> aimvfit;
  
  //Read aerogel info map
  const vector<aerogelInfoMap> &aimv = readAerogelInfoMap( fnameInfo, fnameMap);
  aimvfit = aimv;

  TH1D *h1_chi2_A = new TH1D("h1_chi2_A", "chi2 A", 400, 0.0, 200.0);
  TH1D *h1_p0_A = new TH1D("h1_p0_A","p0 A", 100, 0.0, 10.0);
  TH1D *h1_p1_A = new TH1D("h1_p1_A","p1 A", 200, 0.0, 10.0);
  TH1D *h1_p2_A = new TH1D("h1_p2_A","p2 A", 200, 0.0,  0.2);
  TH1D *h1_p3_A = new TH1D("h1_p3_A","p3 A", 400, 0.0,  0.004);
  TH1D *h1_p4_A = new TH1D("h1_p4_A","p4 A", 400, -0.001,  0.001);
  TH1D *h1_p5_A = new TH1D("h1_p5_A","p5 A", 100, 200, 250);
  TH1D *h1_p6_A = new TH1D("h1_p6_A","p6 A", 100, 650, 750);
  TH1D *h1_trLengthDiff_A = new TH1D("h1_trLengthDiff_A","trLengthDiff A", 400, -15, 15);
  TH1D *h1_trLengthDiffNorm_A = new TH1D("h1_trLengthDiffNorm_A","trLengthDiff Norm A", 400, -1.0, 1.0);
  TH2D *h2_trLengthDiff_vs_lam_A = new TH2D("h2_trLengthDiff_vs_lam_A","trLengthDiff vs lam A", 100, 200, 800, 200, -15, 15);
  TH2D *h2_trLengthDiffNorm_vs_lam_A = new TH2D("h2_trLengthDiffNorm_vs_lam_A","trLengthDiffNorm vs lam A", 100, 200, 800, 200, -1.0, 1.0);
  TH1D *h1_chi2_B = new TH1D("h1_chi2_B", "chi2 B", 400, 0.0, 200.0);
  TH1D *h1_p0_B = new TH1D("h1_p0_B","p0 B", 100, 0.0, 10.0);
  TH1D *h1_p1_B = new TH1D("h1_p1_B","p1 B", 200, 0.0, 10.0);
  TH1D *h1_p2_B = new TH1D("h1_p2_B","p2 B", 200, 0.0,  0.2);
  TH1D *h1_p3_B = new TH1D("h1_p3_B","p3 B", 400, 0.0,  0.004);
  TH1D *h1_p4_B = new TH1D("h1_p4_B","p4 B", 400, -0.001,  0.001);
  TH1D *h1_p5_B = new TH1D("h1_p5_B","p5 B", 100, 200, 250);
  TH1D *h1_p6_B = new TH1D("h1_p6_B","p6 B", 100, 650, 750);
  TH1D *h1_trLengthDiff_B = new TH1D("h1_trLengthDiff_B","trLengthDiff B", 400, -15, 15);
  TH1D *h1_trLengthDiffNorm_B = new TH1D("h1_trLengthDiffNorm_B","trLengthDiff Norm B", 400, -1.0, 1.0);
  TH2D *h2_trLengthDiff_vs_lam_B = new TH2D("h2_trLengthDiff_vs_lam_B","trLengthDiff vs lam B", 100, 200, 800, 200, -15, 15);
  TH2D *h2_trLengthDiffNorm_vs_lam_B = new TH2D("h2_trLengthDiffNorm_vs_lam_B","trLengthDiffNorm vs lam B", 100, 200, 800, 200, -1.0, 1.0);
  Double_t chisquare;
  Double_t trLengthDiff;
  Double_t trLengthDiffNorm;
  TString serialN;
  Int_t nPoints = 0;
  for( unsigned i=0; i<aimvfit.size(); i++){
    TString histN1 = "gr_"; histN1 += aimvfit.at(i).serial;
    TString histN2 = "gr_"; histN2 += aimvfit.at(i).serial; histN2 += "_trLength";
    TF1 *fitf = fitAbsorptionLength(fileN, histN1, histN2, pdfFolder, aimvfit.at(i).thick);
    aimvfit.at(i).p0 = fitf->GetParameter(0);
    aimvfit.at(i).p1 = fitf->GetParameter(1);
    aimvfit.at(i).p2 = fitf->GetParameter(2);
    aimvfit.at(i).p3 = fitf->GetParameter(3);
    aimvfit.at(i).p4 = fitf->GetParameter(4);
    aimvfit.at(i).p5 = fitf->GetParameter(5);
    aimvfit.at(i).p6 = fitf->GetParameter(6);
    chisquare = fitf->GetChisquare();
    serialN = aimvfit.at(i).serial;
    TGraph *gr = plots(fileN, histN2, "./tmp/", "!-v");
    //if( chisquare > 60 && chisquare < 120)
    cout<<"chisquare "<<chisquare<<"     "<<serialN<<endl;
    nPoints = 0;
    for(Int_t j = 0 ; j < gr->GetN(); j++)
      if(gr->GetY()[j]>0.0)
	nPoints++;
    aimvfit.at(i).dLam = gr->GetX()[0] - gr->GetX()[1];
    aimvfit.at(i).nPoints = nPoints;
    if(histN1.Contains("gr_A")){
      h1_chi2_A->Fill(fitf->GetChisquare());
      h1_p0_A->Fill(fitf->GetParameter(0));
      h1_p1_A->Fill(fitf->GetParameter(1));
      h1_p2_A->Fill(fitf->GetParameter(2));
      h1_p3_A->Fill(fitf->GetParameter(3));
      h1_p4_A->Fill(fitf->GetParameter(4));
      h1_p5_A->Fill(fitf->GetParameter(5));
      h1_p6_A->Fill(fitf->GetParameter(6));
      for(Int_t j = 0 ; j < gr->GetN(); j++){
	trLengthDiff = gr->GetY()[j] - fitf->Eval(gr->GetX()[j]);
	if(gr->GetY()[j]>0.0)
	  trLengthDiffNorm = trLengthDiff/gr->GetY()[j];
	else
	  trLengthDiffNorm = 0.0;
	h1_trLengthDiff_A->Fill(trLengthDiff);
	h2_trLengthDiff_vs_lam_A->Fill(gr->GetX()[j],trLengthDiff);
	h2_trLengthDiffNorm_vs_lam_A->Fill(gr->GetX()[j],trLengthDiffNorm);
	h1_trLengthDiffNorm_A->Fill(trLengthDiffNorm);
	if(TMath::Abs(trLengthDiff)>4.0){
	  cout<<"trLengthDiff "<<trLengthDiff<<"     "<<serialN<<endl;
	}
      }
    }
    if(histN1.Contains("gr_B")){
      h1_chi2_B->Fill(fitf->GetChisquare());
      h1_p0_B->Fill(fitf->GetParameter(0));
      h1_p1_B->Fill(fitf->GetParameter(1));
      h1_p2_B->Fill(fitf->GetParameter(2));
      h1_p3_B->Fill(fitf->GetParameter(3));
      h1_p4_B->Fill(fitf->GetParameter(4));
      h1_p5_B->Fill(fitf->GetParameter(5));
      h1_p6_B->Fill(fitf->GetParameter(6));
      for(Int_t j = 0 ; j < gr->GetN() ; j++){
	trLengthDiff = gr->GetY()[j] - fitf->Eval(gr->GetX()[j]);
	if(gr->GetY()[j]>0.0)
	  trLengthDiffNorm = trLengthDiff/gr->GetY()[j];
	else
	  trLengthDiffNorm = 0.0;
	h1_trLengthDiff_B->Fill(trLengthDiff);
	h2_trLengthDiff_vs_lam_B->Fill(gr->GetX()[j],trLengthDiff);
	h2_trLengthDiffNorm_vs_lam_B->Fill(gr->GetX()[j],trLengthDiffNorm);
	h1_trLengthDiffNorm_B->Fill(trLengthDiffNorm);
	if(TMath::Abs(trLengthDiff)>4.0){
	  cout<<"trLengthDiff "<<trLengthDiff<<"     "<<serialN<<endl;
	}
      }
    }
  }
  
  //h1_chi2->SaveAs("h1_chi2.C");  
  //for( unsigned i=0; i<aimv.size(); i++){
  //if( aimv.at(i).layer == layerName){
  //if(parName == "n")
  //if(parName == "transmL")
  //h2_aerogel->SetBinContent(h2_aerogel->GetBinIDFromRingColumn(aimv.at(i).ring, aimv.at(i).column),aimv.at(i).transmL);
  //if(parName == "thick")
  //h2_aerogel->SetBinContent(h2_aerogel->GetBinIDFromRingColumn(aimv.at(i).ring, aimv.at(i).column),aimv.at(i).thick);
  //}
  //}

  TFile* rootFile = new TFile(outFname.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<outFname.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<outFname.Data()<<endl;

  h1_chi2_A->Write();
  h1_p0_A->Write();
  h1_p1_A->Write();
  h1_p2_A->Write();
  h1_p3_A->Write();
  h1_p4_A->Write();
  h1_p5_A->Write();
  h1_p6_A->Write();
  h1_trLengthDiff_A->Write();
  h1_trLengthDiffNorm_A->Write();
  h2_trLengthDiff_vs_lam_A->Write();
  h2_trLengthDiffNorm_vs_lam_A->Write();
  h1_chi2_B->Write();
  h1_p0_B->Write();
  h1_p1_B->Write();
  h1_p2_B->Write();
  h1_p3_B->Write();
  h1_p4_B->Write();
  h1_p5_B->Write();
  h1_p6_B->Write();
  h1_trLengthDiff_B->Write();
  h1_trLengthDiffNorm_B->Write();
  h2_trLengthDiff_vs_lam_B->Write();
  h2_trLengthDiffNorm_vs_lam_B->Write();

  saveXML( aimvfit, outXMLfile, version);

  return aimvfit;
}
}//namespace xmlarichdata{
#ifdef FITALLABSLEN_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 8){
    TString fileN = argv[1];
    TString fnameInfo = argv[2];
    TString fnameMap = argv[3];
    TString pdfFolder = argv[4];
    TString outFname = argv[5];
    TString outXMLfile = argv[6];
    Float_t version = atof(argv[7]);
    fitAllAbsLen(fileN, fnameInfo, fnameMap, pdfFolder, outFname, outXMLfile, version);
    return 0;
  }
  //fitAllAbsLen();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef FITALLABSLEN_MAIN
