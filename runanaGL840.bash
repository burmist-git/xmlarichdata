#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Tue Mar  6 20:15:29 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                 This script run the analysis class.                  #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

function runanaGL840_bash {

    source setUnsetXMLARICHDATA_Fully_Compiled.bash -s
    #source setUnsetXMLARICHDATA_Fully_Compiled.bash -u
    if [ "$XMLARICHDATA_Fully_Compiled" = "" ]
    then
        make cleanDictLib;
        make -j`nproc --all` libxmlarichdataDict.cxx;
        make -j`nproc --all` libxmlarichdataDictLib.so;      
    fi
    
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/180929-154859.CSV.CV.root\",\"./dataGL840/180929-154859.CSV.CV.root_hist.root\", 1)");'

    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/180929-154859.CSV.CV.root\",\"./dataGL840/180929-154859.CSV.CV.root_hist.root\", 1)");'

    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/180930-173053.CSV.CV.root\",\"./dataGL840/180930-173053.CSV.CV.root_hist.root\", 1)");'

    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181001-205815.CSV.CV.root\",\"./dataGL840/181001-205815.CSV.CV.root_hist.root\", 10)");'

    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181009-103656.CSV.CV.root\",\"./dataGL840/181009-103656.CSV.CV.root_hist.root\", 1)");'

    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181009-103725.CSV.CV.root\",\"./dataGL840/181009-103725.CSV.CV.root_hist.root\", 1)");'

    #Wed Oct 17 13:50:46 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181016-152600.CSV.CV.root\",\"./dataGL840/181016-152600.CSV.CV.root_hist.root\", 1)");'

    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181016-152638.CSV.CV.root\",\"./dataGL840/181016-152638.CSV.CV.root_hist.root\", 1)");'

    #Thu Oct 18 11:51:13 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181017-135745.CSV.CV.root\",\"./dataGL840/181017-135745.CSV.CV.root_hist.root\", 1)");'

    #Fri Oct 19 11:39:48 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181018-114805.CSV.CV.root\",\"./dataGL840/181018-114805.CSV.CV.root_hist.root\", 1)");'

    #Sat Oct 20 14:58:19 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181019-113654.CSV.CV.root\",\"./dataGL840/181019-113654.CSV.CV.root_hist.root\", 1)");'

    #Mon Oct 22 10:28:53 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181021-102515.CSV.CV.root\",\"./dataGL840/181021-102515.CSV.CV.root_hist.root\", 1)");'

    #Mon Oct 22 10:28:53 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181021-103202.CSV.CV.root\",\"./dataGL840/181021-103202.CSV.CV.root_hist.root\", 1)");'

    #Mon Oct 22 21:10:06 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(0,\"./rootFileList_181017-135745_181018-114805.dat\",\"./dataGL840/181017-135745_181018-114805.root_hist.root\", 1)");'

    #Tue Oct 23 11:12:29 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181022-102002.CSV.CV.root\",\"./dataGL840/181022-102002.CSV.CV.root_hist.root\", 1)");'

    #Wed Oct 24 10:18:14 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181023-114623.CSV.CV.root\",\"./dataGL840/181023-114623.CSV.CV.root_hist.root\", 1)");'

    #Mon Oct 29 15:08:14 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181024-104333.CSV.CV.root\",\"./dataGL840/181023-114623.CSV.CV.root_hist.root\", 1)");'

    #Tue Oct 30 10:53:18 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181028-155231.CSV.CV.root\",\"./dataGL840/181028-155231.CSV.CV.root_hist.root\", 1)");'

    #Wed Oct 31 09:42:10 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181030-103737.CSV.CV.root\",\"./dataGL840/181030-103737.CSV.CV.root_hist.root\", 1)");'

    #Thu Nov  1 10:20:20 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181031-093942.CSV.CV.root\",\"./dataGL840/181031-093942.CSV.CV.root_hist.root\", 1)");'

    #Fri Nov  2 10:22:22 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181101-101800.CSV.CV.root\",\"./dataGL840/181101-101800.CSV.CV.root_hist.root\", 1)");'

    #Fri Nov  2 16:34:01 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181102-103714.CSV.CV.root\",\"./dataGL840/181102-103714.CSV.CV.root_hist.root\", 1)");'

    #Sat Nov  3 10:09:51 JST 2018
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181102-164133.CSV.CV.root\",\"./dataGL840/181102-164133.CSV.CV.root_hist.root\", 1)");'

    #Sun Nov  4 11:14:46 JST 2018 
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181103-103418.CSV.CV.root\",\"./dataGL840/181103-103418.CSV.CV.root_hist.root\", 1)");'

    #Mon Nov  5 10:34:24 JST 2018 --> 10 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181104-113624.CSV.CV.root\",\"./dataGL840/181104-113624.CSV.CV.root_hist.root\", 1)");'

    #Mon Nov  5 22:33:56 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181105-204034.CSV.CV.root\",\"./dataGL840/181105-204034.CSV.CV.root_hist.root\", 1)");'

    #Tue Nov  6 16:27:54 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181105-205453.CSV.CV.root\",\"./dataGL840/181105-205453.CSV.CV.root_hist.root\", 1)");'

    #Tue Nov  6 16:27:54 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181106-101526.CSV.CV.root\",\"./dataGL840/181106-101526.CSV.CV.root_hist.root\", 1)");'

    # Wed Nov  7 10:12:54 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181106-124017.CSV.CV.root\",\"./dataGL840/181106-124017.CSV.CV.root_hist.root\", 1)");'

    # Thu Nov  8 10:04:36 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181107-102520.CSV.CV.root\",\"./dataGL840/181107-102520.CSV.CV.root_hist.root\", 1)");'

    # Fri Nov  9 11:32:13 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181108-104031.CSV.CV.root\",\"./dataGL840/181108-104031.CSV.CV.root_hist.root\", 1)");'

    # Sat Nov 10 11:28:01 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181109-114941.CSV.CV.root\",\"./dataGL840/181109-114941.CSV.CV.root_hist.root\", 1)");'

    # Sun Nov 11 13:55:50 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181110-112429.CSV.CV.root\",\"./dataGL840/181110-112429.CSV.CV.root_hist.root\", 1)");'

    # Mon Nov 12 10:07:31 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181111-115956.CSV.CV.root\",\"./dataGL840/181111-115956.CSV.CV.root_hist.root\", 1)");'

    # Tue Nov 13 11:10:07 JST 2018 --> 20 channels
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181112-095812.CSV.CV.root\",\"./dataGL840/181112-095812.CSV.CV.root_hist.root\", 1)");'

    # Wed Nov 14 10:24:14 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -d
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181113-110656.CSV.CV.root\",\"./dataGL840/181113-110656.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Thu Nov 15 10:31:27 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -d
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181114-105537.CSV.CV.root\",\"./dataGL840/181114-105537.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Fri Nov 16 11:28:41 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -df 3.2
    #source data_TimeMin_TimeMax_Flux_GL840.bash -df 3.2
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181115-103156.CSV.CV.root\",\"./dataGL840/181115-103156.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Sat Nov 17 11:36:48 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
    #source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181116-155044.CSV.CV.root\",\"./dataGL840/181116-155044.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Sun Nov 18 14:31:52 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
    #source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181117-113241.CSV.CV.root\",\"./dataGL840/181117-113241.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Mon Nov 19 10:00:07 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
    #source data_TimeMin_TimeMax_Flux_GL840.bash -dft 4.2 20.0
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181118-134000.CSV.CV.root\",\"./dataGL840/181118-134000.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Mon Nov 19 15:48:13 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
    #source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(0,\"./rootFileList_181116-155044_181118-134000.dat\",\"./dataGL840/181116-155044_181118-134000.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Tue Nov 20 11:52:27 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
    #source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181119-095824.CSV.CV.root\",\"./dataGL840/181119-095824.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Wed Nov 21 15:59:15 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
    #source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181120-111524.CSV.CV.root\",\"./dataGL840/181120-111524.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    # Thu Nov 22 11:43:41 JST 2018 --> 20 channels
    #source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
    #source data_TimeMin_TimeMax_Flux_GL840.bash -uft 4.2 20.0
    #root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/181121-160847.CSV.CV.root\",\"./dataGL840/181121-160847.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

    #Thu Nov 22 15:43:54 JST 2018
    root -l -q -e 'gROOT->ProcessLine(".L libxmlarichdataDict.cxx"); gROOT->ProcessLine(".L libxmlarichdataDictLib.so"); gROOT->ProcessLine("xmlarichdata::runanaGL840(1,\"./dataGL840/18xxxx-xxxxxx.CSV.CV.root\",\"./dataGL840/18xxxx-xxxxxx.CSV.CV.root_hist.root\", 1,\"./data_TimeMin_TimeMax_Flux_GL840.dat\")");'

}

runanaGL840_bash
