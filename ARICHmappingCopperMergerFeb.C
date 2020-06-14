/***********************************************************************
* Copyright(C) 2018 - LBS - (Single person developer.)                 *
* Tue Oct  2 15:23:32 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "ARICHmappingCopperMergerFeb.h"
#include "libxmlarichdata.h"
#include "ARICHfebStr.h"
#include "ARICHcopperStr.h"
#include "ARICHmergerStr.h"
#include "ARICHsectorStr.h"
#include "ARICHmappingStr.h"

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <vector>

//root
#include <TVector2.h>
#include <TPolyLine.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TText.h>
#include <TMath.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TCrown.h>
#include <TArc.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TPad.h>
#include <TString.h>
#include <TFile.h>
#include <TAxis.h>
#include <TVector2.h>
#include <TImage.h>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{
  
  ARICHmappingCopperMergerFeb::ARICHmappingCopperMergerFeb(TString hapdTemplateMappingFileName) : gHAPDpositionInRingPerSector_Arr{ 7, 8, 9, 10, 11, 12, 13} {
    Int_t nHAPDperSectorTmp = 0;
    for(Int_t i = 0;i<GetnHAPDrings();i++)
      nHAPDperSectorTmp += gHAPDpositionInRingPerSector_Arr[i];
    //cout<<"nHAPDperSector    "<<nHAPDperSector<<endl
    //	<<"nHAPDperSectorTmp "<<nHAPDperSectorTmp<<endl;    
    assert(nHAPDperSector == nHAPDperSectorTmp);
    assert(nFebs == nHAPD);
    initialisationOfTheMappingArr();
    initialisationOfTheHAPDpositionTemplate(hapdTemplateMappingFileName);
    initialisationOfTheFullArichMapping();
  }
  
  ARICHmappingCopperMergerFeb::~ARICHmappingCopperMergerFeb(){
  }

  void ARICHmappingCopperMergerFeb::initialisationOfTheFullArichMapping(){
    for( Int_t sec_i = 0 ; sec_i < GetnSectors(); sec_i++){
      ARICHsectorStr sector;
      sector.localID = sec_i;
      sector.globalID = gSectorID_Arr[sec_i];
      for( Int_t cop_i = 0 ; cop_i < GetnCopperPerSector(); cop_i++){
	ARICHcopperStr copper;
	copper.localID = cop_i;
	copper.globalID = gCoperID_Arr[sec_i][cop_i];
	for( Int_t mer_i = 0 ; mer_i < GetnMergersPerCopper(); mer_i++){
	  ARICHmergerStr merger;
	  merger.localID = mer_i;
	  merger.globalID = gMergerID_Arr[sec_i][cop_i][mer_i];
	  for( Int_t feb_i = 0 ; feb_i < GetnHAPDPerMerger() ; feb_i++){
	    ARICHfebStr feb;
	    feb.iRing = sectorTemplate.copper[cop_i].merger[mer_i].feb[feb_i].iRing;
	    feb.iPos = sectorTemplate.copper[cop_i].merger[mer_i].feb[feb_i].iPos;
	    feb.localID = feb_i;
	    feb.globalID = getHAPD_globalID_from_sec_iR_iP(sector.globalID, feb.iRing, feb.iPos);
	    merger.feb.push_back(feb);
	  }
	  copper.merger.push_back(merger);
	}
	sector.copper.push_back(copper);
      }
      arichmapping.sector.push_back(sector);
    }
    for( Int_t sec_i = 0 ; sec_i < GetnSectors(); sec_i++)
      for( Int_t cop_i = 0 ; cop_i < GetnCopperPerSector(); cop_i++)
	for( Int_t mer_i = 0 ; mer_i < GetnMergersPerCopper(); mer_i++)
	  for( Int_t feb_i = 0 ; feb_i < GetnHAPDPerMerger() ; feb_i++)
	    gHAPDID_Arr[sec_i][cop_i][mer_i][feb_i] = arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].feb[feb_i].globalID;
  }
  
  void ARICHmappingCopperMergerFeb::initialisationOfTheMappingArr(){
    for( Int_t mer_i = 0; mer_i<GetnMergersPerSector(); mer_i++)
      gMergerIDPerSector_Arr[mer_i] = mer_i + 1;    
    for( Int_t rin_i = 0; rin_i<GetnHAPDrings(); rin_i++)
      nHAPDInRingInARICH_Arr[rin_i] = gHAPDpositionInRingPerSector_Arr[rin_i] * GetnSectors();
    for( Int_t sec_i = 0; sec_i<GetnSectors(); sec_i++){
      gSectorID_Arr[sec_i] = sec_i+1;
      for( Int_t cop_j = 0; cop_j<GetnCopperPerSector(); cop_j++){
	gCoperID_Arr[sec_i][cop_j] = 4000 + (cop_j + 1 + sec_i * GetnCopperPerSector());
	for( Int_t mer_k = 0; mer_k<nMergersPerCopper; mer_k++){
	  gMergerID_Arr[sec_i][cop_j][mer_k] = mer_k + 1 + GetnMergersPerCopper() * cop_j + sec_i * GetnCopperPerSector() * GetnMergersPerCopper();
	}
      }
    }
  }
  
  void ARICHmappingCopperMergerFeb::dumpMapping(){
    /*
    printMappingConstants();
    cout<<" sectorTemplate "<<endl;
    sectorTemplate.printInfo();
    Int_t sec_i;
    Int_t cop_j;
    Int_t mer_k;
    cout<<endl;
    for (sec_i = 0; sec_i<nSectors; sec_i++){
      cout<<setw(12)<<"sector ID : "<<setw(14)<<gSectorID_Arr[sec_i]<<endl;
      cout<<setw(16)<<"copper ID : ";
      for (cop_j = 0; cop_j<nCopperPerSector; cop_j++)
	cout<<setw(10)<<gCoperID_Arr[sec_i][cop_j];
      cout<<endl;
      for (mer_k = 0; mer_k<nMergersPerCopper; mer_k++){
	cout<<setw(16)<<"merger ID : ";
	for (cop_j = 0; cop_j<nCopperPerSector; cop_j++){
	  cout<<setw(10)<<gMergerID_Arr[sec_i][cop_j][mer_k];
	}
	cout<<endl;
      }
    }
    */
    for( Int_t sec_i = 0 ; sec_i < GetnSectors(); sec_i++){
      cout<<"sector : "<<arichmapping.sector[sec_i].globalID<<endl;
      for( Int_t cop_i = 0 ; cop_i < GetnCopperPerSector(); cop_i++){
	cout<<"     copper : "<<arichmapping.sector[sec_i].copper[cop_i].globalID<<endl;
	for( Int_t mer_i = 0 ; mer_i < GetnMergersPerCopper(); mer_i++){
	  cout<<"          merger : "<<arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].globalID<<endl;
	  for( Int_t feb_i = 0 ; feb_i < GetnHAPDPerMerger() ; feb_i++){
	    cout<<"               feb : "<<arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].feb[feb_i].globalID<<endl;
	  }
	}
      }
    }
  }
  
  bool ARICHmappingCopperMergerFeb::checkCopperBoardID(Int_t copperBoardID){
    if(copperBoardID>=gCoperID_Arr[0][0] && copperBoardID<=gCoperID_Arr[GetnSectors()-1][GetnCopperPerSector()-1])
      return true;
    cout<<" ERROR ---> copper board does not exist : "<<endl
	<<"                          copperBoardID = "<<copperBoardID<<endl;
    assert(0);
    return false;
  }

  bool ARICHmappingCopperMergerFeb::checkMergerLocalID(Int_t mergerLocalID){
    if(mergerLocalID>=0 && mergerLocalID<GetnMergersPerCopper())
      return true;
    cout<<" ERROR ---> merger local ID does not exist : "<<endl
	<<"                             mergerLocalID = "<<mergerLocalID<<endl;
    assert(0);
    return false;
  }

  bool ARICHmappingCopperMergerFeb::checkMergerID(Int_t mergerID){
    if(mergerID>=1 && mergerID<=GetnMergers())
      return true;
    cout<<" ERROR ---> merger local ID does not exist : "<<endl
	<<"                                  mergerID = "<<mergerID<<endl;
    assert(0);
    return false;
  }

  bool ARICHmappingCopperMergerFeb::checkFebLocalID(Int_t febLocalID){
    if(febLocalID>=0 && febLocalID<GetnHAPDPerMerger())
      return true;
    cout<<" ERROR ---> merger local ID does not exist : "<<endl
	<<"                                febLocalID = "<<febLocalID<<endl;
    assert(0);
    return false;
  }
  
  Int_t ARICHmappingCopperMergerFeb::getSectorIDFromCopperBoardID( Int_t copperBoardID){
    if(checkCopperBoardID(copperBoardID))
      for( Int_t sec_i = 0; sec_i<nSectors; sec_i++)
	for( Int_t cop_j = 0; cop_j<nCopperPerSector; cop_j++)
	  if(gCoperID_Arr[sec_i][cop_j] == copperBoardID)
	    return gSectorID_Arr[sec_i];
    return -999;
  }
  
  Int_t ARICHmappingCopperMergerFeb::getSectorIDFromMergerID( Int_t mergerID){
    if(checkMergerID(mergerID))
      for( Int_t sec_i = 0; sec_i<nSectors; sec_i++)
	for( Int_t cop_j = 0; cop_j<nCopperPerSector; cop_j++)
	  for( Int_t mer_k = 0; mer_k<nMergersPerCopper; mer_k++)
	    if(gMergerID_Arr[sec_i][cop_j][mer_k] == mergerID)
	      return gSectorID_Arr[sec_i];
    return -999;
  }
  
  Int_t ARICHmappingCopperMergerFeb::getCopperBoardLocalIDFromCopperBoardID( Int_t copperBoardID){
    if(checkCopperBoardID(copperBoardID))
      for( Int_t sec_i = 0; sec_i<nSectors; sec_i++)
	for( Int_t cop_j = 0; cop_j<nCopperPerSector; cop_j++)
	  if(gCoperID_Arr[sec_i][cop_j] == copperBoardID)
	    return cop_j;
    return -999;
  }
  
  Int_t ARICHmappingCopperMergerFeb::getMergerIDFromCopperBoardIDAndMergerLocalID( Int_t copperBoardID, Int_t mergerLocalID){
    Int_t sectorLocalNumber = getSectorIDFromCopperBoardID(copperBoardID)-1;         //0,1,2,3,4,5
    Int_t copperLocalNumber = getCopperBoardLocalIDFromCopperBoardID(copperBoardID); //0,1,2,3
    if( checkMergerLocalID(mergerLocalID))
      return gMergerID_Arr[sectorLocalNumber][copperLocalNumber][mergerLocalID];
    return -999;
  }
  
  Int_t ARICHmappingCopperMergerFeb::getFebIDFromCopperBoardIDAndMergerLocalIDAndFebLocalID( Int_t copperBoardID, Int_t mergerLocalID, Int_t febLocalID){
    Int_t sectorLocalNumber = getSectorIDFromCopperBoardID(copperBoardID)-1;         //0,1,2,3,4,5
    Int_t copperLocalNumber = getCopperBoardLocalIDFromCopperBoardID(copperBoardID); //0,1,2,3
    if( checkMergerLocalID(mergerLocalID))
      if( checkFebLocalID(febLocalID))
	return gHAPDID_Arr[sectorLocalNumber][copperLocalNumber][mergerLocalID][febLocalID]; //1 - 420
    return -999;
  }

  void ARICHmappingCopperMergerFeb::printMappingConstants(){
    cout<<"nSectors          : "<<GetnSectors()<<endl
	<<"nCopperPerSector  : "<<GetnCopperPerSector()<<endl
	<<"nMergersPerCopper : "<<GetnMergersPerCopper()<<endl
	<<"nHAPDPerMerger    : "<<GetnHAPDPerMerger()<<endl
	<<"nCopper           : "<<GetnCopper()<<endl
	<<"nMergersPerSector : "<<GetnMergersPerSector()<<endl;
    cout<<"nMergers          : "<<GetnMergers()<<endl
	<<"nFebs             : "<<GetnFebs()<<endl
	<<"nHAPDperSector    : "<<GetnHAPDperSector()<<endl
	<<"nHAPD             : "<<GetnHAPD()<<endl
	<<"nHAPDrings        : "<<nHAPDrings<<endl;
    for(Int_t i = 0;i<nHAPDrings;i++)
      cout<<"gHAPDpositionInRingPerSector_Arr["<<i<<"] = "<<gHAPDpositionInRingPerSector_Arr[i]<<endl;
    for(Int_t i = 0;i<nHAPDrings;i++)
      cout<<"nHAPDInRingInARICH_Arr["<<i<<"] = "<<nHAPDInRingInARICH_Arr[i]<<endl;    
  }

  void ARICHmappingCopperMergerFeb::initialisationOfTheHAPDpositionTemplate(TString hapdTemplateMappingFileName = "hapdTemplateMapping.dat"){
    sectorTemplate.localID=-999;
    Int_t COPPERLOCALID;
    Int_t MERGERLOCALID;
    Int_t FEBLOCALID;
    Int_t iR;
    Int_t iP;
    string mot;
    ifstream tmfile (hapdTemplateMappingFileName.Data());
    if(tmfile.is_open()){
      //for( Int_t mer_i = 0 ; mer_i < GetnMergersPerSector(); mer_i++){
      for( Int_t cop_i = 0 ; cop_i < GetnCopperPerSector(); cop_i++){
	ARICHcopperStr copper;
	tmfile >> mot;
	//cout<<mot<<endl;
	assert(mot == "COPPERLOCALID");
	tmfile >> COPPERLOCALID;
	//cout<<COPPERLOCALID<<endl;
	copper.localID=COPPERLOCALID;
	for( Int_t mer_i = 0 ; mer_i < GetnMergersPerCopper(); mer_i++){
	  ARICHmergerStr merger;
	  tmfile >> mot;
	  assert(mot == "MERGERLOCALID");
	  tmfile >> MERGERLOCALID;
	  merger.localID = MERGERLOCALID;
	  for( Int_t feb_i = 0 ; feb_i < GetnHAPDPerMerger() ; feb_i++){
	    ARICHfebStr feb;
	    tmfile >> mot;
	    assert(mot == "FEBLOCALID");
	    tmfile >> FEBLOCALID;
	    tmfile >> mot;
	    assert(mot == "iR");
	    tmfile >> iR;
	    tmfile >> mot;
	    assert(mot == "iP");
	    tmfile >> iP;
	    feb.iRing=iR;
	    feb.iPos=iP;
	    feb.localID=FEBLOCALID;
	    merger.feb.push_back(feb);
	    //cout<<"iR "<<iR<<endl;
	    //cout<<"iP "<<iP<<endl;
	  }
	  copper.merger.push_back(merger);
	}
	sectorTemplate.copper.push_back(copper);
      }
      tmfile.close();
    }    
    else{
      cout << "Unable to open file"; 
      assert(0);
    }
    //sectorTemplate.printInfo();   
  }

  Int_t ARICHmappingCopperMergerFeb::getHAPD_globalID_from_sec_iR_iP(Int_t secID, Int_t iR, Int_t iP){
    assert(secID>=1);
    assert(secID<=GetnSectors());
    if(iR == 999)
      if(iP == 999)
	return 999;
    assert(iR>=1);
    assert(iR<=GetnHAPDrings());
    assert(iP>=1);
    assert(iP<=gHAPDpositionInRingPerSector_Arr[iR-1]);
    Int_t n0 = 0;
    for(Int_t i=1; i<iR; i++)
      n0 += nHAPDInRingInARICH_Arr[i-1];
    return (iP + gHAPDpositionInRingPerSector_Arr[iR-1]*(secID-1) + n0);
  }

  void ARICHmappingCopperMergerFeb::findPositionInarichmappingFormSecIDiRingiPosition(Int_t secID, Int_t iR, Int_t iP,
										      Int_t &sec_i, Int_t &cop_i, Int_t &mer_i, Int_t &feb_i){
    assert(secID>=1);
    assert(secID<=GetnSectors());
    assert(iR>=1);
    assert(iR<=GetnHAPDrings());
    assert(iP>=1);
    assert(iP<=gHAPDpositionInRingPerSector_Arr[iR-1]);
    sec_i = secID - 1;
    for( cop_i = 0 ; cop_i < GetnCopperPerSector(); cop_i++)
      for( mer_i = 0 ; mer_i < GetnMergersPerCopper(); mer_i++)
	for( feb_i = 0 ; feb_i < GetnHAPDPerMerger() ; feb_i++)
	  if(arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].feb[feb_i].iRing == iR)
	    if(arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].feb[feb_i].iPos == iP)
	      return;
    assert(0);
  }
  
  void ARICHmappingCopperMergerFeb::findPositionInarichmappingFormGlobalFebID(Int_t febID, Int_t &sec_i, Int_t &cop_i, Int_t &mer_i, Int_t &feb_i){
    assert(febID>=1);
    assert(febID<=GetnHAPD());
    for( sec_i = 0 ; sec_i < GetnSectors(); sec_i++)
      for( cop_i = 0 ; cop_i < GetnCopperPerSector(); cop_i++)
	for( mer_i = 0 ; mer_i < GetnMergersPerCopper(); mer_i++)
	  for( feb_i = 0 ; feb_i < GetnHAPDPerMerger() ; feb_i++)
	    if(arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].feb[feb_i].globalID == febID)
	      return;
    assert(0);
  }

  void ARICHmappingCopperMergerFeb::getSecIDAndCopperBoardIDAndMergerIDAndMergerLocalIDAndFebLocalIDFromFebID( Int_t febID,
													       Int_t &sectorID,
													       Int_t &copperBoardID,
													       Int_t &mergerID,
													       Int_t &mergerLocalID,
													       Int_t &febLocalID){
    assert(febID>=1);
    assert(febID<=GetnHAPD());
    Int_t sec_i, cop_i, mer_i, feb_i;
    findPositionInarichmappingFormGlobalFebID(febID, sec_i, cop_i, mer_i, feb_i);
    sectorID = gSectorID_Arr[sec_i];
    copperBoardID = gCoperID_Arr[sec_i][cop_i];
    //mergerLocalID = gMergerID_Arr[sec_i][cop_i][feb_i];
    mergerID = arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].globalID;
    mergerLocalID = arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].localID;
    febLocalID = arichmapping.sector[sec_i].copper[cop_i].merger[mer_i].feb[feb_i].localID;
  }
  
} //namespace xmlarichdata{
  
