#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sun Oct 15 18:35:16 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots TGraph from given root file.      #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

plots_bash(){

    #Old way of execution before : Mon Apr 16 14:05:28 JST 2018
    #make cleanplots ; make plots
    #./plots $fileN $histN $pdfFolder $histOption
    #root -l "plots.C( \"$1\" , \"$2\" , \"$3\" , \"$4\" )"
    #After Mon Apr 16 14:05:28 JST 2018
    # histOption = "-v"  <--- Transmitance
    # histOption = "!-v" <--- Transmitance Length
    mkdir -p "./pdfdatatmp/"
    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.
    #root -l -e 'gROOT->ProcessLine(".L plots.C"); gROOT->ProcessLine("xmlarichdata::plots( \"./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root\" , \"gr_A_L_norm\" , \"./pdfdatatmp/\" , \"!-v\" )");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    make cleanDictLib;
    make libxmlarichdataDict.cxx;
    make libxmlarichdataDictLib.so;
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::plots( \"./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root\" , \"gr_A_L_norm\" , \"./pdfdatatmp/\" , \"!-v\" )");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::plots( \"./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root\" , \"gr_A_L_norm\" , \"\" , \"!-v\" )");'

}

#gr_A167_trLength
#gr_A168_trLength
#gr_A178_trLength
#gr_B012_trLength
#gr_B014_trLength
#gr_B017_trLength
#gr_B018_trLength

# histOption = "-v"  <--- Transmitance
# histOption = "!-v" <--- Transmitance Length

#fileN="./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root"
#fileN="./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root"
#histN="gr_B164"
#histN="gr_A167_trLength"
#histN="gr_B165_trLength"
#histN="gr_A_L_norm"
#histN="gr_B_L_norm"
#pdfFolder="./pdfdatatmp/"
#mkdir -p $pdfFolder
#histOption="-v"
#histOption="!-v"

#Old way of execution before : Mon Apr 16 14:05:28 JST 2018
#plots_bash $fileN $histN $pdfFolder $histOption

#After Mon Apr 16 14:05:28 JST 2018
plots_bash
