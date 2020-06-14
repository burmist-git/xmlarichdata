#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Wed Jun 20 15:54:17 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function toyMC_trg_bash {

    rm -rf toyMC_trg.root ; rm -rf toyMC_trg ; make toyMC_trg ; ./toyMC_trg ; root -l root-util/plots.C

}

toyMC_trg_bash
