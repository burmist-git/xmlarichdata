/***********************************************************************
* Copyright(C) 2018 - LBS - (Single person developer.)                 *
* Mon Oct  1 18:03:07 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
#include "ARICHmappingCopperMergerFeb.h"

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
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TTree.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <time.h>

using namespace std;
using namespace xmlarichdata;
namespace xmlarichdata{

  void convertDataFebMergerTemperatureSlowControl( TString infile = "./dataFebMergerTemperatureSlowControl/2018-09-21/4016.log",
						   Int_t copperBoardID = 4016,
						   TString outfile = "./dataFebMergerTemperatureSlowControl/2018-09-21_root/4016.log.root"){
     
    cout<<"infile        "<<infile<<endl
	<<"copperBoardID "<<copperBoardID<<endl
	<<"outfile       "<<outfile<<endl;

    ARICHmappingCopperMergerFeb *arichmap = new ARICHmappingCopperMergerFeb("hapdTemplateMapping.dat");
    //arichmap->printMappingConstants();
    
    //-----------------------------------------------//-----------------------------------------------//
    const Int_t nFebs = arichmap->GetnFebs();        //                                               //
    const Int_t nMergers = arichmap->GetnMergers();  //                                               //
    //-----------------------------------------------//-----------------------------------------------//
    //const Int_t nMergersPerCopper = arichmap->GetnMergersPerCopper();//                               //
    //const Int_t nFebsPerMerger = arichmap->GetnHAPDPerMerger();//                                     //
    //const Int_t nObjectsToRead = nFebsPerMerger + 1; // Two temperatures per FEB + merger temperature //
    //-----------------------------------------------//-----------------------------------------------//

    cout<<"nFebs    "<<nFebs<<endl;
    cout<<"nMergers "<<nMergers<<endl;

    Int_t eventID = 0;
    Double_t unixTime;
    Float_t febt1[nFebs], _febt1;
    Float_t febt2[nFebs], _febt2;
    Float_t mergert[nMergers], _mergert;

    ///////////////////Root file with data/////////////////
    TFile *hfile = new TFile( outfile.Data(), "RECREATE", "Slow control feb's and mergers temperatures", 1);
    if (hfile->IsZombie()) {
      cout << "PROBLEM with the initialization of the output ROOT ntuple " 
	   << outfile << ": check that the path is correct!!!"
	   << endl;
      exit(-1);
    }
    TTree *tree = new TTree("T", "Slow control data tree");
    hfile->SetCompressionLevel(2);
    tree->SetAutoSave(1000000);
    // Create new event
    TTree::SetBranchStyle(0);
    
    TString febt1_ss = "febt1[";
    febt1_ss+=nFebs; febt1_ss+="]/F";
    TString febt2_ss = "febt2[";
    febt2_ss+=nFebs; febt2_ss+="]/F";
    TString mergert_ss = "mergert[";
    mergert_ss+=nMergers; mergert_ss+="]/F";
    
    //Event ///////////////////////////////////////////////
    tree->Branch("eventID",&eventID, "eventID/I");
    tree->Branch("unixTime",&unixTime, "unixTime/D");
    tree->Branch("febt1", febt1, febt1_ss.Data());
    tree->Branch("febt2", febt2, febt2_ss.Data());
    tree->Branch("mergert", mergert, mergert_ss.Data());
    ///////////////////////////////////////////////////////
    
    TString lineTS;
    Double_t unixTimeTmp;
    string line;
    string lineo;
    string linet;
    ifstream filest (infile.Data());
    int i;
    int dataTimeArr_i[6];
    int year_i;
    //double t1;
    //double t2;
    Int_t mergerLocalID;
    Int_t mergerID;
    Int_t febLocalID;
    Int_t febID;
    TString tsline;
    //bool newEntry = false;
    if(filest.is_open()){
      while( getline (filest,line) ) {
	lineTS = line;
	//cout<<lineTS<<line.size()<<endl;
	if(line.size()>0){
	  unixTimeTmp = getUnixTimeFrom_TString(lineTS, dataTimeArr_i);
	  year_i = dataTimeArr_i[0];
	  if(year_i>2017 && year_i<2019){
	    if(eventID!=0)
	      tree->Fill();
	    eventID++;
	    for(Int_t ii = 0;ii<nFebs;ii++){
	      febt1[ii] = 0.0;
	      febt2[ii] = 0.0;
	    }
	    for(Int_t ii = 0;ii<nMergers;ii++)
	      mergert[ii] = 0.0;	  
	    unixTime = unixTimeTmp;
	    printf ("Unix time : %.f ", unixTime);
	    cout<<"       Time :";
	    for(i = 0;i<6;i++)
	      cout<<setw(6)<<dataTimeArr_i[i];
	    cout<<endl;
	  }
	  if(ifLineContainsString(line, "temp")){
	    //Merger temperature
	    //cout<<line<<endl;
	    tsline = line;
	    getMergerIDandTemperatureFrom_TString( tsline, _mergert, mergerLocalID);
	    mergerID = arichmap->getMergerIDFromCopperBoardIDAndMergerLocalID(copperBoardID,mergerLocalID);
	    mergert[mergerID-1] = _mergert;
	    //cout<<mergerID<<" "<<_mergert<<endl;
	  }
	  else if (ifLineContainsString(line, "].feb[")){
	    if(ifLineContainsString(line, "].t1")){
	      //FEB temperature 1
	      //cout << line << '\n';
	      tsline = line;
	      getFebIDandTemperatureFrom_TString( tsline, _febt1, mergerLocalID, febLocalID);
	      febID = arichmap->getFebIDFromCopperBoardIDAndMergerLocalIDAndFebLocalID(copperBoardID,mergerLocalID,febLocalID);
	      cout<<copperBoardID<<" "<<mergerLocalID<<" "<<febID<<" "<<_febt1<<endl;
	      if(febID != 999)
		febt1[febID-1] = _febt1;
	    }
	    else if(ifLineContainsString(line, "].t2")){
	      //FEB temperature 2
	      tsline = line;
	      getFebIDandTemperatureFrom_TString( tsline, _febt2, mergerLocalID, febLocalID);
	      febID = arichmap->getFebIDFromCopperBoardIDAndMergerLocalIDAndFebLocalID(copperBoardID,mergerLocalID,febLocalID);
	      cout<<copperBoardID<<" "<<mergerLocalID<<" "<<febID<<" "<<_febt2<<endl;
	      if(febID != 999)
		febt2[febID-1] = _febt2;
	    }
	  }
	}
      }
      filest.close();
    }
    else{
      cout << "Unable to open file"; 
      assert(0);
    }
    
    hfile = tree->GetCurrentFile();
    hfile->Write();
    hfile->Close();
    
  }
  
} //namespace xmlarichdata{

#ifdef CONVERTDATAFEBMERGERTEMPERATURESLOWCONTROL_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 4){
    TString infileName = argv[1];
    Int_t copperBoardID = atoi(argv[2]);
    TString outfileName = argv[3];
    xmlarichdata::convertDataFebMergerTemperatureSlowControl( infileName, copperBoardID, outfileName);
    return 0;
  }
  else if(argc != 4){
    xmlarichdata::convertDataFebMergerTemperatureSlowControl();
  }
  else{
    assert(0);
  }
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef CONVERTDATAFEBMERGERTEMPERATURESLOWCONTROL_MAIN
