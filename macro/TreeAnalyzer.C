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
#include "TDirectory.h"
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
bool myfunction (int i,int j) { return (i>j); }
template <class G>
class btagSort{
public:
  btagSort(){}
  ~btagSort(){}
  bool operator()(G o1 ,G o2 ){
    return (o1.second>o2.second);
  }
};
/*
 * 
 */

class someHists{
public:
	someHists(TString name): Name(name){
	  aMu = new TH1D(name+"_aMu","aMu",30, 10, 80);
  	  abQjorig = new TH1D(name+"_abQjorig","abQjorig",200, 0, 500);
	  hbQjorig = new TH1D(name+"_hbQjorig","hbQjorig",500, 0, 1000);
	  abQjReg = new TH1D(name+"_abQjReg","abQjReg",200, 0, 500);
	  hbQjReg = new TH1D(name+"_hbQjReg","hbQjReg",500, 0, 1000);  
	  abQjRegMed = new TH1D(name+"_abQjMed","abQjMed",200, 0, 500);
  	  hbQjRegMed = new TH1D(name+"_hbQjRegMed","hbQjRegMed",500, 0, 1000); 
	}
  TString Name;
  TH1D * aMu;
  TH1D * abQjorig;
  TH1D * hbQjorig;
  TH1D * abQjReg;
  TH1D * hbQjReg;  
  TH1D * abQjRegMed;
  TH1D * hbQjRegMed; 
  void Write(TDirectory * d){
	d->mkdir(Name)->cd();
	aMu->Write();
	abQjorig->Write();
	hbQjorig->Write();
	abQjReg->Write();
	hbQjReg->Write();  
	abQjRegMed->Write();
	hbQjRegMed->Write(); 	
	d->cd();
  }

};

