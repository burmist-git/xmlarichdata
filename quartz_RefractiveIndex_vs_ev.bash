#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Jun  4 20:04:07 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots TGraph of quartz refractive index #
#                  photn energy (eV).                                  #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

quartz_RefractiveIndex_vs_ev_bash(){
    
    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.
    #root -l -e 'gROOT->ProcessLine(".L quartz_RefractiveIndex_vs_wavelength.C"); gROOT->ProcessLine("xmlarichdata::quartz_RefractiveIndex_vs_wavelength()");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::quartz_RefractiveIndex_vs_ev()");'
    
}

quartz_RefractiveIndex_vs_ev_bash
