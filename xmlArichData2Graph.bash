#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Oct  9 03:58:11 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  Program used to convert xml data into TGraph        #
#                  and store them in one root file.                    #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
then
    make cleanxmlArichData2Graph ; make xmlArichData2Graph
fi


xmlArichData2Graph_bash(){

    ./xmlArichData2Graph $1 $2 $3 $4 $5 $6
    #root -l -b -q "xmlArichData2Graph.C( \"$1\" , \"$2\" , \"$3\" , \"$4\" , $5, $6 )"

}

#####################################
filePathXML="./data/1st_measurement/"
filenameXMLList="./data/1st_measurement/AerogelData.xml"
outRootFolder="./rootdata/1st_measurement/"
mkdir -p $outRootFolder
fnameroot="$outRootFolder/aerogel_transmittance_vs_photon_wavelength_1st_measurement.root"
differencesDetailsFilePath="./dataDiffInfo/1st_measurement/"
mkdir -p $differencesDetailsFilePath
differencesDetailsFileName=$differencesDetailsFilePath"differencesDetails.dat"
rm -f $differencesDetailsFileName
normAVal=178.0
normBVal=179.0
xmlArichData2Graph_bash $filePathXML $filenameXMLList $fnameroot $differencesDetailsFileName $normAVal $normBVal
#####################################

#####################################
filePathXML="./data/2nd_measurement/"
filenameXMLList="./data/2nd_measurement/AerogelData.xml"
outRootFolder="./rootdata/2nd_measurement/"
mkdir -p $outRootFolder
fnameroot="$outRootFolder/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root"
differencesDetailsFilePath="./dataDiffInfo/2nd_measurement/"
mkdir -p $differencesDetailsFilePath
differencesDetailsFileName=$differencesDetailsFilePath"differencesDetails.dat"
rm -f $differencesDetailsFileName
normAVal=171.0
normBVal=169.0
xmlArichData2Graph_bash $filePathXML $filenameXMLList $fnameroot $differencesDetailsFileName $normAVal $normBVal
#####################################

#####################################
filePathXML="./data/aerogel_xml_ver3/"
filenameXMLList="./data/aerogel_xml_ver3/AerogelData.xml"
outRootFolder="./rootdata/aerogel_xml_ver3/"
mkdir -p $outRootFolder
fnameroot="$outRootFolder/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root"
differencesDetailsFilePath="./dataDiffInfo/aerogel_xml_ver3/"
mkdir -p $differencesDetailsFilePath
differencesDetailsFileName=$differencesDetailsFilePath"differencesDetails.dat"
rm -f $differencesDetailsFileName
normAVal=124.0
normBVal=124.0
xmlArichData2Graph_bash $filePathXML $filenameXMLList $fnameroot $differencesDetailsFileName $normAVal $normBVal
#####################################

#####################################
filePathXML="./data/aerogel_xml_ver3_L/"
filenameXMLList="./data/aerogel_xml_ver3_L/AerogelData.xml"
outRootFolder="./rootdata/aerogel_xml_ver3_L/"
mkdir -p $outRootFolder
fnameroot="$outRootFolder/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3_L.root"
differencesDetailsFilePath="./dataDiffInfo/aerogel_xml_ver3_L/"
mkdir -p $differencesDetailsFilePath
differencesDetailsFileName=$differencesDetailsFilePath"differencesDetails.dat"
rm -f $differencesDetailsFileName
normAVal=124.0
normBVal=124.0
xmlArichData2Graph_bash $filePathXML $filenameXMLList $fnameroot $differencesDetailsFileName $normAVal $normBVal
#####################################

#####################################
filePathXML="./data/aerogel_xml_ver3_R/"
filenameXMLList="./data/aerogel_xml_ver3_R/AerogelData.xml"
outRootFolder="./rootdata/aerogel_xml_ver3_R/"
mkdir -p $outRootFolder
fnameroot="$outRootFolder/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3_R.root"
differencesDetailsFilePath="./dataDiffInfo/aerogel_xml_ver3_R/"
mkdir -p $differencesDetailsFilePath
differencesDetailsFileName=$differencesDetailsFilePath"differencesDetails.dat"
rm -f $differencesDetailsFileName
normAVal=124.0
normBVal=124.0
xmlArichData2Graph_bash $filePathXML $filenameXMLList $fnameroot $differencesDetailsFileName $normAVal $normBVal
#####################################
