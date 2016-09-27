#include "../interface/Histograms.h"

Histogram1D::Histogram1D( TString samplename , TString propname , int nbins , double from , double to , unsigned int nW) : Histogram1D::base( samplename ,propname , nW){
  for(unsigned int i=0 ; i < nW ; i++)
    theHists.push_back( subDir.make<TH1D>( propname + "_" + samplename + "_" + std::to_string(i) , propname , nbins , from , to ) );
}

Histogram1D::Histogram1D( TString samplename , TString propname , int nbins , double* bins , unsigned int nW) : Histogram1D::base( samplename ,propname , nW) {
  theHists.push_back( subDir.make<TH1D>( propname + "_" + samplename , propname , nbins , bins ) );
}

void Histogram1D::Fill( double v , double w ){
  for( auto hh : theHists )
    hh->Fill( v , w );
}

void Histogram1D::Fill( double v , std::valarray<double> w ){
  double ww;
  for(unsigned int i=0 ; i < NW ; i++ ){
    ww = 1.0;
    if( w.size() > i )
      ww = w[i];
    theHists[i]->Fill( v , ww );
  }
}



/*




Histograms::Histograms( TString samplename , TString propname , int nbins , double from , double to ) : SampleName(samplename),
													PropName(propname),
													SelectionLevel(""){
  edm::Service<TFileService> fs;
  TFileDirectory subDir = fs->mkdir( PropName.Data() );
  theHist = subDir.make<TH1D>( propname + "_" + samplename , propname , nbins , from , to );
  theHistNoW = subDir.make<TH1D>( propname + "_NoW_" + samplename , propname , nbins , from , to );
}

Histograms::Histograms( TString samplename , TString propname , int nbins , double* bins) : SampleName(samplename),
											    PropName(propname),
											    SelectionLevel(""){
  edm::Service<TFileService> fs;
  TFileDirectory subDir = fs->mkdir( PropName.Data() );
  theHist = subDir.make<TH1D>( propname + "_" + samplename , propname , nbins , bins );
  theHistNoW = subDir.make<TH1D>( propname + "_NoW_" + samplename , propname , nbins , bins );
}

Histograms::Histograms( TString selLev , TString samplename , TString propname , int nbins , double from , double to ) : SampleName(samplename),
															 PropName(propname),
															 SelectionLevel(selLev){
  edm::Service<TFileService> fs;
  TFileDirectory catDir = fs->mkdir( SelectionLevel.Data() );
  TFileDirectory subDir = catDir.mkdir( PropName.Data() );
  theHist = subDir.make<TH1D>( selLev + "_" + propname + "_" + samplename , propname , nbins , from , to );
  theHistNoW = subDir.make<TH1D>( selLev + "_" + propname + "_NoW_" + samplename , propname , nbins , from , to );
}

Histograms::Histograms( TString selLev , TString samplename , TString propname , int nbins , double* bins) : SampleName(samplename),
													     PropName(propname),
													     SelectionLevel(selLev){
  edm::Service<TFileService> fs;
  TFileDirectory catDir = fs->mkdir( SelectionLevel.Data() );
  TFileDirectory subDir = catDir.mkdir( PropName.Data() );
  theHist = subDir.make<TH1D>( selLev + "_" + propname + "_" + samplename , propname , nbins , bins );
  theHistNoW = subDir.make<TH1D>( selLev + "_" + propname + "_NoW_" + samplename , propname , nbins , bins );
}


void Histograms::Fill( double v , double w ){
  theHist->Fill( v , w );
  theHistNoW->Fill( v , 1.0 ) ; //w == 0 ? 1 : (w/fabs(w)) );
}
*/
