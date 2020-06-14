/***********************************************************************
* Copyright(C) 2018 - LBS - (Single person developer.)                 *
* Tue Oct  2 15:36:50 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "ARICHmappingCopperMergerFeb.h"
#include "libxmlarichdata.h"
#else 
//my
#include "ARICHmappingCopperMergerFeb.C"
#endif //#if !defined(__CLING__)

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TList.h>
#include <TMath.h>

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

  Int_t runARICHmappingCopperMergerFeb(){

    ARICHmappingCopperMergerFeb *arichMapping = new ARICHmappingCopperMergerFeb("hapdTemplateMapping.dat");
    arichMapping->dumpMapping();

    TString histTitle = "title";
    TString histName = "name";
    
    Belle2::ARICHChannelHist *h2_asic_t = new Belle2::ARICHChannelHist(histTitle.Data(),histName.Data(),1);

    /*
    for(Int_t iR = 1; iR<=arichMapping->GetnHAPDrings(); iR++){
      for(Int_t iP = 1; iP<=arichMapping->gHAPDpositionInRingPerSector_Arr[(iR-1)]; iP++){
	//cout<<"iR "<<iR <<"  iP "<<iP<<"   "<<arichMapping->getHAPD_globalID_from_sec_iR_iP(6, iR,iP)<<endl;
	h2_asic_t->SetBinContent(arichMapping->getHAPD_globalID_from_sec_iR_iP(6, iR, iP),
				 arichMapping->getHAPD_globalID_from_sec_iR_iP(6, iR,iP));
      }
    }
    */

    Int_t sec_i, cop_i, mer_i, feb_i;
    Int_t secID, iR, iP;
    secID = 6;
    for(iR = 1; iR<=arichMapping->GetnHAPDrings(); iR++){
      for(iP = 1; iP<=arichMapping->gHAPDpositionInRingPerSector_Arr[(iR-1)]; iP++){
	arichMapping->findPositionInarichmappingFormSecIDiRingiPosition( secID,  iR,  iP, sec_i, cop_i, mer_i, feb_i);
	h2_asic_t->SetBinContent(arichMapping->getHAPD_globalID_from_sec_iR_iP(6, iR, iP),
				 arichMapping->arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].globalID);
      }
    }

    //gStyle->SetPalette(kRainBow);
    gStyle->SetPalette(0);
    TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
    c1->SetTitle(histTitle.Data());
    c1->SetName(histName.Data());
    c1->SetRightMargin(0.12);
    c1->SetLeftMargin(0.12);
    c1->SetTopMargin(0.1);
    c1->SetBottomMargin(0.15);
    ///////////////////////////////////////////////////////////////
    double envelopeR_min = 43.5;
    double envelopeR_max = 113.2;
    //Double_t l_slot = 29.1;
    Double_t l_slot = 1.0;
    /*
    Double_t frameXmin = -114.0 - l_slot;
    Double_t frameXmax =  114.0 + l_slot;
    Double_t frameYmin = -114.0 - l_slot;
    Double_t frameYmax =  114.0 + l_slot;
    */
    Double_t frameXmin =  20.0;
    Double_t frameXmax =  114.0 + l_slot + 6;
    Double_t frameYmin = -114.0 - l_slot + 15;
    Double_t frameYmax =  1.0;
    TH2F *frame = new TH2F( "h2", "h2", 40, frameXmin, frameXmax,40, frameYmin, frameYmax);
    frame->GetXaxis()->SetTitle("x (cm)");
    frame->GetYaxis()->SetTitle("y (cm)");
    frame->GetXaxis()->CenterTitle();
    frame->GetYaxis()->CenterTitle();
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->SetStats(kFALSE);
    frame->SetTitle("");
    frame->Draw();
    //img->Draw("same");
    ///////////////////////////////////////////////////////////////
    h2_asic_t->SetStats(kFALSE);
    h2_asic_t->GetXaxis()->SetTitle("x (cm)");
    h2_asic_t->GetYaxis()->SetTitle("y (cm)");
    h2_asic_t->GetXaxis()->CenterTitle();
    h2_asic_t->GetYaxis()->CenterTitle();
    h2_asic_t->GetYaxis()->SetTitleOffset(1.5);
    //SetLineStyle(1);
    //SetLineWidth(3.0);
    c1->Modified();
    c1->Update();
    
    //gStyle->SetPalette(1);
    //h2_asic_t->GetZaxis()->SetRangeUser(0.0,420.0);
    //h2_asic_t->Draw("ZCOLOR same");
    h2_asic_t->GetZaxis()->SetRangeUser(61.0,72.0);
    h2_asic_t->Draw("ZTEXT ZCOLOR same");

    vector<TGraph*> m_verticesGraphV;
    vector<TGraph*> m_additionalGraphV;
    vector<TLine*> m_additionalLineV;
    getAdditionalGraphV_and_LineV_for_Plot(m_additionalGraphV, m_additionalLineV, envelopeR_min, envelopeR_max, l_slot);

    for (unsigned i=0; i<m_verticesGraphV.size(); i++)
      m_verticesGraphV.at(i)->Draw("same");
    
    for (unsigned i=0; i<m_additionalGraphV.size(); i++)
      m_additionalGraphV.at(i)->Draw("same");
    
    for (unsigned i=0; i<m_additionalLineV.size(); i++)
      m_additionalLineV.at(i)->Draw("same");
    
    
    
    /*
    gStyle->SetPalette(kRainBow);
    TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
    c1->SetTitle(histTitle.Data());
    c1->SetName(histName.Data());
    c1->SetRightMargin(0.12);
    c1->SetLeftMargin(0.12);
    c1->SetTopMargin(0.1);
    c1->SetBottomMargin(0.15);
    ///////////////////////////////////////////////////////////////
    //double envelopeR_min = 43.5;
    //double envelopeR_max = 113.2;
    ///////////////////////////////////////////////////////////////
    Double_t l_slot = 29.1;
    Double_t frameXmin = -114.0 - l_slot;
    Double_t frameXmax =  114.0 + l_slot;
    Double_t frameYmin = -114.0 - l_slot;
    Double_t frameYmax =  114.0 + l_slot;
    TH2F *frame = new TH2F( "h2", "h2", 40, frameXmin, frameXmax,40, frameYmin, frameYmax);
    frame->GetXaxis()->SetTitle("x (cm)");
    frame->GetYaxis()->SetTitle("y (cm)");
    frame->GetXaxis()->CenterTitle();
    frame->GetYaxis()->CenterTitle();
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->SetStats(kFALSE);
    frame->SetTitle("");
    frame->Draw();
    //img->Draw("same");
    ///////////////////////////////////////////////////////////////
    h2_asic_t->SetStats(kFALSE);
    h2_asic_t->GetXaxis()->SetTitle("x (cm)");
    h2_asic_t->GetYaxis()->SetTitle("y (cm)");
    h2_asic_t->GetXaxis()->CenterTitle();
    h2_asic_t->GetYaxis()->CenterTitle();
    h2_asic_t->GetYaxis()->SetTitleOffset(1.5);
    //SetLineStyle(1);
    //SetLineWidth(3.0);
    c1->Modified();
    c1->Update();
    
    //gStyle->SetPalette(1);
    h2_asic_t->GetZaxis()->SetRangeUser(61.0,72.0);
    //h2_merger->GetZaxis()->SetRangeUser(50.0,80.0);
    h2_asic_t->Draw("ZTEXT ZCOLOR same");
    //h2_merger->DrawHisto("ZCOLOR same","","drawLine");
    // h2_asic_t->Draw("ZCOLOR same");
*/

    
    return 0;
  }
  
}//namespace xmlarichdata{

/*
#ifdef RUNARICHMAPPINGCOPPERMERFERFEB_MAIN
# ifndef __CINT__
  int main(int argc, char *argv[]){
    if(argc == 1){
      xmlarichdata::runARICHmappingCopperMergerFeb();
      return 0;
    }
    xmlarichdata::runARICHmappingCopperMergerFeb();
    return 0;
  }
# endif //ifndef __CINT__
#endif //ifdef RUNARICHMAPPINGCOPPERMERFERFEB_MAIN
*/
