#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

struct cellGeoStr {
  static const int nApexPerCell = 3;
  static const int nPointsPerPosition = 3; //3-D sapce
  const TString nameVector[nApexPerCell][nPointsPerPosition] = {
    {"Apex_1_x","Apex_1_y","Apex_1_z"},
    {"Apex_2_x","Apex_2_y","Apex_2_z"},
    {"Apex_3_x","Apex_3_y","Apex_3_z"}
  };
  void printInfo(){
    unsigned int i;
    unsigned int j;
    for( i = 0; i < nApexPerCell; i++){
      for( j = 0; j < nPointsPerPosition; j++){
	std::cout<<std::setw(15)<<nameVector[i][j];
      }
      std::cout<<std::endl;
    }
  }
};
