/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Thu May 10 16:07:15 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "ARICHcablesMaterial.h"
#include "libxmlarichdata.h"

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

  ARICHcablesMaterial::ARICHcablesMaterial(){
    
    m_rhoOfCore = 0.0;
    m_rhoOfIsolation = 0.0;
    m_cableName = "";
    m_stdID = "";
    m_totalLength = 0.0;
    m_singleWireR = 0.0;
    m_singleWireIsolationR = 0.0;
    m_outerWireIsolationR = 0.0;
    m_totalWeightOfCore = 0.0;
    m_totalWeightOfIsolation = 0.0;
    m_totalWeight = 0.0;
    m_totNumCabl = 0;
    
  }
  
  ARICHcablesMaterial::ARICHcablesMaterial(const char* cableName, 
					   const char* stdID, 
					   double rhoOfCore, 
					   double rhoOfIsolation,
					   double totalLength,
					   int totalNumberOfSubWires,
					   double singleWireR,
					   double singleWireIsolationR, 
					   double outerWireIsolationR,
					   int totNumCabl){
    
    m_cableName = cableName;
    m_stdID = stdID;
    m_rhoOfCore = rhoOfCore;
    m_rhoOfIsolation = rhoOfIsolation;    
    m_totalLength = totalLength;
    m_totalNumberOfSubWires = totalNumberOfSubWires;
    m_singleWireR = singleWireR;
    m_singleWireIsolationR = singleWireIsolationR;
    m_outerWireIsolationR = outerWireIsolationR;

    m_totalWeightOfCore = calculateTotalWeightOfCore();
    m_totalWeightOfIsolation = calculateTotalWeightOfIsolation();

    m_totalWeight = m_totalWeightOfCore + m_totalWeightOfIsolation;
    
    m_totNumCabl = totNumCabl;

  }
  
  ARICHcablesMaterial::~ARICHcablesMaterial(){
  }

  double ARICHcablesMaterial::calculateTotalWeightOfCore(){

    double totalWeightOfCore = m_totalLength*m_totalNumberOfSubWires*TMath::Pi()*m_singleWireR*m_singleWireR*m_rhoOfCore/1000.0;
    return totalWeightOfCore;

  }

  double ARICHcablesMaterial::calculateTotalWeightOfIsolation(){

    double weightOfIsolation = m_totalLength*m_totalNumberOfSubWires*TMath::Pi()*(m_singleWireIsolationR*m_singleWireIsolationR - m_singleWireR*m_singleWireR)*m_rhoOfIsolation/1000.0;
    //We assume that the thickness of the wall of the outer coverage is about 1 mm
    double weightOfOuterWireIsolation = 0.0;
    if(m_outerWireIsolationR > 0.1)
      weightOfOuterWireIsolation = m_totalLength*TMath::Pi()*(m_outerWireIsolationR*m_outerWireIsolationR - (m_outerWireIsolationR - 0.1)*(m_outerWireIsolationR - 0.1))*m_rhoOfIsolation/1000.0;
    return (weightOfIsolation + weightOfOuterWireIsolation);

  }
  
  double ARICHcablesMaterial::getCableHolderMass(double rho){

    double rmin = 44.0;          //cm
    double rmax = 110.0;         //cm
    double thickness = 0.2/10.0; //cm
    double fillFactor = 0.1;
    double cableHolderMass = TMath::Pi()*(rmax*rmax - rmin*rmin)*thickness*fillFactor*rho/1000.0;
    cout<<"cableHolderMass              = "<<cableHolderMass<<endl;
    return cableHolderMass;

  }

  void ARICHcablesMaterial::print(){
    cout<<"-----------------------------------"<<endl;
    cout<<"m_cableName              = "<<m_cableName<<endl
	<<"m_stdID                  = "<<m_stdID<<endl
	<<"m_rhoOfCore              = "<<m_rhoOfCore<<endl
	<<"m_rhoOfIsolation         = "<<m_rhoOfIsolation<<endl
	<<"m_totalLength            = "<<m_totalLength<<endl
    	<<"m_totalNumberOfSubWires  = "<<m_totalNumberOfSubWires<<endl;
    cout<<"m_singleWireR            = "<<m_singleWireR<<endl
	<<"m_singleWireIsolationR   = "<<m_singleWireIsolationR<<endl
	<<"m_outerWireIsolationR    = "<<m_outerWireIsolationR<<endl
	<<"m_totalWeightOfCore      = "<<m_totalWeightOfCore<<endl
	<<"m_totalWeightOfIsolation = "<<m_totalWeightOfIsolation<<endl
	<<"m_totalWeight            = "<<m_totalWeight<<endl
	<<"m_totNumCabl             = "<<m_totNumCabl<<endl;
    cout<<"-----------------------------------"<<endl;
  }

  double ARICHcablesMaterial::getAverageDensityOfIsolation_VolumeFraction(){
    double rho_Pol = 0.97; // g/cm^3 Polyethylene
    double rho_Rub = 0.93; // g/cm^3 Rubber
    double rho_PVC = 1.45; // g/cm^3 Polyvinyl chloride
    double volumeFraction_Pol = 1.0/3.0;
    double volumeFraction_Rub = 1.0/3.0;
    double volumeFraction_PVC = 1.0/3.0;
    double rho_tot = volumeFraction_Pol*rho_Pol + volumeFraction_Rub*rho_Rub + volumeFraction_PVC*rho_PVC;
    cout<<"Density of isolation (volume fraction) rho_tot = "<<rho_tot<<endl;
    return rho_tot;
  }

  double ARICHcablesMaterial::getAverageDensityOfCore_MassFraction(){
    double rho_Al = 2.7;  // g/cm^3
    double rho_Cu = 8.96; // g/cm^3
    double rho_Fe = 7.87; // g/cm^3
    double massFraction_Al = 0.1;
    double massFraction_Cu = 0.8;
    double massFraction_Fe = 0.1;
    double rho_tot = 1.0/(massFraction_Al/rho_Al + massFraction_Cu/rho_Cu + massFraction_Fe/rho_Fe);
    cout<<"Density of core (mass fraction) rho_tot        = "<<rho_tot<<endl;
    return rho_tot;
  }

  void ARICHcablesMaterial::printElementMassFractions( double totalWeightOfIsolation, double totalWeightOfCore){
    double totm = totalWeightOfIsolation + totalWeightOfCore;
    double isol_fr = 0.0;
    double core_fr = 0.0;
    if(totm>0.0)
      isol_fr = totalWeightOfIsolation/totm;
    else
      assert(0);
    if(totm>0.0)
      core_fr = totalWeightOfCore/totm;
    else
      assert(0);
    double H_fr = 0.095*isol_fr;
    double C_fr = 0.66*isol_fr;
    double Cl_fr = 0.245*isol_fr;
    double Al_fr = 0.1*core_fr;
    double Cu_fr = 0.8*core_fr;
    double Fe_fr = 0.1*core_fr;
    cout<<"H_fr  = "<<H_fr<<endl
	<<"C_fr  = "<<C_fr<<endl
	<<"Cl_fr = "<<Cl_fr<<endl
	<<"Al_fr = "<<Al_fr<<endl
	<<"Cu_fr = "<<Cu_fr<<endl
	<<"Fe_fr = "<<Fe_fr<<endl;
    cout<<"Sum   = "<<H_fr + C_fr + Cl_fr + Al_fr + Cu_fr + Fe_fr<<endl;
  }
  
} //namespace xmlarichdata{
