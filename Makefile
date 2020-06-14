########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sun Oct 15 16:08:52 JST 2017                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# Script description:                                                  #
#                     This make file compiles xmlarichdata soft.       #
#                                                                      #
# Input paramete: NON                                                  #
#                                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
########################################################################

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

#basf2 includes
ifeq ($(BELLE2_LOCAL_DIR),)
  $(info BELLE2_LOCAL_DIR is not set)
    ifeq ($(XMLARICHDATA_BASF2_INCLUDE),)
      $(info XMLARICHDATA_BASF2_INCLUDE is not set)
      $(error BASF2INCLUDE is not set)
    else
      BASF2INCLUDE = $(XMLARICHDATA_BASF2_INCLUDE)
    endif
else
  BASF2INCLUDE = $(BELLE2_LOCAL_DIR)/include
endif

#Check if external is set to v01-06-01
GOODEXTERNALS = v01-06-01
SETEXTERNALS = $(notdir $(BELLE2_EXTERNALS_DIR))
ifneq  "$(SETEXTERNALS)" "$(GOODEXTERNALS)"
  $(info BELLE2_EXTERNALS_DIR is not set to $(GOODEXTERNALS))
  $(info BELLE2_EXTERNALS_DIR = $(notdir $(BELLE2_EXTERNALS_DIR)))
  $(error BELLE2_EXTERNALS_DIR is not good)
endif

ifeq ($(BASF2INCLUDE),)
$(error BASF2INCLUDE is not set)
endif

$(info BASF2INCLUDE = $(BASF2INCLUDE))

# add xml files
ROOTLIBS += -lMLP -lXMLIO

OUTLIB = ./obj/
CXX  = g++
CXX += -I./     

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += -I$(BASF2INCLUDE)
CXXFLAGSDICT = -g -Wall -fPIC -Wno-deprecated

PATHTOSHAREDLIB=$(OUTLIB)

#----------------------------------------------------#

all: printmakeinfo xmlArichData2Graph plots fitAbsorptionLength list_TGraph readAerogelInfoMap xmlreadfile runARICHAerogelHist fitAllAbsLen saveXMLdataVector convertdx2xml read_merger_positions read_temperature_meas runARICHcablesMaterial printNumber_of_channels_chips_HAPD_mergers_sectors generateXmlAerogelMaterialFile printSuperKEKBpar convertDataFebMergerTemperatureSlowControl convertGL840csv cellStrTest_main saveTessellatedSolidVerticesToXML_main make_include_lib_indata_dir_symlink libxmlarichdataDict.cxx libxmlarichdataDictLib.so

#makedir: 
#	if [ ! -d "./$(OUTLIB)" ];then	\
#		mkdir -p $(OUTLIB);	\
#	fi
#	if [ ! -d "./tmp" ];then 	\
#		mkdir -p tmp;		\
#	fi

makedir:
	mkdir -p $(OUTLIB);
	mkdir -p tmp;

make_include_lib_indata_dir_symlink: clean_include_lib_indata_dir_symlink
	$(info $PWD = "$(PWD)")
	mkdir -p include lib indata
	ln -s $(PWD)/libxmlarichdata.h $(PWD)/include/libxmlarichdata.h 
	ln -s $(PWD)/aerogelInfoMap.h $(PWD)/include/aerogelInfoMap.h
	ln -s $(PWD)/mergerStruct.h $(PWD)/include/mergerStruct.h
	ln -s $(PWD)/cellStr.h $(PWD)/include/cellStr.h
	ln -s $(PWD)/cellGeoStr.h $(PWD)/include/cellGeoStr.h
	ln -s $(PWD)/tessellatedSolidStr.h $(PWD)/include/tessellatedSolidStr.h
	ln -s -f $(PWD)/$(OUTLIB)/libxmlarichdata.so $(PWD)/lib/libxmlarichdata.so
	ln -s -f $(PWD)/qe_vs_lam.dat $(PWD)/indata/qe_vs_lam.dat
	ln -s -f $(PWD)/n_A_Lam.dat $(PWD)/indata/n_A_Lam.dat
	ln -s -f $(PWD)/n_B_Lam.dat $(PWD)/indata/n_B_Lam.dat

