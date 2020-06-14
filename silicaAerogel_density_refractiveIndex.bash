#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sat Apr 21 16:34:33 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script print refractive index of silica        #
#                  aerogel.                                            #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

silicaAerogel_density_refractiveIndex_bash () {
    
    #Run without generation of the dictionary and shared library. Please _note_ : no LinkDef.h file is needed.
    root -l -e 'gROOT->ProcessLine(".L silicaAerogel_density_refractiveIndex.C"); gROOT->ProcessLine("xmlarichdata::silicaAerogel_density_refractiveIndex()");'

    #Run with generation of the dictionary and shared library. Please _note_ : LinkDef.h file IS needed.
    #make cleanDictLib;
    #make libxmlarichdataDict.cxx;
    #make libxmlarichdataDictLib.so;
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::silicaAerogel_density_refractiveIndex()");'

}

silicaAerogel_density_refractiveIndex_bash

