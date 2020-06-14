#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Tue Oct 17 20:01:01 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script build aerogel tile numbering map.       #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

aerogelTileNumbering(){
    #root -l -b -q "aerogelTileNumbering.C( \"$1\" , \"$2\" )"
    root -l "aerogelTileNumbering.C( \"$1\" , \"$2\" )"
}

outplotsDir="./outplots/"
outputPdf="aerogelTileNumbering.pdf"
outputEps="aerogelTileNumbering.eps"
outputPdfFull=$outplotsDir$outputPdf
outputEpsFull=$outplotsDir$outputEps
mkdir -p $outplotsDir

aerogelTileNumbering $outputPdfFull $outputEpsFull
