/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Mon Apr 30 17:21:45 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TLine.h>
#include <TMath.h>

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
using namespace xmlarichdata;

namespace xmlarichdata{
  
  void coolingSizes() {
    
    int nSectors = 6;

    double diameterTube = 3.2*2.0;
    double rmin = 705.0;
    double lTube = 172;
    double rmax = rmin + lTube;
    double lTube_mid = 1136 - 10 - rmax;
    double lTube_max = 1136 - 10 - rmin;
    double dl_rmin = 10;
    double l_rmin = 2 * TMath::Pi() * rmin / nSectors - dl_rmin * 2.0;
    double dPhi = TMath::ATan(dl_rmin/l_rmin);
    double dl_rmax = dl_rmin + lTube * TMath::Tan(dPhi);
    double hapd_l = 70.0;
    //double hapd_dPhi = TMath::ATan(hapd_l/rmax);
    double l_rmax = 2 * TMath::Pi() * rmax / nSectors - dl_rmax * 2.0 - hapd_l;
    double rPos_Tube = rmin + ( rmax - rmin ) / 2.0;
    double rPos_Tube_mid = rmax + lTube_mid / 2.0 + 5;
    double rPos_Tube_max = rmin + lTube_max / 2.0 + 5;
    double phiPos_Tube = dPhi - TMath::ATan(diameterTube/l_rmin);
    double phiPos_Torus_min = 2*TMath::Pi()/nSectors/2.0;
    double phiPos_Torus_max = l_rmax/rmax/2.0 + dPhi;

    double phiPos_Tube_mid = phiPos_Torus_max + l_rmax/rmax/2.0 + diameterTube / rmax;
    double phiPos_Tube_max = phiPos_Torus_min + l_rmin/rmin/2.0 + diameterTube / rmin;

    double posRotAngle_torus_min = 0;
    double posRotAngle_torus_max = 0;

    double posRotAngle_tube = phiPos_Tube;
    double posRotAngle_tube_mid = phiPos_Tube_mid;
    double posRotAngle_tube_max = phiPos_Tube_max;

    int i = 0;

    const int nn = 30; 
    int coolingGeometryID[nn] = { 2, 2, 1, 1, 1};
    double coolingL[nn] = {l_rmin, l_rmax, lTube, lTube_mid, lTube_max};
    double coolingPosPhi[nn] = {phiPos_Torus_min, phiPos_Torus_max, phiPos_Tube, phiPos_Tube_mid, phiPos_Tube_max};
    double coolingPosR[nn] = { rmin, rmax, rPos_Tube, rPos_Tube_mid, rPos_Tube_max};
    double coolinRotationAngle[nn] = { posRotAngle_torus_min, posRotAngle_torus_max, posRotAngle_tube, posRotAngle_tube_mid, posRotAngle_tube_max};

    cout<<endl<<"coolingGeometryID"<<endl;
    for(i = 0;i<5;i++){
      coolingGeometryID[i + 5] = coolingGeometryID[i];
      coolingGeometryID[i + 10] = coolingGeometryID[i];
      coolingGeometryID[i + 15] = coolingGeometryID[i];
      coolingGeometryID[i + 20] = coolingGeometryID[i];
      coolingGeometryID[i + 25] = coolingGeometryID[i];
    }
    for(i = 0;i<nn;i++){
      //cout<<setw(10)<<coolingGeometryID[i];
      cout<<" "<<coolingGeometryID[i];
    }

    cout<<endl<<"coolingL"<<endl;
    for(i = 0;i<5;i++){
      coolingL[i + 5] = coolingL[i];
      coolingL[i + 10] = coolingL[i];
      coolingL[i + 15] = coolingL[i];
      coolingL[i + 20] = coolingL[i];
      coolingL[i + 25] = coolingL[i];
    }
    for(i = 0;i<nn;i++){
      //cout<<setw(10)<<coolingL[i];
      cout<<" "<<coolingL[i];
    }

    cout<<endl<<"coolingPosPhi"<<endl;
    //1
    for(i = 0;i<5;i++)
      coolingPosPhi[i] = coolingPosPhi[i]*180.0/TMath::Pi();

    //2
    coolingPosPhi[5] = coolingPosPhi[0] + 360.0/nSectors;
    coolingPosPhi[6] = 360.0/nSectors*2.0 - coolingPosPhi[1];
    coolingPosPhi[7] = 360.0/nSectors*2.0 - coolingPosPhi[2];
    coolingPosPhi[8] = 360.0/nSectors + (360.0/nSectors - coolingPosPhi[3]);
    coolingPosPhi[9] = 360.0/nSectors + (360.0/nSectors - coolingPosPhi[4]);
    //3
    coolingPosPhi[10] = coolingPosPhi[0] + 360.0/nSectors*2.0;
    coolingPosPhi[11] = 360.0/nSectors*3.0 - coolingPosPhi[1];
    coolingPosPhi[12] = 360.0/nSectors*3.0 - coolingPosPhi[2];
    coolingPosPhi[13] = coolingPosPhi[8] + 360.0/nSectors;
    coolingPosPhi[14] = coolingPosPhi[9] + 360.0/nSectors;
    //4
    coolingPosPhi[15] = coolingPosPhi[0] + 360.0/nSectors*3.0;
    coolingPosPhi[16] = coolingPosPhi[1] + 360.0/nSectors*3.0;
    coolingPosPhi[17] = coolingPosPhi[2] + 360.0/nSectors*3.0;
    coolingPosPhi[18] = coolingPosPhi[3] + 360.0/nSectors*3.0;
    coolingPosPhi[19] = coolingPosPhi[4] + 360.0/nSectors*3.0;
    //5
    coolingPosPhi[20] = coolingPosPhi[5] + 360.0/nSectors*3.0;
    coolingPosPhi[21] = coolingPosPhi[6] + 360.0/nSectors*3.0;
    coolingPosPhi[22] = coolingPosPhi[7] + 360.0/nSectors*3.0;
    coolingPosPhi[23] = coolingPosPhi[8] + 360.0/nSectors*3.0;
    coolingPosPhi[24] = coolingPosPhi[9] + 360.0/nSectors*3.0;
    //6
    coolingPosPhi[25] = coolingPosPhi[10] + 360.0/nSectors*3.0;
    coolingPosPhi[26] = coolingPosPhi[11] + 360.0/nSectors*3.0;
    coolingPosPhi[27] = coolingPosPhi[12] + 360.0/nSectors*3.0;
    coolingPosPhi[28] = coolingPosPhi[13] + 360.0/nSectors*3.0;
    coolingPosPhi[29] = coolingPosPhi[14] + 360.0/nSectors*3.0;

    for(i = 0;i<nn;i++){
      //cout<<setw(10)<<coolingPosPhi[i];
      cout<<" "<<coolingPosPhi[i];
    }

    cout<<endl<<"coolingPosR"<<endl;
    for(i = 0;i<5;i++){
      coolingPosR[i + 5] = coolingPosR[i];
      coolingPosR[i + 10] = coolingPosR[i];
      coolingPosR[i + 15] = coolingPosR[i];
      coolingPosR[i + 20] = coolingPosR[i];
      coolingPosR[i + 25] = coolingPosR[i];
    }
    for(i = 0;i<nn;i++){
      //cout<<setw(10)<<coolingPosR[i];
      cout<<" "<<coolingPosR[i];
    }

    cout<<endl<<"coolinRotationAngle"<<endl;
    for(i = 0;i<nn;i++)
      coolinRotationAngle[i] = coolingPosPhi[i];
    for(i = 0;i<nn;i++){
      //cout<<setw(10)<<coolinRotationAngle[i];
      cout<<" "<<coolinRotationAngle[i];
    }

    cout<<endl;

  }

}//namespace xmlarichdata{
