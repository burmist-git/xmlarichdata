#pragma once

#include <TString.h>

struct aerogelInfoMap {
  // ----
  // id_map    number    serial  serialID      ring    column     layer         n   transmL     thick
  //   B076         0      B076   CAd9-20         1        12      down    1.0538       3.6      2.03
  // ----
  TString id_map;
  int idnumber;
  TString serial;
  TString serialID;
  int ring;
  int column;
  TString layer;
  float n;
  float transmL;
  float thick;
  // p0 + p1*lambda + p2*lambda^2 .... + p4*lambda^4
  // p5 - lambda min
  // p6 - lambda max
  int nPoints;// Number of measured poits (NON zero)
  float dLam; // delta Lambda
  float p0;   // Fit parameter
  float p1;   // Fit parameter
  float p2;   // Fit parameter
  float p3;   // Fit parameter
  float p4;   // Fit parameter
  float p5;   // Fix parameter (lambda min)
  float p6;   // Fix parameter (lambda max)
  inline aerogelInfoMap operator=(aerogelInfoMap a) {
    id_map = a.id_map;
    idnumber = a.idnumber;
    serial = a.serial;
    serialID = a.serialID;
    ring = a.ring;
    column = a.column;
    layer = a.layer;
    n = a.n;
    transmL = a.transmL;
    thick = a.thick;
    nPoints = a.nPoints;
    dLam = a.dLam;
    p0 = a.p0;
    p1 = a.p1;
    p2 = a.p2;
    p3 = a.p3;
    p4 = a.p4;
    p5 = a.p5;
    p6 = a.p6;
    return a;
  }
  aerogelInfoMap(){
    id_map = "NON";
    idnumber = -999;
    serial = (char*)"NON";
    serialID = (char*)"NON";
    ring = -999;
    column = -999;
    layer = (char*)"NON";
    n = -999.0;
    transmL = -999.0;
    thick = -999.0;
    nPoints = 0;
    dLam = 0;
    p0 = 0;
    p1 = 0;
    p2 = 0;
    p3 = 0;
    p4 = 0;
    p5 = 0;
    p6 = 0;
  }
};
