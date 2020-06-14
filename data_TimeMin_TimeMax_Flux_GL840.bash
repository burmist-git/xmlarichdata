#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Wed Nov 14 10:58:31 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function data_TimeMin_TimeMax_Flux_GL840_default_bash {

    delete_data_TimeMin_TimeMax_Flux_GL840_dat
    echo " $filedatadefault" | tee -a $outputDat

}

function data_TimeMin_TimeMax_Flux_GL840_user_bash {

    delete_data_TimeMin_TimeMax_Flux_GL840_dat
    echo " $filedatauser" | tee -a $outputDat

}

function delete_data_TimeMin_TimeMax_Flux_GL840_dat {

    rm -f $outputDat

}

function printHelp {

    echo " --> ERROR in input arguments "
    echo " -d   : default"
    echo " -df  : input flux"
    echo " -dft : input flux input temperature (default time window)"
    echo " -uft : input flux input temperature (user time window)"
    echo " -rm  : delete dat file"
    echo " -p2  : second parameter"

}

outputDat="data_TimeMin_TimeMax_Flux_GL840.dat"

#Wed Nov 14 12:44:17 JST 2018
#filedatauser="         
#                   year  month    day   hour    min    sec
#        timeMin:   2001     10      1     14     49      0
#        timeMax:   2018     11     14      9      0      0
# totalWaterFlux:   $wflux L/min
#    waterTempIn:   $watertemperaturein deg"

#Wed Nov 14 12:44:17 JST 2018
#filedatauser="
#                   year  month    day   hour    min    sec
#        timeMin:   2018     11     14      9      8      0
#        timeMax:   2100     11     14      9      0      0
# totalWaterFlux:   $wflux L/min
#    waterTempIn:   $watertemperaturein deg"

#Fri Nov 16 19:38:23 JST 2018
#filedatauser="
#                   year  month    day   hour    min    sec
#        timeMin:   2000     10      1     14     49      0
#        timeMax:   2018     11     16     15     26      0
# totalWaterFlux:   $wflux L/min
#    waterTempIn:   $watertemperaturein deg"

#Mon Nov 19 16:02:03 JST 2018
filedatauser="
                   year  month    day   hour    min    sec
        timeMin:   2018     11     17      5      0      0
        timeMax:   2100     11     14      9      0      0
 totalWaterFlux:   $wflux L/min
    waterTempIn:   $watertemperaturein deg"

filedatadefault="
                   year  month    day   hour    min    sec
        timeMin:   2000     10      1     14     49      0
        timeMax:   2100     11     14      9      0      0
 totalWaterFlux:   $wflux L/min
    waterTempIn:   $watertemperaturein deg"

wflux=4.4
watertemperaturein=20.0

if [ $# -eq 0 ] 
then
    
    printHelp
    
else

    if [ "$1" = "-d" ]; then
            
        data_TimeMin_TimeMax_Flux_GL840_default_bash
            
    elif [ "$1" = "-df" ]; then

	wflux=$2
        data_TimeMin_TimeMax_Flux_GL840_default_bash

    elif [ "$1" = "-dft" ]; then

	wflux=$2
	watertemperaturein=$3
        data_TimeMin_TimeMax_Flux_GL840_default_bash

    elif [ "$1" = "-uft" ]; then

	wflux=$2
	watertemperaturein=$3
	data_TimeMin_TimeMax_Flux_GL840_user_bash

    elif [ "$1" = "-rm" ]; then
	
	delete_data_TimeMin_TimeMax_Flux_GL840_dat

    elif [ "$1" = "-p2" ]; then
	
	echo " $1 "

    else
        
        printHelp
            
    fi
   
fi
