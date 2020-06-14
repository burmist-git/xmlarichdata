#pragma once

//my
#include "aerogelInfoMap.h"
#include "mergerStruct.h"
#include "cellStr.h"
#include "cellGeoStr.h"
#include "tessellatedSolidStr.h"

//basf2
#include <arich/utility/ARICHChannelHist.h>

//root
#include <TROOT.h>
#include <TStyle.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TString.h>
#include <TFile.h>
#include <TGraph.h>
#include <TAxis.h>
#include "TXMLEngine.h"
#include "TH2Poly.h"
#include "TLine.h"
#include "TPolyLine3D.h"

//c, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>

namespace xmlarichdata {

  //xmlArichData2Graph.C
  Int_t read_xml_File_List(TString filenameXMLList, TString *xmlDataFileList);
  Int_t read_xml_File_transmittance(TString filename, TString &versionInfo, TString &serialInfo, TString &idInfo, Double_t &indexInfo, Double_t &translengthInfo, Double_t &thickInfo, TGraph *gr);
  Double_t calc_translength( Double_t thick, Double_t translength, TGraph *gr_tr, TGraph *gr_trL);
  void addTGraph( TGraph *gr, TGraph *gr_add);
  void normTGraph( TGraph *gr, Double_t norm);
  void printToFileDifferencesDetails( TString differencesDetailsFileName, TString filename, TString versionInfo, Double_t deltaTrL, Double_t translengthInfo, Double_t translengthInfoData);
  Int_t xmlArichData2Graph(TString filePathXML, TString filenameXMLList, TString fnameroot, TString differencesDetailsFileName, Double_t normAVal, Double_t normBVal);
  
  //plots.C
  TGraph *plots( TString fileN, TString histN, TString pdfFolder, TString histOption);
  
  //fitAbsorptionLength.C
  Double_t fitFunction(Double_t *x, Double_t *par);
  TF1 *fitAbsorptionLength(TString fileN, TString histN1, TString histN2, TString pdfFolder, Double_t dX);
  //std::vector<aerogelInfoMap> fitAllAbsLen( TString fnameInfo, TString fnameMap);

  //fitAllAbsLen.C
  std::vector<aerogelInfoMap> fitAllAbsLen(TString fileN, TString fnameInfo,  TString fnameMap,  TString pdfFolder,  TString outFname, TString outXMLfile, Float_t version);

  //xmlreadfile.C
  void DisplayNode(TXMLEngine* xml, XMLNodePointer_t node, Int_t level);
  void dumpVector(TString name);
  void xmlreadfile(const char* filename);
  
  //readAerogelInfoMap.C
  Int_t readFileInfo( TString fname, TString *serial, TString *serialID, Double_t *version, Double_t *nref, Double_t *transmLength, Double_t *thickness);
  Int_t readFileMap( TString fname, TString *id, Double_t *ring, Double_t *column, TString *layer);
  std::vector<aerogelInfoMap> readAerogelInfoMap( TString fnameInfo, TString fnameMap);
  
  //refractiveIndexSilicaAerogel.C
  Double_t refractiveIndexSilicaAerogel( TString type, Double_t lam);
  void refractiveIndexSilicaAerogelPrintTestData();
  
  //rayleighScatteringCrossSection.C
  Double_t rayleighScatteringCrossSection(Double_t d, Double_t lam, Double_t n);
  
  //saveXMLdataVector.C
  TString float2StrTruncate(Float_t val, Int_t precision);
  Float_t roundVal(Float_t val, Int_t precision);
  void saveXMLdataVector( TString fnameInfo, TString fnameMap, TString outXMLfile, Float_t version);
  void saveXML(const std::vector<aerogelInfoMap> &aimvfit, TString outXMLfile, Float_t version);
  
  //convertdx2xml.C
  void convertdx2xml( TString inFolder, TString inXmlFolder, TString outFolder, TString outTmpFolder, TString versionIDstr, TString conversionKey, TString fnameInfo, TString fnameMap);
  void makeconvertiondx2xml( TString indxFileName, TString outxmlFileName, TString versionIDstr, TString positionstr, Float_t translengthf, Float_t thickf, aerogelInfoMap aimstr);
  
  //convert_TrLength_vs_Lambda_2_TrLength_vs_pe.C
  Double_t lambda_nm_2_ev(Double_t lam);
  Double_t ev_2_lambda_nm(Double_t ev_val);
  TGraph *convert_TrLength_vs_Lambda_2_TrLength_vs_pe(TGraph *grTr_vs_Lam);
  TGraph *convert_TGraph_Lambda_vs_pe(TGraph *gr_vs_Lam);
  void print_TGraph_info( TGraph *gr, TString printMod);
  void printToFile_TGraph_info( std::ofstream &outFile, TGraph *gr, TString printMod);

  //silicaAerogel_density_refractiveIndex.C
  Double_t get_silicaAerogel_density_from_refractiveIndex( Double_t n, Double_t k);
  Double_t get_silicaAerogel_refractiveIndex_from_density( Double_t den, Double_t k);
  void silicaAerogel_density_refractiveIndex();

  //mirror_reflection_vs_wavelength.C
  TGraph *mirror_reflection_vs_wavelength();
  
  //quartzAbsorbtion_vs_wavelength.C
  TGraph *quartzAbsorbtion_vs_wavelength();
  
  //quartz_RefractiveIndex_vs_wavelength.C
  Double_t getSellmeierQuartz(Double_t lam);
  TGraph *quartz_RefractiveIndex_vs_wavelength(TString returnStrID);

