// -*- C++ -*-
//
// Package:    Haamm/HaNaMiniAnalyzer
// Class:      HaNaMiniAnalyzer
// 
/**\class HaNaMiniAnalyzer HaNaMiniAnalyzer.cc Haamm/HaNaMiniAnalyzer/plugins/HaNaMiniAnalyzer.cc

   Description: [one line class summary]

   Implementation:
   [Notes on implementation]
*/
//
// Original Author:  Hamed Bakhshiansohi
//         Created:  Fri, 25 Mar 2016 10:57:06 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

#include "../interface/Histograms.h"

#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "TRandom3.h"
#include "TH2.h"
#include "TROOT.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

using namespace reco;
using namespace edm;
using namespace std;


class HaNaMiniAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit HaNaMiniAnalyzer(const edm::ParameterSet&);
  ~HaNaMiniAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  double MuonSFMedium( double etaL , double ptL , double etaSL , double ptSL ){
    //AN2016_025_v7 Figure 6, Middle Row, Right for trigger
    double ret = 1.0;

    double el = fabs(etaL);
    double esl = fabs(etaSL);
    if(el < 1.2 && esl < 1.2 )
      ret = 0.926 ;				
    else if( el < 1.2 )
      ret = 0.943;
    else if( esl < 1.2 )
      ret = 0.958 ;
    else 
      ret = 0.926 ;

    ret *= ( hMuSFID->GetBinContent( hMuSFID->FindBin( ptL , el ) ) * hMuSFID->GetBinContent( hMuSFID->FindBin( ptSL , esl ) ) );
    ret *= (hMuSFIso->GetBinContent(hMuSFIso->FindBin(ptL ,el ) ) * hMuSFIso->GetBinContent( hMuSFIso->FindBin( ptSL , esl ) ) );

    return ret;
  }
  double MuonSFLoose( double etaL , double ptL , double etaSL , double ptSL ){
    //AN2016_025_v7 Figure 19, Middle Row, Right for trigger
    double ret = 1.0;
    
    double el = fabs(etaL);
    double esl = fabs(etaSL);
    if(el < 1.2 && esl < 1.2 )
      ret = 0.930 ;				
    else if( el < 1.2 )
      ret = 0.933;
    else if( esl < 1.2 )
      ret = 0.951 ;
    else 
      ret = 0.934 ;

    ret *= ( hMuSFID->GetBinContent( hMuSFID->FindBin( ptL , el ) ) * hMuSFID->GetBinContent( hMuSFID->FindBin( ptSL , esl ) ) );
    ret *= (hMuSFIso->GetBinContent(hMuSFIso->FindBin(ptL ,el ) ) * hMuSFIso->GetBinContent( hMuSFIso->FindBin( ptSL , esl ) ) );

    return ret;
  }

  reco::Candidate::LorentzVector HT4( pat::JetCollection jets ){
    reco::Candidate::LorentzVector ret ;
    for( auto j : jets )
      ret += j.p4();

    return ret;
  };

  float JER( pat::Jet jet , double rho , int syst = 0 ){
    JME::JetParameters parameters_1;
    parameters_1.setJetPt(jet.pt());
    parameters_1.setJetEta(jet.eta());
    parameters_1.setRho( rho );
    float sf = resolution_sf.getScaleFactor(parameters_1);

    const reco::GenJet*  genjet =  jet.genJet ();
    float ret = jet.pt();
    if( genjet != NULL && genjet->pt() > 0 ){
      ret = max(0., genjet->pt() + sf*( jet.pt() - genjet->pt() ) );
    }else{
      float r = resolution.getResolution(parameters_1);
      ret = rndJER->Gaus( jet.pt() , r*sqrt( sf*sf - 1) );
    }
    return ret;
  }

  bool JetLooseID( pat::Jet j ){
    float NHF = j.neutralHadronEnergyFraction ();
    float NEMF = j.neutralEmEnergyFraction ();
    int NumConst = j.numberOfDaughters ();
    float eta = j.eta();
    float CHF = j.chargedHadronEnergyFraction ( ) ;
    float CHM = j.chargedMultiplicity ();
    float CEMF = j.chargedEmEnergyFraction ();
    int NumNeutralParticle = j.neutralMultiplicity ( );
    bool looseJetID1 = (NHF<0.99 && NEMF<0.99 && NumConst>1) && ((abs(eta)<=2.4 && CHF>0 && CHM>0 && CEMF<0.99) || abs(eta)>2.4) && abs(eta)<=3.0 ;
    bool looseJetID2 = (NEMF<0.90 && NumNeutralParticle>10 && abs(eta)>3.0 ) ;

    return looseJetID1 || looseJetID2 ;
  }

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;


  // ----------member data ---------------------------
  Histograms* hCutFlowTable;



  string SetupDir;

  bool LHEWeight ;
  bool IsData ;
  string SampleName;
  std::vector<std::string> HLT_To_Or;

  edm::EDGetTokenT< int > ntrpuToken_;
  edm::EDGetTokenT< LHEEventProduct > lheToken_ ;
  edm::EDGetTokenT< edm::TriggerResults > trigResultsToken_;
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<pat::MuonCollection> muonToken_;
  edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
  edm::EDGetTokenT<pat::JetCollection> jetToken_;
  edm::EDGetTokenT<pat::JetCollection> oldjetToken_;
  edm::EDGetTokenT<pat::METCollection> metToken_;

  double MuonLeadingPtCut, MuonSubLeadingPtCut , MuonIsoCut, MuonEtaCut ;
  double JetPtCut , JetEtaCut , BTagWPL , BTagWPM , BTagWPT ;
  string BTagAlgo ;


  JME::JetResolution resolution;
  JME::JetResolutionScaleFactor resolution_sf;
  edm::EDGetTokenT<double> t_Rho_;
  TRandom3* rndJER;

  edm::LumiReWeighting LumiWeights_;

  TH2* hMuSFID;
  TH2* hMuSFIso;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HaNaMiniAnalyzer::HaNaMiniAnalyzer(const edm::ParameterSet& iConfig):
  SetupDir( iConfig.getParameter<string>("SetupDir") ),

  LHEWeight(iConfig.getParameter< bool >("useLHEW") ),
  IsData( iConfig.getParameter< bool >("isData") ),
  SampleName(iConfig.getParameter< string >("sample") ),
  HLT_To_Or ( iConfig.getParameter< vector<string> >("HLT_To_Or" ) ),
  trigResultsToken_( consumes<edm::TriggerResults>( edm::InputTag("TriggerResults","","HLT" ) ) ),

  vtxToken_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"))),
  muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
  jetToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets"))),
  metToken_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("mets"))),

  MuonLeadingPtCut( iConfig.getParameter<double>( "MuonLeadingPtCut" ) ),
  MuonSubLeadingPtCut( iConfig.getParameter<double>( "MuonSubLeadingPtCut" ) ),
  MuonIsoCut( iConfig.getParameter<double>( "MuonIsoCut" ) ),
  MuonEtaCut( iConfig.getParameter<double>( "MuonEtaCut" ) ),

  JetPtCut( iConfig.getParameter<double>( "JetPtCut" ) ),
  JetEtaCut( iConfig.getParameter<double>( "JetEtaCut" ) ),
  BTagWPL( iConfig.getParameter<double>( "BTagWPL" ) ),
  BTagWPM( iConfig.getParameter<double>( "BTagWPM" ) ),
  BTagWPT( iConfig.getParameter<double>( "BTagWPT" ) ),

  BTagAlgo( iConfig.getParameter<string>( "BTagAlgo" ) ),

  resolution( SetupDir + "/MCJetPtResolution.txt" ),
  resolution_sf( SetupDir + "/MCJetSF.txt"),
  t_Rho_(consumes<double>( edm::InputTag( "fixedGridRhoFastjetAll" ) ) ),
  rndJER(new TRandom3( 13611360 ) )
{
  //now do what ever initialization is needed
  usesResource("TFileService");

  if( !IsData ){
    oldjetToken_=consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("oldjets")) ;
    LumiWeights_ = edm::LumiReWeighting( SetupDir + "/pileUpMC.root" ,
					 SetupDir + "/pileUpData.root", 
					 std::string("pileup"), std::string("pileup") );
    ntrpuToken_ = consumes< int >( edm::InputTag( "eventUserData","puNtrueInt" ) );

    if( LHEWeight )
      lheToken_ = consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer") );
  }

}


