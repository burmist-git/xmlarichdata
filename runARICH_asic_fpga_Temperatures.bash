#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon May  7 14:36:00 JST 2018                                         #
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

function runARICH_asic_fpga_Temperatures_bash {
    
    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.
    #root -l -e 'gROOT->ProcessLine(".L runARICH_asic_fpga_Temperatures.C"); gROOT->ProcessLine("xmlarichdata::runARICH_asic_fpga_Temperatures()");'

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then	
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;      
    fi

    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_asic_fpga_Temperatures()");'

}

runARICH_asic_fpga_Temperatures_bash
