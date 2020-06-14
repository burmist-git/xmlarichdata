/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Oct 14 01:14:10 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
#include "cellStr.h"
#include "cellGeoStr.h"

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

using namespace xmlarichdata;

namespace xmlarichdata{

  void saveTessellatedSolidVerticesToXML(const std::vector<cellStr> &tessellatedSolidVertices, int precision, TString outXMLfile){
    
    int i;
    int j;
    TString xmlVectorName;
    int apexID = 0;
    int coordinateID = 0;
    cellGeoStr cellGeo;
    const int nApexPerCell = cellGeo.nApexPerCell;
    const int nPointsPerPosition = cellGeo.nPointsPerPosition; //3-D sapce
    TString printefTemplate = "%.";
    printefTemplate += precision;
    printefTemplate += "f ";
    
    FILE * pFile;
    pFile = fopen (outXMLfile.Data(),"w");

    int bodyTessellationVersion = 1;
    
    fprintf( pFile,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf( pFile,"<mergerCoolingBodies desc=\"Parameters of merger cooling bodies installed after Belle2 phase 2\">\n");
    fprintf( pFile,"  <material desc=\"Material of cooling pipe\">ARICH_merger_Cooling_Bodies_Al</material>\n");
    fprintf( pFile,"\n");
    fprintf( pFile,"  <Bodies>\n");
    fprintf( pFile,"\n");
    fprintf( pFile,"    <Body positionID=\"1\">\n");
    fprintf( pFile,"    <bodyTessellationVersion>%d</bodyTessellationVersion>\n",bodyTessellationVersion);
    fprintf( pFile,"    <nCells>%d</nCells>\n",(int)tessellatedSolidVertices.size());
    fprintf( pFile,"    <nApexPerCell>%d</nApexPerCell>\n",nApexPerCell);
    for(i = 0;i<nApexPerCell;i++){
      for(j = 0;j<nPointsPerPosition;j++){
	xmlVectorName = cellGeo.nameVector[i][j];
	apexID = i;
	coordinateID = j;
	saveVectorToFile(tessellatedSolidVertices, pFile, xmlVectorName, "xml", precision, apexID, coordinateID);
      }
    }
    fprintf( pFile,"    </Body>\n");
    fprintf( pFile,"\n");
    fprintf( pFile,"  </Bodies>\n");
    fprintf( pFile,"\n");
    fprintf( pFile,"</mergerCoolingBodies>\n");

    fclose (pFile);
  }

  void saveTessellatedSolidVerticesToDATfile(const std::vector<cellStr> &tessellatedSolidVertices, int precision, TString outDatfile){
    
    int i;
    int j;
    TString xmlVectorName;
    int apexID = 0;
    int coordinateID = 0;
    cellGeoStr cellGeo;
    
    TString printefTemplate = "%.";
    printefTemplate += precision;
    printefTemplate += "f ";
    
    FILE * pFile;
    pFile = fopen (outDatfile.Data(),"w");
    
    fprintf( pFile,"BodyPositionID 1\n");
    fprintf( pFile," nCells %d\n",(int)tessellatedSolidVertices.size());
    fprintf( pFile,"    nApexPerCell %d\n",cellGeo.nApexPerCell);
    for(i = 0;i<cellGeo.nApexPerCell;i++){
      for(j = 0;j<cellGeo.nPointsPerPosition;j++){
	xmlVectorName = cellGeo.nameVector[i][j];
	apexID = i;
	coordinateID = j;
	saveVectorToFile(tessellatedSolidVertices, pFile, xmlVectorName, "dat", precision, apexID, coordinateID);
      }
    }

    fclose (pFile);
  }
  
  void saveVectorToFile(const std::vector<cellStr> &tessellatedSolidVertices, FILE *pFile, TString xmlVectorName, TString xml_or_dat_key, int precision, int apexID, int coordinateID){
    TString printefTemplate = "%.";
    printefTemplate += precision;
    printefTemplate += "f ";
    TString paragraphS;
    TString paragraphE;
    if(xml_or_dat_key == "xml"){
      paragraphS = "    <";
      paragraphS += xmlVectorName;
      paragraphS += ">\n";
      paragraphE = "    </";
      paragraphE += xmlVectorName;
      paragraphE += ">\n";
    }
    else if(xml_or_dat_key == "dat"){
      paragraphS = xmlVectorName;
      paragraphS += "\n";
      paragraphE = " ";
    }
    else {
      assert(0);
    }
    fprintf( pFile, paragraphS.Data(),"");
    for( unsigned i = 0; i<tessellatedSolidVertices.size();i++){
      fprintf( pFile,printefTemplate.Data(), tessellatedSolidVertices[i].apexs[apexID][coordinateID]);
      if((i+1)%5 == 0 && i<(tessellatedSolidVertices.size()-1))
	fprintf( pFile,"\n");
    }
    fprintf( pFile,"\n");
    if(paragraphE != " ")
      fprintf( pFile,paragraphE.Data(),"");    
  }
  
  void dumpTessellatedSolidVertices(const std::vector<cellStr> &tessellatedSolidVertices, int precision){
    
    unsigned int j;
    unsigned int k;
    unsigned int i;
    
    TString printefTemplate = "%.";
    printefTemplate += precision;
    printefTemplate += "f ";
    
    for( i = 0; i<tessellatedSolidVertices.size();i++){
      printf("cell : %5d \n",i);
      for( j = 0; j < tessellatedSolidVertices[i].apexs.size(); j++){
	printf("    apex : %2d ", j);
	for( k = 0; k < tessellatedSolidVertices[i].apexs[j].size(); k++){
	  printf(printefTemplate.Data(), tessellatedSolidVertices[i].apexs[j][k]);
	}
	std::cout<<std::endl;
      }
    }
    
  }

  tessellatedSolidStr readTessellatedSolidVerticesToDATfile(TString inDATfile){
    std::cout<<"inDATfile "<<inDATfile<<std::endl;
    tessellatedSolidStr solidStr;
    std::string mot;
    std::ifstream infile (inDATfile.Data());
    unsigned int i = 0;
    unsigned int j = 0;
    double val;
    cellGeoStr cellGeo;
    //BodyPositionID 1
    // nCells 2492
    //    nApexPerCell 3
    //Apex_1_x
    //13.50000000000000000000 13.50000000000000000000 13.50000000000000000000 13.50000000000000000000 -50.50650024414062500000 
    if (infile.is_open()) {
      while ( infile>>mot ) {
	if(mot == "BodyPositionID")
	  infile>>solidStr.tessellatedSolidID;
	else
	  assert(0);
	infile>>mot;
	if(mot == "nCells")
	  infile>>solidStr.nCells;
	else
	  assert(0);
	infile>>mot;
	if(mot == "nApexPerCell")
	  infile>>solidStr.nApexPerCell;
	else
	  assert(0);
	std::cout<<"solidStr.tessellatedSolidID "<<solidStr.tessellatedSolidID<<std::endl
		 <<"solidStr.nCells             "<<solidStr.nCells<<std::endl
		 <<"solidStr.nApexPerCell       "<<solidStr.nApexPerCell<<std::endl;
	//Apex_1_x, Apex_1_y, Apex_1_z
	for( i = 0; i < cellGeo.nPointsPerPosition; i++){
	  infile>>mot;
	  //std::cout<<mot<<std::endl;
	  if(mot != cellGeo.nameVector[0][i])
	    assert(0);
	  std::vector<double> valv;
	  for( j = 0; j < solidStr.nCells; j++){
	    //infile>>mot;
	    infile>>val;
	    valv.push_back(val);
	    //val = atof(mot.c_str());
	    //std::cout<<val<<std::endl;
	    //solidStr.posV1[i].push_back(val);
	  }
	  solidStr.posV1.push_back(valv);
	}
	//Apex_2_x, Apex_2_y, Apex_2_z
	for( i = 0; i < cellGeo.nPointsPerPosition; i++){
	  infile>>mot;
	  //std::cout<<mot<<std::endl;
	  if(mot != cellGeo.nameVector[1][i])
	    assert(0);
	  std::vector<double> valv;
	  for( j = 0; j < solidStr.nCells; j++){
	    infile>>val;
	    valv.push_back(val);
	  }
	  solidStr.posV2.push_back(valv);
	}
	//Apex_3_x, Apex_3_y, Apex_3_z
	for( i = 0; i < cellGeo.nPointsPerPosition; i++){
	  infile>>mot;
	  //std::cout<<mot<<std::endl;
	  if(mot != cellGeo.nameVector[2][i])
	    assert(0);
	  std::vector<double> valv;
	  for( j = 0; j < solidStr.nCells; j++){
	    infile>>val;
	    valv.push_back(val);
	  }
	  solidStr.posV3.push_back(valv);
	}
      }
      infile.close();
    }
    else {
      std::cout << "Unable to open file : "<<inDATfile<<std::endl;
    } 
    
    return solidStr;
  }
  
}//namespace xmlarichdata{
