#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Thu Oct 11 10:52:09 JST 2018                                         #
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

function setUnsetXMLARICHDATA_env_var_bash {

    xmlarichdataHome="$PWD"
    export XMLARICHDATAHOME=$xmlarichdataHome
    export XMLARICHDATA_INCLUDE_DIR="$XMLARICHDATAHOME/include/"
    export XMLARICHDATA_LIB="$XMLARICHDATAHOME/lib/"
    export XMLARICHDATA_BASF2_INCLUDE="/home/burmist/home2/KEK/releases/head_01.10.2018/include/"
    
    echo " "
    echo "XMLARICHDATAHOME           = $XMLARICHDATAHOME"
    echo "XMLARICHDATA_INCLUDE_DIR   = $XMLARICHDATA_INCLUDE_DIR"    
    echo "XMLARICHDATA_LIB           = $XMLARICHDATA_LIB"
    echo "XMLARICHDATA_BASF2_INCLUDE = $XMLARICHDATA_BASF2_INCLUDE"
    echo " "

    checkIfaDirectoryExists $XMLARICHDATA_BASF2_INCLUDE
}

function setUpRoot60806 {

    useroot60806

    export ROOT_INCLUDE_DIR="$ROOTSYS/include/root/"
    export ROOT_LIB="$ROOTSYS/lib/root/"
    
    echo " "
    echo "ROOTSYS                    = $ROOTSYS"
    echo "ROOT_INCLUDE_DIR           = $ROOT_INCLUDE_DIR"    
    echo "ROOT_LIB                   = $ROOT_LIB"
    echo " "
    
}

function setGeant41004 {

    usegeant41004
    
    echo " "
    echo "G4INSTALL                  = $G4INSTALL"
    echo "G4INCLUDE                  = $G4INCLUDE"    
    echo "G4LIB                      = $G4LIB"
    echo " "

}

function checkIfaDirectoryExists {

    [ ! -d "$1" ] && echo "ERROR --> directory $1 DOES NOTexists."
    
}


function printHelp {

    echo " --> ERROR in input arguments "
    echo " -d : setup xmlarich lib environment variables "
    echo " -a : setup xmlarich, root (v6.08.06) and geant4 (10.04.p02) environment variables"
    
}

if [ $# -eq 0 ] 
then
    
    printHelp
    
else

    if [ "$1" = "-d" ]; then
        
        setUnsetXMLARICHDATA_env_var_bash
        
    elif [ "$1" = "-a" ]; then

	setUnsetXMLARICHDATA_env_var_bash
	setUpRoot60806
	setGeant41004
	
    else
        
        printHelp
            
    fi
   
fi
