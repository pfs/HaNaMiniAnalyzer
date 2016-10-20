#include <vector>
#include <string>
#include <iostream>
using namespace std;

TString findmass(TString histname){
	string input = string(histname);
	int a = input.find("Signal");
	return (input.substr(a+6,2)).c_str();
}

void compareSignificances(TString fname, TString type, TFile * out){
	TFile * f = TFile::Open(fname);
	TList * cutList = f->GetListOfKeys();
	TDirectory * origDir;
	TDirectory * regDir;
	for(int i = 0; i < cutList->GetSize(); i++){
		if(string(cutList->At(i)->GetName()) == string("CutFlowTable"))
			continue;
		cout<<cutList->At(i)->GetName()" has started"<<endl;
		std::vector<TCanvas*> comps;
		origDir = (TDirectory*)f->Get((string(cutList->At(i)->GetName())+string("/HiggsMDiff/Significances")).c_str());
   		TString name = 	(string(cutList->At(i)->GetName())+string("/bHiggsMDiff/Significances")).c_str();
		regDir = (TDirectory*)f->Get(name);
		TList * histList = ((TDirectory*)origDir->Get(type))->GetListOfKeys();
		TList * histList2 = ((TDirectory*)regDir->Get(type))->GetListOfKeys();
		TCanvas * canvas;
		TH1D * hOrig;
		TH1D * h;
		for(int ihist = 0; ihist < histList->GetSize(); ihist++){
			hOrig = ((TH1D*)origDir->Get((string(type)+string("/")+string(histList->At(ihist)->GetName())).c_str()));
			TString mass = findmass(hOrig->GetName());			
			hOrig->SetTitle("Original, m = "+mass);
			hOrig->SetStats(kFALSE);
			TString name2 = (string(type)+string("/")+string(histList2->At(ihist)->GetName())).c_str();
			h = (TH1D*)regDir->Get(name2);
			h->SetTitle("Regression, m = "+mass);
			h->SetLineColor(kBlue);
			h->SetStats(kFALSE);
			double max = hOrig->GetMaximum();
			if(h->GetMaximum() > max)	
				max = h->GetMaximum();
			hOrig->SetMaximum(max*1.3);
			canvas = new TCanvas(h->GetName());
			canvas->cd();
			hOrig->Draw();
			h->Draw("SAMES");
			canvas->BuildLegend();
			comps.push_back(canvas);
		}
		cout<<comps.size()<<endl;
		out->cd();
		out->mkdir(cutList->At(i)->GetName())->cd();
		for(unsigned int iCan = 0; iCan < comps.size(); iCan++)
			comps[iCan]->Write();
		cout<<cutList->At(i)->GetName()<<" is finished"<<endl;
	}
	out->cd();
	out->Close();	
}


void compareLimits(TString fname, TFile * out){
	TFile * f = TFile::Open(fname);
	TList * cutList = f->GetListOfKeys();
	TDirectory * origDir;
	TDirectory * regDir;
	for(int i = 0; i < cutList->GetSize(); i++){
		if(string(cutList->At(i)->GetName()) == string("CutFlowTable"))
			continue;
		cout<<cutList->At(i)->GetName()<<" has started"<<endl;
		std::vector<TCanvas*> comps;
		origDir = (TDirectory*)f->Get((string(cutList->At(i)->GetName())+string("/HiggsMDiff/ExpLimits")).c_str());
   		TString name = 	(string(cutList->At(i)->GetName())+string("/bHiggsMDiff/ExpLimits")).c_str();
		regDir = (TDirectory*)f->Get(name);
		TList * histList = origDir->GetListOfKeys();
		TList * histList2 = regDir->GetListOfKeys();
		TCanvas * canvas;
		TH1D * hOrig;
		TH1D * h;
		for(int ihist = 0; ihist < histList->GetSize(); ihist++){
			hOrig = ((TH1D*)origDir->Get(histList->At(ihist)->GetName()));
			TString mass = findmass(hOrig->GetName());			
			hOrig->SetTitle("Original, m = "+mass);
			hOrig->SetStats(kFALSE);
			h = (TH1D*)regDir->Get(histList2->At(ihist)->GetName());
			h->SetTitle("Regression, m = "+mass);
			h->SetLineColor(kBlue);
			h->SetStats(kFALSE);
			double max = hOrig->GetMaximum();
			if(h->GetMaximum() > max)	
				max = h->GetMaximum();
			hOrig->SetMaximum(max*1.3);
			canvas = new TCanvas(h->GetName());
			canvas->cd();
			hOrig->Draw();
			h->Draw("SAMES");
			canvas->BuildLegend();
			comps.push_back(canvas);
		}
		cout<<comps.size()<<endl;
		out->cd();
		out->mkdir(cutList->At(i)->GetName())->cd();
		for(unsigned int iCan = 0; iCan < comps.size(); iCan++)
			comps[iCan]->Write();
		cout<<cutList->At(i)->GetName()<<" is finished"<<endl;
	}
	out->cd();
	out->Close();	
}


void RegEffectCheck(){
	TFile * out = new TFile ("SoSqrtB_RegCheck.root","recreate");
	compareSignificances("out_mH_ttdy_significance_all.root","SoSqrtB",out);
	TFile * out2 = new TFile ("SoSqrtBdB2_RegCheck.root","recreate");
	compareSignificances("out_mH_ttdy_significance_all.root","SoSqrtBdB2",out2);	
	TFile * out3 = new TFile ("LnSoSqrtSB_RegCheck.root","recreate");
	compareSignificances("out_mH_ttdy_significance_all.root","LnSoSqrtSB",out3);
	TFile * outLimit = new TFile ("Limits_RegCheck.root","recreate");
	compareLimits("out_mH_ttdy_limit_all.root",outLimit);


}
