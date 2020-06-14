#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sun Oct 14 00:17:08 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

cellStrTest_bash(){

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi
    
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::cellStrTest()");'

}

cellStrTest_bash
