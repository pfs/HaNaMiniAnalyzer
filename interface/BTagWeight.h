//https://github.com/nfaltermann/ST_RunII_EA/blob/master/src/DMAnalysisTreeMaker.cc
//https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods    (method 1a)

#include <vector>
#include <iostream>
#include <string>

#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
using namespace std;



/*
 *
 * enum OperatingPoint {
 *     OP_LOOSE=0,
 *     OP_MEDIUM=1,
 *     OP_TIGHT=2,
 *     OP_RESHAPING=3,
 *     };
 * enum JetFlavor {
 *     FLAV_B=0,
 *     FLAV_C=1,
 *     FLAV_UDSG=2,
 *     };
 *
 */



class BTagWeight
  {
  private:
    string algo;
    int WPT, WPL;
    int syst;
    float bTagMapCSVv2[3];
  public:
    BTagWeight(string algorithm, int WPt, string setupDir, double BLCut = 0.460, double BMCut = 0.800, 
        double BTCut = 0.935, int WPl = -1, int systematics = 0): 
	algo(algorithm), WPT(WPt), WPL(WPl), syst(systematics),readerExc(0),readerCentExc(0)
    {
	bTagMapCSVv2[0] = BLCut;
	bTagMapCSVv2[1] = BMCut;
	bTagMapCSVv2[2] = BTCut;
	if(WPL != -1){
    		if (WPL > WPT){
		       	int tmp;
		       	tmp = WPL;
			WPL = WPT;
			WPT = tmp;
		}
	}
	Systs[0] = "central";
	Systs[-1] = "down";
	Systs[1] = "up";
	cout<< setupDir+"/"+algo+string(".csv")<<endl;
	calib = new BTagCalibration(algo /*"CSVv2"*/, setupDir+"/"+algo+string(".csv"));
	reader = new BTagCalibrationReader(calib,(BTagEntry::OperatingPoint)WPT,"mujets",Systs[syst]);
        readerCent = new BTagCalibrationReader(calib,(BTagEntry::OperatingPoint)WPT,"mujets","central");  
	readerLight = new BTagCalibrationReader(calib,(BTagEntry::OperatingPoint)WPT,"incl",Systs[syst]);
        readerCentLight = new BTagCalibrationReader(calib,(BTagEntry::OperatingPoint)WPT,"incl","central");  
	if(WPL != -1){
		readerExc = new BTagCalibrationReader(calib,(BTagEntry::OperatingPoint)WPL,"mujets",Systs[syst]);
        	readerCentExc = new BTagCalibrationReader(calib,(BTagEntry::OperatingPoint) WPL,"mujets","central");  
		readerExcLight = new BTagCalibrationReader(calib,(BTagEntry::OperatingPoint)WPL,"incl",Systs[syst]);
        	readerCentExcLight = new BTagCalibrationReader(calib,(BTagEntry::OperatingPoint) WPL,"incl","central");  
	}

	/* Sanity checks
	 * std::cout<< "---- BTag WPs ----\n\t" <<bTagMapCSVv2[0] <<",\t"<<bTagMapCSVv2[1] <<",\t"<<bTagMapCSVv2[2]
	 *	 <<"\n---- WPs to select ----\n\t"<<bTagMapCSVv2[WPT]
	 *	 <<"\n---- WPs to veto ----\n\t";
	 *	 if(WPL != -1) std::cout << bTagMapCSVv2[WPL]<<std::endl;
	 *	 else std::cout << "No veto is requested" <<std::endl;
	 * End Sanity Checks
	 */
    };
    float weight(pat::JetCollection jets);
    float weightExclusive(pat::JetCollection jetsTags);
    float TagScaleFactor(pat::Jet jet, bool LooseWP = false);
    float MCTagEfficiency(pat::Jet jet, int WP);
    std::map<int, string> Systs;
    BTagCalibration * calib;
    BTagCalibrationReader * reader;
    BTagCalibrationReader * readerCent;
    BTagCalibrationReader * readerExc;
    BTagCalibrationReader * readerCentExc;
    BTagCalibrationReader * readerLight;
    BTagCalibrationReader * readerCentLight;
    BTagCalibrationReader * readerExcLight;
    BTagCalibrationReader * readerCentExcLight;
  };

float BTagWeight::weight(pat::JetCollection jets){
    float pMC = 1;
    float pData = 1;
	std::cout<<"In jet loop! "<<WPT <<std::endl;
    for (auto j : jets){
	float eff = this->MCTagEfficiency(j,WPT);
	std::cout<<"MC efficiency: "<<eff<<"\t";
	float sf= this->TagScaleFactor(j);
	std::cout<<"Data/MC SF: "<<sf<<endl;
	if(j.bDiscriminator(algo)>bTagMapCSVv2[WPT] ){
		pMC*=eff;
		pData*=sf*eff;
	}else{
		pMC*=(1-eff);
		pData*=(1-sf*eff);
	}
	std::cout<< pMC << "\t"<<pData<<", Probability: "<<pData/pMC<<endl;
    }
    return pData/pMC;
}

