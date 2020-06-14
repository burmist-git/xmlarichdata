#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Thu Dec  7 19:46:29 CET 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script converts dx files in xml format.        #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

make cleanconvertdx2xml; make -j8 convertdx2xml

convertdx2xml_bash(){

    ./convertdx2xml $1 $2 $3 $4 $5 $6 $7 $8
    
}

inFolder="./data/transT_markup_data/dataL/"
inXmlFolder="./data/aerogel_xml_ver3/"
outFolder="./data/aerogel_xml_ver3_L/"
outTmpFolder="./data/aerogel_xml_ver3_Tmp_L/"
versionIDstr="3.0"
conversionKey="Left"
fnameInfo="./aerogelDataFromDB/aerogelInfoBis.dat"
fnameMap="./aerogelDataFromDB/aerogelMap.dat"
mkdir -p $outFolder
mkdir -p $outTmpFolder
convertdx2xml_bash $inFolder $inXmlFolder $outFolder $outTmpFolder $versionIDstr $conversionKey $fnameInfo $fnameMap

inFolder="./data/transT_markup_data/dataR/"
inXmlFolder="./data/aerogel_xml_ver3/"
outFolder="./data/aerogel_xml_ver3_R/"
outTmpFolder="./data/aerogel_xml_ver3_Tmp_R/"
versionIDstr="3.0"
conversionKey="Right"
fnameInfo="./aerogelDataFromDB/aerogelInfoBis.dat"
fnameMap="./aerogelDataFromDB/aerogelMap.dat"
mkdir -p $outFolder
mkdir -p $outTmpFolder
convertdx2xml_bash $inFolder $inXmlFolder $outFolder $outTmpFolder $versionIDstr $conversionKey $fnameInfo $fnameMap
