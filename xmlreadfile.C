/***********************************************************************
* Copyright(C) 2017 - LBS - (Single person developer.)                 *
* Wed Oct 18 23:30:53 2017 +0900                                       *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/
//my
#include "libxmlarichdata.h"
//#if !defined(XMLREADFILE_MAIN)
//#if !defined(__CLING__)
//#include "libxmlarichdata.h"
//#endif
//#endif

//root
#include "TXMLEngine.h"
#include "TString.h"

//c, c++
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace xmlarichdata;

namespace xmlarichdata{

struct point {
  Double_t x;
  Double_t y;
};

std::vector<point> datavector;
point p;

TString globalName;

#ifdef XMLREADFILE_MAIN
void DisplayNode(TXMLEngine* xml, XMLNodePointer_t node, Int_t level);
void dumpVector(TString name);
#endif //XMLREADFILE_MAIN

#if defined(__CLING__)
void DisplayNode(TXMLEngine* xml, XMLNodePointer_t node, Int_t level);
void dumpVector(TString name);
#endif

void xmlreadfile(const char* filename = "CAd12-28wjt_r_database.xml"){ 
  globalName = filename;
  // First create engine
  TXMLEngine* xml = new TXMLEngine();
  // Now try to parse xml file
  // Only file with restricted xml syntax are supported
  XMLDocPointer_t xmldoc = xml->ParseFile(filename);
  if (xmldoc==0) {
    delete xml;
    return;
  }
  // take access to main node
  XMLNodePointer_t mainnode = xml->DocGetRootElement(xmldoc);
  // display recursively all nodes and subnodes
  DisplayNode(xml, mainnode, 1);
  // Release memory before exit
  xml->FreeDoc(xmldoc);
  delete xml;
}

void DisplayNode(TXMLEngine* xml, XMLNodePointer_t node, Int_t level){
  // this function display all accessible information about xml node and its children
  printf("%*c node: %s\n",level,' ', xml->GetNodeName(node));
  // display namespace
  XMLNsPointer_t ns = xml->GetNS(node);
  if (ns!=0)
    printf("%*c namespace: %s refer: %s\n",level+2,' ', xml->GetNSName(ns), xml->GetNSReference(ns));
  // display attributes
  XMLAttrPointer_t attr = xml->GetFirstAttr(node);
  while (attr!=0) {
    printf("%*c attr: %s value: %s\n",level+2,' ', xml->GetAttrName(attr), xml->GetAttrValue(attr));
    //p.x = 10.0;
    p.x = atof(xml->GetAttrValue(attr));
    attr = xml->GetNextAttr(attr);
  }
  // display content (if exists)
  const char* content = xml->GetNodeContent(node);
  if (content!=0){
    printf("%*c cont: %s\n",level+2,' ', content);
    //std::cout<<" wwe "<<xml->GetAttrValue(attr)<<std::endl;
    p.y = atof(content);
    //std::cout<<"   p.x = "<<p.x<<" p.y = "<<p.y<<std::endl;
    datavector.push_back(p);
    //std::cout<<datavector.size()<<std::endl;
  }
  // display all child nodes
  XMLNodePointer_t child = xml->GetChild(node);
  while(child!=0){
    DisplayNode(xml, child, level+2);
    child = xml->GetNext(child);
  }
}

void dumpVector(TString name){
  std::ofstream myfile;
  myfile.open (name.Data());
  for (unsigned i=0; i<datavector.size(); i++)
    myfile<<std::setw(20)<<datavector.at(i).x<<" "<<std::setw(20)<<datavector.at(i).y<<std::endl;
  myfile.close();
}
}//namespace xmlarichdata{

#ifdef XMLREADFILE_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]){
  if(argc == 2){
    xmlreadfile(argv[1]);
    TString name = argv[1];
    name += ".dat";
    dumpVector(name);
    return 0;
  }
  xmlreadfile();
  TString name = globalName;
  name += ".dat";
  dumpVector(name);
  return 0;
}
# endif //ifndef __CINT__
#endif //XMLREADFILE_MAIN
