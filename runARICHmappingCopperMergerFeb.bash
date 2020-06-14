#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Tue Oct  2 15:57:37 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script print the ARICH mapping.                #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function runARICHmappingCopperMergerFeb_bash {
    
    #root -l -e 'gROOT->ProcessLine(".L runARICHmappingCopperMergerFeb.C"); gROOT->ProcessLine("xmlarichdata::runARICHmappingCopperMergerFeb()");'

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
        #make runARICHmappingCopperMergerFeb; make -j`nproc --all` runARICHmappingCopperMergerFeb;
	
        make cleanDictLib;
        make -j`nproc --all` libxmlarichdataDict.cxx;
        make -j`nproc --all` libxmlarichdataDictLib.so;      
    fi

    #./runARICHmappingCopperMergerFeb    
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICHmappingCopperMergerFeb()");'

}

runARICHmappingCopperMergerFeb_bash
