#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Wed Oct 31 11:55:30 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                 This script run plotsARICHphase2performance.C        #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function plotsARICHphase2performance_bash {

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
        make cleanDictLib;
        make -j`nproc --all` libxmlarichdataDict.cxx;
        make -j`nproc --all` libxmlarichdataDictLib.so;      
    fi    

    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::plotsARICHphase2performance(\"theta\")");'
}

plotsARICHphase2performance_bash
