#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Thu Sep 27 19:04:21 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  Program used to convert data from GL840 temperature #
#                  monitor module.                                     #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function convertDataFormat_bash {

    filename=$1
    outfilename=$2
    sed 's/:/ /g' $filename > $filename"_01"
    sed 's/,/ /g' $filename"_01" > $filename"_02"
    sed 's/-/ /g' $filename"_02" > $filename"_03"
    sed 's/+++++++/11/g' $filename"_03" > $filename"_04"
    sed 's/+/ /g' $filename"_04" > $filename"_05"
    sed 's/BURNOUT/10/g' $filename"_05" > $filename"_06"
    sed 's/\x2F/\x20/g' $filename"_06" > $filename"_07"
    mv $filename"_07" $outfilename
    rm $filename"_01" $filename"_02" $filename"_03" $filename"_04" $filename"_05" $filename"_06"
    
}

function convertGL840csv_bash {

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
        nthreads=`nproc --all`
        make cleanconvertGL840csv;
        make -j$nthreads convertGL840csv;
    fi    
    
    ./convertGL840csv $1 $2 $3 | tee $3".log"
    echo "----------------------------"
    tail -n 1 $2 | sed 's/,/ /g' | awk '{ print "Expected  : "$1"           |"}'
    echo "----------------------------"
    
}

# Old befor Tue Oct 16 14:23:45 JST 2018
#inDataFileNameArr=(
#    "180929-150135.CSV"
#    "180929-154859.CSV"
#    "180929-231011.CSV"
#    "180930-173053.CSV"
#)

# Tue Oct 16 14:23:45 JST 2018
# 653914 --> 181001-205815
# 11     --> 181009-103656
# 61799  --> 181009-103725
#inDataFileNameArr=(
#    "181001-205815.CSV"
#    "181009-103656.CSV"
#    "181009-103725.CSV"
#)

# Wed Oct 17 13:50:46 JST 2018
# 1    --> 181016-152600
# 7990 --> 181016-152638
#inDataFileNameArr=(
#    "181016-152600.CSV"
#    "181016-152638.CSV"
#)

# Thu Oct 18 11:48:59 JST 2018
# 7843 --> 181017-135745
#inDataFileNameArr=(
#    "181017-135745.CSV"
#)

# Fri Oct 19 11:38:08 JST 2018
# 8538 --> 181018-114805
#inDataFileNameArr=(
#    "181018-114805.CSV"
#)

# Sat Oct 20 14:56:14 JST 2018
# 9787 --> 181019-113654
#inDataFileNameArr=(
#    "181019-113654.CSV"
#)

# Mon Oct 22 10:24:08 JST 2018
# 1    --> 181021-102515
# 8519 --> 181021-103202
#inDataFileNameArr=(
#    "181021-102515.CSV"
#    "181021-103202.CSV"
#)

# Tue Oct 23 11:07:11 JST 2018
# 8845 --> 181022-102002
#inDataFileNameArr=(
#    "181022-102002.CSV"
#)

# Wed Oct 24 10:16:40 JST 2018 
# 8066 --> 181023-114623
#inDataFileNameArr=(
#    "181023-114623.CSV"
#)

# Mon Oct 29 15:02:07 JST 2018 
# 36383 --> 181024-104333
#inDataFileNameArr=(
#    "181024-104333.CSV"
#)

# Tue Oct 30 10:39:17 JST 2018 
# 15372 --> 181028-155231
#inDataFileNameArr=(
#    "181028-155231.CSV"
#)

# Wed Oct 31 09:41:16 JST 2018 
# 8211 --> 181030-103737
#inDataFileNameArr=(
#    "181030-103737.CSV"
#)

# Thu Nov  1 10:20:20 JST 2018 
# 8772 --> 181031-093942
#inDataFileNameArr=(
#    "181031-093942.CSV"
#)

# Fri Nov  2 10:22:22 JST 2018 
# 8528 --> 181101-101800
#inDataFileNameArr=(
#    "181101-101800.CSV"
#)

# Fri Nov  2 16:32:25 JST 2018 
# 2120 --> 181102-103714
#inDataFileNameArr=(
#    "181102-103714.CSV"
#)

# Sat Nov  3 10:09:51 JST 2018 
# 6267 --> 181102-164133
#inDataFileNameArr=(
#    "181102-164133.CSV"
#)

# Sun Nov  4 11:14:46 JST 2018 
# 8856 --> 181103-103418
#inDataFileNameArr=(
#    "181103-103418.CSV"
#)

# Mon Nov  5 10:34:24 JST 2018 
# 8145 --> 181104-113624
#inDataFileNameArr=(
#    "181104-113624.CSV"
#)

# Mon Nov  5 22:26:09 JST 2018 
# 243 --> 181104-113624
#inDataFileNameArr=(
#    "181105-204034.CSV"
#)

