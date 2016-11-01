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
#include "TLorentzVector.h"
#include <string>
#include <vector>
#include <sstream>
#define HambTree_cxx
#include "../interface/HambTree.h"
using namespace std;


/*
 * 
 */
struct particleinfo{
    float pt, eta, phi , mass, b1Index , b2Index; 
    particleinfo( double pt_=-999, double eta_ =-999, double phi_=-999 , double mass_ = -999 , double b1_ = -999, double b2_ = -999 ){
      pt = pt_;
      eta= eta_;
      phi = phi_;
      mass = mass_;
      b1Index = b1_;
      b2Index = b2_;
    };
    void set( double pt_=-999, double eta_ =-999, double phi_=-999 , double mass_ = -999 , double b1_ = -999, double b2_ = -999 ){
      pt = pt_;
      eta= eta_;
      phi = phi_;
      mass = mass_;
      b1Index = b1_;
      b2Index = b2_;
    };
  };
int main(int argc, char** argv) {
    HambTree * rds;
    TString names;
    TString treename = "Hamb/Trees/Events";
    TH1D * cutflow = 0;
    TString Mode = "";
    bool blind = false;
    for (int f = 1; f < argc; f++) {
        std::string arg_fth(*(argv + f));
        if (arg_fth == "mc") {
            f++;
            std::string out(*(argv + f));
            //TFile * fdata = TFile::Open((string("eos_cb/user/a/ajafari/Hamb13/Oct14_8020_Opt/Trees/")+out).c_str());
			TFile * fdata = TFile::Open(out.c_str());            
            rds = new HambTree((TTree*) fdata->Get(treename));
            int pos = out.find(".root");
            names = (out.substr(0, pos).c_str());
	    cutflow = new TH1D(*(TH1D*) fdata->Get(string("Hamb/CutFlowTable/CutFlowTable_").c_str()+names+string("_0").c_str()));
        } else if(arg_fth == "Mode"){
            f++;
            std::string out(*(argv + f));
            Mode = out.c_str();       
        }
    }


    TFile * fout = new TFile(names + "_withMhs.root", "recreate");
    fout->cd();
	TDirectory* hamb = fout->mkdir("Hamb");
	hamb->mkdir("Trees")->cd();
	
	particleinfo mH, mHReg, mHb, mHbReg;
	float amuMass;
        TTree * newTree = rds->fChain->CloneTree(0);
        if(Mode == "Opt"){
	        newTree->Branch("mH", &mH, "pt:eta:phi:mass:b1Index:b2Index");
    	    newTree->Branch("mHb", &mHb, "pt:eta:phi:mass:b1Index:b2Index");
    	    newTree->Branch("mHReg", &mHReg, "pt:eta:phi:mass:b1Index:b2Index");
    	    newTree->Branch("mHbReg", &mHbReg, "pt:eta:phi:mass:b1Index:b2Index");
		} else if (Mode == "Reg") {
	        newTree->Branch("higgs", &mH, "pt:eta:phi:mass:b1Index:b2Index");
    	    newTree->Branch("abjet", &mHb, "pt:eta:phi:mass:b1Index:b2Index");
    	    newTree->Branch("higgsReg", &mHReg, "pt:eta:phi:mass:b1Index:b2Index");
    	    newTree->Branch("abjetReg", &mHbReg, "pt:eta:phi:mass:b1Index:b2Index");		
		} else {
	        newTree->Branch("aMuMass", &amuMass);			
		}
        cout << rds->fChain->GetEntriesFast() << endl;
        for (int eventNumber = 0; eventNumber < rds->fChain->GetEntriesFast(); eventNumber++) {
	    particleinfo tmp;
	    mH = mHReg = mHb = mHbReg = tmp;
        rds->GetEntry(eventNumber);
		if(Mode == "Opt"){
		    if (rds->muPt->size() <  2)  continue;
    	        if (rds->jetsPt->size() <  2) continue;
    	        if (rds->muPt->at(0) < 25 ) continue;
    	        if (rds->muPt->at(1) < 10 )  continue;
    	        if (rds->jetsPt->at(0) < 20 ) continue;
    	        if (rds->jetsPt->at(1) < 15 )  continue;
    	        if (rds->metSig > 2 )  continue;
    	        TLorentzVector m1,m2,a;
    	        m1.SetPtEtaPhiM(rds->muPt->at(0),
    	               rds->muEta->at(0),
    	               rds->muPhi->at(0),0);
    	        int myIndex = -1;    	        
    	        for(unsigned int i = 1; i < rds->muEta->size(); i++){
    	        	if((!rds->muCharge->at(i) && rds->muCharge->at(0)) || (rds->muCharge->at(i) && !rds->muCharge->at(0))){
    	        		myIndex = i;
    	        		break;
    	        	}    	        
    	        }
    	        if(myIndex == -1){
    	        	cout<<"ERROR WITH MU CHARGE"<<endl;
    	        	return -1;  
    	        }      
    	        
    	        m2.SetPtEtaPhiM(rds->muPt->at(myIndex),
    	               rds->muEta->at(myIndex),
    	               rds->muPhi->at(myIndex),0);                   
    	        a = m1+m2;       
    	        if (a.M() < 15 || a.M() > 70) continue;
		    //No b-flavor requested
		    TLorentzVector bJet1,bJet2, H;
    	        bJet1.SetPtEtaPhiE(rds->jetsPt->at(0), rds->jetsEta->at(0), rds->jetsPhi->at(0), rds->jetsE->at(0));
    	        bJet2.SetPtEtaPhiE(rds->jetsPt->at(1), rds->jetsEta->at(1), rds->jetsPhi->at(1), rds->jetsE->at(1));
		    H = bJet1+bJet2+a;
		    mH.set(H.Pt(), H.Eta(), H.Phi(), H.M(), 0,1);
		    double R = a.M()/(bJet1+bJet2).M();
		    bJet1 = R*bJet1;
		    bJet2 = R*bJet2;
		    H = bJet1+bJet2+a;
		    mHReg.set(H.Pt(), H.Eta(), H.Phi(), H.M(), 0,1);
	
		    //With b-flavor
            std::vector<int> bQuarkJetIndecies;
            std::vector<TLorentzVector> bQuarkJets;
            for(unsigned int iJet = 0; iJet < rds->jetsPt->size(); iJet++){
            	if(fabs(rds->jetsFlavour->at(iJet)) == 5 ){
            		bQuarkJetIndecies.push_back(iJet);
            		TLorentzVector b;
            		b.SetPtEtaPhiE(rds->jetsPt->at(iJet), rds->jetsEta->at(iJet), rds->jetsPhi->at(iJet), rds->jetsE->at(iJet));
            		bQuarkJets.push_back(b);	
        		}
    	    }
           if(bQuarkJets.size() > 1 ) {
			   	H = bQuarkJets[0]+bQuarkJets[1]+a;
		    	mHb.set(H.Pt(), H.Eta(), H.Phi(), H.M(), bQuarkJetIndecies[0],bQuarkJetIndecies[1]);
		    	R = a.M()/(bQuarkJets[0]+bQuarkJets[1]).M();
		    	bQuarkJets[0] = R*bQuarkJets[0];
		    	bQuarkJets[1] = R*bQuarkJets[1];
		    	H = bQuarkJets[0]+bQuarkJets[1]+a;
		    	mHbReg.set(H.Pt(), H.Eta(), H.Phi(), H.M(), 0,1);
		    }
		    newTree->Fill();
		} else  if (Mode == "Reg"){
   	        TLorentzVector m1,m2,a;
  	        m1.SetPtEtaPhiM(rds->muPt->at(0),
   	               rds->muEta->at(0),
   	               rds->muPhi->at(0),0);
   	        int myIndex = -1;    	        
   	        for(unsigned int i = 1; i < rds->muEta->size(); i++){
    	       	if((!rds->muCharge->at(i) && rds->muCharge->at(0)) || (rds->muCharge->at(i) && !rds->muCharge->at(0))){
    	       		myIndex = i;
    	       		break;
    	       	}    	        
    	     }
    	     if(myIndex == -1){
    	       	cout<<"ERROR WITH MU CHARGE"<<endl;
    	       	return -1;  
    	     }      
    	        
    	     m2.SetPtEtaPhiM(rds->muPt->at(myIndex),
    	               rds->muEta->at(myIndex),
    	               rds->muPhi->at(myIndex),0);                       
   	        a = m1+m2;       
		    //No b-flavor requested
		    TLorentzVector bJet1,bJet2, H, ab;
   	        bJet1.SetPtEtaPhiE(rds->jetsPt->at(0), rds->jetsEta->at(0), rds->jetsPhi->at(0), rds->jetsE->at(0));
   	        bJet2.SetPtEtaPhiE(rds->jetsPt->at(1), rds->jetsEta->at(1), rds->jetsPhi->at(1), rds->jetsE->at(1));
    	    ab = bJet1+bJet2;
		    H = bJet1+bJet2+a;
		    mH.set(H.Pt(), H.Eta(), H.Phi(), H.M(), 0,1);
		    mHb.set(ab.Pt(), ab.Eta(), ab.Phi(), ab.M(), 0,1);
		    double R = a.M()/(bJet1+bJet2).M();
		    bJet1 = R*bJet1;
		    bJet2 = R*bJet2;
    	    ab = bJet1+bJet2;		    
			H = bJet1+bJet2+a;
		    mHReg.set(H.Pt(), H.Eta(), H.Phi(), H.M(), 0,1);
		    mHbReg.set(ab.Pt(), ab.Eta(), ab.Phi(), ab.M(), 0,1);
		    newTree->Fill();	
		} else {
			amuMass = rds->aMu_mass;
		    newTree->Fill();			
		}
	}
    newTree->Write();
	hamb->mkdir("CutFlowTable")->cd();
	cutflow->Write();
	fout->cd();
    fout->Save();
    fout->Close();
    
    	return 1;
}

