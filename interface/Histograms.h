#ifndef Histograms_H
#define Histograms_H


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"

using namespace std;

class Histograms {
public:
  TH1* theHist;
  TH1* theHistNoW;
  TString SampleName;
  TString PropName;

  Histograms( TString samplename , TString propname , int nbins , double from , double to );
  Histograms( TString samplename , TString propname , int nbins , double* bins );

  void Fill( double v , double w=1.0 );
  
};

Histograms::Histograms( TString samplename , TString propname , int nbins , double from , double to ) : SampleName(samplename),
													PropName(propname){
  edm::Service<TFileService> fs;
  TFileDirectory subDir = fs->mkdir( PropName.Data() );
  theHist = subDir.make<TH1D>( propname + "_" + samplename , propname , nbins , from , to );
  theHistNoW = subDir.make<TH1D>( propname + "_NoW_" + samplename , propname , nbins , from , to );
}

Histograms::Histograms( TString samplename , TString propname , int nbins , double* bins) : SampleName(samplename),
											    PropName(propname){
  edm::Service<TFileService> fs;
  TFileDirectory subDir = fs->mkdir( PropName.Data() );
  theHist = subDir.make<TH1D>( propname + "_" + samplename , propname , nbins , bins );
  theHistNoW = subDir.make<TH1D>( propname + "_NoW_" + samplename , propname , nbins , bins );
}

void Histograms::Fill( double v , double w ){
  theHist->Fill( v , w );
  theHistNoW->Fill( v , w == 0 ? 1 : (w/fabs(w)) );
}

#endif