  //quartz_RefractiveIndex_vs_ev.C
  TGraph *quartz_RefractiveIndex_vs_ev();

  //aerogel_RefractiveIndex_vs_ev.C
  TGraph *aerogel_RefractiveIndex_vs_ev(TString type, Double_t dn_at_405nm);

  //aerogel_average_RAYLEIGH_vs_ev.C
  TGraph *aerogel_average_RAYLEIGH_vs_ev(TString type);
  TGraph *aerogel_RAYLEIGH_vs_ev(TString histName, TString histNameL, Double_t dX);

  //quartz_Babar_DIRC_polishing_quality_bounds.C
  TGraph *quartz_Babar_DIRC_polishing_quality_bounds();

  //hapdQE.C
  TGraph *hapdQE();

  //read_merger_positions.C
  std::vector<mergerStruct> read_merger_positions( TString fnameInfo, float &size_l, float &size_w, int &nMerger);

  //read_merger_positions.C
  void read_temperature_meas( TString fname, std::vector<double> &posR, std::vector<double> &posPhi, std::vector<double> &measT);

  //coolingSizes.C
  void coolingSizes();

  //testCoolingPlates.C
  void testCoolingPlates();
  void getTestCoolingPlates( TH2Poly *h2poly, std::vector<TGraph*> &m_verticesGraphV, TString h2_name, TString h2_title, double frameXmin, double frameXmax, double frameYmin, double frameYmax, double normalisationV);
  void getAdditionalGraphV_and_LineV_for_Plot( std::vector<TGraph*> &m_additionalGraphV, std::vector<TLine*> &m_additionalLineV, double envelopeR_min, double envelopeR_max, double l_slot);

  //unixTimeManipulation.C
  double getUnixTimeFrom_year_month_day_hour_min_sec(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec);
  double getUnixTimeFrom_TString(TString timestr, int dataTimeArr_i[6]);
  void findAndReplaceString( std::string& str, const std::string& oldStr, const std::string& newStr);
  bool ifLineContainsString(const std::string& line, const std::string& str);
  void getMergerIDandTemperatureFrom_TString(TString str, Float_t &t, Int_t &mergerLocalID);
  void getFebIDandTemperatureFrom_TString(TString str, Float_t &t, Int_t &mergerLocalID, Int_t &febLocalID);

  //runARICH_asic_fpga_Temperatures.C
  Belle2::ARICHChannelHist* runARICH_asic_fpga_Temperatures();

  //runARICH_asic_fpga_Temperatures_newCooling.C
  Belle2::ARICHChannelHist* runARICH_asic_fpga_Temperatures_newCooling();
  
  //runARICH_asic_fpga_numbering.C
  Belle2::ARICHChannelHist* runARICH_asic_fpga_numbering();

  //runARICH_FEB_MERGER_numbering.C
  void runARICH_FEB_numbering(Int_t secID, Int_t executionKey);
  void runARICH_MERGER_numbering( Int_t secID);
  void setFrameLimits(Int_t secID, Double_t dl, Double_t envelopeR_center, Double_t &frameXmin, Double_t &frameXmax, Double_t &frameYmin, Double_t &frameYmax);
    
  //runARICHcablesMaterial.C
  Int_t runARICHcablesMaterial();

  //runARICHmappingCopperMergerFeb.C
  Int_t runARICHmappingCopperMergerFeb();

  //runanaSCT.C
  Int_t runanaSCT(Int_t executionIDnumber, TString rootFilesList, TString outRootFileF, double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec, double dTimeWindow, double tMin, double tMax);

  //runanaGL840.C
  int runanaGL840( Int_t keyID, TString rootFileOrList, TString outRootFileF, Int_t dataDivision, TString parametersFileIn);
  
  //convertDataFebMergerTemperatureSlowControl.C
  void convertDataFebMergerTemperatureSlowControl( TString infile, Int_t copperBoardID, TString outfile);

  //convertGL840csv.C
  void convertGL840csv( TString inputDataFile, TString outputrootFile);
  double getUnixTime(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec);

  //cellStrTest.C
  std::vector<cellStr> cellStrTest();

  //saveTessellatedSolidVerticesToXML.C
  void saveTessellatedSolidVerticesToXML(const std::vector<cellStr> &tessellatedSolidVertices, int precision, TString outXMLfile);
  void saveTessellatedSolidVerticesToDATfile(const std::vector<cellStr> &tessellatedSolidVertices, int precision, TString outDatfile);
  void dumpTessellatedSolidVertices(const std::vector<cellStr> &tessellatedSolidVertices, int precision);
  void saveVectorToFile(const std::vector<cellStr> &tessellatedSolidVertices, FILE *pFile, TString xmlVectorName, TString xml_or_dat_key, int precision, int apexID, int coordinateID);
  tessellatedSolidStr readTessellatedSolidVerticesToDATfile(TString inDATfile);

  //plotsARICHphase2performance.C
  Int_t plotsARICHphase2performance(TString plotKey);

  //tessellationSolidVisualisation.C
  std::vector<TPolyLine3D*> tessellationSolidVisualisation(TString inDatFile, double x0, double y0, double z0, double lineWidth);
  TPolyLine3D *buildTriangle( double *x, double *y, double *z, double lineWidth);

  //printNumber_of_channels_chips_HAPD_mergers_sectors.C
  //void printNumber_of_channels_chips_HAPD_mergers_sectors();

  //generateXmlAerogelMaterialFile.C
  //Int_t generateXmlAerogelMaterialFile();

}
