#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sun Nov 11 21:37:46 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script to run tessellation solid visualisation #
#                  program.                                            #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function tessellationSolidVisualisation_bash {
    
    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi

    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::tessellationSolidVisualisation(\"tessellatedSolidVertices.dat\",0.0,0.0,0.0,3.0)");'
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::tessellationSolidVisualisation(\"tessellatedSolidVertices_racing_track.dat\",-898,-6700,0.0,1.0)");'

}

tessellationSolidVisualisation_bash