int main(int argc, char** argv) {
  int step = 1000;
  TString DirFile = "eos_cb/user/a/ajafari/Hamb13/Oct14_8020_Opt/Trees/";
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
  someHists ptOrdered("ptOrdered");
  someHists btagOrdered("btagOrdered");
  for (int eventNumber = 0; eventNumber < hTree->fChain->GetEntriesFast(); eventNumber++) {
    hTree->GetEntry(eventNumber);

    //Based on optimization studies
    if (hTree->muPt->size() <  2)  continue;
    if (hTree->jetsPt->size() <  2) continue;
    if (hTree->muPt->at(0) < 25 ) continue;
    if (hTree->muPt->at(1) < 10 )  continue;
    if (hTree->jetsPt->at(0) < 20 ) continue;
    if (hTree->jetsPt->at(1) < 15 )  continue;
    if (hTree->metSig > 2 )  continue;
    TLorentzVector m1,m2,a;
    m1.SetPtEtaPhiM(hTree->muPt->at(0),
                   hTree->muEta->at(0),
                   hTree->muPhi->at(0),0);
    m2.SetPtEtaPhiM(hTree->muPt->at(1),
                   hTree->muEta->at(1),
                   hTree->muPhi->at(1),0);                   
    a = m1+m2;       
    if (a.M() < 20 || a.M() > 70) continue;
    ptOrdered.aMu->Fill(a.M());
    btagOrdered.aMu->Fill(a.M());
    std::vector<int> bQuarkJetIndecies;
    std::vector<std::pair<TLorentzVector,float> > bQuarkJets;
    std::vector<std::pair<TLorentzVector,float> > bQuarkJetsBtagOrderd;
    for(unsigned int iJet = 0; iJet < hTree->jetsPt->size(); iJet++){
        if(fabs(hTree->jetsFlavour->at(iJet)) == 5 ){
	    bQuarkJetIndecies.push_back(iJet);
            TLorentzVector b;
	    b.SetPtEtaPhiE(hTree->jetsPt->at(iJet), hTree->jetsEta->at(iJet), hTree->jetsPhi->at(iJet), hTree->jetsE->at(iJet));
	    bQuarkJets.push_back(make_pair(b,hTree->jetsBtag->at(iJet)));	
	    bQuarkJetsBtagOrderd.push_back(make_pair(b,hTree->jetsBtag->at(iJet)));
        }
    }
    if(bQuarkJets.size() < 2 ) continue;
    if(bQuarkJets.size() > 2){
	btagSort<std::pair<TLorentzVector,float> > mybtag;
	std::sort(bQuarkJetsBtagOrderd.begin(),bQuarkJetsBtagOrderd.end(),mybtag);
    }
    float mB = (bQuarkJets[0].first+bQuarkJets[1].first).M();
    float mH = ((bQuarkJets[0].first+bQuarkJets[1].first)+a).M();
    double R = a.M()/mB;
    ptOrdered.abQjorig->Fill(mB);
    ptOrdered.hbQjorig->Fill(mH);
    float mBb = (bQuarkJetsBtagOrderd[0].first+bQuarkJetsBtagOrderd[1].first).M();
    float mHb = ((bQuarkJetsBtagOrderd[0].first+bQuarkJetsBtagOrderd[1].first)+a).M();
    double Rb = a.M()/mBb;
    btagOrdered.abQjorig->Fill(mBb);
    btagOrdered.hbQjorig->Fill(mHb);
    bQuarkJets[0].first.SetPxPyPzE(R*bQuarkJets[0].first.Px(),R*bQuarkJets[0].first.Py(),R*bQuarkJets[0].first.Pz(),R*bQuarkJets[0].first.E());
    bQuarkJets[1].first.SetPxPyPzE(R*bQuarkJets[1].first.Px(),R*bQuarkJets[1].first.Py(),R*bQuarkJets[1].first.Pz(),R*bQuarkJets[1].first.E());    
    mB = (bQuarkJets[0].first+bQuarkJets[1].first).M();
    mH = ((bQuarkJets[0].first+bQuarkJets[1].first)+a).M();
    ptOrdered.abQjReg->Fill(mB);
    ptOrdered.hbQjReg->Fill(mH);
    bQuarkJetsBtagOrderd[0].first.SetPxPyPzE(Rb*bQuarkJetsBtagOrderd[0].first.Px(),Rb*bQuarkJetsBtagOrderd[0].first.Py(),Rb*bQuarkJetsBtagOrderd[0].first.Pz(),Rb*bQuarkJetsBtagOrderd[0].first.E());
    bQuarkJetsBtagOrderd[1].first.SetPxPyPzE(Rb*bQuarkJetsBtagOrderd[1].first.Px(),Rb*bQuarkJetsBtagOrderd[1].first.Py(),Rb*bQuarkJetsBtagOrderd[1].first.Pz(),Rb*bQuarkJetsBtagOrderd[1].first.E());    
    mBb = (bQuarkJetsBtagOrderd[0].first+bQuarkJetsBtagOrderd[1].first).M();
    mHb = ((bQuarkJetsBtagOrderd[0].first+bQuarkJetsBtagOrderd[1].first)+a).M();
    btagOrdered.abQjReg->Fill(mBb);
    btagOrdered.hbQjReg->Fill(mHb);
    if (!((hTree->jetsBtag->at(bQuarkJetIndecies[0]) < 0.814) || (hTree->jetsBtag->at(bQuarkJetIndecies[1]) < 0.814))) {
    	ptOrdered.abQjRegMed->Fill(mB);
    	ptOrdered.hbQjRegMed->Fill(mH);    
    }
    if(!((bQuarkJetsBtagOrderd[0].second < 0.814) || (bQuarkJetsBtagOrderd[1].second < 0.814))){
    	btagOrdered.abQjRegMed->Fill(mBb);
    	btagOrdered.hbQjRegMed->Fill(mHb);    
    }
    //cout<< hTree->aMu_mass<<endl;
  }
  TFile * f = new TFile("hist_"+fname, "recreate");
  f->cd();
  ptOrdered.Write(f);
  btagOrdered.Write(f);
  f->Close();
  return 1;
}

