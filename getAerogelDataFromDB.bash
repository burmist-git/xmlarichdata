#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Oct 16 20:10:05 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script pull ARICH data from DB.                #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
then
    make cleanreadAerogelInfoMap; make readAerogelInfoMap
fi

aerDataFol="./aerogelDataFromDB/"
aerogelInfo="aerogelInfo"
aerogelMap="aerogelMap"
aerInfoFile="aerogelInfo.dat"
aerMapFile="aerogelMap.dat"
aerInfoMapFile="aerogelInfoMap.dat"
aerInfoFileFull=$aerDataFol$aerInfoFile
aerMapFileFull=$aerDataFol$aerMapFile
aerInfoMapFull=$aerDataFol$aerInfoMapFile
rm -rf $aerDataFol
mkdir -p $aerDataFol

ifBASF2isOK(){
    if [ -z "$BELLE2_LOCAL_DIR" ]; then
	echo " Please setup BASF2 framework "
	echo " For leonid@nb-gred02 : source setupBasf2my.bash "
	return 1
    fi  
    return 0   
}

getAerogelDataFromDB(){
    aerogelOutF=$1
    aerFileFull=$2
    rm -f $aerFileFull
    echo " ---> Getting  : $aerogelOutF"
    basf2 ARICHDatabaseImporter_condDB.py -- -c $aerogelOutF | grep -v Steering | grep -v processing, | tee $aerFileFull".tmp" > /dev/null
    sed 's/,/ /g' $aerFileFull".tmp" > $aerFileFull
    echo "               : $aerFileFull"
    rm $aerFileFull".tmp"
}

ifBASF2isOK
checkStatus=$(echo $?)
#echo $checkStatus

if [ "$checkStatus" -eq 0 ]
then
    getAerogelDataFromDB $aerogelInfo $aerInfoFileFull
    getAerogelDataFromDB $aerogelMap $aerMapFileFull
    rm -f $aerInfoMapFull
    echo " ---> Writting : $aerInfoMapFull"
    ./readAerogelInfoMap $aerInfoFileFull $aerMapFileFull | tee $aerInfoMapFull > /dev/null
fi
