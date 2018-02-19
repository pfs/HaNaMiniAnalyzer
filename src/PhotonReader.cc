#include "Haamm/HaNaMiniAnalyzer/interface/PhotonReader.h"

using namespace edm;
using namespace pat;

PhotonReader::PhotonReader( edm::ParameterSet const& iConfig, edm::ConsumesCollector && iC , bool isData , string SetupDir) :
  BaseEventReader< pat::PhotonCollection >( iConfig , &iC ),
  PhotonEtCut( iConfig.getParameter<double>( "PhotonEtCut" ) ),
  PhotonIsoCut( iConfig.getParameter<double>( "PhotonIsoCut" ) ),
  PhotonEtaCut( iConfig.getParameter<double>( "PhotonEtaCut" ) ),
  PhotonID( iConfig.getParameter<int>( "PhotonID" ) ), // 0 no id, 1 loose, 2 medium, 3 tight, 4 soft
  IsData(isData)
{
  if( !IsData ){
   //readout id scale factors here 
   // TFile* f1 = TFile::Open( TString(SetupDir + "/PhotonIDSF.root") );
   // f1->Close();
  }
  cout << "[PhotonReader][CTOR] ET=" << PhotonETCut  
       << " eta=" << PhotonEtaCut 
       << " id=" << PhotonID
       << " iso=" << PhotonIsoCut 
       << endl;
}

PhotonReader::SelectionStatus PhotonReader::Read( const edm::Event& iEvent){ 
  BaseEventReader< pat::PhotonCollection >::Read( iEvent );
    
  edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
  edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> > tight_id_decisions;
  iEvent.getByToken(phoLooseIdMapToken_ ,loose_id_decisions);
  iEvent.getByToken(phoMediumIdMapToken_,medium_id_decisions);
  iEvent.getByToken(phoTightIdMapToken_ ,tight_id_decisions);
  edm::Handle<edm::ValueMap<vid::CutFlowResult> > medium_id_cutflow_data;
  iEvent.getByToken(phoMediumIdFullInfoMapToken_,medium_id_cutflow_data);
    
   
  goodPhotons.clear();
  for (const pat::Photon &g : *handle) {
    if (g.pt() < PhotonPtCut || fabs(g.eta()) > PhotonEtaCut )
      continue;
      
    bool isPassLoose  = (*loose_id_decisions)[g];
    bool isPassMedium = (*medium_id_decisions)[g];
    bool isPassTight  = (*tight_id_decisions)[g];
    passLooseId_.push_back ( (int)isPassLoose );
    passMediumId_.push_back( (int)isPassMedium);
    passTightId_.push_back ( (int)isPassTight );
      
    if( PhotonID == 1 && !isPassLoose ) continue;
    if( PhotonID == 2 && !isPassMedium) continue;
    if( PhotonID == 3 && !isPassTight)  continue;

    goodPhotons.push_back( g );
  }
    
  W = 1.0;
  //if( !IsData ){
  //  if( MuonIsoCut == 0.25 )
  //    W = MuonSFLoose(  goodMusOS[0].eta() , goodMusOS[0].pt() , goodMusOS[1].eta() , goodMusOS[1].pt() ); 
  //  else if( MuonIsoCut == 0.15 )
  //   W = MuonSFMedium( goodMusOS[0].eta() , goodMusOS[0].pt() , goodMusOS[1].eta() , goodMusOS[1].pt() ); 
  //}
      
  return PhotonReader::Pass;
}