//*************************************************************************
//DONT USE !!!!! METHOD INCOMPLETE ****************************************
//*************************************************************************
float BTagWeight::weightExclusive(pat::JetCollection jets){
//This function takes into account cases where you have n b-tags and m vetoes, but they have different thresholds.
    if(WPL == -1){
	std::cout<<"FATAL ERROR: Provide the second btag WP!!!!"<<std::endl;
	return 0;
    } 
    float pMC = 1;
    float pData = 1;
    for (auto j : jets){
	float effL = this->MCTagEfficiency(j,WPL);
	float sfL= this->TagScaleFactor(j,(WPL != -1));
	float effT = this->MCTagEfficiency(j,WPT);
	float sfT= this->TagScaleFactor(j);
	if(j.bDiscriminator(algo) > bTagMapCSVv2[WPT]){
		pMC*=effT;
		pData*=sfT*effT;
	}else if (j.bDiscriminator(algo) > bTagMapCSVv2[WPL]){
		pMC*=(effL-effT);
		pData*=fabs(sfL*effL - sfT*effT);
	} else {
		pMC*=(1-effL);
		pData*=(1-sfL*effL);
	}
    }
    
    return pData/pMC;
}
//*************************************************************************

float BTagWeight::MCTagEfficiency(pat::Jet jet, int WP){
  int flavor = fabs(jet.hadronFlavour());
  if(flavor == 5){
    if(WP==0) return 0.38; //L
    if(WP==1) return 0.58; //M
    if(WP==2) return 0.755;//T
  }
  if(flavor == 4){
    if(WP==0) return 0.015; //L
    if(WP==1) return 0.08; //M
    if(WP==2) return 0.28;//T
  }
  if(flavor != 4){
    if(WP==0) return 0.0008; //L
    if(WP==1) return 0.007; //M
    if(WP==2) return 0.079;//T
 }
  return 1.0;
}

float BTagWeight::TagScaleFactor(pat::Jet jet, bool LooseWP ){

	float MinJetPt = 20.;
	float MaxBJetPt = 670., MaxLJetPt = 1000.;
        float JetPt = jet.pt(); bool DoubleUncertainty = false;
	int flavour = fabs(jet.hadronFlavour());
	cout<<"Jet Flavor: "<<flavour<<endl;
	if(flavour == 5) flavour = BTagEntry::FLAV_B;
	else if(flavour == 4) flavour = BTagEntry::FLAV_C;
	else flavour = BTagEntry::FLAV_UDSG;
	
	if(flavour != BTagEntry::FLAV_UDSG){
	   if (JetPt>MaxBJetPt)  { // use MaxLJetPt for  light jets
        	JetPt = MaxBJetPt; 
        	DoubleUncertainty = true;
      	   }
	} else {
 	   cout<<"Jet is Light!"<<endl;
	   if (JetPt>MaxLJetPt)  { // use MaxLJetPt for  light jets
                JetPt = MaxBJetPt;
                DoubleUncertainty = true;
           }
	}
	if(JetPt<MinJetPt){
	   JetPt = MinJetPt;
	   DoubleUncertainty = true;
	}

	float jet_scalefactor = 1;
	if((BTagEntry::JetFlavor)flavour != BTagEntry::FLAV_UDSG){
		jet_scalefactor = reader->eval((BTagEntry::JetFlavor)flavour, jet.eta(), JetPt); 
		if(LooseWP)
			jet_scalefactor = readerExc->eval((BTagEntry::JetFlavor)flavour, jet.eta(), JetPt);
	} else {
		jet_scalefactor = readerLight->eval((BTagEntry::JetFlavor)flavour, jet.eta(), JetPt);
		if(LooseWP)
			jet_scalefactor = readerExcLight->eval((BTagEntry::JetFlavor)flavour, jet.eta(), JetPt);
	}

	cout<<"\tSF is "<<jet_scalefactor<<endl;

	if(DoubleUncertainty && syst != 0){
	        float jet_scalefactorCent = 1;
		if((BTagEntry::JetFlavor)flavour != BTagEntry::FLAV_UDSG){
			jet_scalefactorCent = readerCent->eval((BTagEntry::JetFlavor)flavour, jet.eta(), JetPt); 
			if(LooseWP)
				jet_scalefactorCent = readerCentExc->eval((BTagEntry::JetFlavor)flavour, jet.eta(), JetPt);
		} else {
			jet_scalefactorCent = readerCentLight->eval((BTagEntry::JetFlavor)flavour, jet.eta(), JetPt); 
			if(LooseWP)
				jet_scalefactorCent = readerCentExcLight->eval((BTagEntry::JetFlavor)flavour, jet.eta(), JetPt);
		}
                jet_scalefactor = 2*(jet_scalefactor - jet_scalefactorCent) + jet_scalefactorCent; 
	}
	return jet_scalefactor;
}

