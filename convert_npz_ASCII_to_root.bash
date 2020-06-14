#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Fri Jun 15 22:44:39 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots TGraph of memory usage.           #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function convert_npz_ASCII_to_root_bash {
    
    make cleanconvert_npz_ASCII_to_root; 
    make convert_npz_ASCII_to_root;
    ./convert_npz_ASCII_to_root $1

    root -l $1'.root' -e 'gROOT->ProcessLine("c1->Draw()")'

}

function printHelp {
    
    echo " --> ERROR in input arguments "
    echo " Provide input root file "

}

if [ $# -eq 0 ]
then
    
    printHelp 
    
else

    convert_npz_ASCII_to_root_bash $1

fi
