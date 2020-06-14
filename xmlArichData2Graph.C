/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Oct 15 16:09:59 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "libxmlarichdata.h"
#endif

//my
#include "aerogelInfoMap.h"

//c, c++
#include <iostream>
#include <fstream>

//root
#include "TXMLEngine.h"
#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TVector3.h>
#include <TGraph.h>
#include <TMath.h>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{

  const Int_t nFileMax = 400;
  
  //Int_t read_xml_File_List(TString filenameXMLList,
  //			 TString *xmlDataFileList);
  
  //Int_t read_xml_File_transmittance(TString filename, TString &versionInfo, TString &serialInfo, TString &idInfo, 
  //				  Double_t &indexInfo, Double_t &translengthInfo, Double_t &thickInfo, TGraph *gr);
  
  //Double_t calc_translength( Double_t thick, Double_t translength, TGraph *gr_tr, TGraph *gr_trL);
  
  //void addTGraph( TGraph *gr, TGraph *gr_add);
  //void normTGraph( TGraph *gr, Double_t norm);
  
  //void printToFileDifferencesDetails( TString differencesDetailsFileName, TString filename, TString versionInfo, Double_t deltaTrL, Double_t translengthInfo, Double_t translengthInfoData);
  
  Int_t xmlArichData2Graph(TString filePathXML = "./data/2nd_measurement/", 
			   TString filenameXMLList = "./data/2nd_measurement/AerogelData.xml", 
			   TString fnameroot = "./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength.root",
			   TString differencesDetailsFileName = "./dataDiffInfo/2nd_measurement/differencesDetails.dat",
			   Double_t normAVal = 171.0,
			   Double_t normBVal = 169.0){
    cout<<"filePathXML                "<<filePathXML<<endl
	<<"filenameXMLList            "<<filenameXMLList<<endl
	<<"fnameroot                  "<<fnameroot<<endl
	<<"differencesDetailsFileName "<<differencesDetailsFileName<<endl
	<<"normAVal                   "<<normAVal<<endl
	<<"normBVal                   "<<normBVal<<endl;
    //return 0;
    TString xmlDataFileList[nFileMax];
    Int_t nFiles = 0;
    nFiles = read_xml_File_List( filenameXMLList, xmlDataFileList);
    cout<<"nFiles "<<nFiles<<endl;
    
    Int_t i = 0;
    
    TString versionInfo;      //<version>2.0</version>
    TString serialInfo;       //<serial>A001</serial>
    TString idInfo;           //<id>CAu1-1</id>
    Double_t indexInfo;       //<index>1.0435</index>
    Double_t translengthInfo; //<translength>56</translength>
    Double_t thickInfo;       //<thick>20.3</thick>
    TGraph *gr[nFileMax];
    TGraph *gr_L[nFileMax];
    TGraph *gr_A_norm = new TGraph();gr_A_norm->SetName("gr_A_norm");gr_A_norm->SetTitle("gr_A_norm");
    TGraph *gr_A_L_norm = new TGraph();gr_A_L_norm->SetName("gr_A_L_norm");gr_A_L_norm->SetTitle("gr_A_L_norm");
    TGraph *gr_B_norm = new TGraph();gr_B_norm->SetName("gr_B_norm");gr_B_norm->SetTitle("gr_B_norm");
    TGraph *gr_B_L_norm = new TGraph();gr_B_L_norm->SetName("gr_B_L_norm");gr_B_L_norm->SetTitle("gr_B_L_norm");
    TString filename;
    
    Double_t deltaTrL = -999.0;
    TH1D *h1_deltaTrL   = new TH1D("h1_deltaTrL","#Delta translength",100,-5,5);
    TH1D *h1_deltaTrL_A = new TH1D("h1_deltaTrL_A","#Delta translength A",100,-5,5);
    TH1D *h1_deltaTrL_B = new TH1D("h1_deltaTrL_B","#Delta translength B",100,-5,5);
    
    TH1D *h1_n_A = new TH1D("h1_n_A","n A",100,1.04,1.06);
    TH1D *h1_n_B = new TH1D("h1_n_B","n B",100,1.04,1.06);
    
    TH1D *h1_Tr_A_300 = new TH1D("h1_Tr_A_300","Tr 300",100,0.0,100);
    TH1D *h1_Tr_B_300 = new TH1D("h1_Tr_B_300","Tr 300",100,0.0,100);
    TH1D *h1_TrL_A_400   = new TH1D( "h1_TrL_A_400",  "TrL 400",  100,0.0,100);
    TH1D *h1_TrL_B_400   = new TH1D( "h1_TrL_B_400",  "TrL 400",  100,0.0,100);
    TH1D *h1_TrLre_A_400 = new TH1D("h1_TrLre_A_400","TrL re 400",100,0.0,100);
    TH1D *h1_TrLre_B_400 = new TH1D("h1_TrLre_B_400","TrL re 400",100,0.0,100);
    
    TGraph *gr_A_TrL_vs_DataTrL = new TGraph();gr_A_TrL_vs_DataTrL->SetName("gr_A_TrL_vs_DataTrL");gr_A_TrL_vs_DataTrL->SetTitle("gr_A_TrL_vs_DataTrL");
    TGraph *gr_B_TrL_vs_DataTrL = new TGraph();gr_B_TrL_vs_DataTrL->SetName("gr_B_TrL_vs_DataTrL");gr_B_TrL_vs_DataTrL->SetTitle("gr_B_TrL_vs_DataTrL");
    
    TFile f(fnameroot.Data(), "recreate");
    f.cd();
    for( i = 0; i < nFiles ; i++){
      gr[i] = new TGraph();
      gr_L[i] = new TGraph();
      //cout<<xmlDataFileList[i]<<endl;
      versionInfo = "";
      serialInfo = "";
      idInfo = "";
      indexInfo = 0.0;
      translengthInfo = 0.0;
      thickInfo = 0.0;  
      filename = filePathXML;  
      filename += xmlDataFileList[i];
      read_xml_File_transmittance(filename, versionInfo, serialInfo, idInfo, indexInfo, translengthInfo, thickInfo, gr[i]);
      deltaTrL = calc_translength( thickInfo, translengthInfo, gr[i], gr_L[i]);
      if(TMath::Abs(deltaTrL)>1.0)
	printToFileDifferencesDetails( differencesDetailsFileName, filename, versionInfo, deltaTrL, translengthInfo, gr_L[i]->Eval(400.0));
      h1_deltaTrL->Fill(deltaTrL);
      if(serialInfo.Contains("A")){
	addTGraph(gr[i],gr_A_norm);
	addTGraph(gr_L[i],gr_A_L_norm);
	h1_Tr_A_300->Fill(gr[i]->Eval(300.0));
	h1_TrL_A_400->Fill(translengthInfo);
	h1_TrLre_A_400->Fill(gr_L[i]->Eval(400.0));
	h1_deltaTrL_A->Fill(deltaTrL);
	gr_A_TrL_vs_DataTrL->SetPoint(gr_A_TrL_vs_DataTrL->GetN(),translengthInfo,gr_L[i]->Eval(400.0));
	h1_n_A->Fill(indexInfo);
      }
      if(serialInfo.Contains("B")){
	addTGraph(gr[i],gr_B_norm);
	addTGraph(gr_L[i],gr_B_L_norm);
	h1_Tr_B_300->Fill(gr[i]->Eval(300.0));
	h1_TrL_B_400->Fill(translengthInfo);
	h1_TrLre_B_400->Fill(gr_L[i]->Eval(400.0));
	h1_deltaTrL_B->Fill(deltaTrL);
	gr_B_TrL_vs_DataTrL->SetPoint(gr_B_TrL_vs_DataTrL->GetN(),translengthInfo,gr_L[i]->Eval(400.0));
	h1_n_B->Fill(indexInfo);
      }
      gr[i]->Write();
      gr_L[i]->Write();
    }
    normTGraph(gr_A_norm,normAVal);
    normTGraph(gr_A_L_norm,normAVal);
    normTGraph(gr_B_norm,normBVal);
    normTGraph(gr_B_L_norm,normBVal);
    h1_deltaTrL->Write();
    gr_A_norm->Write();
    gr_A_L_norm->Write();
    gr_B_norm->Write();
    gr_B_L_norm->Write();
    h1_Tr_A_300->Write();
    h1_Tr_B_300->Write();
    h1_deltaTrL_A->Write();
    h1_deltaTrL_B->Write();
    gr_A_TrL_vs_DataTrL->Write();
    gr_B_TrL_vs_DataTrL->Write();
    h1_TrL_A_400->Write();
    h1_TrL_B_400->Write();
    h1_TrLre_A_400->Write();
    h1_TrLre_B_400->Write();
    h1_n_A->Write();
    h1_n_B->Write();
    // // // xcout<<"versionInfo     -> "<<versionInfo<<endl
    // // //      <<"serialInfo      -> "<<serialInfo<<endl
    // // //      <<"idInfo          -> "<<idInfo<<endl
    // // //      <<"indexInfo       -> "<<indexInfo<<endl
    // // //      <<"translengthInfo -> "<<translengthInfo<<endl
    // // //      <<"thickInfo       -> "<<thickInfo<<endl;
    //gr->Draw("APL");
    
    return 0;
  }
  
  Double_t calc_translength( Double_t thick, Double_t translength, TGraph *gr_tr, TGraph *gr_trL){
    TString grLName = gr_tr->GetName();
    TString grLTitle = gr_tr->GetTitle();
    grLName += "_trLength";
    grLTitle += "_trLength";
    gr_trL->SetName(grLName.Data());
    gr_trL->SetTitle(grLTitle.Data());
    Int_t i = 0;
    Double_t x = 0;
    Double_t y = 0;
    for(i = 0 ; i<gr_tr->GetN() ; i++){
      gr_tr->GetPoint(i,x,y);
      if(y>0.0)
	gr_trL->SetPoint(i,x,-thick/TMath::Log(y/100.0));
      else
	gr_trL->SetPoint(i,x,0.0);
    }
    return translength - gr_trL->Eval(400);
  }
  
  Int_t read_xml_File_List(TString filenameXMLList, TString *xmlDataFileList){
    
    Int_t ii = 0;
    TString xmlDataFileName;
    
    TXMLEngine* xml;
    XMLNodePointer_t mainnode;
    // First create engine
    xml = new TXMLEngine();
    // Now try to parse xml file
    // Only file with restricted xml syntax are supported
    XMLDocPointer_t xmldoc = xml->ParseFile(filenameXMLList.Data());
    if(xmldoc==0){
      delete xml;
      cout<<" ---> ERROR : not XMLDocPointer_t created "<<endl;
      return 1;
    }
    // take access to main node
    mainnode = xml->DocGetRootElement(xmldoc);
    XMLNodePointer_t child = xml->GetChild(mainnode);
    child = xml->GetChild(child);
    XMLAttrPointer_t attr = xml->GetFirstAttr(child);
    ii = 0;
    while (attr!=0) {
      xmlDataFileName = xml->GetAttrValue(attr);
      //cout<<xmlDataFileName<<endl;
      xmlDataFileList[ii] = xmlDataFileName;
      attr = xml->GetNextAttr(attr);
      child = xml->GetNext(child);
      attr = xml->GetFirstAttr(child);
      ii++;
    }
    
    // Release memory before exit
    xml->FreeDoc(xmldoc);
    delete xml;
    
    return ii;
  }
  
  Int_t read_xml_File_transmittance(TString filename,
				    TString &versionInfo, TString &serialInfo, TString &idInfo, 
				    Double_t &indexInfo, Double_t &translengthInfo, Double_t &thickInfo, TGraph *gr){
    
    //cout<<filename<<endl;
    
    TString grName = "";
    TString grTitle = "";
    char lineIndex[100];
    char lineTransleng[100];
    char lineThick[100];
    TString lineIndexStr;
    TString lineTranslengStr;
    TString lineThickStr;
    //<?xml version="1.0" encoding="utf-8"?>
    //<aerogel>
    //<version>2.0</version>
    //<serial>A001</serial>
    //<id>CAu1-1</id>
    //<index>1.0435</index>
    //<translength>56</translength>
    //<thick>20.3</thick>
    //<transmittance>
    //<transpoint lambda='700'>93.7</transpoint>
    //<transpoint lambda='690'>93.5</transpoint>
    //<transpoint lambda='680'>93.2</transpoint>
    //<transpoint lambda='670'>93.0</transpoint>
    //<transpoint lambda='660'>92.8</transpoint>
    //<transpoint lambda='650'>92.5</transpoint>
    //.
    //.
    //.
    //<transpoint lambda='220'>0.0</transpoint>
    //<transpoint lambda='210'>0.0</transpoint>
    //<transpoint lambda='200'>0.0</transpoint>
    //</transmittance>
    //</aerogel>
    TXMLEngine* xml;
    XMLNodePointer_t mainnode;
    // First create engine
    xml = new TXMLEngine();
    // Now try to parse xml file
    // Only file with restricted xml syntax are supported
    XMLDocPointer_t xmldoc = xml->ParseFile(filename.Data());
    if(xmldoc==0){
      delete xml;
      cout<<" ---> ERROR : not XMLDocPointer_t created "<<endl;
      return 1;
    }
    // take access to main node
    mainnode = xml->DocGetRootElement(xmldoc);
    Double_t transpointVal;
    Double_t lambdaVal;
    TString nodeName;
    //cout<<xml->GetNodeName(mainnode)<<endl;
    XMLNodePointer_t child = xml->GetChild(mainnode);
    while(child!=0){
      nodeName = xml->GetNodeName(child);
      //cout<<"   "<<nodeName<<endl;
      if(nodeName == "version"){
	versionInfo = xml->GetNodeContent(child);
      }
      else if(nodeName == "serial"){
	serialInfo = xml->GetNodeContent(child);
      }
      else if(nodeName == "id"){
	idInfo = xml->GetNodeContent(child);
      }
      else if(nodeName == "index"){
	indexInfo = atof(xml->GetNodeContent(child));
	//1.0444
	sprintf (lineIndex, "%1.4f", indexInfo);
	lineIndexStr = lineIndex;
      }
      else if(nodeName == "translength"){
	translengthInfo = atof(xml->GetNodeContent(child));
	//56
	sprintf (lineTransleng, "%2.1f", translengthInfo);
	lineTranslengStr = lineTransleng;
      }
      else if(nodeName == "thick"){
	thickInfo = atof(xml->GetNodeContent(child));
	//20.3
	sprintf (lineThick, "%2.1f", thickInfo);
	lineThickStr = lineThick;
      }
      else if(nodeName == "transmittance"){
	grName = "gr_"; grName += serialInfo;
	grTitle = "gr"; 
	grTitle +="_version_";
	grTitle +=versionInfo;
	grTitle +="_serial_";
	grTitle +=serialInfo;
	grTitle +="_id_";
	grTitle +=idInfo;
	grTitle +="_index_";
	//grTitle +=indexInfo;
	grTitle +=lineIndexStr;
	grTitle +="_translength_";
	//grTitle +=translengthInfo;
	grTitle +=lineTranslengStr;
	grTitle +="_thick_";
	//grTitle +=thickInfo;
	grTitle +=lineThickStr;
	gr->SetName(grName.Data());
	gr->SetTitle(grTitle.Data());
	child = xml->GetChild(child);
	while(child!=0){
	  nodeName = xml->GetNodeName(child);
	  //child = xml->GetNext(child);
	  if(nodeName == "transpoint"){
	    XMLAttrPointer_t attr = xml->GetFirstAttr(child);
	    //cout<<xml->GetAttrName(attr)<<endl;
	    lambdaVal = atof(xml->GetAttrValue(attr));
	    transpointVal = atof(xml->GetNodeContent(child));
	    //cout<<"lambdaVal     = "<<lambdaVal<<endl
	    //<<"transpointVal = "<<transpointVal<<endl;
	    gr->SetPoint(gr->GetN(),lambdaVal,transpointVal);
	    child = xml->GetNext(child);
	  }
	}
      }
      child = xml->GetNext(child);
      //cout<<"   "<<nodeName<<endl;
    }
  
    // Release memory before exit
    xml->FreeDoc(xmldoc);
    delete xml;
    
    return 0;
  }
  
  void addTGraph( TGraph *gr, TGraph *gr_add){
    Int_t i = 0;
    Double_t x = 0;
    Double_t y = 0;
    Double_t y_add = 0;
    for(i = 0 ; i<gr->GetN() ; i++){
      gr->GetPoint(i,x,y);
      gr_add->GetPoint(i,x,y_add);
      gr_add->SetPoint(i,x,y_add+y);
    }
  }

  void normTGraph( TGraph *gr, Double_t norm){
    Int_t i = 0;
    Double_t x = 0;
    Double_t y = 0;
    Double_t y_norm = 0;
    for(i = 0 ; i<gr->GetN() ; i++){
      gr->GetPoint(i,x,y);
      y_norm = y/norm;
      gr->SetPoint(i,x,y_norm);
    }
  }
  
  void printToFileDifferencesDetails( TString differencesDetailsFileName, TString filename, TString versionInfo, Double_t deltaTrL, Double_t translengthInfo, Double_t translengthInfoData){
    static int nn = 1;
    //cout<<"printToFileDifferencesDetails"<<endl;
    ofstream myfile;
    myfile.open(differencesDetailsFileName.Data(),ios::app);
    myfile<<"nn                  "<<nn<<endl
	  <<"filename            "<<filename<<endl
	  <<"versionInfo         "<<versionInfo<<endl
	  <<"deltaTrL            "<<deltaTrL<<endl
	  <<"translengthInfo     "<<translengthInfo<<endl
	  <<"translengthInfoData "<<translengthInfoData<<endl<<endl;
    myfile.close();
    nn++;
  }
}//namespace xmlarichdata {

#ifdef XMLARICHDATA2GRAPH_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 7){
    TString filePathXML = argv[1];
    TString filenameXMLList = argv[2];
    TString fnameroot = argv[3];
    TString differencesDetailsFileName = argv[4];
    Double_t normAVal = atof(argv[5]);
    Double_t normBVal = atof(argv[6]);
    xmlArichData2Graph(filePathXML,filenameXMLList,fnameroot,differencesDetailsFileName,normAVal,normBVal);
    return 0;
  }
  xmlArichData2Graph();
  return 0;
}
# endif //ifndef __CINT__
#endif //XMLARICHDATA2GRAPH_MAIN
