/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Tue Apr 3 17:30:57 2018 +0200                                        *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
#ifdef __CLING__
#include "refractiveIndexSilicaAerogel.C"
#endif

//root
#include <TROOT.h>
#include <TString.h>
#include <TMath.h>

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{

  //#if defined(__CLING__)
  //#include "refractiveIndexSilicaAerogel.C"
  //void silicaAerogel_density_refractiveIndex();
  //#endif

  //Nuclear Instruments and Methods in Physics Research A 668 (2012) 64–70
  //Hydrophobic silica aerogel production at KEK
  //k = 0.251 cm^3/g - ethanol
  //k = 0.283 cm^3/g - methanol
  //k = 0.300 cm^3/g - DMF
  //n(lam) = 1 + k(lam)*rho(cm^3/g)
  Double_t get_silicaAerogel_density_from_refractiveIndex( Double_t n, Double_t k = 0.283){
    if(n>1.0){
      return (n - 1.0)/k;
    }
    return -999.0;
  }
  
  //den is density in g/cm^3
  Double_t get_silicaAerogel_refractiveIndex_from_density( Double_t den, Double_t k = 0.283){
    if(den>0.0){
      return 1 + k*den;
    }
    return -999.0;
  }
  
  void silicaAerogel_density_refractiveIndex(){
    TString aerogelType;
    Double_t lam;  
    Double_t n;
    Double_t rho;
    aerogelType = "A";
    lam = 405.0;
    n = refractiveIndexSilicaAerogel(aerogelType,lam);
    rho = get_silicaAerogel_density_from_refractiveIndex(n);
    cout<<n<<"  "<<rho<<" g/cm^3 (Type A)"<<endl;
    aerogelType = "B";
    lam = 405.0;
    n = refractiveIndexSilicaAerogel(aerogelType,lam);
    rho = get_silicaAerogel_density_from_refractiveIndex(n);
    cout<<n<<"  "<<rho<<" g/cm^3 (Type B)"<<endl;
  }

}//namespace xmlarichdata{