printmakeinfo:
	$(info CXX          = "$(CXX)")
	$(info CXXFLAGS     = "$(CXXFLAGS)")
	$(info CXXFLAGSDICT = "$(CXXFLAGSDICT)")

printmakehelp_and_reminder: n_A_Lam.dat n_B_Lam.dat
	$(info  /***************************************************************/)
	$(info  * task --> printmakehelp_and_reminder: n_A_Lam.dat n_B_Lam.dat *)
	$(info  * $$@ ----> $@                          *)
	$(info  * $$< --------------------------------> $<             *)
	$(info  * $$^ --------------------------------> $^ *)
	$(info  /***************************************************************/)

#xmlArichData2Graph: xmlArichData2Graph.C
#	$(CXX) -DXMLARICHDATA2GRAPH_MAIN -o xmlArichData2Graph xmlArichData2Graph.C $(CXXFLAGS) 

xmlArichData2Graph: xmlArichData2Graph.C obj/libxmlarichdata.so
	$(CXX) -DXMLARICHDATA2GRAPH_MAIN -o xmlArichData2Graph xmlArichData2Graph.C $(OUTLIB)*.so $(CXXFLAGS)

plots: plots.C obj/libxmlarichdata.so
	$(CXX) -DPLOTS_MAIN -o plots plots.C $(OUTLIB)*.so $(CXXFLAGS) 

#plots: plots.C obj/libxmlarichdata.so
#	$(CXX) -DPLOTS_MAIN -o plots plots.C $(CXXFLAGS) 

fitAbsorptionLength: fitAbsorptionLength.C obj/libxmlarichdata.so
	$(CXX) -DFITABSORPTIONLENGHT_MAIN -o fitAbsorptionLength fitAbsorptionLength.C $(OUTLIB)*.so $(CXXFLAGS) 

fitAllAbsLen: fitAllAbsLen.C obj/libxmlarichdata.so
	$(CXX) -DFITALLABSLEN_MAIN -o fitAllAbsLen fitAllAbsLen.C $(OUTLIB)*.so $(CXXFLAGS) 

list_TGraph: list_TGraph.C
	$(CXX) -DLIST_TGRAPH_MAIN -o list_TGraph list_TGraph.C $(ROOTCFLAGS) $(ROOTLIBS) $(ROOTGLIBS)

readAerogelInfoMap: readAerogelInfoMap.C
	$(CXX) -DREADAEROGELINFOMAP_MAIN -o readAerogelInfoMap readAerogelInfoMap.C $(CXXFLAGS)

read_merger_positions: read_merger_positions.C mergerStruct.h
	$(CXX) -DREADMERGERPOSITION_MAIN -o read_merger_positions read_merger_positions.C $(CXXFLAGS)

read_temperature_meas: read_temperature_meas.C
	$(CXX) -DREADTEMPERATURE_MEAS -o read_temperature_meas read_temperature_meas.C $(CXXFLAGS)

xmlreadfile: xmlreadfile.C
	$(CXX) -DXMLREADFILE_MAIN -o xmlreadfile xmlreadfile.C $(CXXFLAGS)

runARICHAerogelHist: runARICHAerogelHist.C obj/ARICHAerogelHist.o obj/libxmlarichdata.so
	$(CXX) -DRUNARICHAEROGELHIST_MAIN -o runARICHAerogelHist runARICHAerogelHist.C $(OUTLIB)*.o $(OUTLIB)*.so $(CXXFLAGS)

saveXMLdataVector: saveXMLdataVector.C obj/libxmlarichdata.so
	$(CXX) -DSAVEXMLDATAVECTOR_MAIN -o saveXMLdataVector saveXMLdataVector.C $(OUTLIB)*.so $(CXXFLAGS)

convertdx2xml: convertdx2xml.C obj/libxmlarichdata.so
	$(CXX) -DCONVERTDX2XML_MAIN -o convertdx2xml convertdx2xml.C $(OUTLIB)*.so $(CXXFLAGS)

convertDataFebMergerTemperatureSlowControl: convertDataFebMergerTemperatureSlowControl.C obj/libxmlarichdata.so
	$(CXX) -DCONVERTDATAFEBMERGERTEMPERATURESLOWCONTROL_MAIN -o convertDataFebMergerTemperatureSlowControl convertDataFebMergerTemperatureSlowControl.C $(OUTLIB)*.so $(CXXFLAGS)

