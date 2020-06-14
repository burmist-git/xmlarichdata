/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Oct 22 11:48:25 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "ARICHMergerHist.h"
#include "libxmlarichdata.h"
#include "ARICHmappingCopperMergerFeb.h"
#else 
#include "ARICHMergerHist.C"
#include "read_temperature_meas.C"
#include "testCoolingPlates.C"
#include "ARICHmappingCopperMergerFeb.C"
#endif //#if !defined(__CLING__)
#include "mergerStruct.h"

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

  //if executionKey == 0 --> build FEB(HAPD) with FEB(HAPD) global ID
  //if executionKey == 1 --> build FEB(HAPD) with FEB(HAPD) local  ID
  //if executionKey == 2 --> build FEB(HAPD) with MERGER    global ID
  //if executionKey == 3 --> build FEB(HAPD) with MERGER    local  ID
  //if executionKey == 4 --> build FEB(HAPD) with COPPER    global ID
  //if executionKey == 5 --> build FEB(HAPD) with SECTOR    global ID
  void runARICH_FEB_numbering( Int_t secID, Int_t executionKey) {
    
    TString histTitle;
    TString fname;
    TString histName;
    
    histTitle = "h2_feb_numbering";
    histName = "FEB numbering";
    
    Belle2::ARICHChannelHist *h2_feb_numbering = new Belle2::ARICHChannelHist(histTitle.Data(),histName.Data(),1);
    ARICHmappingCopperMergerFeb *arichMapping = new ARICHmappingCopperMergerFeb("hapdTemplateMapping.dat");
    //arichMapping->dumpMapping();
    //arichMapping->printMappingConstants();

    Int_t febID;
    Int_t sectorID, copperBoardID, mergerID, mergerLocalID, febLocalID;
    Int_t febBinValue = 0;
    for (int i=1; i<=arichMapping->GetnFebs(); i++){
      febID = i;
      arichMapping->getSecIDAndCopperBoardIDAndMergerIDAndMergerLocalIDAndFebLocalIDFromFebID( febID, sectorID, copperBoardID, mergerID, mergerLocalID, febLocalID);
      //mergerID = arichMapping->getMergerIDFromCopperBoardIDAndMergerLocalID( copperBoardID, mergerLocalID);
      if(executionKey == 0)
	febBinValue = febID;
      else if(executionKey == 1)
	febBinValue = febLocalID;
      else if(executionKey == 2)
	febBinValue = mergerID;
      else if(executionKey == 3)
	febBinValue = mergerLocalID;
      else if(executionKey == 4)
	febBinValue = copperBoardID;
      else if(executionKey == 5)
	febBinValue = sectorID;
      else
	assert(0);
      if(secID>=1 && secID<=arichMapping->GetnSectors()){
	if(sectorID == secID){
	  h2_feb_numbering->setBinContent(febID,febBinValue);
	}
      }
      else{
	h2_feb_numbering->setBinContent(febID,febBinValue);
      }
    }

    gStyle->SetPalette(kRainBow);
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
    Double_t envelopeR_center = (envelopeR_max + envelopeR_min)/2.0;
    //Double_t l_slot = 29.1;
    Double_t l_slot = 1.0;
    Double_t dl = 2*(114.0 + l_slot);
    Double_t frameXmin;
    Double_t frameXmax;
    Double_t frameYmin;
    Double_t frameYmax;
    setFrameLimits(secID, dl, envelopeR_center, frameXmin, frameXmax, frameYmin, frameYmax);
    /*
    Double_t frameXmin = -114.0 - l_slot;
    Double_t frameXmax =  114.0 + l_slot;
    Double_t frameYmin = -114.0 - l_slot;
    Double_t frameYmax =  114.0 + l_slot;
    */
    /*
    Double_t frameXmin =  20.0;
    Double_t frameXmax =  114.0 + l_slot + 6;
    Double_t frameYmin = -114.0 - l_slot + 15;
    Double_t frameYmax =  1.0;
    */
    TString frameTitle = " ";
    if(secID>=1 && secID<=arichMapping->GetnSectors()){
      frameTitle = "sec ";
      frameTitle += secID;
    }
    else
      frameTitle = "All";
	
    TH2F *frame = new TH2F( "h2", "h2", 40, frameXmin, frameXmax,40, frameYmin, frameYmax);
    frame->GetXaxis()->SetTitle("x (cm)");
    frame->GetYaxis()->SetTitle("y (cm)");
    frame->GetXaxis()->CenterTitle();
    frame->GetYaxis()->CenterTitle();
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->SetStats(kFALSE);
    //frame->SetTitle("");
    frame->SetTitle(frameTitle.Data());
    frame->Draw();
    //img->Draw("same");
    ///////////////////////////////////////////////////////////////
    h2_feb_numbering->SetStats(kFALSE);
    h2_feb_numbering->GetXaxis()->SetTitle("x (cm)");
    h2_feb_numbering->GetYaxis()->SetTitle("y (cm)");
    h2_feb_numbering->GetXaxis()->CenterTitle();
    h2_feb_numbering->GetYaxis()->CenterTitle();
    h2_feb_numbering->GetYaxis()->SetTitleOffset(1.5);
    //SetLineStyle(1);
    //SetLineWidth(3.0);
    c1->Modified();
    c1->Update();
    
    //gStyle->SetPalette(1);
    //h2_asic_t->GetZaxis()->SetRangeUser(0.0,420.0);
    //h2_asic_t->Draw("ZCOLOR same");
    h2_feb_numbering->Draw("ZTEXT same");

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
    
    //const Int_t Number = 3;
    //Double_t Red[Number]    = { 1.00, 0.00, 0.00};
    //Double_t Green[Number]  = { 0.00, 1.00, 0.00};
    //Double_t Blue[Number]   = { 1.00, 0.00, 1.00};
    //Double_t Length[Number] = { 30.00, 45.0, 60.00 };
    //Int_t nb=20;
    //TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);

    TString outpdf = "feb_numbering";
    if(secID>=1 && secID<=arichMapping->GetnSectors()){
      outpdf += "_sec0";
      outpdf +=  secID;
    }
    outpdf += ".pdf";
    c1->SaveAs(outpdf.Data());
    
  }

  void runARICH_MERGER_numbering( Int_t secID) {
    TString histTitle;
    TString fname;
    TString histName;
    
    histTitle = "h2_merger_numbering";
    histName = "MERGER numbering";

    double scaleFactor = 10; //mm->cm
    ARICHMergerHist *h2_merger_numbering = new ARICHMergerHist(histTitle.Data(),histName.Data(),scaleFactor);
    ARICHmappingCopperMergerFeb *arichMapping = new ARICHmappingCopperMergerFeb("hapdTemplateMapping.dat");
    //arichMapping->dumpMapping();
    //arichMapping->printMappingConstants();

    Int_t mergerID;
    for (int i=1; i<=arichMapping->GetnMergers(); i++){
      mergerID = i;
      if(secID>=1 && secID<=arichMapping->GetnSectors()){
	if( arichMapping->getSectorIDFromMergerID(mergerID) == secID)
	  h2_merger_numbering->SetBinContent(h2_merger_numbering->GetBinIDFromMergerSlotNumber(mergerID),mergerID);
      }
      else{
	h2_merger_numbering->SetBinContent(h2_merger_numbering->GetBinIDFromMergerSlotNumber(mergerID),mergerID);      
      }
    }
    
    gStyle->SetPalette(kRainBow);
    TCanvas *c1 = new TCanvas("c1","c1",1000,1000);
    c1->SetTitle(histTitle.Data());
    c1->SetName(histName.Data());
    c1->SetRightMargin(0.12);
    c1->SetLeftMargin(0.12);
    c1->SetTopMargin(0.1);
    c1->SetBottomMargin(0.15);
    ///////////////////////////////////////////////////////////////
    double envelopeR_min = 43.50;  //cm
    double envelopeR_max = 113.20; //cm
    Double_t envelopeR_center = (envelopeR_max + envelopeR_min)/2.0;
    //Double_t l_slot = 29.1;
    Double_t l_slot = 1.0;
    Double_t dl = 2*(114.0 + l_slot);
    Double_t frameXmin;
    Double_t frameXmax;
    Double_t frameYmin;
    Double_t frameYmax;
    setFrameLimits(secID, dl, envelopeR_center, frameXmin, frameXmax, frameYmin, frameYmax);
    /*
    Double_t frameXmin = -114.0 - l_slot;
    Double_t frameXmax =  114.0 + l_slot;
    Double_t frameYmin = -114.0 - l_slot;
    Double_t frameYmax =  114.0 + l_slot;
    */
    /*
    Double_t frameXmin =  20.0;
    Double_t frameXmax =  114.0 + l_slot + 6;
    Double_t frameYmin = -114.0 - l_slot + 15;
    Double_t frameYmax =  1.0;
    */
    TString frameTitle = " ";
    if(secID>=1 && secID<=arichMapping->GetnSectors()){
      frameTitle = "sec ";
      frameTitle += secID;
    }
    else
      frameTitle = "All";
	
    TH2F *frame = new TH2F( "h2", "h2", 40, frameXmin, frameXmax,40, frameYmin, frameYmax);
    frame->GetXaxis()->SetTitle("x (cm)");
    frame->GetYaxis()->SetTitle("y (cm)");
    frame->GetXaxis()->CenterTitle();
    frame->GetYaxis()->CenterTitle();
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->SetStats(kFALSE);
    //frame->SetTitle("");
    frame->SetTitle(frameTitle.Data());
    frame->Draw();
    //img->Draw("same");
    ///////////////////////////////////////////////////////////////
    h2_merger_numbering->SetStats(kFALSE);
    h2_merger_numbering->GetXaxis()->SetTitle("x (cm)");
    h2_merger_numbering->GetYaxis()->SetTitle("y (cm)");
    h2_merger_numbering->GetXaxis()->CenterTitle();
    h2_merger_numbering->GetYaxis()->CenterTitle();
    h2_merger_numbering->GetYaxis()->SetTitleOffset(1.5);
    //SetLineStyle(1);
    //SetLineWidth(3.0);
    c1->Modified();
    c1->Update();
    
    //gStyle->SetPalette(1);
    //h2_asic_t->GetZaxis()->SetRangeUser(0.0,420.0);
    //h2_asic_t->Draw("ZCOLOR same");
    h2_merger_numbering->Draw("ZTEXT same");

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
    
    //const Int_t Number = 3;
    //Double_t Red[Number]    = { 1.00, 0.00, 0.00};
    //Double_t Green[Number]  = { 0.00, 1.00, 0.00};
    //Double_t Blue[Number]   = { 1.00, 0.00, 1.00};
    //Double_t Length[Number] = { 30.00, 45.0, 60.00 };
    //Int_t nb=20;
    //TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);

    TString outpdf = "merger_numbering";
    if(secID>=1 && secID<=arichMapping->GetnSectors()){
      outpdf += "_sec0";
      outpdf +=  secID;
    }
    outpdf += ".pdf";
    c1->SaveAs(outpdf.Data());
    
  }

  void setFrameLimits(Int_t secID, Double_t dl, Double_t envelopeR_center, Double_t &frameXmin, Double_t &frameXmax, Double_t &frameYmin, Double_t &frameYmax){
    frameXmin = -dl/2.0;
    frameXmax =  dl/2.0;
    frameYmin = -dl/2.0;
    frameYmax =  dl/2.0;
    Double_t deltaTheta[6];
    deltaTheta[0] = TMath::Pi()/180.0*7;
    deltaTheta[1] = 0.0;
    deltaTheta[2] = -TMath::Pi()/180.0*7;
    deltaTheta[3] = TMath::Pi()/180.0*7;
    deltaTheta[4] = 0.0;
    deltaTheta[5] = -TMath::Pi()/180.0*7;
    ARICHmappingCopperMergerFeb *arichMapping = new ARICHmappingCopperMergerFeb("hapdTemplateMapping.dat");
    if(secID>=1 && secID<=arichMapping->GetnSectors()){
      Double_t theta = 2.0*TMath::Pi()/arichMapping->GetnSectors()*(1.0/2.0 + secID-1) + deltaTheta[secID-1];
      Double_t cx = envelopeR_center*TMath::Cos(theta);
      Double_t cy = envelopeR_center*TMath::Sin(theta);
      frameXmin = cx - dl/2.0*0.5;
      frameXmax = cx + dl/2.0*0.5;
      frameYmin = cy - dl/2.0*0.5;
      frameYmax = cy + dl/2.0*0.5;
    }
  }
  
}//namespace xmlarichdata{
