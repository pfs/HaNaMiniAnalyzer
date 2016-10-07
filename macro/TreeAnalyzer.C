/* 
 * File:   TemplateFit.C
 * Author: nadjieh
 *
 * Created on June 9, 2012, 3:57 PM
 */
#include<iostream>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TDirectory.h"
#include "TString.h"
#include <string>
#include <vector>
#include <sstream>
#define HambTree_cxx
#include "../interface/HambTree.h"
using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
  int step = 1000;
  TString treename = "Hamb/Trees/Events";
  HambTree* hTree;
  for (int f = 1; f < argc; f++) {
    std::string arg_fth(*(argv + f));
    if (arg_fth == "input") {
      f++;
      std::string out(*(argv + f));
      TFile * fdata = TFile::Open(out.c_str());
      hTree = new HambTree((TTree*) fdata->Get(treename));
    }
  }
  for (int eventNumber = 0; eventNumber < hTree->fChain->GetEntriesFast(); eventNumber++) {
    hTree->GetEntry(eventNumber);
    cout<< hTree->aMu_mass<<endl;
  }
  return 1;
}

