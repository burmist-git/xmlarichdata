#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Thu Oct  4 10:02:23 JST 2018                                         #
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

function runanaSCT_bash {
    
    #root -l -e 'gROOT->ProcessLine(".L runARICHmappingCopperMergerFeb.C"); gROOT->ProcessLine("xmlarichdata::runARICHmappingCopperMergerFeb()");'

    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
        #make runARICHmappingCopperMergerFeb; make -j`nproc --all` runARICHmappingCopperMergerFeb;
	
        make cleanDictLib;
        make -j`nproc --all` libxmlarichdataDict.cxx;
        make -j`nproc --all` libxmlarichdataDictLib.so;      
    fi

    #./runARICHmappingCopperMergerFeb    
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList.dat\",\"./hist.root\")");'
    #
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-21.dat\",\"./hist_2018-09-21.root\", 2018,  9,  21,  15,  7,  6,  60, 20, 55)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-21.dat\",\"./hist_2018-09-21.root\", 2018,  9,  21,  17,  45,  38,  60, 20, 55)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-21.dat\",\"./hist_2018-09-21.root\", 2018,  9,  21,  18,  16,  10,  60, 20, 55)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-21.dat\",\"./hist_2018-09-21.root\", 2018,  9,  21,  18,  16,  10,  60, 25, 50)");'
    #
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-30.dat\",\"./hist_2018-09-30.root\", 2018,  9,  30,  14,  41,  56,  60, 20, 55)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-30.dat\",\"./hist_2018-09-30.root\", 2018,  9,  30,  17,  10,  11,  60, 25, 35)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-30.dat\",\"./hist_2018-09-30.root\", 2018,  9,  30,  17,  10,  11,  60, 30, 40)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-30.dat\",\"./hist_2018-09-30.root\", 2018,  9,  30,  19,  49,  57,  60, 30, 45)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-09-30.dat\",\"./hist_2018-09-30.root\", 2018,  9,  30,  19,  49,  57,  60, 25, 45)");'
    #
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-10-01.dat\",\"./hist_2018-10-01.root\", 2018,  10,   1,  11,  37,  56,  60, 25, 35)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-10-01.dat\",\"./hist_2018-10-01.root\", 2018,  10,   1,  17,  10,  6,  60, 25, 35)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-10-01.dat\",\"./hist_2018-10-01.root\", 2018,  10,   1,  17,  10,  6,  60, 25, 50)");'
    #root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaSCT(0,\"./rootFileList_2018-10-01.dat\",\"./hist_2018-10-01.root\", 2018,  10,   1,  17,  10,  6,  60, 25, 45)");'
}

runanaSCT_bash
