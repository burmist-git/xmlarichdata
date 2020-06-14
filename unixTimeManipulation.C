/***********************************************************************
* Copyright(C) 2018 - LBS - (Single person developer.)                 *
* Mon Oct  1 19:07:42 JST 2018                                         *
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
#include <TLegend.h>
#include <TMultiGraph.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <time.h>

using namespace std;
using namespace xmlarichdata;

namespace xmlarichdata{

  double getUnixTimeFrom_year_month_day_hour_min_sec(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec){
    struct tm y2k = {0};
    y2k.tm_year = d_year - 1900; y2k.tm_mon = d_month-1; y2k.tm_mday = d_day;
    y2k.tm_hour = d_hour;   y2k.tm_min = d_min; y2k.tm_sec = d_sec;
    return difftime(mktime(&y2k),0);
  }

  double getUnixTimeFrom_TString(TString timestr, int dataTimeArr_i[6]){
    string tstr = timestr.Data();
    findAndReplaceString( tstr, "[", "");
    findAndReplaceString( tstr, "-", " ");
    findAndReplaceString( tstr, ":", " ");
    findAndReplaceString( tstr, "]", "");
    istringstream buf(tstr);
    //cout<<tstr<<endl;
    double d_year, d_month, d_day, d_hour, d_min, d_sec;
    buf>>d_year>>d_month>>d_day>>d_hour>>d_min>>d_sec;
    dataTimeArr_i[0] = d_year;
    dataTimeArr_i[1] = d_month;
    dataTimeArr_i[2] = d_day;
    dataTimeArr_i[3] = d_hour;
    dataTimeArr_i[4] = d_min;
    dataTimeArr_i[5] = d_sec;
    //cout<<d_year<<endl;
    return getUnixTimeFrom_year_month_day_hour_min_sec(d_year, d_month, d_day, d_hour, d_min, d_sec);
  }

  void findAndReplaceString(string& str, const string& oldStr, const string& newStr){
    std::string::size_type pos = 0u;
    while((pos = str.find(oldStr, pos)) != std::string::npos){
      str.replace(pos, oldStr.length(), newStr);
      pos += newStr.length();
    }
  }

  bool ifLineContainsString(const string& line, const string& str){
    std::size_t found = line.find(str);
    if (found!=std::string::npos)
      return true;
    return false;
  }

  void getMergerIDandTemperatureFrom_TString(TString str, Float_t &t, Int_t &mergerLocalID){
    //arich[0].temp : float(34.125)
    string tstr = str.Data();
    findAndReplaceString( tstr, "arich[", "");
    findAndReplaceString( tstr, "].temp", " ");
    findAndReplaceString( tstr, ":", " ");
    findAndReplaceString( tstr, "float(", "");
    findAndReplaceString( tstr, ")", "");
    istringstream buf(tstr);
    //cout<<tstr<<endl;
    //double d_year, d_month, d_day, d_hour, d_min, d_sec;
    buf>>mergerLocalID>>t;
    //cout<<mergerLocalID<<" "<<t<<endl;
  }

  void getFebIDandTemperatureFrom_TString(TString str, Float_t &t, Int_t &mergerLocalID, Int_t &febLocalID){
    //arich[0].feb[0].t1 : float(28.625)
    string tstr = str.Data();
    findAndReplaceString( tstr, "arich[", "");
    findAndReplaceString( tstr, "].feb[", " ");
    findAndReplaceString( tstr, "].t1", " ");
    findAndReplaceString( tstr, "].t2", " ");
    findAndReplaceString( tstr, ":", " ");
    findAndReplaceString( tstr, "float(", "");
    findAndReplaceString( tstr, ")", "");
    istringstream buf(tstr);
    //cout<<tstr<<endl;
    //double d_year, d_month, d_day, d_hour, d_min, d_sec;
    buf>>mergerLocalID>>febLocalID>>t;
    //cout<<mergerLocalID<<" "<<febLocalID<<" "<<t<<endl;
  }
  
} //namespace xmlarichdata{
