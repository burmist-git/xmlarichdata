#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Apr 16 13:48:16 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script builds the xmlarichdata binaries and    #
#                  libraries.                                          #
#                                                                      #
# Input paramete:                                                      #
#                  NON.                                                #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function make_bash {

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    make clean;
    make makedir;
    makelog="Makefile.log"
    rm -rf $makelog
    nthreads=`nproc --all`
    make -j$nthreads -k 2>&1 | tee $makelog
    #make -k 2>&1 | tee $makelog

    nErrors=`grep -i error $makelog | nl | wc -l`     
    nWarnings=`grep -i warning $makelog | nl | wc -l`

    echo "Total number of errors   = $nErrors"
    echo "Total number of warnings = $nWarnings"

    echo "Total number of errors   = $nErrors" >> $makelog
    echo "Total number of warnings = $nWarnings" >> $makelog

    if [ $nErrors -eq 0 ]
    then
	source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
	source setUnsetXMLARICHDATA_Fully_Compiled.bash -p
    else
	source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
	source setUnsetXMLARICHDATA_Fully_Compiled.bash -p
    fi

    #export XMLARICHDATA_Fully_Compiled="yes"
    #echo "XMLARICHDATA_Fully_Compiled = $XMLARICHDATA_Fully_Compiled"

    espeak "I have done"
    
}

make_bash
