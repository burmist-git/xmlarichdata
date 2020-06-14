#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Jun  4 15:13:19 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots the ARICH material budget.        #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function plotARICHmaterialbudget_bash {
    ln -s -f $BELLE2_LOCAL_DIR/arich/utility/scripts/plotARICHmaterialbudget.C plotARICHmaterialbudget.C
    root -l ARICHMaterialScan_Mon_Jun_4_13-41-16_JST_2018.root plotARICHmaterialbudget.C
}

plotARICHmaterialbudget_bash
