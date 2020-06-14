#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Jun  4 14:24:02 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script print the ARICH number of channels      #
#                  chips, HAPD, mergers and sector information.        #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function listOfMaterials_bash {

    root -l -b -q "listOfMaterials.C(\"$1\")" | grep TH2D | grep -v _lambda | awk '{print $4}' | grep -v All_Materials | nl | sed 's/_x0//g' | sed 's/_/ /g'

}

listOfMaterials_bash 'ARICHMaterialScan_Mon_Jun_4_13-41-16_JST_2018.root'
#listOfMaterials_bash 'ARICHMaterialScan.root'
