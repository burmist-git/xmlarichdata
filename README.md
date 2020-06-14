#  **README**

   Timeline :

|            date                |         short comment                               | 
| -------------------------------|-----------------------------------------------------|
|  Sun Oct 15 16:12:04 JST 2017  |        **START**                                    |
|  Mon Mar 26 11:17:48 CEST 2018 |        **Global documentation update**              |
|  Mon Apr 16 18:56:38 JST 2018  |        **Global software update**                   |
   Status : **In process**

## 1. data

   Contains data of aerogel transmittance as a function of wavelength for each produced tile. 
   Please note not all of them installed (there are some spare).
 
   * 1st_measurement -> First set of measurements/analysis (data is stored in xml format).
   * 2nd_measurement -> Second set of measurements/analysis** (one tile one tile is missing); (data is stored in xml format).
   * 2nd_measurement_bis -> Second set of measurements/analysis (artificially add the missing tile); (data is stored in xml format).
   * aerogel_xml_ver3 -> **Third set of measurements/analysis set of measurements** (The one in data base); (data is stored in xml format).
   * transT_markup_data/downstream/ -> Raw dx data for downstream aerogel tiles (data is stored in dx format).
   * transT_markup_data/upstream/ -> Raw dx data for upstrea aerogel tiles (data is stored in dx format).

## 2. Makefile, make.bash, setUnsetXMLARICHDATA_Fully_Compiled.bash
   This make file compiles xmlarichdata soft. Please use make.bash to compile the library.
   The make.bash script use setUnsetXMLARICHDATA_Fully_Compiled.bash to set XMLARICHDATA_Fully_Compiled to yes state. 
   In this case we can run scripts/programs without recompilation of the code. Please note not all the functions check this variable. 

