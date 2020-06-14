/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Nov 27 22:23:08 2017 +0100                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/
//my
#include "libxmlarichdata.h"

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

  Double_t refractiveIndexSilicaAerogel( TString type = "A", Double_t lam = 400){
    Double_t a0 = 0.0;
    Double_t lam0 = 0.0;
    if(type == "A"){
      //Not modified data before : Tue Jun  5 19:15:56 JST 2018
      //Type A (upstream aerogel)   Aerogel1
      //a0 = 0.0904;
      //lam0 = 86;
      //Modified data to much 1.045 (for type A) and 1.055 (for type B)
      //Date : Tue Jun  5 19:18:13 JST 2018
      a0 = 0.0877337;
      lam0 = 87.1909;
    }
    else if(type == "B"){
      //Not modified data before : Tue Jun  5 19:15:56 JST 2018
      //Type B (downstream aerogel) Aerogel2
      //a0 = 0.1087;
      //lam0 = 85;
      //Modified data to much 1.045 (for type A) and 1.055 (for type B)
      //Date : Tue Jun  5 19:18:13 JST 2018
      a0 = 0.108061;
      lam0 = 84.7807;
    }
    else{
      cout<<" ERROR -> Aerogel type is not defined "<<endl
	  <<"          Aerogel type : "<<type<<endl;
      assert(0.0);
    }
    if(lam<=lam0){
      cout<<" ERROR -> lam <= lam0"<<endl
	  <<"          lam  = "<<lam<<endl
	  <<"          lam0 = "<<lam0<<endl;
      assert(0.0);
    }
    return TMath::Sqrt(1 + (a0*lam*lam)/(lam*lam - lam0*lam0));
  }
  
  void refractiveIndexSilicaAerogelPrintTestData(){
    TString aerogelType;
    Double_t lam;  
    //A
    //405.0 1.0463 0.2 0.0001
    //543.5 1.0453 0.2 0.0001
    //633.0 1.0451 0.2 0.0001
                                                    
    cout<<"/**************************************************************"<<endl;
    aerogelType = "A";
    lam = 405.0;
    cout<<"* Type A (upstream aerogel)   @ 405.0 nm --> "<<refractiveIndexSilicaAerogel(aerogelType,lam)<<"   "<<1.0450<<"  *"<<endl;
    lam = 543.5;
    cout<<"* Type A (upstream aerogel)   @ 543.5 nm --> "<<refractiveIndexSilicaAerogel(aerogelType,lam)<<"   "<<1.0440<<"  *"<<endl;
    lam = 633.0;
    cout<<"* Type A (upstream aerogel)   @ 633.0 nm --> "<<refractiveIndexSilicaAerogel(aerogelType,lam)<<"   "<<1.0438<<" *"<<endl;
    //B
    //405.0 1.0553 0.2 0.0001
    //543.5 1.0542 0.2 0.0001
    //633.0 1.0539 0.2 0.0001
    aerogelType = "B";
    lam = 405.0;
    cout<<"* Type B (downstream aerogel) @ 405.0 nm --> "<<refractiveIndexSilicaAerogel(aerogelType,lam)<<"   "<<1.0550<<"  *"<<endl;
    lam = 543.5;
    cout<<"* Type B (downstream aerogel) @ 543.5 nm --> "<<refractiveIndexSilicaAerogel(aerogelType,lam)<<"   "<<1.0539<<" *"<<endl;
    lam = 633.0;
    cout<<"* Type B (downstream aerogel) @ 633.0 nm --> "<<refractiveIndexSilicaAerogel(aerogelType,lam)<<"   "<<1.0536<<" *"<<endl;
    cout<<"***************************************************************"<<endl;
    lam = 420.0;
    cout<<"* Type A (upstream aerogel)   @ 420.0 nm --> "<<refractiveIndexSilicaAerogel("A",lam)<<"          *"<<endl;
    lam = 420.0;
    cout<<"* Type B (downstream aerogel) @ 420.0 nm --> "<<refractiveIndexSilicaAerogel("B",lam)<<"          *"<<endl;
    cout<<"***************************************************************"<<endl;
    lam = 400.0;
    cout<<"* Type A (upstream aerogel)   @ 400.0 nm --> "<<refractiveIndexSilicaAerogel("A",lam)<<"          *"<<endl;
    lam = 400.0;
    cout<<"* Type B (downstream aerogel) @ 400.0 nm --> "<<refractiveIndexSilicaAerogel("B",lam)<<"          *"<<endl;
    cout<<"***************************************************************"<<endl;
    lam = 500.0;
    cout<<"* Type A (upstream aerogel)   @ 500.0 nm --> "<<refractiveIndexSilicaAerogel("A",lam)<<"          *"<<endl;
    lam = 500.0;
    cout<<"* Type B (downstream aerogel) @ 500.0 nm --> "<<refractiveIndexSilicaAerogel("B",lam)<<"          *"<<endl;
    cout<<"***************************************************************"<<endl;
    cout<<"* Type A (upstream aerogel)   Aerogel1                        *"<<endl;
    cout<<"* Type B (downstream aerogel) Aerogel2                        *"<<endl;
    cout<<"**************************************************************/"<<endl;

  }

}//namespace xmlarichdata{