convertGL840csv: convertGL840csv.C obj/libxmlarichdata.so
	$(CXX) -DCONVERTGL840CSV_MAIN -o convertGL840csv convertGL840csv.C $(OUTLIB)*.so $(CXXFLAGS)

runARICHcablesMaterial: runARICHcablesMaterial.C obj/ARICHcablesMaterial.o 
	$(CXX) -DRUNARICHCABLESMATERIAL_MAIN -o runARICHcablesMaterial runARICHcablesMaterial.C $(OUTLIB)*.o $(CXXFLAGS)

#runARICHmappingCopperMergerFeb: runARICHmappingCopperMergerFeb.C obj/ARICHmappingCopperMergerFeb.o
#	$(CXX) -DRUNARICHMAPPINGCOPPERMERFERFEB_MAIN -o runARICHmappingCopperMergerFeb runARICHmappingCopperMergerFeb.C $(OUTLIB)*.o $(CXXFLAGS)

printNumber_of_channels_chips_HAPD_mergers_sectors: printNumber_of_channels_chips_HAPD_mergers_sectors.C
	$(CXX) -DPRINTNUMBER_OF_CHANNELS_CHIPS_HAPD_MERGERS_SECTORS_MAIN -o printNumber_of_channels_chips_HAPD_mergers_sectors printNumber_of_channels_chips_HAPD_mergers_sectors.C $(OUTLIB)*.o $(CXXFLAGS)

printSuperKEKBpar: printSuperKEKBpar.C
	$(CXX) -DPRINTSUPERKEKBPAR_MAIN -o printSuperKEKBpar printSuperKEKBpar.C $(OUTLIB)*.o $(CXXFLAGS)

toyMC_trg: toyMC_trg.C
	$(CXX) -DTOYMC_TRG -o toyMC_trg toyMC_trg.C $(OUTLIB)*.o $(CXXFLAGS)

convert_npz_ASCII_to_root: convert_npz_ASCII_to_root.C
	$(CXX) -DCONVERT_NPZ_TO_ROOT_MAIN -o convert_npz_ASCII_to_root convert_npz_ASCII_to_root.C $(OUTLIB)*.o $(CXXFLAGS)

generateXmlAerogelMaterialFile: generateXmlAerogelMaterialFile.C obj/libxmlarichdata.so
	$(CXX) -DGENERATEXMLAEROGELMATERIALFILE_MAIN -o generateXmlAerogelMaterialFile generateXmlAerogelMaterialFile.C $(OUTLIB)*.so $(CXXFLAGS)

cellStrTest_main: cellStrTest_main.C obj/libxmlarichdata.so
	$(CXX) -DCELLSTRTEST_MAIN -o cellStrTest_main cellStrTest_main.C $(OUTLIB)*.so $(CXXFLAGS)

saveTessellatedSolidVerticesToXML_main: saveTessellatedSolidVerticesToXML_main.C obj/libxmlarichdata.so
	$(CXX) -DSAVETESSELLATEDSOLIDVERTICESTOXML_MAIN -o saveTessellatedSolidVerticesToXML_main saveTessellatedSolidVerticesToXML_main.C $(OUTLIB)*.so $(CXXFLAGS)

obj/ARICHAerogelHist.o: ARICHAerogelHist.C ARICHAerogelHist.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)ARICHAerogelHist.o $<

obj/ARICHMergerHist.o: ARICHMergerHist.C ARICHMergerHist.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)ARICHMergerHist.o $<

obj/ARICHcablesMaterial.o: ARICHcablesMaterial.C ARICHcablesMaterial.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)ARICHcablesMaterial.o $<

obj/ARICHmappingCopperMergerFeb.o: ARICHmappingCopperMergerFeb.C ARICHmappingCopperMergerFeb.h ARICHfebStr.h ARICHcopperStr.h ARICHmergerStr.h ARICHsectorStr.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)ARICHmappingCopperMergerFeb.o $<

obj/anaSCT.o: anaSCT.C anaSCT.h obj/anaSCTbase.o
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)anaSCT.o $<

obj/anaSCTbase.o: anaSCTbase.C anaSCTbase.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)anaSCTbase.o $<

