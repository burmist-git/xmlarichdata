#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

struct cellStr {
  std::vector<std::vector<double>> apexs;
  //std::vector<double> apexs;
  cellStr(){
  }
  ~cellStr(){;}
  void printInfo(){
    unsigned int i;
    unsigned int j;
    for( i = 0; i < apexs.size(); i++){
      std::cout<<"    apex : "<<std::setw(3)<<i<<std::endl;
      for( j = 0; j < apexs[i].size(); j++){
	std::cout<<std::setw(15)<<apexs[i][j]<<std::endl;
      }
    }
  }
};
