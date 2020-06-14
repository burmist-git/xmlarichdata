/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Thu Jan 18 14:24:45 2018 +0100                                       *
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

void convertdx2xml(TString inFolder = "./data/transT_markup_data/dataL/",
		   TString inXmlFolder = "./data/aerogel_xml_ver3/",
		   TString outFolder = "./data/aerogel_xml_ver3_L/",
		   TString outTmpFolder = "./data/aerogel_xml_ver3_Tmp_L/",
		   TString versionIDstr = "3.0",
		   TString conversionKey = "Left",
		   TString fnameInfo = "./aerogelDataFromDB/aerogelInfoBis.dat",
		   TString fnameMap = "./aerogelDataFromDB/aerogelMap.dat"){

  cout<<"inFolder     "<<inFolder<<endl
      <<"inXmlFolder  "<<inXmlFolder<<endl
      <<"outFolder    "<<outFolder<<endl;
  cout<<"outTmpFolder "<<outTmpFolder<<endl
      <<"fnameInfo    "<<fnameInfo<<endl
      <<"fnameMap     "<<fnameMap<<endl;
  
  TString lrstr="";
  TString outlrstr="";
  
  if(conversionKey == "Left"){
    lrstr = "_l_";
    outlrstr = "L";
  }
  else if(conversionKey == "Right"){
    lrstr = "_r_";
    outlrstr = "R";
  }
  
  //Read aerogel info map
  const vector<aerogelInfoMap> &aimv = readAerogelInfoMap( fnameInfo, fnameMap);
  
  for( unsigned i=0; i<aimv.size(); i++){
    aerogelInfoMap aimstr = aimv.at(i);
    TString indxFileName = inFolder;
    indxFileName += aimv.at(i).serialID; 
    indxFileName += "wjt";
    indxFileName += lrstr;
    indxFileName += "database.dx";
    TString inXmlFileName = inXmlFolder;
    inXmlFileName += aimv.at(i).serial;
    inXmlFileName += "data";
    inXmlFileName += ".xml";
    TString outTmpxmlFileName = outTmpFolder;
    outTmpxmlFileName += aimv.at(i).serial;
    outTmpxmlFileName += "data";
    outTmpxmlFileName += outlrstr;
    outTmpxmlFileName += ".xml";
    TString outxmlFileName = outFolder;
    outxmlFileName += aimv.at(i).serial;
    outxmlFileName += "data";
    outxmlFileName += outlrstr;
    outxmlFileName += ".xml";
    //cout<<"indxFileName  "<<indxFileName<<endl
    //	<<"outTmpxmlFileName "<<outTmpxmlFileName<<endl;
    //cout<<"diff "<<indxFileName<<" "<<outTmpxmlFileName<<endl;
    Float_t translengthf = 0.0;
    Float_t thickf = 0.0;
    makeconvertiondx2xml(indxFileName,outTmpxmlFileName,versionIDstr,conversionKey,translengthf,thickf,aimstr);
    TGraph *gr = new TGraph();
    TGraph *gr_L = new TGraph();
    //cout<<xmlDataFileList[i]<<endl;
    TString versionInfo = "";      //<version>2.0</version>
    TString serialInfo = "";       //<serial>A001</serial>
    TString idInfo = "";           //<id>CAu1-1</id>
    Double_t indexInfo = 0.0;       //<index>1.0435</index>
    Double_t translengthInfo = 0.0; //<translength>56</translength>
    Double_t thickInfo = 0.0;       //<thick>20.3</thick>
    read_xml_File_transmittance(inXmlFileName, versionInfo, serialInfo, idInfo, indexInfo, translengthInfo, thickInfo, gr);
    //cout<<thickInfo<<endl;
    //cout<<translengthInfo<<endl;
    calc_translength(thickInfo, translengthInfo, gr, gr_L);
    thickf = thickInfo;
    translengthf = gr_L->Eval(400);
    //cout<<thickf<<endl;
    makeconvertiondx2xml(indxFileName,outxmlFileName,versionIDstr,conversionKey,translengthf,thickf,aimstr);
  }

}

void makeconvertiondx2xml( TString indxFileName, TString outxmlFileName, TString versionIDstr, TString positionstr, Float_t translengthf, Float_t thickf, aerogelInfoMap aimstr){
  string mot1;
  string mot2;
  ifstream indata;
  ofstream outdata;

  indata.open(indxFileName.Data());
  outdata.open(outxmlFileName.Data());
  assert(indata.is_open());
  assert(outdata.is_open());
  //////Header//////
  outdata<<"<?xml version=\"1.0\" encoding=\"utf-8\"?>"<<endl;
  outdata<<"<aerogel>"<<endl;
  outdata<<"<version>"<<versionIDstr<<"</version>"<<endl;
  outdata<<"<position>"<<positionstr<<"</position>"<<endl;
  outdata<<"<serial>"<<aimstr.serial<<"</serial>"<<endl;
  outdata<<"<id>"<<aimstr.serialID<<"</id>"<<endl;
  outdata<<"<index>"<<aimstr.n<<"</index>"<<endl;
  //translengthf = aimv.at(i).transmL*10;
  //-thick/TMath::Log(y/100.0)
  outdata<<"<translength>"<<translengthf<<"</translength>"<<endl;
  //outdata<<"<thick>"<<aimstr.thick<<"</thick>"<<endl;
  outdata<<"<thick>"<<thickf<<"</thick>"<<endl;
  outdata<<"<transmittance>"<<endl;
  //////////////////
  while(indata>>mot1>>mot2){
    outdata<<"  "<<mot1<<" "<<mot2<<endl;
  }
  outdata<<"</transmittance>"<<endl;
  outdata<<"</aerogel>"<<endl;
  indata.close();
  outdata.close();

}
}//namespace xmlarichdata{

#ifdef CONVERTDX2XML_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 9){
    TString inFolder = argv[1];
    TString inXmlFolder = argv[2];
    TString outFolder = argv[3];
    TString outTmpFolder = argv[4];
    TString versionIDstr = argv[5];
    TString conversionKey = argv[6];
    TString fnameInfo = argv[7];
    TString fnameMap = argv[8];
    convertdx2xml( inFolder, inXmlFolder, outFolder, outTmpFolder, versionIDstr, conversionKey, fnameInfo, fnameMap);
    return 0;
  }
  //convertdx2xml();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef CONVERTDX2XML_MAIN
