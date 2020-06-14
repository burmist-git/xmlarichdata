#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Thu Nov 23 19:46:55 CET 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script fits transmition length fuctions.       #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

#fitAllAbsLen_CLING_bash(){
#root -l "fitAllAbsLen.C( \"$1\" , \"$2\" , \"$3\" , \"$4\", $5 )"
#}

make cleanfitAllAbsLen; make -j8 fitAllAbsLen    

fitAllAbsLen_bash(){

    fileN=$1
    fnameInfo=$2
    fnameMap=$3
    pdfFolder=$4
    outFname=$5
    outXMLfile=$6
    version=$7
    fitAllAbsLenLog=$8
    ./fitAllAbsLen $fileN $fnameInfo $fnameMap $pdfFolder $outFname $outXMLfile $version | tee $fitAllAbsLenLog > /dev/null

}

fileN="./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root"
fnameInfo="./aerogelDataFromDB/aerogelInfoBis.dat"
fnameMap="./aerogelDataFromDB/aerogelMap.dat"
pdfFolder="./pdfdataFit/aerogel_xml_ver3/"
outFname="./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3_fit.root"
outXMLFolder="./xmlData/aerogel_xml_ver3/"
outXMLfile="./xmlData/aerogel_xml_ver3/aerogel_xml_ver3_fit.xml"
version="3.0"
fitAllAbsLenLog="fitAllAbsLen"$version".log"
mkdir -p $pdfFolder
mkdir -p $outXMLFolder
fitAllAbsLen_bash $fileN $fnameInfo $fnameMap $pdfFolder $outFname $outXMLfile $version $fitAllAbsLenLog
echo "Output Histos file ---> $outFname";


fileN="./rootdata/aerogel_xml_ver3_L/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3_L.root"
fnameInfo="./aerogelDataFromDB/aerogelInfoBis.dat"
fnameMap="./aerogelDataFromDB/aerogelMap.dat"
pdfFolder="./pdfdataFit/aerogel_xml_ver3_L/"
outFname="./rootdata/aerogel_xml_ver3_L/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3_L_fit.root"
outXMLFolder="./xmlData/aerogel_xml_ver3_L/"
outXMLfile="./xmlData/aerogel_xml_ver3_L/aerogel_xml_ver3_L_fit.xml"
version="3.0"
fitAllAbsLenLog="fitAllAbsLen"$version"_L.log"
mkdir -p $pdfFolder
mkdir -p $outXMLFolder
fitAllAbsLen_bash $fileN $fnameInfo $fnameMap $pdfFolder $outFname $outXMLfile $version $fitAllAbsLenLog
echo "Output Histos file ---> $outFname";


fileN="./rootdata/aerogel_xml_ver3_R/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3_R.root"
fnameInfo="./aerogelDataFromDB/aerogelInfoBis.dat"
fnameMap="./aerogelDataFromDB/aerogelMap.dat"
pdfFolder="./pdfdataFit/aerogel_xml_ver3_R/"
outFname="./rootdata/aerogel_xml_ver3_R/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3_R_fit.root"
outXMLFolder="./xmlData/aerogel_xml_ver3_R/"
outXMLfile="./xmlData/aerogel_xml_ver3_R/aerogel_xml_ver3_R_fit.xml"
version="3.0"
fitAllAbsLenLog="fitAllAbsLen"$version"_R.log"
mkdir -p $pdfFolder
mkdir -p $outXMLFolder
fitAllAbsLen_bash $fileN $fnameInfo $fnameMap $pdfFolder $outFname $outXMLfile $version $fitAllAbsLenLog
echo "Output Histos file ---> $outFname";

#grep chisquare $fitAllAbsLenLog | awk '{if($2>60){{print }}}'
#grep trLengthDiff $fitAllAbsLenLog 
