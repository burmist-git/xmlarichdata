/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Thu May 10 16:43:27 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "ARICHcablesMaterial.h"
#include "libxmlarichdata.h"
#else 
//my
#include "ARICHcablesMaterial.C"
#endif //#if !defined(__CLING__)

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
#include <TMath.h>

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

  Int_t runARICHcablesMaterial(){

    TString cableName; 
    TString stdID;
    double rhoOfCore = ARICHcablesMaterial::getAverageDensityOfCore_MassFraction();
    double rhoOfIsolation = ARICHcablesMaterial::getAverageDensityOfIsolation_VolumeFraction();
    
    double totalLength; 
    int totalNumberOfSubWires; 
    double singleWireR;
    double singleWireIsolationR;
    double outerWireIsolationR;
    int totalNumberOfCablesInARICH; 

    vector<ARICHcablesMaterial*> matv;

    //cout<<"xmlarichdata::runARICHcablesMaterial()"<<endl;

    //Merger LV (ID = M)
    cableName = "Merger_LV"; 
    stdID = "M";
    //totalLength = 165.5*100;                      //cm before Mon May 28 17:06:03 JST 2018
    totalNumberOfCablesInARICH = 72.0;
    totalLength = 100.0*totalNumberOfCablesInARICH; //cm Mon May 28 17:11:10 JST 2018 (72 cables/ARICH)
    //totalLength = 40.5;                           //cm -> test value
    totalNumberOfSubWires = 5; 
    singleWireR = 0.6/10.0;                         //cm
    singleWireIsolationR = 0.8/10.0;                //cm
    outerWireIsolationR = 6.5/2.0/10.0;             //cm
    ARICHcablesMaterial *mat_Merger_LV = new ARICHcablesMaterial(cableName.Data(),
								 stdID.Data(),
								 rhoOfCore,
								 rhoOfIsolation,
								 totalLength,
								 totalNumberOfSubWires,
								 singleWireR,
								 singleWireIsolationR, 
								 outerWireIsolationR,
								 totalNumberOfCablesInARICH);
    //mat_Merger_LV->print();
    matv.push_back(mat_Merger_LV);
    
    //FEB LV (ID = F)
    cableName = "FEB_LV"; 
    stdID = "F";
    //totalLength = 165.5*100;                      //cm before Mon May 28 17:06:03 JST 2018
    totalNumberOfCablesInARICH = 72.0;
    totalLength = 100.0*totalNumberOfCablesInARICH; //cm Mon May 28 17:11:10 JST 2018 (72 cables/ARICH)
    //totalLength = 40.5;                           //cm -> test value
    totalNumberOfSubWires = 9; 
    singleWireR = 0.4/10.0;                         //cm
    singleWireIsolationR = 0.7/10.0;                //cm
    outerWireIsolationR = 6.5/2.0/10.0;             //cm
    ARICHcablesMaterial *mat_FEB_LV = new ARICHcablesMaterial(cableName.Data(),
							      stdID.Data(),
							      rhoOfCore,
							      rhoOfIsolation,
							      totalLength,
							      totalNumberOfSubWires,
							      singleWireR,
							      singleWireIsolationR, 
							      outerWireIsolationR,
							      totalNumberOfCablesInARICH);
    //mat_FEB_LV->print();
    matv.push_back(mat_FEB_LV);

    //HV (ID = H)
    cableName = "HV"; 
    stdID = "H";
    //totalLength = 648*100;                        //cm before Mon May 28 17:06:03 JST 2018
    totalNumberOfCablesInARICH = 24.0;
    totalLength = 100.0*totalNumberOfCablesInARICH; //cm Mon May 28 17:11:10 JST 2018 (24 cables/ARICH)
    //totalLength = 70;                             //cm -> test value
    totalNumberOfSubWires = 18; 
    singleWireR = 0.7/2.0/10.0;                     //cm
    singleWireIsolationR = 2.6/2.0/10.0;            //cm
    outerWireIsolationR = 0.0;                      //cm
    ARICHcablesMaterial *mat_HV = new ARICHcablesMaterial(cableName.Data(),
							  stdID.Data(),
							  rhoOfCore,
							  rhoOfIsolation,
							  totalLength,
							  totalNumberOfSubWires,
							  singleWireR,
							  singleWireIsolationR, 
							  outerWireIsolationR,
							  totalNumberOfCablesInARICH);
    //mat_HV->print();
    matv.push_back(mat_HV);

    //BIAS/GUARD (ID = B)
    cableName = "BIAS_GUARD"; 
    stdID = "B";
    //totalLength = 648*100;                        //cm before Mon May 28 17:06:03 JST 2018
    totalNumberOfCablesInARICH = 48*9;
    totalLength = 100.0*totalNumberOfCablesInARICH; //cm Mon May 28 17:11:10 JST 2018 (48*9 cables/ARICH)
    //totalLength = 53.0;                           //cm -> test value
    totalNumberOfSubWires = 6; 
    singleWireR = 0.5/2.0/10.0;                     //cm
    singleWireIsolationR = 1.3/2.0/10.0;            //cm
    outerWireIsolationR = 0.0;                      //cm
    ARICHcablesMaterial *mat_BIAS_GUARD = new ARICHcablesMaterial(cableName.Data(),
								  stdID.Data(),
								  rhoOfCore,
								  rhoOfIsolation,
								  totalLength,
								  totalNumberOfSubWires,
								  singleWireR,
								  singleWireIsolationR, 
								  outerWireIsolationR,
								  totalNumberOfCablesInARICH);
    //mat_BIAS_GUARD->print();
    matv.push_back(mat_BIAS_GUARD);

    //CAT7 (ID = C)
    cableName = "CAT7"; 
    stdID = "C";
    //totalLength = 288*100;                        //cm before Mon May 28 17:06:03 JST 2018
    totalNumberOfCablesInARICH = 144;
    totalLength = 100.0*totalNumberOfCablesInARICH; //cm Mon May 28 17:11:10 JST 2018 (144 = 72*2 cables/ARICH)
    //totalLength = 200;                            //cm -> test value
    totalNumberOfSubWires = 1; 
    singleWireR = 1.0/10.0;                         //cm
    singleWireIsolationR = 2.0/10.0;                //cm
    outerWireIsolationR = 0.0;                      //cm
    ARICHcablesMaterial *mat_CAT7 = new ARICHcablesMaterial(cableName.Data(),
							    stdID.Data(),
							    rhoOfCore,
							    rhoOfIsolation,
							    totalLength,
							    totalNumberOfSubWires,
							    singleWireR,
							    singleWireIsolationR, 
							    outerWireIsolationR,
							    totalNumberOfCablesInARICH);
    //mat_CAT7->print();
    matv.push_back(mat_CAT7);    

    //Optical (ID = O)
    cableName = "Optical"; 
    stdID = "O";
    //totalLength = 72*100;                         //cm before Mon May 28 17:06:03 JST 2018
    totalNumberOfCablesInARICH = 72;
    totalLength = 100.0*totalNumberOfCablesInARICH; //cm Mon May 28 17:11:10 JST 2018 (72 cables/ARICH)
    //totalLength = 310;                            //cm -> test value
    totalNumberOfSubWires = 2; 
    singleWireR = 0.0/10.0;                         //cm
    singleWireIsolationR = 2.4/2.0/10.0;            //cm
    outerWireIsolationR = 0.0;                      //cm
    ARICHcablesMaterial *mat_Optical = new ARICHcablesMaterial(cableName.Data(),
							       stdID.Data(),
							       rhoOfCore,
							       rhoOfIsolation,
							       totalLength,
							       totalNumberOfSubWires,
							       singleWireR,
							       singleWireIsolationR, 
							       outerWireIsolationR,
							       totalNumberOfCablesInARICH);
    //mat_Optical->print();
    matv.push_back(mat_Optical);    
    
    //LV distribution board to FEB cable
    cableName = "LV_distBoardFEB"; 
    stdID = "L";
    //totalLength = 4200;                        //cm before Mon May 28 17:06:03 JST 2018
    totalNumberOfCablesInARICH = 420;
    totalLength = 10*totalNumberOfCablesInARICH; //cm Mon May 28 17:11:10 JST 2018 (420 cables/ARICH)
    //totalLength = 10;                          //cm -> test value
    totalNumberOfSubWires = 5; 
    singleWireR = 0.5/2.0/10.0;                  //cm
    singleWireIsolationR = 1.0/2.0/10.0;         //cm
    outerWireIsolationR = 0.0;                   //cm
    ARICHcablesMaterial *mat_LV_distribution_board_to_FEB_cable = new ARICHcablesMaterial(cableName.Data(),
											  stdID.Data(),
											  rhoOfCore,
											  rhoOfIsolation,
											  totalLength,
											  totalNumberOfSubWires,
											  singleWireR,
											  singleWireIsolationR, 
											  outerWireIsolationR,
											  totalNumberOfCablesInARICH);
    //mat_LV_distribution_board_to_FEB_cable->print();
    matv.push_back(mat_LV_distribution_board_to_FEB_cable);    

    //Data (ID = D)
    cableName = "Data"; 
    stdID = "D";
    //totalLength = 8400;                        //cm before Mon May 28 17:06:03 JST 2018
    totalNumberOfCablesInARICH = 420;
    totalLength = 20*totalNumberOfCablesInARICH; //cm Mon May 28 17:11:10 JST 2018 (420 cables/ARICH)
    //totalLength = 19;                          //cm
    totalNumberOfSubWires = 39; 
    singleWireR = 0.28/2.0/10.0;                 //cm
    singleWireIsolationR = 0.5/2.0/10.0;         //cm
    outerWireIsolationR = 0.0;                   //cm
    ARICHcablesMaterial *mat_Data = new ARICHcablesMaterial(cableName.Data(),
							    stdID.Data(),
							    rhoOfCore,
							    rhoOfIsolation,
							    totalLength,
							    totalNumberOfSubWires,
							    singleWireR,
							    singleWireIsolationR, 
							    outerWireIsolationR,
							    totalNumberOfCablesInARICH);
    //mat_Data->print();
    matv.push_back(mat_Data);    

    //Cable holder
    double cableHolderMass = ARICHcablesMaterial::getCableHolderMass(rhoOfCore);

    double totalWeightOfCore = 0.0;
    double totalWeightOfIsolation = 0.0;

    for (unsigned i=0; i<matv.size(); i++){
      totalWeightOfCore = totalWeightOfCore + matv.at(i)->getTotalWeightOfCore();
      totalWeightOfIsolation = totalWeightOfIsolation + matv.at(i)->getTotalWeightOfIsolation();
    }
    
    cout<<"totalWeightOfCore            = "<<totalWeightOfCore<<endl
	<<"totalWeightOfIsolation       = "<<totalWeightOfIsolation<<endl;
    double totalWOfCore = totalWeightOfCore + cableHolderMass + totalWeightOfCore*0.3;
    double totalWOfIsol = totalWeightOfIsolation + totalWeightOfIsolation*0.3;
    cout<<"totalWeightOfCore + cableHolderMass + 30% = "<<totalWOfCore<<endl
	<<"totalWeightOfIsolation + 30%              = "<<totalWOfIsol<<endl;

    double cablesEnvelopOuterRadius = 1136.0/10.0;
    double cablesEnvelopInnerRadius = 435.0/10.0;
    double cablesEnvelopThickness = 3.0/10.0;
    double cablesEnvelopVolume = TMath::Pi()*(cablesEnvelopOuterRadius*cablesEnvelopOuterRadius - cablesEnvelopInnerRadius*cablesEnvelopInnerRadius)*cablesEnvelopThickness;
    double cablesEnvelopTotalWeight = (totalWOfCore + cableHolderMass + totalWOfIsol)*1000.0; // g
    double cablesEnvelopDensity = cablesEnvelopTotalWeight/cablesEnvelopVolume;

    cout<<"--------------------------------"<<endl;
    cout<<"cablesEnvelopOuterRadius = "<<cablesEnvelopOuterRadius<<" cm"<<endl
	<<"cablesEnvelopInnerRadius = "<<cablesEnvelopInnerRadius<<" cm"<<endl
	<<"cablesEnvelopThickness   = "<<cablesEnvelopThickness<<" cm"<<endl
	<<"cablesEnvelopVolume      = "<<cablesEnvelopVolume<<" cm^3"<<endl
	<<"cablesEnvelopTotalWeight = "<<cablesEnvelopTotalWeight<<" g"<<endl
	<<"cablesEnvelopDensity     = "<<cablesEnvelopDensity<<" g/cm^3"<<endl;
    cout<<"--------------------------------"<<endl;

    ARICHcablesMaterial::printElementMassFractions( totalWOfIsol, totalWOfCore);

    //for (unsigned i=0; i<matv.size(); i++)
    //matv.at(i)->print();

    //totalLength,
    //singleWireR,
    //singleWireIsolationR, 
    //outerWireIsolationR);

    //xmlarichdata::ARICHcablesMaterial *mat_test = new xmlarichdata::ARICHcablesMaterial();
    //mat_test->print();
    
    //double rhoOfCoreCu = 8.92;//g/cm^3 
    //double rhoOfIsolation,
    //mat_test->getAverageDensityOfIsolation_VolumeFraction();
    //mat_test->getAverageDensityOfCore_MassFraction();

    return 0;
  }
  
}//namespace xmlarichdata{

#ifdef RUNARICHCABLESMATERIAL_MAIN
# ifndef __CINT__
  int main(int argc, char *argv[]){
    if(argc == 1){
      xmlarichdata::runARICHcablesMaterial();
      return 0;
    }
    xmlarichdata::runARICHcablesMaterial();
    return 0;
  }
# endif //ifndef __CINT__
#endif //ifdef RUNARICHCABLESMATERIAL_MAIN
