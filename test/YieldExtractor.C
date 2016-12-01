TString dirs[16]={"Trigger","MuPt","JetPt","OptimCuts", "JetPt25","MET", "METJet25", "Chi2B","Chi2H","Chi2Sum","LL","ML","TL","MM","TM","TT"};
TString var = "aMuMass";
TString bkgs[3] =  {"Top","DY","Diboson"};
TString sigs[10] = {"15","20","25","30","35","40","45","50","55","60"};
void YieldExtractor(){
	TFile * f = TFile::Open("out_cft_normtolumi_unblind_checkYields.root");
	cout<<"||";
	for(int i = 0; i < 13; i++){
			TString mysample;
			if(i < 3) mysample = bkgs[i];
			else mysample = sigs[i-3];
			cout <<	mysample	<<" | ";
	}
	cout<<endl;
	for(int icut = 0; icut < 16; icut++){
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
			cout << ((TH1D*)f->Get(histname))->Integral() <<"|";	
		}
		cout<<endl;
	}
}
