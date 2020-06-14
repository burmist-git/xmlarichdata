#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Apr 16 13:48:16 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots TGraph of probability of the      #
#                  photon to be absorbed after total internal          #
#                  reflection from the quartz - air interface          #
#                  as a function of wavelength. It shows the quartz    #
#                  polishing quality.                                  #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

quartz_Babar_DIRC_polishing_quality_bounds_bash(){

    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.    
    #root -l -e 'gROOT->ProcessLine(".L quartz_Babar_DIRC_polishing_quality_bounds.C"); gROOT->ProcessLine("xmlarichdata::quartz_Babar_DIRC_polishing_quality_bounds()");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi
    
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::quartz_Babar_DIRC_polishing_quality_bounds()");'

}

quartz_Babar_DIRC_polishing_quality_bounds_bash
 
