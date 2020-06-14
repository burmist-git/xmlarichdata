#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Thu Sep 27 19:04:21 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  Program used to convert data fromat of the          #
#                  temperature measurements of the ARICH febs slow     #
#                  control.                                            #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function convertDataFebMergerTemperatureSlowControl_bash {

    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
	nthreads=`nproc --all`
        make cleanconvertDataFebMergerTemperatureSlowControl;
        make -j$nthreads convertDataFebMergerTemperatureSlowControl;
    fi
    
    ./convertDataFebMergerTemperatureSlowControl $1 $2 $3
    
}

#inDataFolder="./dataFebMergerTemperatureSlowControl/2018-09-21/"
#outDataFolder="./dataFebMergerTemperatureSlowControl/2018-09-21_root/"
inDataFolder="./dataFebMergerTemperatureSlowControl/2018-09-30/"
outDataFolder="./dataFebMergerTemperatureSlowControl/2018-09-30_root/"
#inDataFolder="./dataFebMergerTemperatureSlowControl/2018-10-01/"
#outDataFolder="./dataFebMergerTemperatureSlowControl/2018-10-01_root/"

mkdir -p $outDataFolder

fileArr=(
#    "4016.log"
    "4017.log"
    "4018.log"
)

copperBoardIDArr=(
#    4016
    4017
    4018
)

nn=${#fileArr[@]}
let nn=nn-1

for i in `seq 0 $nn`;
do
    
    infile=$inDataFolder${fileArr[$i]}
    copperBoardID=${copperBoardIDArr[$i]}
    outfile=$outDataFolder${fileArr[$i]}".root"
    convertDataFebMergerTemperatureSlowControl_bash $infile $copperBoardID $outfile
    
done
