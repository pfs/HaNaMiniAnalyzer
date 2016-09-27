#include "../interface/Category.h"
#include <iostream>
using namespace std;
Category::Category( TString name, TString SampleName) : Name(name){
    hNPV_pv = new Histograms(Name+"_NPV_pv", SampleName, 100, -0.5, 99.5);
    hMuMult = new Histograms(Name+"_MuMult", SampleName, 10, -0.5, 9.5);
    hJetMult = new Histograms(Name+"_JetMult", SampleName, 10, -0.5, 9.5);
    hBJetMult = new Histograms(Name+"_BJetMult", SampleName, 10, -0.5, 9.5);
    hNPV_final = new Histograms(Name+"_NPV_final", SampleName, 100, -0.5, 99.5);
    hMuPt = new Histograms(Name+"_MuPt", SampleName, 30, 0., 150.);
    hMuEta = new Histograms(Name+"_MuEta", SampleName, 30, -3.0, 3.0);
    hLeadMuPt = new Histograms(Name+"_LeadMuPt", SampleName, 30, 0., 150.);
    hLeadMuEta = new Histograms(Name+"_LeadMuEta", SampleName, 30, -3.0, 3.0);
    hSubLeadMuPt = new Histograms(Name+"_SubLeadMuPt", SampleName, 30, 0., 150.);
    hSubLeadMuEta = new Histograms(Name+"_SubLeadMuEta", SampleName, 30, -3.0, 3.0);
    hDiMuMass = new Histograms(Name+"_DiMuMass", SampleName, 85, 10., 180.);
    hDiMuPt = new Histograms(Name+"_DiMuPt", SampleName, 40, 0., 200.);
    hDiMuDr = new Histograms(Name+"_DiMuDr", SampleName, 50, 0, 5.0);
    hJetPt = new Histograms(Name+"_JetPt", SampleName, 30, 0., 150.);
    hJetEta = new Histograms(Name+"_JetEta", SampleName, 50, -5.0, 5.0);
    hJetBTag = new Histograms(Name+"_JetBTag", SampleName, 20, 0, 1.);
    hLeadJetPt = new Histograms(Name+"_LeadJetPt", SampleName, 30, 0., 150.);
    hLeadJetEta = new Histograms(Name+"_LeadJetEta", SampleName, 50, -5.0, 5.0);
    hLeadJetBTag = new Histograms(Name+"_LeadJetBTag", SampleName, 20, 0, 1.);
    hSubLeadJetPt = new Histograms(Name+"_SunLeadJetPt", SampleName, 30, 0., 150.);
    hSubLeadJetEta = new Histograms(Name+"_SubLeadJetEta", SampleName, 50, -5.0, 5.0);
    hSubLeadJetBTag = new Histograms(Name+"_SubLeadJetBTag", SampleName, 20, 0, 1.);
    hDiBJetMass = new Histograms(Name+"_DiBJetMass", SampleName, 30, 0., 300.);
    hDiBJetPt = new Histograms(Name+"_DiBJetPt", SampleName, 15, 0., 150.);
    hDiBJetDr = new Histograms(Name+"_DiBJetDr", SampleName, 50, 0, 5.0);
    hFourBodyMass = new Histograms(Name+"_FourBodyMass", SampleName, 120, 0., 1200.);
    hFourBodyPt = new Histograms(Name+"_FourBodyPt", SampleName, 20, 0., 200.);
    hDiffMassMuB = new Histograms(Name+"_DiffMassMuB", SampleName, 15, 0., 150.);
    hRelDiffMassMuB = new Histograms(Name+"_RelDiffMassMuB", SampleName, 20, 0, 1.);
    hMET = new Histograms(Name+"_MET", SampleName, 20, 0., 200.);
    hMETSignificance = new Histograms(Name+"_METSignificance", SampleName, 100, 0, 100.);
}


void Category::Fill( std::vector<float> v , double w = 1., double PU = -1. ){
    if(PU != -1)
    	hNPV_pv->Fill(v[0],w/(PU==0. ? 1.0 : PU));
    else
        hNPV_pv->Fill(v[0],w);
    hMuMult->Fill(v[1], w);
    hJetMult->Fill(v[2], w);
    hBJetMult->Fill(v[3], w);
    hNPV_final->Fill(v[4], w);
    hMuPt->Fill(v[5], w);
    hMuEta->Fill(v[6], w);
    hMuPt->Fill(v[32], w);
    hMuEta->Fill(v[33], w);
    hLeadMuPt->Fill(v[7], w);
    hLeadMuEta->Fill(v[8], w);
    hSubLeadMuPt->Fill(v[9], w);
    hSubLeadMuEta->Fill(v[10], w);
    hDiMuMass->Fill(v[11], w);
    hDiMuPt->Fill(v[12], w);
    hDiMuDr->Fill(v[13], w);
    hJetPt->Fill(v[14], w);
    hJetEta->Fill(v[15], w);
    hJetBTag->Fill(v[16], w);
    hLeadJetPt->Fill(v[17], w);
    hLeadJetEta->Fill(v[18], w);
    hLeadJetBTag->Fill(v[19], w);
    hSubLeadJetPt->Fill(v[20], w);
    hSubLeadJetEta->Fill(v[21], w);
    hSubLeadJetBTag->Fill(v[22], w);
    hDiBJetMass->Fill(v[23], w);
    hDiBJetPt->Fill(v[24], w);
    hDiBJetDr->Fill(v[25], w);
    hFourBodyMass->Fill(v[26], w);
    hFourBodyPt->Fill(v[27], w);
    hDiffMassMuB->Fill(v[28], w);
    hRelDiffMassMuB->Fill(v[29], w);
    hMET->Fill(v[30], w);
    hMETSignificance->Fill(v[31], w);
    int diff = v.size() - 34;
    if(diff <= 0) return;
    if((diff % 3) != 0) {
	cout<<"Problem with number of jet quantities, pt, eta, btag"<<endl;
	return;
    }
    for(int i = 0; i < (int)(diff/3); i++){
	hJetPt->Fill(v[i], w);
	hJetEta->Fill(v[i], w);
	hJetBTag->Fill(v[i], w);
    }
}

