// A LinkDef.h file with all the explicit template instances
// that will be needed at link time
#ifdef __CLING__
//#print "LinkDef.h";
#pragma link C++ namespace xmlarichdata;
#pragma link C++ namespace Belle2;
#pragma link C++ function plots;
#pragma link C++ function lambda_nm_2_ev;
#pragma link C++ function convert_TrLength_vs_Lambda_2_TrLength_vs_pe;
#pragma link C++ function mirror_reflection_vs_wavelength;
#pragma link C++ function quartzAbsorbtion_vs_wavelength;
#pragma link C++ function quartz_Babar_DIRC_polishing_quality_bounds;
#pragma link C++ function getSellmeierQuartz;
#pragma link C++ function quartz_RefractiveIndex_vs_wavelength;
#pragma link C++ function quartz_RefractiveIndex_vs_ev;
#pragma link C++ function aerogel_RefractiveIndex_vs_ev;
#pragma link C++ function aerogel_average_RAYLEIGH_vs_ev;
#pragma link C++ function aerogel_RAYLEIGH_vs_ev;
#pragma link C++ function hapdQE;
#pragma link C++ function refractiveIndexSilicaAerogel;
#pragma link C++ function refractiveIndexSilicaAerogelPrintTestData;
#pragma link C++ function get_silicaAerogel_density_from_refractiveIndex;
#pragma link C++ function get_silicaAerogel_refractiveIndex_from_density;
#pragma link C++ function silicaAerogel_density_refractiveIndex;
#pragma link C++ function read_merger_positions;
#pragma link C++ function read_temperature_meas;
#pragma link C++ function coolingSizes;
#pragma link C++ function testCoolingPlates;
//#pragma link C++ class ARICHcablesMaterial+;
#pragma link C++ function runARICHcablesMaterial;
#pragma link C++ function plotsARICHphase2performance;
#endif
