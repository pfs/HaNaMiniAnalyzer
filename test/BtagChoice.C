#include <vector>
#include <string>
#include <iostream>
using namespace std;
const TString hist = "amuMass";
const TString massVals[9] = {"15","20","25","30","35","40","45","55","60"};
const TString p1 = "ROC_";
const TString p2 = hist + "_Signal";
const TString bCom[6] = {"LL","ML","TL","MM","TM","TT"};
const TString bComB[6] = {"LLb","MLb","TLb","MMb","TMb","TTb"};
std::vector<TString> GetLabels(TString higgsType){
	std::vector<TString> labels;
	for(int iBtagComb = 0; iBtagComb < 6; iBtagComb++){
		if(higgsType == "b"){
			labels.push_back(bComB[iBtagComb]);
		}
		if(higgsType == ""){
			labels.push_back(bCom[iBtagComb]);
		}
		
	}
	return labels;
}

double mHCutFinder(TH1D * h, bool Max = true){
	double max = h->GetMaximum();
	if(!Max)
		max = h->GetMinimum();
	int bin = 0;
	//h->GetBinWithContent(max, bin);
	for(int i = 0; i<h->GetXaxis()->GetNbins(); i++){
		if(h->GetBinContent(i+1) == max){
			bin = i+1;
			break;
		}
	}
	cout <<">>>>>>>>>>>> " << bin <<"\t"<<max<<endl;
	return h->GetXaxis()->GetBinUpEdge(bin);
}

std::vector<TH1D*> compareSignificances(TString fname, TString higgsType /* "b" or ""*/, TString SigType, std::vector<TH1D*>& Ms, TString matchTyp = ""){
	TFile * f = TFile::Open(fname);
	TList * cutList = f->GetListOfKeys();
	std::vector<TString> labels = GetLabels(matchTyp);
	
	
	TString hname = "BtagComp_";
	if(higgsType == "")
		hname = hname+"Orig_"+SigType;
	else
		hname = hname+"Reg_"+SigType;
	if(matchTyp != "")
		hname = hname+"_MatchedJets";
	TString foutname = hname+".root";
	std::vector<TH1D*> myhists;
	TH1D * tmp = 0;
	for(int iMass = 0; iMass < 9; iMass++){
		TString hname2 = hname+"_"+massVals[iMass];
		TH1D * h = new TH1D(hname2,"",6,-0.5,5.5);
		TH1D * mass = new TH1D(hname2+"_mass","",6,-0.5,5.5);		
		tmp = 0;
		for(unsigned int iBtag = 0; iBtag < labels.size(); iBtag++){
			TString histName = labels[iBtag]+"/"+higgsType+hist+"/Significances/"+SigType+"/"+p1+labels[iBtag]+"_"+higgsType+p2+massVals[iMass]+"_"+SigType;
			cout<<histName<<endl;
			tmp = (TH1D*)f->Get(histName);
			//tmp->GetXaxis()->SetRangeUser(tmp->GetXaxis()->GetXmin(),tmp->GetXaxis()->GetBinLowEdge(tmp->GetXaxis()->GetNbins()-2));
			tmp->GetXaxis()->SetRangeUser(0,40);
			h->SetBinContent(iBtag+1, (tmp->GetMaximum()));
			cout << tmp->GetMaximum()<< "  --- "<<endl;
			double bin = mHCutFinder(tmp);
			mass->SetBinContent(iBtag+1, bin);
			cout<<"|"<<massVals[iMass]<<"|"<<bin<<"|"<<endl;
			h->GetXaxis()->SetBinLabel(iBtag+1 , labels[iBtag]);
			mass->GetXaxis()->SetBinLabel(iBtag+1 , labels[iBtag]);
		}
		myhists.push_back(h);
		Ms.push_back(mass);
	}
	return myhists;
}

