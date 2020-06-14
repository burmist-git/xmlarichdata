#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Thu Nov 22 14:17:14 JST 2018                                         #
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

function convert_GL840csv_bash {

    local convertGL840csvbashFile="convertGL840csv.bash"
    local runScript="run_"$convertGL840csvbashFile
    sed "s/18xxxx-xxxxxx/$1/g" $convertGL840csvbashFile > $runScript
    source $runScript
    
}

function runana_GL840_bash {

    local runanaGL840bashFile="runanaGL840.bash"
    local runScript="run_"$runanaGL840bashFile
    sed "s/18xxxx-xxxxxx/$1/g" $runanaGL840bashFile > $runScript
    source data_TimeMin_TimeMax_Flux_GL840.bash -uft $2 $3
    source data_TimeMin_TimeMax_Flux_GL840.bash -uft $2 $3
    source $runScript
    
}

function plotsGL840csv_C {

    local plotsGL840csvCFile="plotsGL840csv.C"
    local runScript="run_"$plotsGL840csvCFile
    sed "s/18xxxx-xxxxxx/$1/g" $plotsGL840csvCFile > $runScript'_tmp'
    sed "s/plotsGL840csv/run_plotsGL840csv/g" $runScript'_tmp' > $runScript
    rm -rf $runScript'_tmp'
    root -l $runScript

}

function plotsGL840csv_Power_C {

    local plotsGL840csvPowerCFile="plotsGL840csv_Power.C"
    local runScript="run_"$plotsGL840csvPowerCFile
    sed "s/18xxxx-xxxxxx/$1/g" $plotsGL840csvPowerCFile > $runScript'_tmp'
    sed "s/plotsGL840csv_Power/run_plotsGL840csv_Power/g" $runScript'_tmp' > $runScript'_tmp''_tmp'
    sed "s/waterFluxXXXX=4.2/waterFluxXXXX=$2/g" $runScript'_tmp''_tmp' > $runScript'_tmp''_tmp''_tmp'
    sed "s/waterTemperatureXXXX=20.0/waterTemperatureXXXX=$3/g" $runScript'_tmp''_tmp''_tmp' > $runScript
    rm -rf $runScript'_tmp' $runScript'_tmp''_tmp' $runScript'_tmp''_tmp''_tmp'
    root -l $runScript

}
    
function printHelp {

    echo " --> ERROR in input arguments "
    echo " -d  : default"
    echo " -p2 : second parameter"

}

infile="181212-103234"
waterflow="4.2"
watertemperature="24.0" 

if [ $# -eq 0 ] 
then
    
    printHelp
    
else

    if [ "$1" = "-d" ]; then
            
        #convert_analyse_plot_GL840csv_bash
	convert_GL840csv_bash $infile 
	runana_GL840_bash $infile $waterflow $watertemperature
	plotsGL840csv_C $infile
	plotsGL840csv_Power_C $infile $waterflow $watertemperature
	
    elif [ "$1" = "-p2" ]; then
	
	echo " $1 "
    else
        
        printHelp
            
    fi
   
fi
