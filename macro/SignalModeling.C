#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
//50:     	RooRealVar sigma("sigma", "sigma",  0.1,0.,10.);  

RooFitResult* fitToSignal(TString Mass, int nbin = 100){
		TString name = "test";
	    double bL = 10.;
    	double bH = 70.;
   		TString pf = "4";		
    	RooRealVar aMuMass("aMuMass", "aMuMass", 10, 70);
    	TFile * fsig = new TFile("GGH" + Mass + ".root", "read");
		 	
    	TTree* hsig = (TTree*) fsig->Get("Hamb/Trees/Events");
    	RooDataSet data("data_dimu", "data", hsig, aMuMass, "");
    	
    	TH1D * hist = (TH1D*)data.createHistogram("hist",aMuMass,Binning(nbin));
    	cout<<hist->GetMean()<<endl;
    	RooRealVar mean("mean", "mean", hist->GetMean(), 10,70);
    	RooRealVar sigma("sigma", "sigma", 0,1);  
    	RooRealVar width("width", "width", 0.048);    	
    	RooVoigtian Voig("tmp","",aMuMass,mean, width,sigma);    	

    	RooRealVar mean_cb("mean_cb", "Mean", hist->GetMean(), 10, 70);
		RooRealVar sigma_cb("sigma_cb", "Width",  0., 2);
		RooRealVar n1("n1", "", 2.31);
		RooRealVar alpha("alpha", "",1.25);
    	RooCBShape CB("cball", "crystal ball", aMuMass, mean_cb, sigma_cb, alpha, n1);
    	
    	RooRealVar frac("frac","frac",0.55);
    	RooAddPdf Voig2("sum", "Gaussian crystal ball and Voig PDF", RooArgList(Voig, CB), RooArgList(frac));
    	RooFitResult * ret = Voig2.fitTo(data,RooFit::Save());
		cout<<"============ ret: "<<ret<<endl;
		RooPlot * p = aMuMass.frame();
		data.plotOn(p);
		Voig2.plotOn(p);
		Voig2.plotOn(p,Components("cball"), LineColor(kRed), LineStyle(kDashed));		
		Voig2.plotOn(p,Components("tmp"), LineColor(kGreen), LineStyle(kDashed));				
		TCanvas C;
		p->Draw();
		C.SaveAs("testCBVoig_"+Mass+".C");
	
		delete 	hist;	
		return ret;
}


