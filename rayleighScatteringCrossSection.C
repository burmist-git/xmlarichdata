/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Nov 27 22:23:08 2017 +0100                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "libxmlarichdata.h"
#endif

//root
#include <TROOT.h>
#include <TMath.h>

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{

//                                           nm                   nm
Double_t rayleighScatteringCrossSection(Double_t d = 40, Double_t lam = 400, Double_t n = 1.0463){
  if(lam<=0.0 || d < 0.0 || n <= 1.0){
    //assert(0);
    return 0.0;
  }
  return 2*TMath::Power(TMath::Pi(),5.0)/3.0*TMath::Power(d,6.0)/TMath::Power(lam,4.0)*TMath::Power((n*n - 1.0)/(n*n + 2.0),2.0);
}
}//namespace xmlarichdata{
