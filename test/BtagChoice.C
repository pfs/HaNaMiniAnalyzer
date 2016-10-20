#include <vector>
#include <string>
#include <iostream>
using namespace std;
const TString massVals[9] = {"15","20","25","30","35","40","45","55","60"};
const TString p1 = "ROC_";
const TString p2 = "HiggsMDiff_Signal";

std::vector<TString> GetLabels(TFile * f, TString higgsType){
	TList * cutList = f->GetListOfKeys();
	std::vector<TString> labels;
	for(int iBtagComb = 0; iBtagComb < cutList->GetSize(); iBtagComb++){
		if(string(cutList->At(iBtagComb)->GetName()) == string("CutFlowTable"))
			continue;
		TString name = cutList->At(iBtagComb)->GetName();
		if(name.Contains("b") && higgsType == "b"){
			labels.push_back(cutList->At(iBtagComb)->GetName());
		}
		if(!(name.Contains("b")) && higgsType == ""){
			labels.push_back(cutList->At(iBtagComb)->GetName());
		}
		
	}
	return labels;
}

std::vector<TH1D*> compareSignificances(TString fname, TString higgsType /* "b" or ""*/, TString SigType){
	TFile * f = TFile::Open(fname);
	TList * cutList = f->GetListOfKeys();
	std::vector<TString> labels = GetLabels(f, higgsType);
	
	TString hname = "BtagComp_";
	if(higgsType == "")
		hname = hname+"Orig_"+SigType;
	else
		hname = hname+"Reg_"+SigType;
	TString foutname = hname+".root";
	std::vector<TH1D*> myhists;
	TH1D * tmp = 0;
	for(int iMass = 0; iMass < 9; iMass++){
		TString hname2 = hname+"_"+massVals[iMass];
		TH1D * h = new TH1D(hname2,"",6,-0.5,5.5);
		tmp = 0;
		for(unsigned int iBtag = 0; iBtag < labels.size(); iBtag++){
			TString histName = labels[iBtag]+"/"+higgsType+"HiggsMDiff/Significances/"+SigType+"/"+p1+labels[iBtag]+"_"+higgsType+p2+massVals[iMass]+"_"+SigType;
			cout<<histName<<endl;
			tmp = (TH1D*)f->Get(histName);
			tmp->GetXaxis()->SetRangeUser(tmp->GetXaxis()->GetXmin(),tmp->GetXaxis()->GetBinLowEdge(tmp->GetXaxis()->GetNbins()-2));
			h->SetBinContent(iBtag+1, (tmp->GetMaximum()));
			h->GetXaxis()->SetBinLabel(iBtag+1 , labels[iBtag]);
		}
		myhists.push_back(h);
	}
	return myhists;
}

std::vector<TH1D*> compareLimits(TString fname, TString higgsType /* "b" or ""*/){
	TFile * f = TFile::Open(fname);
	TList * cutList = f->GetListOfKeys();
	std::vector<TString> labels = GetLabels(f, higgsType);
	
	TString hname = "BtagComp_";
	if(higgsType == "")
		hname = hname+"Orig";
	else
		hname = hname+"Reg";
	TString foutname = hname+".root";
	std::vector<TH1D*> myhists;
	TH1D * tmp = 0;
	for(int iMass = 0; iMass < 9; iMass++){
		TString hname2 = hname+"_"+massVals[iMass];
		TH1D * h = new TH1D(hname2,"",6,-0.5,5.5);
		tmp = 0;
		for(unsigned int iBtag = 0; iBtag < labels.size(); iBtag++){
			TString histName = labels[iBtag]+"/"+higgsType+"HiggsMDiff/ExpLimits/"+p1+labels[iBtag]+"_"+higgsType+p2+massVals[iMass]+"_ExpLimit";
			cout<<histName<<endl;
			tmp = (TH1D*)f->Get(histName);
			tmp->GetXaxis()->SetRangeUser(tmp->GetXaxis()->GetXmin(),tmp->GetXaxis()->GetBinLowEdge(tmp->GetXaxis()->GetNbins()-2));
			h->SetBinContent(iBtag+1, (tmp->GetMinimum()));
			h->GetXaxis()->SetBinLabel(iBtag+1 , labels[iBtag]);
		}
		myhists.push_back(h);
	}
	return myhists;
}

void BtagChoice(){
	std::vector<TH1D*> vec1 = compareSignificances("out_mH_ttdy_significance_all.root","","SoSqrtB");
	std::vector<TH1D*> vec2 = compareSignificances("out_mH_ttdy_significance_all.root","","SoSqrtBdB2");
	std::vector<TH1D*> vec3 = compareSignificances("out_mH_ttdy_significance_all.root","","LnSoSqrtSB");
	
	TFile * f = new TFile("BtagComp_Orig_Significance.root","recreate");
	f->mkdir("SoSqrtB")->cd();
	for(unsigned int i = 0; i<vec1.size(); i++)
		vec1[i]->Write();
	f->cd();
	
	f->mkdir("SoSqrtBdB2")->cd();	
	for(unsigned int i = 0; i<vec2.size(); i++)
		vec2[i]->Write();
	f->cd();
	
	f->mkdir("LnSoSqrtSB")->cd();	
	for(unsigned int i = 0; i<vec3.size(); i++)
		vec3[i]->Write();
	f->cd();	
	f->Write();
	f->Close();

	f = new TFile("BtagComp_Orig_Limit.root","recreate");	
	std::vector<TH1D*> vec4 = compareLimits("out_mH_ttdy_limit_all.root","");
	f->mkdir("Limits")->cd();	
	for(unsigned int i = 0; i<vec4.size(); i++)
		vec4[i]->Write();
	f->cd();
	f->Write();
	f->Close();

}
