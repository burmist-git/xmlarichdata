/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue May 29 11:44:49 JST 2018                                         *
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

  void printNumber_of_channels_chips_HAPD_mergers_sectors(){
    int nSectors = 6;
    int nMergers = 72;
    int nHAPD = 420;
    int nChips = 4*nHAPD;
    int nChannels = 4*6*6*nHAPD;
    cout<<"***************************"<<endl;
    cout<<"nSectors  "<<nSectors<<endl
	<<"nMergers  "<<nMergers<<endl
	<<"nHAPD     "<<nHAPD<<endl
	<<"nChips    "<<nChips<<endl
	<<"nChannels "<<nChannels<<endl;
    cout<<"---------------------------"<<endl;
    int nAerogelTileLayers = 2;
    int nAerogelTileRings = 4;
    int nAerogelTileRing1 = 22;
    int nAerogelTileRing2 = 28;
    int nAerogelTileRing3 = 34;
    int nAerogelTileRing4 = 40;
    int nAerogelTileTotPerLayer = nAerogelTileRing1 + nAerogelTileRing2 + nAerogelTileRing3 + nAerogelTileRing4;
    int nAerogelTileTot = nAerogelTileLayers*nAerogelTileTotPerLayer;
    cout<<"nAerogelTileLayers      "<<nAerogelTileLayers<<endl
	<<"nAerogelTileRings       "<<nAerogelTileRings<<endl
	<<"nAerogelTileRing1       "<<nAerogelTileRing1<<endl
	<<"nAerogelTileRing2       "<<nAerogelTileRing2<<endl
	<<"nAerogelTileRing3       "<<nAerogelTileRing3<<endl
	<<"nAerogelTileRing4       "<<nAerogelTileRing4<<endl
	<<"nAerogelTileTotPerLayer "<<nAerogelTileTotPerLayer<<endl
	<<"nAerogelTileTot         "<<nAerogelTileTot<<endl;
    cout<<"***************************"<<endl;
  }

}//namespace xmlarichdata {

#ifdef PRINTNUMBER_OF_CHANNELS_CHIPS_HAPD_MERGERS_SECTORS_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 1){
    printNumber_of_channels_chips_HAPD_mergers_sectors();
    return 0;
  }
  printNumber_of_channels_chips_HAPD_mergers_sectors();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef PRINTNUMBER_OF_CHANNELS_CHIPS_HAPD_MERGERS_SECTORS_MAIN
