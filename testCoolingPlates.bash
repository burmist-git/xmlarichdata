#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Tue May  1 12:33:24 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script draw the TH2Poly histogram of  test     #
#                  cooling plates.                                     #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

testCoolingPlates_bash () {
    
    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.
    root -l -e 'gROOT->ProcessLine(".L testCoolingPlates.C"); gROOT->ProcessLine("xmlarichdata::testCoolingPlates()");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    #make cleanDictLib;
    #make libxmlarichdataDict.cxx;
    #make libxmlarichdataDictLib.so;
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::testCoolingPlates()");'

}

testCoolingPlates_bash