std::vector<TH1D*> compareLimits(TString fname, TString higgsType /* "b" or ""*/, std::vector<TH1D*>& Ms, TString matchTyp = ""){
	TFile * f = TFile::Open(fname);
	TList * cutList = f->GetListOfKeys();
	std::vector<TString> labels = GetLabels(matchTyp);
	
	TString hname = "BtagComp_";
	if(higgsType == "")
		hname = hname+"Orig";
	else
		hname = hname+"Reg";
	if(matchTyp != "")
		hname = hname+"_MatchedJets";	
	TString foutname = hname+".root";
	std::vector<TH1D*> myhists;
	TH1D * tmp = 0;
	for(int iMass = 0; iMass < 9; iMass++){
		TString hname2 = hname+"_"+massVals[iMass];
		TH1D * h = new TH1D(hname2,"",6,-0.5,5.5);
		TH1D * mass = new TH1D(hname2+"_mass","",6,-0.5,5.5);
		tmp = 0;
		for(unsigned int iBtag = 0; iBtag < labels.size(); iBtag++){
			TString histName = labels[iBtag]+"/"+higgsType+hist+"/ExpLimits/"+p1+labels[iBtag]+"_"+higgsType+p2+massVals[iMass]+"_ExpLimit";
			cout<<histName<<endl;
			tmp = (TH1D*)f->Get(histName);
			//tmp->GetXaxis()->SetRangeUser(tmp->GetXaxis()->GetXmin(),tmp->GetXaxis()->GetBinLowEdge(tmp->GetXaxis()->GetNbins()-2));
			tmp->GetXaxis()->SetRangeUser(0,40);
			h->SetBinContent(iBtag+1, (tmp->GetMinimum()));
			double bin = mHCutFinder(tmp, false);
			cout<<"|"<<massVals[iMass]<<"|"<<bin<<"|"<<endl;	
			mass->SetBinContent(iBtag+1, bin);
			h->GetXaxis()->SetBinLabel(iBtag+1 , labels[iBtag]);
			mass->GetXaxis()->SetBinLabel(iBtag+1 , labels[iBtag]);
		}
		myhists.push_back(h);
		Ms.push_back(mass);
	}
	return myhists;
}

void BtagChoice(){

	TString match = "";
	TString ismatched ="";

	if(match == "b") ismatched = "_MatchedJets";
	//std::vector<TH1D*> vec1 = compareSignificances("out_mH_ttdy_significance_all.root","b","SoSqrtB",match);
	//std::vector<TH1D*> vec2 = compareSignificances("out_mH_ttdy_significance_all.root","b","SoSqrtBdB2",match);
	std::vector<TH1D*> mass3;
	std::vector<TH1D*> vec3 = compareSignificances("out_mH_ttdy_significance_Opt.root","","LnSoSqrtSB", mass3, match);
	std::vector<TH1D*> mass4;
	std::vector<TH1D*> vec4 = compareSignificances("out_mH_ttdy_significance_Opt.root","","LnSoSqrtSBdB", mass4, match);	
	TFile * f = new TFile("BtagComp_Reg_Significance"+ismatched+"_Opt.root","recreate");
	/*f->mkdir("SoSqrtB")->cd();
	for(unsigned int i = 0; i<vec1.size(); i++)
		vec1[i]->Write();
	f->cd();
	
	f->mkdir("SoSqrtBdB2")->cd();	
	for(unsigned int i = 0; i<vec2.size(); i++)
		vec2[i]->Write();
	f->cd();
	*/
	f->mkdir("LnSoSqrtSB")->cd();	
	for(unsigned int i = 0; i<vec3.size(); i++){
		vec3[i]->Write();
		mass3[i]->Write();
	}
	f->cd();	
	f->mkdir("LnSoSqrtSBdB")->cd();	
	for(unsigned int i = 0; i<vec4.size(); i++){
		vec4[i]->Write();
		mass4[i]->Write();
	}
	f->cd();
	f->Write();
	f->Close();

	TFile *f = new TFile("BtagComp_Reg_Limit"+ismatched+"_Opt.root","recreate");	
	std::vector<TH1D*> eMass;
	std::vector<TH1D*> vec5 = compareLimits("out_mH_ttdy_limit_Opt.root","",eMass,match);
	f->mkdir("Limits")->cd();	
	for(unsigned int i = 0; i<vec5.size(); i++){
		vec5[i]->Write();
		eMass[i]->Write();
	}
	f->cd();
	f->Write();
	f->Close();

}