HaNaMiniAnalyzer::~HaNaMiniAnalyzer()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
HaNaMiniAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  double W = 1.0;

  if( LHEWeight ){
    edm::Handle<LHEEventProduct> lhes;
    iEvent.getByToken(lheToken_, lhes);
    double LHE_weight = lhes->hepeup().XWGTUP;
    W = (LHE_weight > 0) ? 1.0 : -1.0 ; 
  }

  int nCut = 1;
  hCutFlowTable->Fill( nCut , W );

  using namespace edm;
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByToken(trigResultsToken_,trigResults);
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);
  bool passTrig = false;
  for(auto hlt : HLT_To_Or){
    uint hltindex = trigNames.triggerIndex(hlt);
    if( hltindex < trigNames.size() )
      passTrig |= trigResults->accept();
  }

  if( !passTrig )
    return;
  hCutFlowTable->Fill( ++nCut , W );


  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(vtxToken_, vertices);
  if (vertices->empty()) return; // skip the event if no PV found
  reco::Vertex * PV = NULL;
  for(auto vtx : *vertices){
    if(vtx.ndof() < 4 ) continue;
    if(vtx.position().z() > 24 ) continue;
    if(vtx.position().rho() > 2 ) continue;
    if( !PV )
      PV = &vtx ;
  }
  if( !PV )
    return;
  hCutFlowTable->Fill( ++nCut , W );

  if( !IsData ){
    edm::Handle<int> ntrpu;
    iEvent.getByToken(ntrpuToken_,ntrpu);
    W *= LumiWeights_.weight(*ntrpu);
  }

  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(muonToken_, muons);

  pat::MuonCollection goodMus;
  for (const pat::Muon &mu : *muons) {
    if (mu.pt() < MuonSubLeadingPtCut || fabs(mu.eta()) > MuonEtaCut || !mu.isTightMuon(*PV)) continue;

    reco::MuonPFIsolation iso = mu.pfIsolationR04();
    double reliso = (iso.sumChargedHadronPt+ max(0.,iso.sumNeutralHadronEt+iso.sumPhotonEt-(0.5*iso.sumPUPt)))/mu.pt();
    if( reliso > MuonIsoCut ) continue;

    goodMus.push_back( mu );
  }

   
  if( goodMus.size() < 2 ) return;
  if( goodMus[0].pt() < MuonLeadingPtCut ) return ;

  if( !IsData ){
    if( MuonIsoCut == 0.25 )
      W *= MuonSFLoose(  goodMus[0].eta() , goodMus[0].pt() , goodMus[1].eta() , goodMus[1].pt() ); 
    else if( MuonIsoCut == 0.15 )
      W *= MuonSFMedium( goodMus[0].eta() , goodMus[0].pt() , goodMus[1].eta() , goodMus[1].pt() ); 
  }

  hCutFlowTable->Fill( ++nCut , W );

  Candidate::LorentzVector oldht;
  if( ! IsData ){
    edm::Handle<pat::JetCollection> oldjets;
    iEvent.getByToken(oldjetToken_, oldjets);
    oldht = HT4( *oldjets );
  }

  edm::Handle<pat::JetCollection> jets;
  iEvent.getByToken(jetToken_, jets);

  Candidate::LorentzVector newht;
  if( !IsData )
    newht = HT4( *jets );

  pat::JetCollection selectedJets;
  pat::JetCollection bjetsL;
  pat::JetCollection bjetsM;
  pat::JetCollection bjetsT;


  edm::Handle<double> rho;
  iEvent.getByToken(t_Rho_ ,rho);
  double Rho = *rho;

  for ( pat::Jet j : *jets) {
    if( !IsData ){
      float pt = JER(j , Rho);
      Candidate::LorentzVector tmp(j.p4());
      tmp.SetPx( tmp.X()*pt/tmp.Pt() );
      tmp.SetPy( tmp.Y()*pt/tmp.Pt() );
      j.setP4(tmp);
    }
    if (j.pt() < JetPtCut) continue;
    if ( fabs(j.eta() ) > JetEtaCut ) continue;
    if ( !JetLooseID( j ) ) continue;
    double dr0 = reco::deltaR( j.p4() , goodMus[0].p4() );
    double dr1 = reco::deltaR( j.p4() , goodMus[1].p4() );
    if( dr0 < 0.4 || dr1 < 0.4 ) continue ;

    selectedJets.push_back(j);

    float btagval = j.bDiscriminator( BTagAlgo );
    if( btagval > BTagWPL )
      bjetsL.push_back( j );
    else if( btagval > BTagWPM )
      bjetsM.push_back(j );
    else if( btagval > BTagWPT )
      bjetsT.push_back( j);
   
  }

  if( selectedJets.size() < 2 ) return ;
  hCutFlowTable->Fill( ++nCut , W );

  if( bjetsL.size() + bjetsM.size() + bjetsT.size() < 2 ) return;
  hCutFlowTable->Fill( ++nCut , W );

  edm::Handle<pat::METCollection> mets;
  iEvent.getByToken(metToken_, mets);
  const pat::MET &met_ = mets->front();
  /*printf("MET: pt %5.1f, phi %+4.2f, sumEt (%.1f). genMET %.1f. MET with JES up/down: %.1f/%.1f\n",
	 met.pt(), met.phi(), met.sumEt(),
	 met.genMET()->pt(),
	 met.shiftedPt(pat::MET::JetEnUp), met.shiftedPt(pat::MET::JetEnDown));
  */
  Candidate::LorentzVector met = met_.p4() ;
  if( !IsData )
    met -= ( newht - oldht ); 

  if( met.Pt() > 30 )
    hCutFlowTable->Fill( ++nCut , W );
}




