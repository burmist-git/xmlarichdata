#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Fri Jun 15 22:33:01 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script builds the xmlarichdata binaries and    #
#                  libraries and test the memory usage with            #
#                  b2code-memoryusage.                                 #
#                                                                      #
# Input paramete:                                                      #
#                  NON.                                                #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function make_npz_bash {

    make makedir;
    b2code-memoryusage -m record -i 0.01 -p $1 -- ./make.bash
    #b2code-memoryusage -m plot -p $npzFile -o $2

}

npzFile='./tmp/xmlarichdatacompilation.npz'
pdfFile='./tmp/xmlarichdatacompilation.pdf'

make_npz_bash $npzFile $pdfFile
