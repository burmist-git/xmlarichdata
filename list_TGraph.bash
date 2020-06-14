#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sun Oct 15 20:26:17 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script print list of histograms in given root  #
#                  file and plots almost all the TGraph on same        #
#                  TCanvas.                                            #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

list_TGraph_bash(){
    #make cleanlist_TGraph ; make list_TGraph
    root -l "list_TGraph.C( \"$1\" , \"$2\" , \"$3\" , $4 )"
    #./list_TGraph $1 $2 $3 $4
}

#hname="./rootdata/1st_measurement/aerogel_transmittance_vs_photon_wavelength_1st_measurement.root"
#hname="./rootdata/2nd_measurement/aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root"
hname="./rootdata/aerogel_xml_ver3/aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root"

# histOption = "-v"  <--- Transmitance
# histOption = "!-v" <--- Transmitance Length
histOption="-"
plotsOption="yes"
verboseLevel=0
list_TGraph_bash $hname $histOption $plotsOption $verboseLevel
