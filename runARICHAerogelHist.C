/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Wed Oct 18 21:02:16 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "ARICHAerogelHist.h"
#include "libxmlarichdata.h"
#else 
//my
#include "ARICHAerogelHist.C"
#include "plots.C"
#include "xmlreadfile.C"
#include "readAerogelInfoMap.C"
#endif //#if !defined(__CLING__)
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
#include <TAxis.h>
#include <TList.h>

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

//    id_map    number    serial  serialID      ring    column     layer         n   transmL     thick
//      B076         0      B076   CAd9-20         1        12      down    1.0538       3.6      2.03

Int_t runARICHAerogelHist(){
  ARICHAerogelHist *h2_aerogel = new ARICHAerogelHist( "h2_aerogel", "aerogel");

  /*
  Int_t binx;
  Int_t biny;
  Int_t binz;
  h2_aerogel->GetBinXYZ(102, binx,biny,binz);

  cout<<"binx "<<binx<<endl
      <<"biny "<<biny<<endl
      <<"binz "<<binz<<endl;
  */
  /*
  h2_aerogel->Fill(  500,  50);
  h2_aerogel->Fill(  500, -50);
  h2_aerogel->Fill(  650,  50);
  h2_aerogel->Fill(  850, -50);
  h2_aerogel->Fill( 1000, -50);
  */

  //h2_aerogel->DrawHisto();
  h2_aerogel->DrawHisto("same","");
  //h2_aerogel->GetBins()->Print();

  //cout<<"h2_aerogel->GetNcells() = "<<h2_aerogel->GetNcells()<<endl;
  //cout<<"h2_aerogel->GetNbinsX() = "<<h2_aerogel->GetNbinsX()<<endl;
  //cout<<"h2_aerogel->GetNbinsY() = "<<h2_aerogel->GetNbinsY()<<endl;
  //cout<<"h2_aerogel->GetNbinsZ() = "<<h2_aerogel->GetNbinsZ()<<endl;

  //cout<<"h2_aerogel->GetBinContent(1) "<<h2_aerogel->GetBinContent(1)<<endl;
  //cout<<"h2_aerogel->GetBinContent(22) "<<h2_aerogel->GetBinContent(22)<<endl;
  //cout<<"h2_aerogel->GetBinContent(23) "<<h2_aerogel->GetBinContent(23)<<endl;
  //cout<<"h2_aerogel->GetBinContent(84) "<<h2_aerogel->GetBinContent(84)<<endl;
  //cout<<"h2_aerogel->GetBinContent(124) "<<h2_aerogel->GetBinContent(124)<<endl;

  //plots("./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root", "gr_A001", "./pdfdata/2nd_measurement/", "-v");
  //xmlreadfile("CAd12-28wjt_r_database.xml");
  //plots();
  //xmlreadfile();

  //aerogelInfoMap aim;
  //aim.id_map = "qwqe";
  //aim.idnumber = 1;
  //aim.thick = 10.2;
  //cout<<"aim.id_map   = "<<aim.id_map<<endl
  //  <<"aim.idnumber = "<<aim.idnumber<<endl
  //  <<"aim.serial   = "<<aim.serial<<endl
  //  <<"aim.ring     = "<<aim.ring<<endl
  //  <<"aim.thick    = "<<aim.thick<<endl;

  TString fnameInfo = "./aerogelDataFromDB/aerogelInfo.dat";
  TString fnameMap = "./aerogelDataFromDB/aerogelMap.dat";

  const vector<aerogelInfoMap> &aimv = readAerogelInfoMap( fnameInfo, fnameMap);
  
  //for (unsigned i=0; i<aimv.size(); i++)
  //cout<<setw(20)<<aimv.at(i).id_map<<endl;

  return 0;
}

#ifdef RUNARICHAEROGELHIST_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 1){
    runARICHAerogelHist();
    return 0;
  }
  runARICHAerogelHist();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef RUNARICHAEROGELHIST_MAIN
