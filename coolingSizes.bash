#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Apr 30 17:46:00 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script print parameters of ARICH cooling       #
#                  system.                                             #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

coolingSizes_bash () {

    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.
    #root -l -q -b -e 'gROOT->ProcessLine(".L coolingSizes.C"); gROOT->ProcessLine("xmlarichdata::coolingSizes()");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    #make cleanDictLib;
    #make libxmlarichdataDict.cxx;
    #make libxmlarichdataDictLib.so;
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::coolingSizes()");'

}

coolingSizes_bash
