#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Wed Jun  6 17:16:33 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script converts TCanvas with ARICH efficiency  #
#                  produced with                                       #
#                  arich/utility/scripts/plotEfficiency.C to simple    #
#                  root files with histograms.                         #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function plotEfficiencyConvertTCanvasToHist_bash {
    
    root -l -b -q ARICHPerformance.root plotEfficiencyConvertTCanvasToHist.C

}

plotEfficiencyConvertTCanvasToHist_bash
