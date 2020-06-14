/***********************************************************************
* Copyright(C) 2018 - LBS - (Single person developer.)                 *
* 2018 Sun Sep 30 00:24:28 JST 2018                                    *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"

//root
#include <TH1D.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

using namespace xmlarichdata;

namespace xmlarichdata{
    
  void convertGL840csv( TString inputDataFile, TString outputrootFile){
    
    const Int_t nChannels = 20;
    
    //Data//
    Int_t eventID;
    Double_t unixTime;
    Float_t temperatureGL[nChannels], _temperatureGL; 
    double d_year;
    double d_month;
    double d_day;
    double d_hour;
    double d_min;
    double d_sec;
    ///////////////////////
    
    ///////////////////Root file with data/////////////////
    TFile *hfile = new TFile( outputrootFile, "RECREATE", "GL840 data", 1);
    if (hfile->IsZombie()) {
      cout << "PROBLEM with the initialization of the output ROOT ntuple " 
	   << outputrootFile << ": check that the path is correct!!!"
	   << endl;
      exit(-1);
    }
    TTree *tree = new TTree("T", "GL840 data tree");
    hfile->SetCompressionLevel(2);
    tree->SetAutoSave(1000000);
    // Create new event
    TTree::SetBranchStyle(0);
    
    TString temperatureGL_ss = "temperatureGL[";
    temperatureGL_ss+=nChannels; temperatureGL_ss+="]/F";
    
    //Event ///////////////////////////////////////////////
    tree->Branch("eventID",&eventID, "eventID/I");
    tree->Branch("unixTime",&unixTime, "unixTime/D");
    tree->Branch("temperatureGL", temperatureGL, temperatureGL_ss.Data());
    ///////////////////////////////////////////////////////
    
    Int_t i = 0;
    string mot;
    //Int_t nEv = 0;
    
    // Init event variables
    eventID = -999;
    unixTime = -999.0;
    for(i = 0;i<nChannels;i++)
      temperatureGL[i] = -999.0;
    
    ifstream indata;

    indata.open(inputDataFile.Data()); 
    assert(indata.is_open());
    //cout<<indata.is_open()<<endl;
    cout<<" ---> Conversion of "<<inputDataFile<<endl;
    //nEv = 0; // Event counter for a given file
    while (indata >> mot ){
      //cout<<" New word: "<<mot<<endl;
      if(mot == "Data"){
	for(i = 0; i<28;i++)
	  indata  >> mot;
	//cout<<mot<<endl;
	for(i = 0; i<26;i++)
	  indata  >> mot;
	//cout<<mot<<endl;
	/////////////////////////////
	while( indata >> eventID >> d_year >> d_month >> d_day >> d_hour >> d_min >> d_sec >> mot ){
	  unixTime = getUnixTime( d_year, d_month, d_day, d_hour, d_min, d_sec);
	  printf ("Unix time : %d  %.f \n", eventID, unixTime);
	  for( i = 0; i<nChannels; i++){
	    indata >> _temperatureGL;
	    temperatureGL[i] = _temperatureGL;
	  }
	  for( i = 0; i<20-nChannels; i++){
	    indata >> mot;
	  }
	  indata >> mot;	indata >> mot;	indata >> mot;
	  //cout<<mot<<endl;
	  tree->Fill();
	  eventID = -999;
	  unixTime = -999.0;
	  for(i = 0;i<nChannels;i++)
	    temperatureGL[i] = -999.0;	
	}
	/////////////////////////////
      } 
    }
    indata.close();
    
    hfile = tree->GetCurrentFile();
    hfile->Write();
    hfile->Close();
    
  }
  
  double getUnixTime(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec){
    struct tm y2k = {0};
    y2k.tm_year = d_year - 1900; y2k.tm_mon = d_month-1; y2k.tm_mday = d_day;
    y2k.tm_hour = d_hour;   y2k.tm_min = d_min; y2k.tm_sec = d_sec;
    return difftime(mktime(&y2k),0);
  }

}

#ifdef CONVERTGL840CSV_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  TString inputDataFile;
  TString outputrootFile;
  if(argc == 4 && atoi(argv[1])==0){
    inputDataFile = argv[2];
    outputrootFile = argv[3];
    cout<<"In data file   : "<<inputDataFile<<endl
        <<"Out root file  : "<<outputrootFile<<endl;
    convertGL840csv( inputDataFile, outputrootFile);
  }
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"  runID [1] = 0  "<<endl
        <<"        [2] - in data file"<<endl
        <<"        [3] - out root file"<<endl;
  }  
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef CONVERTGL840CSV_MAIN