obj/anaGL840.o: anaGL840.C anaGL840.h obj/anaGL840base.o
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)anaGL840.o $<

obj/anaGL840base.o: anaGL840base.C anaGL840base.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)anaGL840base.o $<

obj/libxmlarichdata.so: obj/convert_TrLength_vs_Lambda_2_TrLength_vs_pe.o obj/plots.o obj/fitAbsorptionLength.o obj/fitAllAbsLen.o obj/xmlreadfile.o obj/readAerogelInfoMap.o obj/refractiveIndexSilicaAerogel.o obj/rayleighScatteringCrossSection.o obj/saveXMLdataVector.o obj/convertdx2xml.o obj/xmlArichData2Graph.o obj/silicaAerogel_density_refractiveIndex.o obj/mirror_reflection_vs_wavelength.o obj/quartzAbsorbtion_vs_wavelength.o obj/quartz_Babar_DIRC_polishing_quality_bounds.o obj/quartz_RefractiveIndex_vs_wavelength.o obj/quartz_RefractiveIndex_vs_ev.o obj/aerogel_RefractiveIndex_vs_ev.o obj/hapdQE.o obj/read_merger_positions.o obj/read_temperature_meas.o obj/coolingSizes.o obj/testCoolingPlates.o obj/ARICHcablesMaterial.o obj/ARICHmappingCopperMergerFeb.o obj/aerogel_average_RAYLEIGH_vs_ev.o obj/unixTimeManipulation.o obj/cellStrTest.o obj/saveTessellatedSolidVerticesToXML.o obj/tessellationSolidVisualisation.o
	$(CXX) -shared -o $(PATHTOSHAREDLIB)libxmlarichdata.so $(OUTLIB)convert_TrLength_vs_Lambda_2_TrLength_vs_pe.o $(OUTLIB)plots.o $(OUTLIB)fitAbsorptionLength.o $(OUTLIB)fitAllAbsLen.o $(OUTLIB)xmlreadfile.o $(OUTLIB)readAerogelInfoMap.o $(OUTLIB)refractiveIndexSilicaAerogel.o $(OUTLIB)rayleighScatteringCrossSection.o $(OUTLIB)saveXMLdataVector.o $(OUTLIB)convertdx2xml.o $(OUTLIB)xmlArichData2Graph.o $(OUTLIB)silicaAerogel_density_refractiveIndex.o $(OUTLIB)mirror_reflection_vs_wavelength.o $(OUTLIB)/quartzAbsorbtion_vs_wavelength.o $(OUTLIB)/quartz_Babar_DIRC_polishing_quality_bounds.o $(OUTLIB)/quartz_RefractiveIndex_vs_wavelength.o $(OUTLIB)/quartz_RefractiveIndex_vs_ev.o $(OUTLIB)/aerogel_RefractiveIndex_vs_ev.o $(OUTLIB)/hapdQE.o $(OUTLIB)/read_merger_positions.o $(OUTLIB)/read_temperature_meas.o $(OUTLIB)/coolingSizes.o $(OUTLIB)/testCoolingPlates.o $(OUTLIB)/ARICHcablesMaterial.o $(OUTLIB)/ARICHmappingCopperMergerFeb.o $(OUTLIB)/aerogel_average_RAYLEIGH_vs_ev.o $(OUTLIB)/unixTimeManipulation.o $(OUTLIB)/cellStrTest.o $(OUTLIB)/saveTessellatedSolidVerticesToXML.o $(OUTLIB)/tessellationSolidVisualisation.o $(ROOTLIBS) $(ROOTGLIBS)

obj/convert_TrLength_vs_Lambda_2_TrLength_vs_pe.o: convert_TrLength_vs_Lambda_2_TrLength_vs_pe.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)convert_TrLength_vs_Lambda_2_TrLength_vs_pe.o $<

obj/plots.o: plots.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)plots.o $<

obj/fitAbsorptionLength.o: fitAbsorptionLength.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)fitAbsorptionLength.o $<

obj/fitAllAbsLen.o: fitAllAbsLen.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)fitAllAbsLen.o $<

obj/xmlreadfile.o: xmlreadfile.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)xmlreadfile.o $<

obj/readAerogelInfoMap.o: readAerogelInfoMap.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)readAerogelInfoMap.o $<

