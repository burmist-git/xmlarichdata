/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Sun Oct 14 12:45:36 JST 2018                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "libxmlarichdata.h"
#include "tessellatedSolidStr.h"

#ifdef SAVETESSELLATEDSOLIDVERTICESTOXML_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  xmlarichdata::saveTessellatedSolidVerticesToXML(xmlarichdata::cellStrTest(),20,"saveTessellatedSolidVerticesToXML_test.xml");
  xmlarichdata::saveTessellatedSolidVerticesToDATfile(xmlarichdata::cellStrTest(),20,"saveTessellatedSolidVerticesToXML_test.dat");
  tessellatedSolidStr tessellatedSolid = xmlarichdata::readTessellatedSolidVerticesToDATfile("saveTessellatedSolidVerticesToXML_test.dat");
  tessellatedSolid.printInfo();
  //xmlarichdata::dumpTessellatedSolidVertices(xmlarichdata::cellStrTest(),20);
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef SAVETESSELLATEDSOLIDVERTICESTOXML_MAIN
