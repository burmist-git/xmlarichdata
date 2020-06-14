#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Tue Nov 28 21:45:18 CET 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script write xml file with empty data for      #
#                  for tests only.                                     #
#                  Please note this script is only for tests of the    #
#                  xml file creation (it does not put correct values   #
#                  of the fit parameters into the file).               #
#                                                                      #
# Input paramete:                                                      #
#                  NON.                                                #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

#saveXMLdataVector_CLING_bash(){
#root -l "saveXMLdataVector.C( ... )"
#}

saveXMLdataVector_bash(){

    make cleansaveXMLdataVector; make -j8 saveXMLdataVector    
    ./saveXMLdataVector $1 $2 $3 $4

}

fnameInfo="./aerogelDataFromDB/aerogelInfoBis.dat"
fnameMap="./aerogelDataFromDB/aerogelMap.dat"
outXMLfile="./xmlData/aerogel_xml_ver3/aerogel_xml_ver3_fit_test.xml"
version=3

saveXMLdataVector_bash $fnameInfo $fnameMap $outXMLfile $version
