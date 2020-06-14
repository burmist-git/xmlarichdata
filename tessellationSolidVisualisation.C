/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Nov 11 21:12:08 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

#if !defined(__CLING__)
//my
#include "libxmlarichdata.h"
#else 
#include "saveTessellatedSolidVerticesToXML.C"
#endif //#if !defined(__CLING__)
#include "tessellatedSolidStr.h"

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TList.h>
#include <TMath.h>
#include <TPolyLine3D.h>
#include <TView.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TH1D.h>

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{
  
  vector<TPolyLine3D*> tessellationSolidVisualisation(TString inDatFile = "tessellatedSolidVertices.dat", double x0 = 0.0, double y0 = 0.0, double z0 = 0.0, double lineWidth = 3.0){
    tessellatedSolidStr tessellatedSolid = readTessellatedSolidVerticesToDATfile(inDatFile);
    tessellatedSolid.printInfo();
    double x[tessellatedSolid.cellGeo.nPointsPerPosition];
    double y[tessellatedSolid.cellGeo.nPointsPerPosition];
    double z[tessellatedSolid.cellGeo.nPointsPerPosition];
    vector<TPolyLine3D*> trVector;
    TH1D *h1_x = new TH1D("h1_x","x",20000, -10000,10000);
    TH1D *h1_y = new TH1D("h1_y","y",20000, -10000,10000);
    TH1D *h1_z = new TH1D("h1_z","z",20000, -10000,10000);
    TH2D *h2_y_vs_x = new TH2D("h2_y_vs_x","y vs x", 300, -150, 150, 300, -150, 150);
    TGraph *gr = new TGraph();
    TCanvas *c1 = new TCanvas( "c1", inDatFile.Data(), 10, 10, 700, 500);
    c1->SetTitle(inDatFile.Data());
    // creating a view
    TView *view = TView::CreateView(1);
    view->SetRange(-150,-150,-150,150,150,150);
    for( unsigned int i = 0; i < tessellatedSolid.posV1[0].size(); i++){
      x[0] = tessellatedSolid.posV1[0][i] - x0;
      x[1] = tessellatedSolid.posV2[0][i] - x0;
      x[2] = tessellatedSolid.posV3[0][i] - x0;
      y[0] = tessellatedSolid.posV1[1][i] - y0;
      y[1] = tessellatedSolid.posV2[1][i] - y0;
      y[2] = tessellatedSolid.posV3[1][i] - y0;
      z[0] = tessellatedSolid.posV1[2][i] - z0;
      z[1] = tessellatedSolid.posV2[2][i] - z0;
      z[2] = tessellatedSolid.posV3[2][i] - z0;
      TPolyLine3D *tr = buildTriangle( x, y, z, lineWidth);
      trVector.push_back(tr);
      tr->Draw();
      for(int j = 0;j<3;j++){
	h1_x->Fill(x[j]);
	h1_y->Fill(y[j]);
	h1_z->Fill(z[j]);
	h2_y_vs_x->Fill(x[j],y[j]);
	gr->SetPoint(gr->GetN(),x[j],y[j]);
      }
    }
    TCanvas *c2 = new TCanvas("c2",inDatFile.Data(),20,20,700,500);
    c2->SetTitle(inDatFile.Data());
    c2->Divide(3,1);
    c2->cd(1);
    h1_x->Draw();
    c2->cd(2);
    h1_y->Draw();
    c2->cd(3);
    h1_z->Draw();
    TCanvas *c3 = new TCanvas("c3",inDatFile.Data(),30,30,700,500);
    c3->SetTitle(inDatFile.Data());
    h2_y_vs_x->Draw();
    TCanvas *c4 = new TCanvas("c4",inDatFile.Data(),40,40,700,500);
    c4->SetTitle(inDatFile.Data());
    gr->Draw("AP");
    return trVector;
  }

  TPolyLine3D *buildTriangle( double *x, double *y, double *z, double lineWidth){
    TPolyLine3D *tr = new TPolyLine3D(3);
    for(Int_t i = 0;i<3;i++)
      tr->SetPoint(i, x[i], y[i], z[i]);
    tr->SetPoint(3, x[0], y[0], z[0]);
    tr->SetLineWidth(lineWidth);
    tr->SetLineColor(kBlack);
    return tr;
  }
  
}//namespace xmlarichdata{
