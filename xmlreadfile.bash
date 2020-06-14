#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Wed Oct 18 23:05:53 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script runs xmlreadfile.C - xml to data        #
#                  convertor.                                          #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

make cleanxmlreadfile; make xmlreadfile

xmlreadfile_bash(){

    ./xmlreadfile $1

}

inxmlfile="./TabataSan/CAd12-28wjt_l_database.xml"
xmlreadfile_bash $inxmlfile
inxmlfile="./TabataSan/CAd12-28wjt_r_database.xml"
xmlreadfile_bash $inxmlfile
