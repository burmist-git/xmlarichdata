#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Wed Nov 22 01:38:26 CET 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots TGraph from given root file and   #
#                  fit transmission length.                            #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

fitAbsorptionLength_CLING_bash(){

    root -l "fitAbsorptionLength.C( \"$1\" , \"$2\" , \"$3\" , \"$4\", $5 )"

}

fitAbsorptionLength_bash(){

    make cleanfitAbsorptionLength ; make -j8 fitAbsorptionLength
    fileN=$1
    histN1=$2
    histN2=$3
    pdfFolder=$4
    dX=$5
    ./fitAbsorptionLength $fileN $histN1 $histN2 $pdfFolder $dX

}

#fileN="./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root"
fileN="./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root"
#aerogelInfoMapBis="./aerogelDataFromDB/aerogelInfoMapBis.dat"
aerogelInfoMapBis="./aerogelDataFromDB/aerogelInfoMap.dat"
histSufix="A088"
histN1="gr_"$histSufix
histN2="gr_"$histSufix"_trLength"
pdfFolder="./pdfdatatmp/"
#dX=2.03
dX=`more $aerogelInfoMapBis | grep $histSufix | awk '{print $10}'`
mkdir -p $pdfFolder
fitAbsorptionLength_CLING_bash $fileN $histN1 $histN2 $pdfFolder $dX
#fitAbsorptionLength_bash $fileN $histN1 $histN2 $pdfFolder $dX
