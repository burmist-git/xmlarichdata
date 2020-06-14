#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sun Jun 10 14:21:55 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots TGraph from given root file and   #
#                  fit transmission length.                            #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

fitAbsorptionLength_averaged_bash(){

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    #root -l "fitAbsorptionLength.C( \"$1\" , \"$2\" , \"$3\" , \"$4\", $5 )"
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi
    #A
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::fitAbsorptionLength(\"./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root\" , \"gr_A_norm\" , \"gr_A_L_norm\" , \"pdfFolder\", 1.96 )");'
    #B
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::fitAbsorptionLength(\"./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root\" , \"gr_B_norm\" , \"gr_B_L_norm\" , \"pdfFolder\", 1.97 )");'

}

fitAbsorptionLength_averaged_bash