obj/refractiveIndexSilicaAerogel.o: refractiveIndexSilicaAerogel.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)refractiveIndexSilicaAerogel.o $<

obj/rayleighScatteringCrossSection.o: rayleighScatteringCrossSection.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)rayleighScatteringCrossSection.o $<

obj/saveXMLdataVector.o: saveXMLdataVector.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)saveXMLdataVector.o $<

obj/convertdx2xml.o: convertdx2xml.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)convertdx2xml.o $<

obj/xmlArichData2Graph.o: xmlArichData2Graph.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)xmlArichData2Graph.o $<

obj/silicaAerogel_density_refractiveIndex.o: silicaAerogel_density_refractiveIndex.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)silicaAerogel_density_refractiveIndex.o $<

obj/mirror_reflection_vs_wavelength.o: mirror_reflection_vs_wavelength.C
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)mirror_reflection_vs_wavelength.o $<

obj/quartzAbsorbtion_vs_wavelength.o: quartzAbsorbtion_vs_wavelength.C
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)quartzAbsorbtion_vs_wavelength.o $<

obj/quartz_Babar_DIRC_polishing_quality_bounds.o: quartz_Babar_DIRC_polishing_quality_bounds.C
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)quartz_Babar_DIRC_polishing_quality_bounds.o $<

obj/quartz_RefractiveIndex_vs_wavelength.o: quartz_RefractiveIndex_vs_wavelength.C
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)quartz_RefractiveIndex_vs_wavelength.o $<

obj/quartz_RefractiveIndex_vs_ev.o: quartz_RefractiveIndex_vs_ev.C
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)quartz_RefractiveIndex_vs_ev.o $<

obj/aerogel_RefractiveIndex_vs_ev.o: aerogel_RefractiveIndex_vs_ev.C
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)aerogel_RefractiveIndex_vs_ev.o $<

obj/aerogel_average_RAYLEIGH_vs_ev.o: aerogel_average_RAYLEIGH_vs_ev.C
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)aerogel_average_RAYLEIGH_vs_ev.o $<

obj/hapdQE.o: hapdQE.C
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)hapdQE.o $<

obj/read_merger_positions.o: read_merger_positions.C libxmlarichdata.h mergerStruct.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)read_merger_positions.o $<

obj/read_temperature_meas.o: read_temperature_meas.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)read_temperature_meas.o $<

obj/coolingSizes.o: coolingSizes.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)coolingSizes.o $<

obj/testCoolingPlates.o: testCoolingPlates.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)testCoolingPlates.o $<

obj/unixTimeManipulation.o: unixTimeManipulation.C libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)unixTimeManipulation.o $<

obj/cellStrTest.o: cellStrTest.C cellStr.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)cellStrTest.o $<

obj/saveTessellatedSolidVerticesToXML.o: saveTessellatedSolidVerticesToXML.C cellStr.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)saveTessellatedSolidVerticesToXML.o $<

obj/tessellationSolidVisualisation.o: tessellationSolidVisualisation.C obj/saveTessellatedSolidVerticesToXML.o libxmlarichdata.h
	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)tessellationSolidVisualisation.o $<

#obj/printNumber_of_channels_chips_HAPD_mergers_sectors.o: printNumber_of_channels_chips_HAPD_mergers_sectors.C libxmlarichdata.h
#	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)printNumber_of_channels_chips_HAPD_mergers_sectors.o $<

#obj/generateXmlAerogelMaterialFile.o: generateXmlAerogelMaterialFile.C libxmlarichdata.h
#	$(CXX) $(CXXFLAGS) -c -I. -o $(OUTLIB)generateXmlAerogelMaterialFile.o $<

libxmlarichdataDict.cxx: libxmlarichdata.h LinkDef.h
	rootcling -f $@ -c $(CXXFLAGSDICT) -I$(BASF2INCLUDE) -p $^

