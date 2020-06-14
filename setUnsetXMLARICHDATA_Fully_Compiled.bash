#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Fri Jun  8 16:18:56 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script sets and unset                          #
#                  XMLARICHDATA_Fully_Compiled environment variable.   #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function setXMLARICHDATA_Fully_Compiled {

    export XMLARICHDATA_Fully_Compiled="yes"
    #printState
    
    return 0

}

function unsetXMLARICHDATA_Fully_Compiled {
    
    unset XMLARICHDATA_Fully_Compiled
    #printState

    return 0

}

function printState {

    echo "XMLARICHDATA_Fully_Compiled = $XMLARICHDATA_Fully_Compiled"

    return 0

}

function printHelp { 
 
    echo " --> ERROR in input arguments "
    echo " -s  : set XMLARICHDATA_Fully_Compiled to yes state"
    echo " -u  : unset XMLARICHDATA_Fully_Compiled"
    echo " -p  : print present state"

    return 1

}

if [ $# -eq 0 ]
then
    
    printHelp 
    
else
    if [ "$1" = "-s" ]
    then
	
	setXMLARICHDATA_Fully_Compiled
	
    elif [ "$1" = "-u" ]
    then
	
	unsetXMLARICHDATA_Fully_Compiled

    elif [ "$1" = "-p" ]
    then

	printState
	
    else
	
	printHelp 
	
    fi
fi
