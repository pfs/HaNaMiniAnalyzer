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
    	RooRealVar sigma("sigma", "sigma", 0.2,0,10);  
    	RooRealVar width("width", "width", hist->GetRMS(), 0, 100*hist->GetRMS());    	
    	RooVoigtian Voig("tmp","",aMuMass,mean, width,sigma);    	

    	RooRealVar mean_cb("mean_cb", "Mean", hist->GetMean(), 10, 70);
		RooRealVar sigma_cb("sigma_cb", "Width", 2.3, 0., 260.0);
		RooRealVar n("n", "", 6,0,50);
		RooRealVar alpha("alpha", "", 5,0.0, 10);
    	RooCBShape CB("cball", "crystal ball", aMuMass, mean_cb, sigma_cb, alpha, n);
    	
    	RooRealVar frac("frac","frac",0.5,0.,1.);
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
    /*stringstream means;
    stringstream meansErrL;    
    stringstream meansErrH;        
    means<<"	double means[4] = {";
    meansErrL<<"	double meansErrL[4] = {";
    meansErrH<<"	double meansErrH[4] = {";
    
    stringstream sigmas;
    stringstream sigmasErrL;
    stringstream sigmasErrH;        
    sigmas<<"	double sigmas[4] = {";
    sigmasErrL<<"	double sigmasErrL[4] = {";
    sigmasErrH<<"	double sigmasErrH[4] = {";
        
    stringstream widths;
    stringstream widthsErrL;
    stringstream widthsErrH;        
    widths<<"	double widths[4] = {";
    widthsErrL<<"	double widthsErrL[4] = {";
    widthsErrH<<"	double widthsErrH[4] = {";
    
    
    stringstream mean_cbs;
    stringstream mean_cbsErrL;    
    stringstream mean_cbsErrH;        
    mean_cbs<<"	double mean_cbs[4] = {";
    mean_cbsErrL<<"	double mean_cbsErrL[4] = {";
    mean_cbsErrH<<"	double mean_cbsErrH[4] = {";
    
    stringstream sigma_cbs;
    stringstream sigma_cbsErrL;
    stringstream sigma_cbsErrH;        
    sigma_cbs<<"	double sigma_cbs[4] = {";
    sigma_cbsErrL<<"	double sigma_cbsErrL[4] = {";
    sigma_cbsErrH<<"	double sigma_cbsErrH[4] = {";
        
    stringstream ns;
    stringstream nsErrL;
    stringstream nsErrH;        
    ns<<"	double ns[4] = {";
    nsErrL<<"	double nsErrL[4] = {";
    nsErrH<<"	double nsErrH[4] = {";
         
    stringstream alphas;
    stringstream alphasErrL;
    stringstream alphasErrH;        
    alphas<<"	double alphas[4] = {";
    alphasErrL<<"	double alphasErrL[4] = {";
    alphasErrH<<"	double alphasErrH[4] = {";
    
    
    for(unsigned int i = 0; i < results.size(); i++){
    	RooRealVar* mean = (RooRealVar*) results[i]->floatParsFinal().find("mean");
    	RooRealVar* sigma = (RooRealVar*) results[i]->floatParsFinal().find("sigma");    
    	RooRealVar* width = (RooRealVar*) results[i]->floatParsFinal().find("width");
    	RooRealVar* mean_cb = (RooRealVar*) results[i]->floatParsFinal().find("mean_cb");
    	RooRealVar* sigma_cb = (RooRealVar*) results[i]->floatParsFinal().find("sigma_cb");    
    	RooRealVar* alpha = (RooRealVar*) results[i]->floatParsFinal().find("alpha");    	
    	RooRealVar* n = (RooRealVar*) results[i]->floatParsFinal().find("n");    
    	TString append = ", ";
    	if (i == (results.size()-1))
    		append = "};";
    		
   	    means<<mean->getVal()<<append;
	    meansErrL<<fabs(mean->getErrorLo())<<append;
	    meansErrH<<mean->getErrorHi()<<append;  
   	    sigmas<<sigma->getVal()<<append;
	    sigmasErrL<<fabs(sigma->getErrorLo())<<append;
	    sigmasErrH<<sigma->getErrorHi()<<append;  	    
   	    widths<<width->getVal()<<append;
	    widthsErrL<<fabs(width->getErrorLo())<<append;
	    widthsErrH<<width->getErrorHi()<<append;  	  

   	    mean_cbs<<mean_cb->getVal()<<append;
	    mean_cbsErrL<<fabs(mean_cb->getErrorLo())<<append;
	    mean_cbsErrH<<mean_cb->getErrorHi()<<append;  
   	    sigma_cbs<<sigma_cb->getVal()<<append;
	    sigma_cbsErrL<<fabs(sigma_cb->getErrorLo())<<append;
	    sigma_cbsErrH<<sigma_cb->getErrorHi()<<append;  	    
   	    ns<<n->getVal()<<append;
	    nsErrL<<fabs(n->getErrorLo())<<append;
	    nsErrH<<n->getErrorHi()<<append;  	  
   	    alphas<<alpha->getVal()<<append;
	    alphasErrL<<fabs(alpha->getErrorLo())<<append;
	    alphasErrH<<alpha->getErrorHi()<<append;	         		    	
    }*/
  /*	cout<<"	Int_t N = 4;"<<endl;
  	cout<<"	double x[4] = {30,40,50,60};"<<endl;  	
  	cout<<"	double exl[4] = {0,0,0,0};"<<endl;  	  	
  	cout<<"	double exh[4] = {0,0,0,0};"<<endl;  	  	
  	
	cout<<"	TCanvas M;"<<endl;
	cout<<"	M.Divide(4,2);"<<endl;		    
	
	cout<<means.str()<<endl;
    cout<<meansErrL.str()<<endl;    
    cout<<meansErrH.str()<<endl;        
	cout<<"	TGraphAsymmErrors Means(N, x, means, exl, exh, meansErrL, meansErrH);"<<endl;
	cout<<"	Means.SetNameTitle(\"MeanV\",\"Mean Voig\");"<<endl;
    cout<<"	M.cd(1);"<<endl;
    cout<<"	Means.Draw(\"ap\");"<<endl;    
    cout<<endl;
    cout<<sigmas.str()<<endl;
    cout<<sigmasErrL.str()<<endl;
    cout<<sigmasErrH.str()<<endl;        
	cout<<"	TGraphAsymmErrors Sigmas(N, x, sigmas, exl, exh, sigmasErrL, sigmasErrH);"<<endl;
	cout<<"	Sigmas.SetNameTitle(\"SigmaV\",\"Sigma Voig\");"<<endl;	
    cout<<"	M.cd(2);"<<endl;
    cout<<"	Sigmas.Draw(\"ap\");"<<endl; 
    cout<<endl;        
    cout<<widths.str()<<endl;
    cout<<widthsErrL.str()<<endl;
    cout<<widthsErrH.str()<<endl;        
	cout<<"	TGraphAsymmErrors Widths(N, x, widths, exl, exh, widthsErrL, widthsErrH);"<<endl;
	cout<<"	Widths.SetNameTitle(\"WidthV\",\"Width Voig\");"<<endl;		
    cout<<"	M.cd(3);"<<endl;
    cout<<"	Widths.Draw(\"ap\");"<<endl; 	
    cout<<endl;    
    cout<<mean_cbs.str()<<endl;
    cout<<mean_cbsErrL.str()<<endl;    
    cout<<mean_cbsErrH.str()<<endl;        
	cout<<"	TGraphAsymmErrors Mean_cbs(N, x, mean_cbs, exl, exh, mean_cbsErrL, mean_cbsErrH);"<<endl;
	cout<<"	Mean_cbs.SetNameTitle(\"Mean_cbs\",\"Mean CB\");"<<endl;			
    cout<<"	M.cd(5);"<<endl;
    cout<<"	Mean_cbs.Draw(\"ap\");"<<endl; 
    cout<<endl;    
    cout<<sigma_cbs.str()<<endl;
    cout<<sigma_cbsErrL.str()<<endl;
    cout<<sigma_cbsErrH.str()<<endl;        
	cout<<"	TGraphAsymmErrors Sigma_cbs(N, x, sigma_cbs, exl, exh, sigma_cbsErrL, sigma_cbsErrH);"<<endl;
	cout<<"	Sigma_cbs.SetNameTitle(\"Sigma_cbs\",\"Sigma CB\");"<<endl;				
    cout<<"	M.cd(6);"<<endl;
    cout<<"	Sigma_cbs.Draw(\"ap\");"<<endl;   
    cout<<endl;          
    cout<<ns.str()<<endl;
    cout<<nsErrL.str()<<endl;
    cout<<nsErrH.str()<<endl;        
	cout<<"	TGraphAsymmErrors Ns(N, x, ns, exl, exh, nsErrL, nsErrH);"<<endl;
	cout<<"	Ns.SetNameTitle(\"Ns\",\"N CB\");"<<endl;					
    cout<<"	M.cd(7);"<<endl;
    cout<<"	Ns.Draw(\"ap\");"<<endl;  
    cout<<endl;           
    cout<<alphas.str()<<endl;
    cout<<alphasErrL.str()<<endl;
    cout<<alphasErrH.str()<<endl;        
	cout<<"	TGraphAsymmErrors Alphas(N, x, alphas, exl, exh, alphasErrL, alphasErrH);"<<endl;
	cout<<"	Alphas.SetNameTitle(\"Alphas\",\"Alpha CB\");"<<endl;						
    cout<<"	M.cd(8);"<<endl;
    cout<<"	Alphas.Draw(\"ap\");"<<endl;         
    cout<<endl;    
    cout<<"	M.SaveAs(\"allParameters.C\");"<<endl;

   
    cout<<endl;
 */   
}
