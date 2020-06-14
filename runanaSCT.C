/***********************************************************************
* Copyright(C) 2018 - LBS - (Single person developer.)                 *
* Thu Oct  4 09:55:31 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "ARICHmappingCopperMergerFeb.h"
#include "libxmlarichdata.h"
#include "anaSCTbase.h"
#include "anaSCT.h"
#else 
//my
#include "ARICHmappingCopperMergerFeb.C"
#include "anaSCTbase.C"
#include "anaSCT.C"
#endif //#if !defined(__CLING__)

//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{

  //Int_t runanaSCT(int argc, char *argv[]){
  Int_t runanaSCT(Int_t executionIDnumber, TString rootFilesList, TString outRootFileF, double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec, double dTimeWindow, double tMin, double tMax){
    
    cout<<"--> Parameter calculation from the WF <--"<<endl
	<<"rootFilesList : "<<rootFilesList<<endl
	<<"outRootFileF  : "<<outRootFileF<<endl;
    anaSCT a(rootFilesList);
    a.Loop(outRootFileF, d_year, d_month, d_day, d_hour, d_min, d_sec, dTimeWindow, tMin, tMax);
        
    /*
    if(argc == 4 && atoi(argv[1])==0){
      TString rootFilesList = argv[2];
      TString outRootFileF = argv[3];
      cout<<"--> Parameter calculation from the WF <--"<<endl
	  <<"rootFilesList : "<<rootFilesList<<endl
	  <<"outRootFileF  : "<<outRootFileF<<endl;
      anaSCT a(rootFilesList);
      a.Loop(outRootFileF);
    }
    else if(argc == 4 && atoi(argv[1])==1){
      TString inRootFiles = argv[2];
      TString outRootFileF = argv[3];
      cout<<"--> Parameter calculation from the WF <--"<<endl
	  <<"inRootFiles : "<<inRootFiles<<endl
	  <<"outRootFileF  : "<<outRootFileF<<endl;
      anaSCT a( inRootFiles, atoi(argv[1]));
      a.Loop(outRootFileF);
    }
    else if(argc == 4 && atoi(argv[1])==2){
      // if else
    }
    else{
      cout<<" --> ERROR in input arguments "<<endl
	  <<" runID [1] = 0 (execution ID number)"<<endl
	  <<"       [2] - file with list of the root files"<<endl
	  <<"       [3] - name of root file with histograms"<<endl;
      cout<<" runID [1] = 1 (execution ID number)"<<endl
	  <<"       [2] - in root files"<<endl
	  <<"       [3] - name of root file with histograms"<<endl;
    }
    */
    return 0;
  }
  
}//namespace xmlarichdata{
