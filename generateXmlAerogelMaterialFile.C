/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Fri Oct 27 15:11:21 2017 +0900                                       *
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

namespace xmlarichdata{

  Int_t generateXmlAerogelMaterialFile(){
    
    TString outputXMLfile="ARICH-Materials-Aerogel.xml";
    TString outputXML_data_file="ARICH-Aerogel-tiles.xml";
    ofstream xmlFile;
    ofstream xmlFileData;
    
    TString fnameInfo = "./aerogelDataFromDB/aerogelInfo.dat";
    TString fnameMap = "./aerogelDataFromDB/aerogelMap.dat";
    const vector<aerogelInfoMap> &aimv = xmlarichdata::readAerogelInfoMap( fnameInfo, fnameMap);
    
    //TH1D *h1_thickness_A = new TH1D("h1_thickness_A", "thickness A",100,1.85,2.15);
    //TH1D *h1_thickness_B = new TH1D("h1_thickness_B", "thickness B",100,1.85,2.15);
    
    TString histName;
    TString histNameL;
    Double_t dX;
    Int_t layerid;
    TString type;
    Double_t dn_at_405nm = 0.0;
    TString aerogelName;
    TString aerogelNameSimple;
    Float_t densityAero1 = 0.160;
    Float_t densityAero2 = 0.195;
    xmlFile.open(outputXMLfile.Data());
    xmlFileData.open(outputXML_data_file.Data());
    xmlFile<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl<<endl;

    xmlFile<<"<!--"<<endl 
	   <<"This file contains Aerogel material description only."<<endl
	   <<"-->"<<endl<<endl;

    xmlFile<<"<Materials>"<<endl<<endl;
    xmlFileData<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl<<endl;
    xmlFileData<<"<AerogelTiles  desc=\"Individual optical parameters and thickness of the aerogel tiles\">"<<endl<<endl;
    xmlFileData<<"  <Tiles>"<<endl<<endl;
    for( unsigned i=0; i<aimv.size(); i++){
      //xmlFile<<aimv.at(i).layer<<endl;
      //Aero1_serA090_rin4_col26
      //Aero2_serB162_rin4_col14
      //name
      if(aimv.at(i).layer == "up"){
	aerogelName = "Aero1";
	aerogelNameSimple = "Aerogel1";
	type = "A";
	dn_at_405nm = aimv.at(i).n - 1.045;
	layerid = 0;
      }
      if(aimv.at(i).layer == "down"){
	aerogelName = "Aero2";
	aerogelNameSimple = "Aerogel2";
	type = "B";
	dn_at_405nm = aimv.at(i).n - 1.055;
	layerid = 1;
      }
      //gr_B164;
      //gr_B164_trLength;
      histName = "gr_"; histName += aimv.at(i).serial;
      histNameL = histName; histNameL += "_trLength";
      dX = aimv.at(i).thick;
      aerogelName +="_ser";
      aerogelName +=aimv.at(i).serial;
      aerogelName +="_rin";
      aerogelName +=aimv.at(i).ring;
      aerogelName +="_col";
      aerogelName +=aimv.at(i).column;
      //aerogelName +="_layer";
      //aerogelName +=aimv.at(i).layer;
      // ---> xmlFile
      xmlFile<<"  <Material name=\"";
      xmlFile<<aerogelName<<"\">"<<endl;
      //density
      if(aimv.at(i).layer == "up"){
	xmlFile<<"    <density unit=\"g/cm3\">"<<densityAero1<<"</density>"<<endl;
	//h1_thickness_A->Fill(aimv.at(i).thick);
      }
      if(aimv.at(i).layer == "down"){
	xmlFile<<"    <density unit=\"g/cm3\">"<<densityAero2<<"</density>"<<endl;
	//h1_thickness_B->Fill(aimv.at(i).thick);
      }
      //Components
      xmlFile<<"    <Components>"<<endl;
      xmlFile<<"      <Element fraction=\"0.48\">O</Element>"<<endl;
      xmlFile<<"      <Element fraction=\"0.01\">H</Element>"<<endl;
      xmlFile<<"      <Element fraction=\"0.45\">Si</Element>"<<endl;
      xmlFile<<"      <Element fraction=\"0.06\">C</Element>"<<endl;
      xmlFile<<"    </Components>"<<endl;      
      //Property name RINDEX
      xmlFile<<"    <Property name=\"RINDEX\" unit=\"eV\">"<<endl;
      xmlarichdata::printToFile_TGraph_info( xmlFile, xmlarichdata::aerogel_RefractiveIndex_vs_ev( type, dn_at_405nm), "basf2");
      xmlFile<<"    </Property>"<<endl;
      //Property name ABSLENGTH
      xmlFile<<"    <Property name=\"ABSLENGTH\" unit=\"eV\">"<<endl;
      xmlFile<<"      <value energy=\"1.5\">100</value>"<<endl;
      xmlFile<<"      <value energy=\"2.2\">100</value>"<<endl;
      xmlFile<<"      <value energy=\"2.9\">100</value>"<<endl;
      xmlFile<<"      <value energy=\"3.6\">100</value>"<<endl;
      xmlFile<<"      <value energy=\"4.3\">100</value>"<<endl;
      xmlFile<<"      <value energy=\"5.0\">100</value>"<<endl;
      xmlFile<<"    </Property>"<<endl;
      //Property name RAYLEIGH
      xmlFile<<"    <Property name=\"RAYLEIGH\" unit=\"eV\">"<<endl;
      xmlarichdata::printToFile_TGraph_info( xmlFile, xmlarichdata::aerogel_RAYLEIGH_vs_ev(histName, histNameL, dX), "basf2");
      xmlFile<<"    </Property>"<<endl;
      xmlFile<<"  </Material>"<<endl<<endl;
      // ---> xmlFile END
      // ---> xmlFileData
      //id_map    number    serial  serialID      ring    column     layer         n   transmL     thick
      //  B081        11      B081   CAd9-25         1         1      down    1.0544      3.16      1.98
      //<AerogelTiles>
      //
      //  <Tiles>
      //    <Tile serial="B081">
      //      <ring>1</ring>
      //      <column>1</column>
      //      <layer>1</layer>
      //      <refIndex>1.0544</refIndex>
      //      <trLength unit="cm"> 3.16</trLength>
      //      <thickness unit="cm">1.98 </thickness>
      //      <material>Aero2_serB081_rin1_col1</material>
      //    </Tile>
      //  </Tiles>
      //
      //</AerogelTiles>
      xmlFileData<<"    <Tile serial=\""<<aimv.at(i).serial<<"\">"<<endl;
      xmlFileData<<"      <ring>"<<aimv.at(i).ring<<"</ring>"<<endl;
      xmlFileData<<"      <column>"<<aimv.at(i).column<<"</column>"<<endl;
      xmlFileData<<"      <!-- layer : 0 - up; 1 - down; -->"<<endl;
      xmlFileData<<"      <layer>"<<layerid<<"</layer>"<<endl;
      xmlFileData<<"      <n>"<<aimv.at(i).n<<"</n>"<<endl;
      xmlFileData<<"      <transmL unit=\"mm\">"<<aimv.at(i).transmL*10.0<<"</transmL>"<<endl;
      xmlFileData<<"      <thick unit=\"mm\">"<<aimv.at(i).thick*10.0<<"</thick>"<<endl;
      xmlFileData<<"      <material>"<<aerogelNameSimple<<"</material>"<<endl;
      xmlFileData<<"      <!-- <material>"<<aerogelName<<"</material> -->"<<endl;
      //xmlFileData<<"      <material>"<<aerogelName<<"</material>"<<endl;
      xmlFileData<<"    </Tile>"<<endl<<endl;
      // ---> xmlFileData END
    }
    xmlFile<<"</Materials>"<<endl;
    xmlFileData<<"  </Tiles>"<<endl<<endl;
    xmlFileData<<"</AerogelTiles>"<<endl<<endl;
    xmlFile.close();
    xmlFileData.close();
    //cout<<"aerogel_RefractiveIndex_vs_ev( \"A\", 0.0);"<<endl;
    //aerogel_RefractiveIndex_vs_ev( "A", 0.0);
    
    //h1_thickness_A->Draw();
    return 0;
  }
}//namespace xmlarichdata {


#ifdef GENERATEXMLAEROGELMATERIALFILE_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 1){
    xmlarichdata::generateXmlAerogelMaterialFile();
    return 0;
  }
  xmlarichdata::generateXmlAerogelMaterialFile();
  return 0;
}
# endif //ifndef __CINT__
#endif //GENERATEXMLAEROGELMATERIALFILE_MAIN
