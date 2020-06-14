#pragma once

//My
#include "anaSCTbase.h"

//basf2
#include <arich/utility/ARICHChannelHist.h>

//root
#include <TROOT.h>

class TChain;
class TCanvas;
class TFile;
class TTree;
class TString;
class TBranch;

class anaSCT: public anaSCTbase {
public:
  anaSCT(TString fileList) : anaSCTbase(fileList)
  {
  }

  anaSCT(TString file, Int_t key) : anaSCTbase(file, key)
  {
  }

  void Loop(TString histOut, double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec, double dTimeWindow, double tMin, double tMax);
  void plot(TCanvas *cc, Belle2::ARICHChannelHist *h2_asic);
  
};
