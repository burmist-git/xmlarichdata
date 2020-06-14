#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Tue May 29 11:50:56 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script print the ARICH number of channels      #
#                  chips, HAPD, mergers and sector information.        #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function printNumber_of_channels_chips_HAPD_mergers_sectors_bash {

    make cleanprintNumber_of_channels_chips_HAPD_mergers_sectors; make printNumber_of_channels_chips_HAPD_mergers_sectors -j8;
    ./printNumber_of_channels_chips_HAPD_mergers_sectors

    #root -l -e 'gROOT->ProcessLine(".L runARICHcablesMaterial.C"); gROOT->ProcessLine("xmlarichdata::runARICHcablesMaterial()");'

    #make cleanDictLib;
    #make libxmlarichdataDict.cxx;
    #make libxmlarichdataDictLib.so;
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICHcablesMaterial()");'

}

printNumber_of_channels_chips_HAPD_mergers_sectors_bash