void SignalModeling(int seed = 37) {
    using namespace RooFit;
    using namespace std;
    int nbin = 50;
    bool binned = false;

	TString myMasses[]={"20","25","30","35","40","45","50","55","60"};
    ///	Data-fit ////////////////
	
	std::vector<RooFitResult*> results;
    results.push_back(fitToSignal("20"));
    results.push_back(fitToSignal("25"));    
    results.push_back(fitToSignal("30"));
    results.push_back(fitToSignal("35"));    
    results.push_back(fitToSignal("40"));
    results.push_back(fitToSignal("45"));    
    results.push_back(fitToSignal("50"));
    results.push_back(fitToSignal("55"));
    results.push_back(fitToSignal("60"));
    
    ofstream f("tmp.C");
    
    const unsigned int massSize = results.size();
    stringstream means;
    stringstream meansErrL;    
    stringstream meansErrH;        
    means<<"	double means["<<massSize<<"] = {";
    meansErrL<<"	double meansErrL["<<massSize<<"] = {";
    meansErrH<<"	double meansErrH["<<massSize<<"] = {";
    
    stringstream sigmas;
    stringstream sigmasErrL;
    stringstream sigmasErrH;        
    sigmas<<"	double sigmas["<<massSize<<"] = {";
    sigmasErrL<<"	double sigmasErrL["<<massSize<<"] = {";
    sigmasErrH<<"	double sigmasErrH["<<massSize<<"] = {";
        
    stringstream widths;
    stringstream widthsErrL;
    stringstream widthsErrH;        
    widths<<"	double widths["<<massSize<<"] = {";
    widthsErrL<<"	double widthsErrL["<<massSize<<"] = {";
    widthsErrH<<"	double widthsErrH["<<massSize<<"] = {";
    
    
    stringstream mean_cbs;
    stringstream mean_cbsErrL;    
    stringstream mean_cbsErrH;        
    mean_cbs<<"	double mean_cbs["<<massSize<<"] = {";
    mean_cbsErrL<<"	double mean_cbsErrL["<<massSize<<"] = {";
    mean_cbsErrH<<"	double mean_cbsErrH["<<massSize<<"] = {";
    
    stringstream sigma_cbs;
    stringstream sigma_cbsErrL;
    stringstream sigma_cbsErrH;        
    sigma_cbs<<"	double sigma_cbs["<<massSize<<"] = {";
    sigma_cbsErrL<<"	double sigma_cbsErrL["<<massSize<<"] = {";
    sigma_cbsErrH<<"	double sigma_cbsErrH["<<massSize<<"] = {";
        
    stringstream ns;
    stringstream nsErrL;
    stringstream nsErrH;        
    ns<<"	double ns["<<massSize<<"] = {";
    nsErrL<<"	double nsErrL["<<massSize<<"] = {";
    nsErrH<<"	double nsErrH["<<massSize<<"] = {";
         
    stringstream alphas;
    stringstream alphasErrL;
    stringstream alphasErrH;        
    alphas<<"	double alphas["<<massSize<<"] = {";
    alphasErrL<<"	double alphasErrL["<<massSize<<"] = {";
    alphasErrH<<"	double alphasErrH["<<massSize<<"] = {";
    
    stringstream fracs;
    stringstream fracsErrL;
    stringstream fracsErrH;        
    fracs<<"	double fracs["<<massSize<<"] = {";
    fracsErrL<<"	double fracsErrL["<<massSize<<"] = {";
    fracsErrH<<"	double fracsErrH["<<massSize<<"] = {";

    
    for(unsigned int i = 0; i < results.size(); i++){
    	RooRealVar* mean = (RooRealVar*) results[i]->floatParsFinal().find("mean");
    	RooRealVar* sigma = (RooRealVar*) results[i]->floatParsFinal().find("sigma");    
    	RooRealVar* width = (RooRealVar*) results[i]->floatParsFinal().find("width");
    	RooRealVar* mean_cb = (RooRealVar*) results[i]->floatParsFinal().find("mean_cb");
    	RooRealVar* sigma_cb = (RooRealVar*) results[i]->floatParsFinal().find("sigma_cb");    
    	RooRealVar* alpha = (RooRealVar*) results[i]->floatParsFinal().find("alpha");    	
    	RooRealVar* n = (RooRealVar*) results[i]->floatParsFinal().find("n1");    
    	RooRealVar* frac_ = (RooRealVar*) results[i]->floatParsFinal().find("frac");        	
    	TString append = ", ";
    	if (i == (results.size()-1))
    		append = "};";
    		
   	    means<<mean->getVal()<<append;
	    meansErrL<<fabs(mean->getErrorLo())<<append;
	    meansErrH<<mean->getErrorHi()<<append;  
   	    sigmas<<sigma->getVal()<<append;
	    sigmasErrL<<fabs(sigma->getErrorLo())<<append;
	    sigmasErrH<<sigma->getErrorHi()<<append;  
	    if(width != NULL){ 	    
   	    	widths<<width->getVal()<<append;
	    	widthsErrL<<fabs(width->getErrorLo())<<append;
	    	widthsErrH<<width->getErrorHi()<<append;   	  
	    } else {
	    	widths<<0<<append;
	    	widthsErrL<<0<<append;
	    	widthsErrH<<0<<append;	    
	    }    
	  

   	    mean_cbs<<mean_cb->getVal()<<append;
	    mean_cbsErrL<<fabs(mean_cb->getErrorLo())<<append;
	    mean_cbsErrH<<mean_cb->getErrorHi()<<append;  
   	    sigma_cbs<<sigma_cb->getVal()<<append;
	    sigma_cbsErrL<<fabs(sigma_cb->getErrorLo())<<append;
	    sigma_cbsErrH<<sigma_cb->getErrorHi()<<append; 
	    if(n != NULL){ 	    
   	    	ns<<n->getVal()<<append;
	    	nsErrL<<fabs(n->getErrorLo())<<append;
	    	nsErrH<<n->getErrorHi()<<append;  	  
	    } else {
	    	ns<<0<<append;
	    	nsErrL<<0<<append;
	    	nsErrH<<0<<append;
	    }
	    if(alpha != NULL){ 
   	    	alphas<<alpha->getVal()<<append;
		    alphasErrL<<fabs(alpha->getErrorLo())<<append;
		    alphasErrH<<alpha->getErrorHi()<<append;
	    } else {
   		    alphas<<0<<append;
		    alphasErrL<<0<<append;
		    alphasErrH<<0<<append;	    
	    }
	    if(frac_ != NULL){ 	    
	    	fracs<<frac_->getVal()<<append;
		    fracsErrL<<fabs(frac_->getErrorLo())<<append;
		    fracsErrH<<frac_->getErrorHi()<<append;	
	    } else {
   		    fracs<<0<<append;
		    fracsErrL<<0<<append;
		    fracsErrH<<0<<append;	    
	    }	         		    	
    }
  	f <<"{"<<endl;    
  	f <<"	Int_t N = "<<massSize<<";"<<endl;
  	f <<"	double x["<<massSize<<"] = {";
  	for(unsigned int i = 0; i <massSize; i++ )
  		f << myMasses[i]<<", ";
  	
  	f <<"};"<<endl;  	
  	f <<"	double exl["<<massSize<<"] = {0,0,0,0};"<<endl;  	  	
  	f <<"	double exh["<<massSize<<"] = {0,0,0,0};"<<endl;  	  	
  	
	f <<"	TCanvas M;"<<endl;
	f <<"	M.Divide(4,2);"<<endl;		    
	
	f <<means.str()<<endl;
    f <<meansErrL.str()<<endl;    
    f <<meansErrH.str()<<endl;        
	f <<"	TGraphAsymmErrors Means(N, x, means, exl, exh, meansErrL, meansErrH);"<<endl;
	f <<"	Means.SetNameTitle(\"MeanV\",\"Mean Voig\");"<<endl;
    f <<"	M.cd(1);"<<endl;
    f <<"	Means.Draw(\"ap\");"<<endl;    
    f <<endl;
    f <<sigmas.str()<<endl;
    f <<sigmasErrL.str()<<endl;
    f <<sigmasErrH.str()<<endl;        
	f <<"	TGraphAsymmErrors Sigmas(N, x, sigmas, exl, exh, sigmasErrL, sigmasErrH);"<<endl;
	f <<"	Sigmas.SetNameTitle(\"SigmaV\",\"Sigma Voig\");"<<endl;	
    f <<"	M.cd(2);"<<endl;
    f <<"	Sigmas.Draw(\"ap\");"<<endl; 
    f <<endl;        
    f <<widths.str()<<endl;
    f <<widthsErrL.str()<<endl;
    f <<widthsErrH.str()<<endl;        
	f <<"	TGraphAsymmErrors Widths(N, x, widths, exl, exh, widthsErrL, widthsErrH);"<<endl;
	f <<"	Widths.SetNameTitle(\"WidthV\",\"Width Voig\");"<<endl;		
    f <<"	M.cd(3);"<<endl;
    f <<"	Widths.Draw(\"ap\");"<<endl; 	
    f <<endl;    
    f <<mean_cbs.str()<<endl;
    f <<mean_cbsErrL.str()<<endl;    
    f <<mean_cbsErrH.str()<<endl;        
	f <<"	TGraphAsymmErrors Mean_cbs(N, x, mean_cbs, exl, exh, mean_cbsErrL, mean_cbsErrH);"<<endl;
	f <<"	Mean_cbs.SetNameTitle(\"Mean_cbs\",\"Mean CB\");"<<endl;			
    f <<"	M.cd(4);"<<endl;
    f <<"	Mean_cbs.Draw(\"ap\");"<<endl; 
    f <<endl;    
    f <<sigma_cbs.str()<<endl;
    f <<sigma_cbsErrL.str()<<endl;
    f <<sigma_cbsErrH.str()<<endl;        
	f <<"	TGraphAsymmErrors Sigma_cbs(N, x, sigma_cbs, exl, exh, sigma_cbsErrL, sigma_cbsErrH);"<<endl;
	f <<"	Sigma_cbs.SetNameTitle(\"Sigma_cbs\",\"Sigma CB\");"<<endl;				
    f <<"	M.cd(5);"<<endl;
    f <<"	Sigma_cbs.Draw(\"ap\");"<<endl;   
    f <<endl;          
    f <<ns.str()<<endl;
    f <<nsErrL.str()<<endl;
    f <<nsErrH.str()<<endl;        
	f <<"	TGraphAsymmErrors Ns(N, x, ns, exl, exh, nsErrL, nsErrH);"<<endl;
	f <<"	Ns.SetNameTitle(\"Ns\",\"N CB\");"<<endl;					
    f <<"	M.cd(6);"<<endl;
    f <<"	Ns.Draw(\"ap\");"<<endl;  
    f <<endl;           
    f <<alphas.str()<<endl;
    f <<alphasErrL.str()<<endl;
    f <<alphasErrH.str()<<endl;        
	f <<"	TGraphAsymmErrors Alphas(N, x, alphas, exl, exh, alphasErrL, alphasErrH);"<<endl;
	f <<"	Alphas.SetNameTitle(\"Alphas\",\"Alpha CB\");"<<endl;						
    f <<"	M.cd(7);"<<endl;
    f <<"	Alphas.Draw(\"ap\");"<<endl;         
    f <<endl;  
    f <<fracs.str()<<endl;
    f <<fracsErrL.str()<<endl;
    f <<fracsErrH.str()<<endl;        
	f <<"	TGraphAsymmErrors Fracs(N, x, fracs, exl, exh, fracsErrL, fracsErrH);"<<endl;
	f <<"	Fracs.SetNameTitle(\"Fracs\",\"Fracs\");"<<endl;						
    f <<"	M.cd(8);"<<endl;
    f <<"	Fracs.Draw(\"ap\");"<<endl;         
    f <<endl;   
    f <<"	M.SaveAs(\"allParameters.C\");"<<endl;

   
    f <<"}"<<endl;
    f.close();
    
}
