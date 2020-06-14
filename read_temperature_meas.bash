#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Tue May  1 22:35:41 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script read txt file with temperature sensor   #
#                  information.                                        #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

read_temperature_meas_bash () {

    make cleanread_temperature_meas; make -j8 read_temperature_meas;
    ./read_temperature_meas $1

}

inFile="temperature_merger.txt"
#inFile="temperature_fpga.txt"
#inFile="temperature_asic.txt"
read_temperature_meas_bash $inFile

#inFile="temperature_merger.txt"
#read_temperature_meas_bash $inFile > temperature_merger_f.txt

#inFile="temperature_fpga.txt"
#read_temperature_meas_bash $inFile > temperature_fpga_f.txt

#inFile="temperature_asic.txt"
#read_temperature_meas_bash $inFile > temperature_asic_f.txt