# Tue Nov  6 16:11:09 JST 2018
# 4748 --> 181105-205453
# 618  --> 181106-101526
#inDataFileNameArr=(
#    "181105-205453.CSV"
#    "181106-101526.CSV"
#)

# Wed Nov  7 10:12:54 JST 2018
# 4938 --> 181106-124017
#inDataFileNameArr=(
#    "181106-124017.CSV"
#)

# Thu Nov  8 10:04:36 JST 2018
# 8473 --> 181107-102520
#inDataFileNameArr=(
#    "181107-102520.CSV"
#)

# Fri Nov  9 11:32:13 JST 2018
# 8927 --> 181108-104031
#inDataFileNameArr=(
#    "181108-104031.CSV"
#)

# Sat Nov 10 11:28:01 JST 2018
# 8465 --> 181109-114941
#inDataFileNameArr=(
#    "181109-114941.CSV"
#)

# Sun Nov 11 13:55:50 JST 2018
# 8789 --> 181110-112429
#inDataFileNameArr=(
#    "181110-112429.CSV"
#)

# Mon Nov 12 10:07:31 JST 2018
# 7890 --> 181111-115956
#inDataFileNameArr=(
#    "181111-115956.CSV"
#)

# Tue Nov 13 11:10:07 JST 2018
# 9043 --> 181112-095812
#inDataFileNameArr=(
#    "181112-095812.CSV"
#)

# Wed Nov 14 10:24:14 JST 2018
# 8258 --> 181113-110656
#inDataFileNameArr=(
#    "181113-110656.CSV"
#)

# Thu Nov 15 10:31:27 JST 2018
# 8482 --> 181114-105537
#inDataFileNameArr=(
#    "181114-105537.CSV"
#)

# Fri Nov 16 11:28:41 JST 2018
# 8946 --> 181115-103156
#inDataFileNameArr=(
#    "181115-103156.CSV"
#)

# Fri Nov 16 16:39:41 JST 2018
# 1587 --> 181116-112357
#inDataFileNameArr=(
#    "181116-112357.CSV"
#)

# Sat Nov 17 11:36:48 JST 2018
# 7083 --> 181116-155044
#inDataFileNameArr=(
#    "181116-155044.CSV"
#)

# Sun Nov 18 14:31:52 JST 2018
# 9252 --> 181117-113241
#inDataFileNameArr=(
#    "181117-113241.CSV"
#)

# Mon Nov 19 10:00:07 JST 2018
# 7303 --> 181118-134000
#inDataFileNameArr=(
#    "181118-134000.CSV"
#)

# Tue Nov 20 11:52:27 JST 2018
# 9088 --> 181119-095824
#inDataFileNameArr=(
#    "181119-095824.CSV"
#)

# Wed Nov 21 15:59:15 JST 2018
# 1716 --> 181120-111524
#inDataFileNameArr=(
#    "181120-111524.CSV"
#)

# Thu Nov 22 11:43:41 JST 2018
# 1168 --> 181121-160847
#inDataFileNameArr=(
#    "181121-160847.CSV"
#)

# Thu Nov 22 14:24:20 JST 2018
inDataFileNameArr=(
    "18xxxx-xxxxxx.CSV"
)

rawDataFolder="./dataGL840/"

nn=${#inDataFileNameArr[@]}
let nn=nn-1

for i in `seq 0 $nn`;
do
    fileIn=$rawDataFolder${inDataFileNameArr[$i]}
    fileOut=$fileIn".CV"
    echo $fileIn
    echo $fileOut

    nchannels=`more $fileIn | grep 'TEMP,TC_K,100degC' | wc -l`
    branchName=`git branch | grep '*' | awk {' print $2'}`

    echo $nchannels
    echo $branchName

    # Master branch for 20 channels:
    if [ "$branchName" = "master" ]
    then
	if [ "$nchannels" = "20" ]
	then
	    convertDataFormat_bash $fileIn $fileOut
	    rootFileOut=$fileOut".root"
	    convertGL840csv_bash 0 $fileOut $rootFileOut | tee $rootFileOut".log"
	else
	    echo "ERROR --> branchName = $branchName"
	    echo "           nchannels = $nchannels"
	    echo "           Please change to the v1_GL840 branch"
	fi	    
    fi

    # v1_GL840 branch for 10 channels:
    if [ "$branchName" = "v1_GL840" ]
    then
	if [ "$nchannels" = "10" ]
	then
	    convertDataFormat_bash $fileIn $fileOut
	    rootFileOut=$fileOut".root"
	    convertGL840csv_bash 0 $fileOut $rootFileOut | tee $rootFileOut".log"
	else
	    echo "ERROR --> branchName = $branchName"
	    echo "           nchannels = $nchannels"
	    echo "           Please change to the master branch"
	fi	    
    fi
    
done
