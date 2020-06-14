#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sat Jun 16 01:26:43 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script plots memory usage measured with        #
#                  b2code-memoryusage for a given proces.              #
#                                                                      #
# Input paramete:                                                      #
#                  NON.                                                #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function plot_proc_memory_bash {

    python3 convert_npz_to_ASCII.py -f $npzFile -a $proc
    source convert_npz_ASCII_to_root.bash $npzFile'_'$proc'.dat'

}

#npzFile='./tmp/xmlarichdatacompilation.npz'
npzFile='./tmp/ARICHStandAlone_memoryusage.npz'
#npzFile='./tmp/ARICHStandAlone_memoryusageTess.npz'
proc='total_memory'
#proc='15480'
plot_proc_memory_bash
