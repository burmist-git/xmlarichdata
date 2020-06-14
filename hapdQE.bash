#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Apr 16 20:24:15 JST 2018                                         #
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

hapdQE_bash(){

    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.    
    #root -l -e 'gROOT->ProcessLine(".L hapdQE.C"); gROOT->ProcessLine("xmlarichdata::hapdQE()");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::hapdQE()");'
}

hapdQE_bash
