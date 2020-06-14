/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue Nov 28 21:53:16 2017 +0100                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "libxmlarichdata.h"
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
//xml
#include "TXMLEngine.h"

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

TString float2StrTruncate(Float_t val, Int_t precision){
  if(precision>=0){
    char buffer [50];
    TString precisionStr="%1."; precisionStr += precision; precisionStr += "f";
    sprintf (buffer, precisionStr.Data(), val);
    TString  valStr = buffer; 
    return valStr;
  }
  TString  valStr = "";
  valStr += val;
  return valStr;
}

//TString float2StrTruncate(Float_t val, Int_t precision){
//  if(precision>=0){
//    TString  valStr = "";
//    valStr += roundVal(val, precision);
//    return valStr(0,precision+2);
//  }
//  TString  valStr = "";
//  valStr += val;
//  return valStr;
//}

Float_t roundVal(Float_t val, Int_t precision){
  return ceil( ( val * pow( 10,precision ) ) - 0.49 ) / pow( 10,precision );
}

void saveXMLdataVector( TString fnameInfo = "./aerogelDataFromDB/aerogelInfoBis.dat", TString fnameMap = "./aerogelDataFromDB/aerogelMap.dat", TString outXMLfile = "./xmlData/aerogel_xml_ver3/aerogel_xml_ver3_fit.xml", Float_t version=3.0){
  
  const vector<aerogelInfoMap> &aimv = readAerogelInfoMap( fnameInfo, fnameMap);
  
  saveXML(aimv, outXMLfile, version);
  
}

void saveXML(const std::vector<aerogelInfoMap> &aimvfit, TString outXMLfile, Float_t version){

  TString versionStr = "";
  versionStr += version;

  TString valStr = "";

  TString valTruncStr = "";

  // First create engine
  TXMLEngine* xml = new TXMLEngine;
  // Create main node of document tree
  XMLNodePointer_t mainnode = xml->NewChild(0, 0, "aerogelFit");
  xml->NewAttr(mainnode, 0, "descr","Fit parameters of aerogel transmission length.");
  // Simple child node with content inside
  xml->NewChild(mainnode, 0, "version", versionStr.Data());

  //Other child node with attributes
  //XMLNodePointer_t child2 = xml->NewChild(mainnode, 0, "child2");
  //xml->NewAttr(child2, 0, "attr1","value1");
  //xml->NewAttr(child2, 0, "attr2","value2");
  //Child node with subnodes

  //<p0>2.7530379295349121</p0>
  //<p1>0.35418826341629028</p1>
  //<p2>0.072765141725540161</p2>
  //<p3>0.00079104327596724033</p3>
  //<p4>7.801799256412778e-06</p4>

  for( unsigned i=0; i<aimvfit.size(); i++){
    //XMLNodePointer_t child3 = xml->NewChild(mainnode, 0, aimvfit.at(i).serial);
    XMLNodePointer_t child3 = xml->NewChild(mainnode, 0, "aerogeltile");
    xml->NewAttr(child3, 0, "serial",aimvfit.at(i).serial);
    xml->NewChild(child3, 0, "serial", aimvfit.at(i).serial.Data());
    valStr = ""; valStr += aimvfit.at(i).nPoints;
    xml->NewChild(child3, 0, "nPoints", valStr.Data());
    valStr = ""; valStr += aimvfit.at(i).dLam;
    xml->NewChild(child3, 0, "dLam", valStr.Data());
    //valStr = ""; valStr += roundVal(, 3); valTruncStr = valStr(0,5);
    xml->NewChild(child3, 0, "p0", float2StrTruncate(aimvfit.at(i).p0, 5).Data());
    //xml->NewChild(child3, 0, "p0", float2StrTruncate(aimvfit.at(i).p0, -1).Data());
    xml->NewChild(child3, 0, "p1", float2StrTruncate(aimvfit.at(i).p1, 6).Data());
    //xml->NewChild(child3, 0, "p1", float2StrTruncate(aimvfit.at(i).p1, -1).Data());
    xml->NewChild(child3, 0, "p2", float2StrTruncate(aimvfit.at(i).p2, 7).Data());
    //xml->NewChild(child3, 0, "p2", float2StrTruncate(aimvfit.at(i).p2, -1).Data());
    xml->NewChild(child3, 0, "p3", float2StrTruncate(aimvfit.at(i).p3, 8).Data());
    //xml->NewChild(child3, 0, "p3", float2StrTruncate(aimvfit.at(i).p3, -1).Data());
    xml->NewChild(child3, 0, "p4", float2StrTruncate(aimvfit.at(i).p4, 9).Data());
    //xml->NewChild(child3, 0, "p4", float2StrTruncate(aimvfit.at(i).p4, -1).Data());
    valStr = ""; valStr += aimvfit.at(i).p5;
    xml->NewChild(child3, 0, "p5", valStr.Data());
    valStr = ""; valStr += aimvfit.at(i).p6;
    xml->NewChild(child3, 0, "p6", valStr.Data());
  }

  // Child node with subnodes and namespace
  //XMLNodePointer_t child4 = xml->NewChild(mainnode, 0, "child4");
  //XMLNsPointer_t ns4 = xml->NewNS(child4, "http://wesite/webpage");
  //xml->NewChild(child4, ns4, "subchild1", "subchild1 content");
  //xml->NewChild(child4, ns4, "subchild2", "subchild2 content");
  //xml->NewChild(child4, ns4, "subchild3", "subchild3 content");


  // now create document and assign main node of document
  XMLDocPointer_t xmldoc = xml->NewDoc();
  xml->DocSetRootElement(xmldoc, mainnode);
  // Save document to file
  xml->SaveDoc(xmldoc, outXMLfile.Data());
  // Release memory before exit
  xml->FreeDoc(xmldoc);

  cout<<" Output xml file : "<<outXMLfile<<endl;

  delete xml;

}
}//namespace xmlarichdata{

#ifdef SAVEXMLDATAVECTOR_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 5){
    TString fnameInfo = argv[1];
    TString fnameMap = argv[2];
    TString outXMLfile = argv[3];
    Float_t version = atof(argv[4]);
    saveXMLdataVector(fnameInfo,fnameMap,outXMLfile,version);
    return 0;
  }
  saveXMLdataVector();
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef SAVEXMLDATAVECTOR_MAIN
