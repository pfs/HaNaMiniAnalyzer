//TString dirs[6]={"LL","ML","TL","MM","TM","TT"};
TString dirs[6]={"TL","TL","TL","TL","TL","TL"};
TString var = "amuMass";
TString bkgs[3] =  {"Top","DY","DY"};
TString sigs[10] = {"15","20","25","30","35","40","45","50","55","60"};
double corr[10] = {1.3, 1.3, 1.3, 1.3, 1.2, 1.2, 1.1, 1.1, 1.1, 1.1};
void YieldExtractor(){
	//TFile * f = TFile::Open("out_mH_ttdy_significance_Opt.root");
	TFile * f = TFile::Open("out_mH_ttdy_significance_TL_chi2Sum5MET60_m20_5.root");
	cout<<"||";
	for(int i = 0; i < 13; i++){
			TString mysample;
			if(i < 3) mysample = bkgs[i];
			else mysample = sigs[i-3];
			cout <<	mysample	<<" | ";
	}
	cout<<endl;
	for(int icut = 0; icut < 6; icut++){
		cout << "| "<<dirs[icut] <<"|";
		for(int i = 0; i < 13; i++){
			TString mysample;
			TString histname = dirs[icut] +"/"+var+"/";
			if(i < 3) {
				mysample = bkgs[i];
				histname = histname + "cats/"+dirs[icut]+"_"+var+"_"+mysample;
			} else {
				mysample = sigs[i-3];
				histname = histname + "signals/"+dirs[icut]+"_"+var+"_Signal"+mysample;
			}
			//cout<<"--- "<<histname<<endl;
			if(i > 2)
				cout << corr[i-3]*((TH1D*)f->Get(histname))->Integral() <<"|";	
			else
				cout << ((TH1D*)f->Get(histname))->Integral() <<"|";
		}
		cout<<endl;
	}
}
