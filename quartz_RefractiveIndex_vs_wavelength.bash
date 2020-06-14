#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Apr 16 13:48:16 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots TGraph of mirror reflection vs    #
#                  wavelength.                                         #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

quartz_RefractiveIndex_vs_wavelength_bash(){
    
    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.
    #root -l -e 'gROOT->ProcessLine(".L quartz_RefractiveIndex_vs_wavelength.C"); gROOT->ProcessLine("xmlarichdata::quartz_RefractiveIndex_vs_wavelength()");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    make cleanDictLib;
    make libxmlarichdataDict.cxx;
    make libxmlarichdataDictLib.so;
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::quartz_RefractiveIndex_vs_wavelength(\"RI\")");'

}

quartz_RefractiveIndex_vs_wavelength_bash
