#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Tue Jun  5 20:01:59 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots TGraph of aerogel refractive      #
#                  index vs photn energy (eV).                         #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function aerogel_RefractiveIndex_vs_ev_bash {
    
    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.
    #root -l -e 'gROOT->ProcessLine(".L aerogel_RefractiveIndex_vs_ev.C"); gROOT->ProcessLine("xmlarichdata::aerogel_RefractiveIndex_vs_ev(\"A\", 0.0)");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::aerogel_RefractiveIndex_vs_ev(\"A\", 0.0)");'
    
}

aerogel_RefractiveIndex_vs_ev_bash
