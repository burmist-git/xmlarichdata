#pragma once

#include <iostream>
#include <vector>
#include "ARICHcopperStr.h"

struct ARICHsectorStr {
  int localID;
  int globalID;
  ARICHsectorStr(){
    localID = -999;
    globalID = -999;
  }
  std::vector<ARICHcopperStr> copper;
  void printInfo(){
    std::cout<<"SectorGID "<<globalID<<std::endl;
    std::cout<<"SectorLID "<<localID<<std::endl;
    for (unsigned i = 0; i<copper.size(); i++)
      copper[i].printInfo();
  }
};
