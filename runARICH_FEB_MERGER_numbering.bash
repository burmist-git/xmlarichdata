#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Oct 22 14:02:42 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script draw the TH2Poly histogram of numbering #
#                  scheme of the FEB (HAPD's).                         #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function runARICH_FEB_merge_pdfs {

    singlePlotPdfList="feb_numbering_sec01.pdf feb_numbering_sec02.pdf feb_numbering_sec03.pdf feb_numbering_sec04.pdf feb_numbering_sec05.pdf feb_numbering_sec06.pdf feb_numbering.pdf"
    mergedPdfOutFile="feb_numbering_All.pdf"

    echo "--> runARICH_FEB_merge_pdfs"
    gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$mergedPdfOutFile $singlePlotPdfList > /dev/null 2>&1
    
}

function runARICH_MERGER_merge_pdfs {

    singlePlotPdfList="merger_numbering_sec01.pdf merger_numbering_sec02.pdf merger_numbering_sec03.pdf merger_numbering_sec04.pdf merger_numbering_sec05.pdf merger_numbering_sec06.pdf merger_numbering.pdf"
    mergedPdfOutFile="merger_numbering_All.pdf"
    
    echo "--> runARICH_MERGER_merge_pdfs"
    gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$mergedPdfOutFile $singlePlotPdfList > /dev/null 2>&1
    
}

function runARICH_FEB_numbering_all_bash {

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi

    #if executionKey == 0 --> build FEB(HAPD) with FEB(HAPD) global ID
    #if executionKey == 1 --> build FEB(HAPD) with FEB(HAPD) local  ID
    #if executionKey == 2 --> build FEB(HAPD) with MERGER    global ID
    #if executionKey == 3 --> build FEB(HAPD) with MERGER    local  ID
    #if executionKey == 4 --> build FEB(HAPD) with COPPER    global ID
    #if executionKey == 5 --> build FEB(HAPD) with SECTOR    global ID
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_FEB_numbering(1,3)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_FEB_numbering(2,3)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_FEB_numbering(3,3)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_FEB_numbering(4,3)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_FEB_numbering(5,3)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_FEB_numbering(6,3)");'
    root -l -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_FEB_numbering(7,3)");'

    runARICH_FEB_merge_pdfs

}

function runARICH_MERGER_numbering_all_bash {

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	make cleanDictLib;
	make libxmlarichdataDict.cxx;
	make libxmlarichdataDictLib.so;
    fi

    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_MERGER_numbering(1)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_MERGER_numbering(2)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_MERGER_numbering(3)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_MERGER_numbering(4)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_MERGER_numbering(5)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_MERGER_numbering(6)");'
    root -l -b -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runARICH_MERGER_numbering(7)");'

    runARICH_MERGER_merge_pdfs

}

runARICH_FEB_numbering_all_bash

runARICH_MERGER_numbering_all_bash
