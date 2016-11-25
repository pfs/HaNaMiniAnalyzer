#include <iostream>
#include <sstream>

#include "TFile.h"
#include "TArrow.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TStyle.h"
#include "TChain.h"
#include "TH2.h"
#include "TH1.h"
#include "TF1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
#include "TMath.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TVirtualFitter.h"

#include <stdio.h>
#include <math.h>

void Mytest (int Nbins=55, int Ndata=5000, double alpha=0.1, int option=1) {
 	double xmin = 20.;
 	double xmax = 70.;
 	
 	double xsecDylm13 = 22635.1;
 	double xsecDyhm13 = 6025.2;
 	double xsecDyhm8 = 3503.71;
 	double xsecDylm8 = 13229.7;
 	
 	cout<< "low mass: "<<xsecDylm13/xsecDylm8<<endl;
 	cout<< "high mass: "<<xsecDyhm13/xsecDyhm8<<endl;
 	
  	gStyle->SetOptFit(111111);
  	gStyle->SetOptStat(0);
  	// To read the data:
  	// ------------------------------
    RooDataSet::setDefaultStorageType(RooAbsData::Tree);
	RooRealVar * var = new RooRealVar("aMuMass", "aMuMass", 15, 70);
    TFile * input = TFile::Open("out_cft_normtolumi_Signal.root");
    TH1D * h = (TH1D*) input->Get("SigCount/aMuMass/cats/SumMC");
    int nData = h->Integral();
    cout<<nData<<endl;
	RooDataHist* data_h = new RooDataHist("data_h","data_h", RooArgList(*var), h);
	RooHistPdf histpdf1("histpdf1","histpdf1",*var,*data_h,0) ;
    RooDataSet* data2 = histpdf1.generate(*var,nData);
    
    RooKeysPdf kest1("kest1","kest1",*var,*data2,RooKeysPdf::MirrorBoth);
    RooDataSet* newdata = kest1.generate(*var,nData);
    
    RooPlot* frame = var->frame(RooFit::Title("new data"),RooFit::Bins(55)) ;
    newdata->plotOn(frame);
    histpdf1->plotOn(frame);
    //data->plotOn(frame);
    //kest1.plotOn(frame) ; 
    frame->Draw();
    cout<<(((RooTreeDataStore*)newdata->store())->tree()).GetEntries()<<endl;
    TFile * f = new TFile("myData.root","recreate");
    if (newdata->store()->InheritsFrom(RooTreeDataStore::Class())==kTRUE) cout<<"It is OK!"<<endl;
    (((RooTreeDataStore*)newdata->store())->tree()).Write("Events");
    
    f->Close();
}

