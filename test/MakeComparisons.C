#include <vector>
TString dirs[1]={"OptimCuts"};
TString var[16] = {"aMuMass" , "DR" , "DMass" , "Dphi" , "Deta" ,  "hPtReg", "hPt" , "hMassReg" , "hMass" , "LeadmuLeadbMass" ,"LeadmuSubleadbMass", "SubmuLeadbMass", "SubmuSubleadbMass", "Chi2B","Chi2H","Chi2Sum" };
TString sigs[10] = {"15","20","25","30","35","40","45","50","55","60"};

std::vector<TH1D*> histsperVar(int iVar, double & max){
	TFile * f = TFile::Open("out_cft_normtolumi_unblind_checkYields.root");
	std::vector<TH1D*> ret;
	TString mysample = "SumMC";
	for(int icut = 0; icut < 1; icut++){
		TString histname = dirs[icut] +"/"+var[iVar]+"/cats/";
		ret.push_back((TH1D*)f->Get(histname+mysample));
		double tmp = (ret[ret.size()-1]->GetMaximum()/ret[ret.size()-1]->Integral());
		cout << " >>> "<<tmp<<endl;
		if(tmp > max) max = tmp;
		for(int i = 0; i < 10; i++){
			mysample = sigs[i];
			histname = dirs[icut] +"/"+var[iVar] + "/signals/"+dirs[icut]+"_"+var[iVar]+"_Signal"+mysample;
			ret.push_back((TH1D*)f->Get(histname));
			tmp = (ret[ret.size()-1]->GetMaximum()/ret[ret.size()-1]->Integral());
			if(tmp > max) max = tmp;
			cout << "\t"<<tmp<<endl;
		}	
		cout <<"----- "<<max << endl;	
	}
	return ret;
}

void MakeComparisons(){
	std::vector<TCanvas*> cs;
	for(int i = 0; i < 16; i++){
		double max = -100;
		std::vector<TH1D*> hists = histsperVar(i, max);
		CS = new TCanvas("Can_"+var[i],"Can_"+var[i]);
		CS->cd();
		for(unsigned int iHist = 0; iHist < hists.size(); iHist++){
			if(iHist == 0){
				hists[iHist]->SetFillStyle(3002);
				hists[iHist]->SetFillColor(kGray);
				hists[iHist]->SetMaximum(1.3*max*hists[iHist]->Integral());
				hists[iHist]->GetXaxis()->SetTitle(var[i]);
				hists[iHist]->DrawNormalized("HIST");
			} else
				hists[iHist]->DrawNormalized("sames");
		}
		cs.push_back(CS);
		gDirectory->cd();	
	}
	TFile * f = new TFile("comparisons.root","recreate");
	f->cd();
	for(unsigned int iCan = 0; iCan < cs.size(); iCan++)
		cs[iCan]->Write();
	f->Close();
}
