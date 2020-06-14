#pragma once

#include "cellGeoStr.h"

#include <iostream>
#include <iomanip>
#include <vector>

struct tessellatedSolidStr {
  cellGeoStr cellGeo;
  int tessellatedSolidID;
  unsigned int nCells;
  unsigned int nApexPerCell;
  // Tessellated solid represented by the array (vector) of triangles
  std::vector<std::vector<double>> posV1; // x, y, z of apex1
  std::vector<std::vector<double>> posV2; // x, y, z of apex2
  std::vector<std::vector<double>> posV3; // x, y, z of apex3
  tessellatedSolidStr(){
    tessellatedSolidID = -999;
    nCells = 999;
    nApexPerCell = 999;
  }
  ~tessellatedSolidStr(){;}  
  void printInfo(){
    unsigned int i;
    unsigned int j;
    for( i = 0; i < posV1.size(); i++){
      std::cout<<cellGeo.nameVector[0][i]<<std::endl;
      for( j = 0; j < posV1[i].size(); j++){
        std::cout<<std::setw(5)<<j<<std::setw(15)<<posV1[i][j]<<std::endl;
      }
    }
    for( i = 0; i < posV2.size(); i++){
      std::cout<<cellGeo.nameVector[1][i]<<std::endl;
      for( j = 0; j < posV2[i].size(); j++){
        std::cout<<std::setw(5)<<j<<std::setw(15)<<posV2[i][j]<<std::endl;
      }
    }
    for( i = 0; i < posV3.size(); i++){
      std::cout<<cellGeo.nameVector[2][i]<<std::endl;
      for( j = 0; j < posV3[i].size(); j++){
        std::cout<<std::setw(5)<<j<<std::setw(15)<<posV3[i][j]<<std::endl;
      }
    }
  }  
};