// ------------ method called once each job just before starting event loop  ------------
void 
HaNaMiniAnalyzer::beginJob()
{
  hCutFlowTable = new Histograms( SampleName , "CutFlowTable" , 10 , 0.5 , 10.5 );


  TFile* f1 = TFile::Open( TString(SetupDir + "/MuonIDSF.root") );
  gROOT->cd();
  hMuSFID = (TH2*)( f1->Get("MC_NUM_TightIDandIPCut_DEN_genTracks_PAR_pt_spliteta_bin1/pt_abseta_ratio")->Clone("MuSFID") );
  f1->Close();

  f1 = TFile::Open( TString(SetupDir + "/MuonIsoSF.root") );
  gROOT->cd();
  if( MuonIsoCut == 0.15 )
    hMuSFIso = (TH2*)( f1->Get("MC_NUM_TightRelIso_DEN_TightID_PAR_pt_spliteta_bin1/pt_abseta_ratio")->Clone("MuSFIso") );
  else if( MuonIsoCut == 0.25 )
    hMuSFIso = (TH2*)( f1->Get("MC_NUM_LooseRelIso_DEN_TightID_PAR_pt_spliteta_bin1/pt_abseta_ratio")->Clone("MuSFIso") );
  f1->Close();
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HaNaMiniAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HaNaMiniAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HaNaMiniAnalyzer);
