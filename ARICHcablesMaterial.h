#pragma once

//root
#include <TObject.h>
#include <TH2Poly.h>
#include <TGraph.h>
#include <TVector2.h>

//c, c++
#include <string>
#include <vector>
#include <map>

struct mergerStruct;

namespace xmlarichdata{

  class ARICHcablesMaterial  {
    
  public:
    
    ARICHcablesMaterial();  
    ARICHcablesMaterial(const char* cableName, const char* stdID, double rhoOfCore, double rhoOfIsolation, double totalLength, int totalNumberOfSubWires, double singleWireR, double singleWireIsolationR, double outerWireIsolationR, int m_totNumCabl);
    ~ARICHcablesMaterial();
    
    void print();

    static double getAverageDensityOfIsolation_VolumeFraction();
    static double getAverageDensityOfCore_MassFraction();
    static double getCableHolderMass(double rho);

    double getTotalWeightOfCore() const { return m_totalWeightOfCore;}
    double getTotalWeightOfIsolation() const { return m_totalWeightOfIsolation;}

    static void printElementMassFractions( double totalWeightOfIsolation, double totalWeightOfCore);

  private:
    
    double m_rhoOfCore;
    double m_rhoOfIsolation;
    double m_totalLength;
    int m_totalNumberOfSubWires;
    double m_singleWireR;
    double m_singleWireIsolationR;
    double m_outerWireIsolationR;
    double m_totalWeightOfCore;
    double m_totalWeightOfIsolation;
    double m_totalWeight;
    int m_totNumCabl;
    
    TString m_cableName;
    TString m_stdID;

    double calculateTotalWeightOfCore();
    double calculateTotalWeightOfIsolation();
    
  };
  
}//namespace xmlarichdata{
