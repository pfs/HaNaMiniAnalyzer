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
#include "TLorentzVector.h"
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
  TString DirFile = "eos/cms/store/user/ajafari/Oct5_8020_v2/";
  TString fname;
  TString treename = "Hamb/Trees/Events";
  HambTree* hTree;
  for (int f = 1; f < argc; f++) {
    std::string arg_fth(*(argv + f));
    if (arg_fth == "input") {
      f++;
      std::string out(*(argv + f));
      fname = out.c_str();
      TFile * fdata = TFile::Open(DirFile+fname);
      hTree = new HambTree((TTree*) fdata->Get(treename));
    }
  }
  TH1D * muPt0 = new TH1D("muPt0","muPt0",200, 0, 200);
  TH1D * muPt1 = new TH1D("muPt1","muPt1",200, 0, 200);
  TH1D * jetPt0 = new TH1D("jetPt0","jetPt0",200, 0, 200);
  TH1D * jetPt1 = new TH1D("jetPt1","jetPt1",200, 0, 200);
  TH1D * aMu = new TH1D("aMu","aMu",30, 10, 80);
  TH1D * abQjorig = new TH1D("abQjorig","abQjorig",200, 0, 500);
  TH1D * hbQjorig = new TH1D("hbQjorig","hbQjorig",500, 0, 1000);
  TH1D * abQjReg = new TH1D("abQjReg","abQjReg",200, 0, 500);
  TH1D * hbQjReg = new TH1D("hbQjReg","hbQjReg",500, 0, 1000);  
  TH1D * abQjRegMed = new TH1D("abQjMed","abQjMed",200, 0, 500);
  TH1D * hbQjRegMed = new TH1D("hbQjRegMed","hbQjRegMed",500, 0, 1000);    
  for (int eventNumber = 0; eventNumber < hTree->fChain->GetEntriesFast(); eventNumber++) {
    hTree->GetEntry(eventNumber);
    if (hTree->muPt->size() <  2)  continue;
    muPt0->Fill(hTree->muPt->at(0));
    muPt1->Fill(hTree->muPt->at(1));
    if (hTree->jetsPt->size() <  2) continue;
    jetPt0->Fill(hTree->jetsPt->at(0));
    jetPt1->Fill(hTree->jetsPt->at(1));
    if (hTree->muPt->at(0) < 24 ) continue;
    if (hTree->muPt->at(1) < 8 )  continue;
    TLorentzVector m1,m2,a;
    m1.SetPtEtaPhiM(hTree->muPt->at(0),
                   hTree->muEta->at(0),
                   hTree->muPhi->at(0),0);
    m2.SetPtEtaPhiM(hTree->muPt->at(1),
                   hTree->muEta->at(1),
                   hTree->muPhi->at(1),0);                   
    a = m1+m2;       
    if (a.M() < 20 || a.M() > 70) continue;
    aMu->Fill(a.M());
    std::vector<int> bQuarkJetIndecies;
    std::vector<TLorentzVector> bQuarkJets;
    for(unsigned int iJet = 0; iJet < hTree->jetsPt->size(); iJet++){
        if(fabs(hTree->jetsFlavour->at(iJet)) == 5 ){
	    bQuarkJetIndecies.push_back(iJet);
            TLorentzVector b;
	    b.SetPtEtaPhiM(hTree->jetsPt->at(iJet), hTree->jetsEta->at(iJet), hTree->jetsPhi->at(iJet), 4.0);
	    bQuarkJets.push_back(b);	    
        }
    }
    if(bQuarkJets.size() < 2 ) continue;
    //cout << hTree->muPt->size() <<"\t"<<hTree->jetsPt->size()<<"\t"<<a.M() <<"\t\t"<<bQuarkJets.size()<<endl;
    float mB = (bQuarkJets[0]+bQuarkJets[1]).M();
    float mH = ((bQuarkJets[0]+bQuarkJets[1])+a).M();
    double R = a.M()/mB;
    abQjorig->Fill(mB);
    hbQjorig->Fill(mH);
    bQuarkJets[0].SetPxPyPzE(R*bQuarkJets[0].Px(),R*bQuarkJets[0].Py(),R*bQuarkJets[0].Pz(),R*bQuarkJets[0].E());
    bQuarkJets[1].SetPxPyPzE(R*bQuarkJets[1].Px(),R*bQuarkJets[1].Py(),R*bQuarkJets[1].Pz(),R*bQuarkJets[1].E());    
    mB = (bQuarkJets[0]+bQuarkJets[1]).M();
    mH = ((bQuarkJets[0]+bQuarkJets[1])+a).M();
    abQjReg->Fill(mB);
    hbQjReg->Fill(mH);
    if((hTree->jetsBtag->at(bQuarkJetIndecies[0]) < 0.814) || (hTree->jetsBtag->at(bQuarkJetIndecies[1]) < 0.814)) continue;
    abQjRegMed->Fill(mB);
    hbQjRegMed->Fill(mH);    
    //cout<< hTree->aMu_mass<<endl;
  }
  TFile * f = new TFile("hist_"+fname, "recreate");
  f->cd();
  muPt0->Write();
  muPt1->Write();
  jetPt0->Write();
  jetPt1->Write();
  aMu->Write();
  abQjorig->Write();
  hbQjorig->Write();  
  abQjReg->Write();
  hbQjReg->Write();  
  abQjRegMed->Write();
  hbQjRegMed->Write();   
  f->Close();
  return 1;
}