## 3. README.md
   This file. Markdown syntax used for writing the file. 
  * Markdown syntax guide : 
   (https://confluence.atlassian.com/display/STASH038/Markdown+syntax+guide)

## 4. xmlArichData2Graph.C
   Program used to convert xml data into TGraph and store them in one root file.
   This program can be compiled (use Makefile) or executed like CINT root script.
   It also save the difference between data in database and data extracted from Tabata - san raw data.
   To run please use xmlArichData2Graph.bash bash script.

   ```
   source xmlArichData2Graph.bash
   ```
   The output root file will be stored in ./rootdata/

## 5. xmlArichData2Graph.bash
   Bash script to run xmlArichData2Graph.C.

## 6. plots.C
   This script/function plots TGraph from given root file.
   To run please use plots.bash bash script. 

   ```
   source plots.bash
   ```
   By default pdf generated from TGraph will saved in pdfdatatmp folder.

## 7. plots.bash
   Bash script to run plots.C.

## 8. list_TGraph.C
   This script/function print list of histograms in given root file and plots almost all the TGraph on same TCanvas.
   To run please use list_TGraph.bash bash script. 

   ```
   source list_TGraph.bash
   ```

## 9. list_TGraph.bash
   Bash script to run list_TGraph.C.

## 10. convertdx2xml.bash convertdx2xml.C
   This script/function converts raw xd data to xml format.

   ```
   source convertdx2xml.bash
   ```

## 11. aerogelTileNumbering.bash aerogelTileNumbering.C
   This script/function build map of tile numbering and save it as eps/pdf in ./outplots/ (optional).

   ```
   source  aerogelTileNumbering.bash
   ```

## 12. getAerogelDataFromDB.bash
   This script/function save aerogel map (aerogelMap) and properties (aerogelInfo) from database 
   to dat files in ./aerogelDataFromDB/. It use bsf2 framework and ARICHDatabaseImporter_condDB.py - as a steering file

   ```
   source getAerogelDataFromDB.bash
   ```

## 13. ARICHDatabaseImporter_condDB.py
   basf2 steering file to get the data from database. Below is an example how to get the aerogel map :

   ```
   basf2 ARICHDatabaseImporter_condDB.py -- -c aerogelMap
   ```

## 14. aerogelPlots.C ARICHAerogelHist.C ARICHAerogelHist.h
   This script use the data from the dat files produced by getAerogelDataFromDB.bash script about the aerogel and plot them with a help of ARICHAerogelHist class. 
   The ARICHAerogelHist inherited from TH2Poly class for 2D-histograms with arbitrary shapes of the bin.
   The bins of ARICHAerogelHist have the shape of aerogel tiles. The plots are saved into ./outplots/ folder.

   ```
   root -l aerogelPlots.C
   ```

## 15. readAerogelInfoMap.C
   This script/function read the aerogelInfo.dat and aerogelMap.dat (produced by getAerogelDataFromDB.bash script) into a vector of structures (aerogelInfoMap.h).
   This function used by other script/function.

   ```
   root -l aerogelPlots.C
   ```

## 16. aerogelInfoMap.h
   This structure contains parameter of the ARICH aerogel tile.

## 17. fitAbsorptionLength.bash fitAbsorptionLength.C
   This script/function fit the absorption length (in reality rayleigh scattering length) as a function of photon wavelength of the aerogel tiles.

## 18. fitAllAbsLen.bash  fitAllAbsLen.C
   This script/function fit the absorption length (in reality rayleigh scattering length) as a function of photon wavelength of **ALL** aerogel 
   tiles and store the fit parameters first to a vector of aerogelInfoMap.h structures.
   And then via saveXML - function (see saveXMLdataVector.C) save the vector to XML file.  

## 19. saveXMLdataVector.bash saveXMLdataVector.C
   This script/function save the data vector of aerogelInfoMap.h structures to XML file.

## 20. xmlreadfile.bash xmlreadfile.C
   This script/function xml data from Tabata - san and print out the information.

## 21. plotsSimple.C plotsSimpleFit.C plotsSimpleGr.C
   This set of script/function build plots from root files pruduced by the xml to root converter (xmlArichData2Graph.C).

## 22. runARICHAerogelHist.C
   This script/function used as test to put function together.

## 23. rayleighScatteringCrossSection.C
   Rayleigh scattering cross-section for single scattering center. 

## 24. refractiveIndexSilicaAerogel.C
   Refractive index of silica aerogel of type A (upstream aerogel n = 1.045) and B (downstream aerogel n = 1.055) using Sellmeier parametrisation.

   (https://confluence.desy.de/display/BI/ARICH+NumberingScheme)

   (https://confluence.desy.de/display/BI/ARICH+NumberingScheme?preview=/34029175/37487141/b2gm_arich_numbering_scheme_pestotnik_18062014.pdf)

## 25. get_pdf.bash
   This script/function create the gif and pdf plots for all the aerogel ARICH-tiles.

## 26. hapdQE.C qe_vs_lam.dat
   This script/function produce a plot of quantum efficiency vs photon wavelength of the HAPDs taken from qe_vs_lam.dat

## 27. graph_n_vs_lambda.C n_A_Lam.dat n_B_Lam.dat
   This script/function fit dependence of refractive index as a function of photon wavelength. The data is taken from n_A_Lam.dat n_B_Lam.dat files.

## 28. convert_TrLength_vs_Lambda_2_TrLength_vs_pe.C
   This script/function convert (TGraph*) plots of data as a function of photon wavelength to the function of photon energy (eV).

## 29. silicaAerogel_density_refractiveIndex.C
   This script/function calculated density of aerogel from refractive index and refractive index from density.

## 30. mirror_reflection_vs_wavelength.C mirror_reflection_vs_wavelength.bash
   This script/function return TGraph of mirror reflection vs wavelength.

## 31. quartzAbsorbtion_vs_wavelength.C quartzAbsorbtion_vs_wavelength.bash
   This script/function return TGraph of quartz absorption vs wavelength.        

## 32. quartz_Babar_DIRC_polishing_quality_bounds.C quartz_Babar_DIRC_polishing_quality_bounds.bash
   This script/function return TGraph of probability of the photon to be absorbed after total internal
   reflection from the quartz - air interface as a function of wavelength. It shows the quartz polishing quality.

## 33. quartz_RefractiveIndex_vs_wavelength.C quartz_RefractiveIndex_vs_wavelength.bash
   This script/function return TGraph of mirror reflection vs wavelength.

## 34. LinkDef.h
   A LinkDef.h file with all the explicit template instances that will be needed at link time (for dictionary and shared library generation). 

   (https://root.cern.ch/interacting-shared-libraries-rootcling)

   (https://root.cern.ch/selecting-dictionary-entries-linkdefh)

## 35. nm.bash
   This script/function use **nm** to list functions from object (Shared library - obj/libxmlarichdata.so)

## 36. libxmlarichdata.h
   Shared library.

## 37. Useful links
   * Markdown syntax guide --> (https://confluence.atlassian.com/display/STASH038/Markdown+syntax+guide)

   * ARICH numbering scheme --> (https://confluence.desy.de/display/BI/ARICH+NumberingScheme) (https://confluence.desy.de/display/BI/ARICH+NumberingScheme?preview=/34029175/37487141/b2gm_arich_numbering_scheme_pestotnik_18062014.pdf)

   * Belle II Coordinate System and Guideline of Belle II Numbering Scheme --> (https://indico.mpp.mpg.de/event/2308/material/0/1?contribId=0)

   * Interpreter Interacting with Shared Libraries: rootcling --> (https://root.cern.ch/interacting-shared-libraries-rootcling)

   * Selecting Dictionary Entries: Linkdef.h --> (https://root.cern.ch/selecting-dictionary-entries-linkdefh)
