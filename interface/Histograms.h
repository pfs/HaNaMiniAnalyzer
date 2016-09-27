#ifndef Histograms_H
#define Histograms_H

#include <valarray> 
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH2D.h"

using namespace std;

template<typename T>
class BaseHistograms {
public:
  std::vector<T*> theHists;
  unsigned int NW;

  TFileDirectory subDir;
  TString SampleName;
  TString PropName;
  
  BaseHistograms( TString samplename , TString propname ,unsigned int nW = 1 ) :
    NW( nW ),
    SampleName(samplename),
    PropName(propname) {
    edm::Service<TFileService> fs;
    subDir = fs->mkdir( PropName.Data() );
  };
};

class Histogram1D : public BaseHistograms<TH1> {
public:
  typedef BaseHistograms<TH1> base;
  Histogram1D( TString samplename , TString propname , int nbins , double from , double to , unsigned int nW = 1 );
  Histogram1D( TString samplename , TString propname , int nbins , double* bins ,unsigned int nW = 1);
  void Fill( double v  , std::valarray<double> w);
  void Fill( double v  , double w=1.0);
};

typedef Histogram1D Histograms;



#endif
