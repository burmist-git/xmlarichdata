#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Thu May 10 17:42:37 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script print the ARICH cable information.      #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function runARICHcablesMaterial_bash {

    #make cleanrunARICHcablesMaterial; make runARICHcablesMaterial -j8;
    #./runARICHcablesMaterial

    #root -l -e 'gROOT->ProcessLine(".L runARICHcablesMaterial.C"); gROOT->ProcessLine("xmlarichdata::runARICHcablesMaterial()");'

    make cleanDictLib;
    make libxmlarichdataDict.cxx;
    make libxmlarichdataDictLib.so;
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICHcablesMaterial()");'

}

runARICHcablesMaterial_bash
