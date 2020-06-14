/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Oct 15 16:09:59 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TKey.h>
#include <TClass.h>
#include <TMultiGraph.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>

using namespace std;

void listOfMaterials(TString hname = "ARICHMaterialScan_Mon_Jun_4_13-41-16_JST_2018.root"){

  cout<<"hname        = "<<hname<<endl;

  TH2D *grColl[1000];

  TString th2dTitle;
  
  const char *fname = hname;
  TKey *key;
  TFile *f = TFile::Open(fname, "READ");
  if (!f || f->IsZombie()) {
    cout << "Unable to open " << fname << " for reading..." <<endl;
    return;
  }
  f->cd("Planar");
  f->ls();
}
