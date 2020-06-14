#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Mon Oct  9 03:58:11 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  This script generates pdf files from root TGraph.   #
#                  pdf files containe transmittance vs photon          #
#                  wavelength for ARICH aerogel tiles.                 #
#                                                                      #
# Input paramete:                                                      #
#                   NON.                                               #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

make cleanlist_TGraph ; make list_TGraph
make cleanplots ; make plots

get_pdf_loop(){
    pdfFolder=$2
    pdfOutFile=$3
    fnamerootPath=$4
    fnameroot=$5
    verboseLevel=$6
    histList=$fnamerootPath"histList.dat"
    mkdir -p $pdfFolder
    ./list_TGraph $fnameroot $1 "no" $verboseLevel | grep Histo | grep found: | grep -v _norm  | grep -v _TrL_ | grep $1 trLength | awk '{print $4}' | tee $histList > /dev/null
    #return 0
    #root -l -b -q "list_TGraph.C( \"$fnameroot\" , \"$1\" , \"no\" )" | grep Histo | grep found: | grep -v _norm | grep -v _TrL_ | grep $1 trLength | awk '{print $4}' | tee $histList > /dev/null
    singlePlotPdfList=""
    while read -r line
    do
	histName="$line"
	#root -l -b -q "plots.C( \"$fnameroot\" , \"$histName\", \"$pdfFolder\", \"$1\" )" > /dev/null
	./plots $fnameroot $histName $pdfFolder $1 > /dev/null
	singlePlotPdfList="$singlePlotPdfList $pdfFolder$histName.pdf"
    done < "$histList"
    echo "-> merge single pdf : $pdfOutFile"
    gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$pdfOutFile $singlePlotPdfList
    return 0
}

get_pdf_xargs(){
    pdfFolder=$2
    pdfOutFile=$3
    fnamerootPath=$4
    fnameroot=$5
    verboseLevel=$6
    histList=$fnamerootPath"histList.dat"
    histListPdf=$fnamerootPath"histListPdf.dat"
    rm -f $histListPdf
    mkdir -p $pdfFolder
    ./list_TGraph $fnameroot $1 "no" $verboseLevel | grep Histo | grep found: | grep -v _norm | grep -v _TrL_ | grep $1 trLength | awk '{print $4}' | tee $histList > /dev/null
    cat $histList | awk '{print $1}' | xargs -i{} ./plots $fnameroot {} $pdfFolder $1 > /dev/null
    cat $histList | awk '{print $1}' | xargs -i{} echo "$pdfFolder{}.pdf" > $histListPdf
    singlePlotPdfList="$(cat $histListPdf)"
    #echo $singlePlotPdfList
    echo "-> merge single pdf : $pdfOutFile"
    gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$pdfOutFile $singlePlotPdfList
    return 0
}

gifCreator(){
    pdfFolder=$1
    cd $pdfFolder
    convert -delay 1 -loop 0 *A*_trLength.gif gr_A_trLength.gif
    convert -delay 1 -loop 0 *B*_trLength.gif gr_B_trLength.gif
    mkdir -p trLength
    mv *_trLength.gif ./trLength/.
    convert -delay 1 -loop 0 *A*.gif gr_A.gif
    convert -delay 1 -loop 0 *B*.gif gr_B.gif
    mkdir -p tr
    mv *.gif ./tr/.
    cd -
}

verboseLevel=1

#1st measurement#############################
pdfFolder="./pdfdata/1st_measurement/"
pdfOutFile=$pdfFolder"aerogel_transmittance_vs_photon_wavelength_1st_measurement.pdf"
fnamerootPath="./rootdata/1st_measurement/"
fnameroot=$fnamerootPath"aerogel_transmittance_vs_photon_wavelength_1st_measurement.root"
##gr_XXXX
#get_pdf_loop "-v" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
get_pdf_xargs "-v" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
pdfOutFile=$pdfFolder"aerogel_transmittanceLength_vs_photon_wavelength_1st_measurement.pdf"
##gr_XXXX_trLength
#get_pdf_loop "-i" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
get_pdf_xargs "-i" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
gifCreator $pdfFolder
#############################################

#2nd_measurement#############################
pdfFolder="./pdfdata/2nd_measurement/"
pdfOutFile=$pdfFolder"aerogel_transmittance_vs_photon_wavelength_2nd_measurement.pdf"
fnamerootPath="./rootdata/2nd_measurement/"
fnameroot=$fnamerootPath"aerogel_transmittance_vs_photon_wavelength_2nd_measurement.root"
##gr_XXXX
#get_pdf_loop "-v" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
get_pdf_xargs "-v" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
pdfOutFile=$pdfFolder"aerogel_transmittanceLength_vs_photon_wavelength_2nd_measurement.pdf"
##gr_XXXX_trLength
#get_pdf_loop "-i" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
get_pdf_xargs "-i" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
gifCreator $pdfFolder
#############################################

#aerogel_xml_ver3#############################
pdfFolder="./pdfdata/aerogel_xml_ver3/"
pdfOutFile=$pdfFolder"aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.pdf"
fnamerootPath="./rootdata/aerogel_xml_ver3/"
fnameroot=$fnamerootPath"aerogel_transmittance_vs_photon_wavelength_aerogel_xml_ver3.root"
##gr_XXXX
#get_pdf_loop "-v" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
get_pdf_xargs "-v" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
pdfOutFile=$pdfFolder"aerogel_transmittanceLength_vs_photon_wavelength_aerogel_xml_ver3.pdf"
##gr_XXXX_trLength
#get_pdf_loop "-i" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
get_pdf_xargs "-i" $pdfFolder $pdfOutFile $fnamerootPath $fnameroot $verboseLevel
gifCreator $pdfFolder
#############################################
