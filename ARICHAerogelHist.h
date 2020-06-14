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

class ARICHAerogelHist: public TH2Poly {
 public:
  
  ARICHAerogelHist(const char* name, const char* title);
  ~ARICHAerogelHist();
  void DrawHisto( TString opt, TString outDirName);
  Int_t GetBinIDFromRingColumn( Int_t ring, Int_t column);
  
 private:

  void SetInitialParametersByDefault();

  void SetUpVerticesMap();

  void dumpVerticesMap();

  void makeRotation( Double_t xold, Double_t yold, Double_t &xnew, Double_t &ynew, Double_t phi);

  //Number of tiles per ring.
  std::vector<Int_t> m_nTiles;
  //Minimum radius of aerogel ring
  std::vector<Double_t> m_tileRmin;
  //Maximum radius of aerogel ring
  std::vector<Double_t> m_tileRmax;
  //Center radius of aerogel ring
  std::vector<Double_t> m_tileRcenter;
  //Angle opening (phi) of the aerogel tile measured between two rays (0.0,0.0 : and centre of the ring from ).
  std::vector<Double_t> m_tileDeltaPhiCenter;
  //Angle opening (phi) of the air gap between aerogel tiles. Measured between ray (0.0,0.0 : and centre of the ring from left/right).
  std::vector<Double_t> m_aerogelAriGapDeltaPhiCenter;
  //Verbose level
  Int_t m_verboseLevel;
  //Number of circular points 
  Int_t m_nCircularPoints;
  //Distance between aerogel tiles
  Double_t m_aerogelTileGap;

  ////Aerogel vertices map Int_t -> aerogel ring number
  std::map<Int_t,std::vector<TVector2>> m_verticesMap;

  TString m_histName;
  TString m_histTitle;

};
