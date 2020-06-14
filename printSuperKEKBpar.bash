#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sun Jun 24 11:42:15 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script print the SUperKEK B machine parameters #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function printSuperKEKBpar_bash {

    make cleanprintSuperKEKBpar; make printSuperKEKBpar;
    ./printSuperKEKBpar

}

printSuperKEKBpar_bash
