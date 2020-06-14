/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sat Oct 13 22:54:08 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
#include "cellStr.h"

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

//root
#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TVector3.h>
#include <TStyle.h>
#include <TPad.h>
#include <TString.h>
#include <TGraph.h>
#include <TAxis.h>

using namespace xmlarichdata;

namespace xmlarichdata{

  std::vector<cellStr> cellStrTest(){
    std::vector<cellStr> tessellatedSolid;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    for( k = 0; k<11; k++){
      cellStr apexs;
      for( i = 0; i<3; i++){
	std::vector<double> apex;
	for( j = 0; j<3; j++){
	  apex.push_back(j);
	}
	apexs.apexs.push_back(apex);
      }
      //apexs.printInfo();
      tessellatedSolid.push_back(apexs);
    }
    return tessellatedSolid;
  }
  
}