libxmlarichdataDictLib.so: libxmlarichdataDict.cxx plots.C convert_TrLength_vs_Lambda_2_TrLength_vs_pe.C mirror_reflection_vs_wavelength.C quartzAbsorbtion_vs_wavelength.C quartz_Babar_DIRC_polishing_quality_bounds.C quartz_RefractiveIndex_vs_wavelength.C quartz_RefractiveIndex_vs_ev.C aerogel_RefractiveIndex_vs_ev.C aerogel_average_RAYLEIGH_vs_ev.C hapdQE.C refractiveIndexSilicaAerogel.C silicaAerogel_density_refractiveIndex.C read_merger_positions.C read_temperature_meas.C coolingSizes.C testCoolingPlates.C runARICH_asic_fpga_Temperatures.C runARICH_asic_fpga_Temperatures_newCooling.C runARICH_asic_fpga_numbering.C runARICH_FEB_MERGER_numbering.C ARICHcablesMaterial.C runARICHcablesMaterial.C ARICHmappingCopperMergerFeb.C anaSCTbase.C anaSCT.C runanaSCT.C runanaGL840.C anaGL840base.C anaGL840.C runARICHmappingCopperMergerFeb.C fitAbsorptionLength.C unixTimeManipulation.C cellStrTest.C saveTessellatedSolidVerticesToXML.C plotsARICHphase2performance.C tessellationSolidVisualisation.C
	g++ -shared -o $@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^

clean: cleanxmlArichData2Graph cleanplots cleanfitAbsorptionLength cleanfitAllAbsLen cleanlist_TGraph cleanreadAerogelInfoMap cleanxmlreadfile cleansaveXMLdataVector cleanconvertdx2xml cleanrunARICHcablesMaterial cleanrunARICHmappingCopperMergerFeb cleanread_merger_positions cleanread_temperature_meas cleanDictLib clean_include_lib_indata_dir_symlink cleanprintSuperKEKBpar cleanconvertDataFebMergerTemperatureSlowControl cleanconvertGL840csv cleanprintNumber_of_channels_chips_HAPD_mergers_sectors cleangenerateXmlAerogelMaterialFile
	rm -f *~
	rm -f .*~
	rm -rf $(OUTLIB)
	rm -f runARICHAerogelHist

cleanAll: clean
	rm -rf rootdata
	rm -rf pdfdatatmp
	rm -rf pdfdata
	rm -rf dataDiffInfo
	rm -rf centraldb
	rm -rf aerogelDataFromDB
	rm -rf CAd12-28wjt_r_database.xml.dat

cleanxmlArichData2Graph:
	rm -f xmlArichData2Graph

cleanplots:
	rm -f plots

cleanfitAbsorptionLength:
	rm -f fitAbsorptionLength

cleanfitAllAbsLen:
	rm -f fitAllAbsLen

cleanlist_TGraph:
	rm -f list_TGraph

cleanreadAerogelInfoMap:
	rm -f readAerogelInfoMap

cleanread_merger_positions:
	rm -f read_merger_positions

cleanread_temperature_meas:
	rm -f read_temperature_meas

cleanxmlreadfile:
	rm -f xmlreadfile

cleansaveXMLdataVector:
	rm -f saveXMLdataVector

cleanconvertdx2xml:
	rm -f convertdx2xml

cleanrunARICHcablesMaterial:
	rm -f runARICHcablesMaterial
	rm -f obj/ARICHcablesMaterial.o

cleanrunARICHmappingCopperMergerFeb:
	rm -f runARICHmappingCopperMergerFeb
	rm -f obj/ARICHmappingCopperMergerFeb.o

cleanconvertDataFebMergerTemperatureSlowControl:
	rm -f convertDataFebMergerTemperatureSlowControl

cleanconvertGL840csv:
	rm -f convertGL840csv

cleanprintNumber_of_channels_chips_HAPD_mergers_sectors:
	rm -f printNumber_of_channels_chips_HAPD_mergers_sectors

cleanprintSuperKEKBpar:
	rm -f printSuperKEKBpar

cleanconvert_npz_ASCII_to_root:
	rm -f convert_npz_ASCII_to_root

cleangenerateXmlAerogelMaterialFile:
	rm -f generateXmlAerogelMaterialFile

cleancellStrTest_main:
	rm -f cellStrTest_main

cleansaveTessellatedSolidVerticesToXML_main:
	rm -f saveTessellatedSolidVerticesToXML_main

cleanDictLib:
	rm -f libxmlarichdataDict.cxx
	rm -f libxmlarichdataDictLib.so
	rm -f libxmlarichdataDict_rdict.pcm

clean_include_lib_indata_dir_symlink: 
	rm -rf include lib indata
