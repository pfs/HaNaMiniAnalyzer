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
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "../interface/Histograms.h"
#include "../interface/BTagWeight.h"

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


template <class G>
class ptSort{
public:
  bool operator()(G o1 ,G o2 ){
    return (o1.pt()>o2.pt());
  }
};

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

    if( ptSL < 20 || ptL < 20 )
      return ret;

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

    if( ptSL < 20 || ptL < 20 )
      return ret;

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
  void initHistograms(){   
    hNPV_pv = new Histograms(SampleName, "NPV_pv", 100, -0.5, 99.5);
    hMuMult = new Histograms(SampleName, "MuMult", 10, -0.5, 9.5);
    hJetMult = new Histograms(SampleName, "JetMult", 10, -0.5, 9.5);
    hBJetMult = new Histograms(SampleName, "BJetMult", 10, -0.5, 9.5);
    hNPV_final = new Histograms(SampleName, "NPV_final", 100, -0.5, 99.5);
    hMuPt = new Histograms(SampleName, "MuPt", 30, 0., 150.);
    hMuEta = new Histograms(SampleName, "MuEta", 30, -3.0, 3.0);
    hLeadMuPt= new Histograms(SampleName, "LeadMuPt", 30, 0., 150.);
    hLeadMuEta= new Histograms(SampleName, "LeadMuEta", 30, -3.0, 3.0);
    hSubLeadMuPt= new Histograms(SampleName, "SubLeadMuPt", 30, 0., 150.);
    hSubLeadMuEta= new Histograms(SampleName, "SubLeadMuEta", 30, -3.0, 3.0);
    hDiMuMass= new Histograms(SampleName, "DiMuMass", 17, 10., 180.);
    hDiMuPt= new Histograms(SampleName, "DiMuPt", 40, 0., 200.);
    hDiMuDr= new Histograms(SampleName, "DiMuDr", 50, 0, 5.0);
    hJetPt= new Histograms(SampleName, "JetPt", 30, 0., 150.);
    hJetEta= new Histograms(SampleName, "JetEta", 50, -5.0, 5.0);
    hJetBTag= new Histograms(SampleName, "JetBTag", 20, 0, 1.);
    hLeadJetPt= new Histograms(SampleName, "LeadJetPt", 30, 0., 150.);
    hLeadJetEta= new Histograms(SampleName, "LeadJetEta", 50, -5.0, 5.0);
    hLeadJetBTag= new Histograms(SampleName, "LeadJetBTag", 20, 0, 1.);
    hSubLeadJetPt= new Histograms(SampleName, "SunLeadJetPt", 30, 0., 150.);
    hSubLeadJetEta= new Histograms(SampleName, "SubLeadJetEta", 50, -5.0, 5.0);
    hSubLeadJetBTag= new Histograms(SampleName, "SubLeadJetBTag", 20, 0, 1.);
    hDiBJetMass= new Histograms(SampleName, "DiBJetMass", 30, 0., 300.);
    hDiBJetPt= new Histograms(SampleName, "DiBJetPt", 15, 0., 150.);
    hDiBJetDr= new Histograms(SampleName, "DiBJetDr", 50, 0, 5.0);
    hFourBodyMass= new Histograms(SampleName, "FourBodyMass", 30, 0., 300.);
    hFourBodyPt= new Histograms(SampleName, "FourBodyPt", 20, 0., 200.);
    hDiffMassMuB= new Histograms(SampleName, "DiffMassMuB", 15, 0., 150.);
    hRelDiffMassMuB= new Histograms(SampleName, "RelDiffMassMuB", 20, 0, 1.);
    hMET= new Histograms(SampleName, "MET", 20, 0., 200.);
    hMETSignificance= new Histograms(SampleName, "METSignificance", 20, 0, 20.);
    hNMuHits = new Histograms(SampleName, "nMuHits", 10, -0.5, 9.5);
  }

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;



  // --------- All Info needed in the event processing ---------------
  double W, Rho; //to store the event weight
  int nCut ;
  reco::Vertex * PV;
  pat::MuonCollection goodMus;
  pat::MuonCollection goodMusOS;
  Candidate::LorentzVector oldht , newht;
  pat::JetCollection selectedJets;
  pat::JetCollection selectedBJets;

  // ----------member data ---------------------------
  Histograms* hCutFlowTable;
  Histograms* hNPV_pv;
  Histograms* hMuMult;
  Histograms* hJetMult;
  Histograms* hBJetMult;
  Histograms* hNPV_final;
  Histograms* hMuPt;
  Histograms* hMuEta;
  Histograms* hLeadMuPt;
  Histograms* hLeadMuEta;
  Histograms* hSubLeadMuPt;
  Histograms* hSubLeadMuEta;
  Histograms* hDiMuMass;
  Histograms* hDiMuPt;
  Histograms* hDiMuDr;
  Histograms* hJetPt;
  Histograms* hJetEta;
  Histograms* hJetBTag;
  Histograms* hLeadJetPt;
  Histograms* hLeadJetEta;
  Histograms* hLeadJetBTag;
  Histograms* hSubLeadJetPt;
  Histograms* hSubLeadJetEta;
  Histograms* hSubLeadJetBTag;
  Histograms* hDiBJetMass;
  Histograms* hDiBJetPt;
  Histograms* hDiBJetDr;
  Histograms* hFourBodyMass;
  Histograms* hFourBodyPt;
  Histograms* hDiffMassMuB;
  Histograms* hRelDiffMassMuB;
  Histograms* hMET;
  Histograms* hMETSignificance;
  Histograms* hNMuHits;

  BTagWeight* btw; 


  string SetupDir;

  bool LHEWeight ;
  bool IsData ;
  string SampleName;
  std::vector<std::string> HLT_To_Or;



  edm::Handle<LHEEventProduct> lhes;  edm::Handle<edm::TriggerResults> trigResults;
  edm::Handle<reco::VertexCollection> vertices;
  edm::Handle<std::vector< PileupSummaryInfo > >  PupInfo;
  edm::Handle<pat::MuonCollection> muons;
  edm::Handle<pat::JetCollection> oldjets;
  edm::Handle<pat::JetCollection> jets;
  edm::Handle<double> rho;
  edm::Handle<pat::METCollection> mets;

  edm::EDGetTokenT< std::vector< PileupSummaryInfo > > PileupToken_;
  edm::EDGetTokenT< LHEEventProduct > lheToken_ ;
  edm::EDGetTokenT< edm::TriggerResults > trigResultsToken_;
  edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  edm::EDGetTokenT<pat::MuonCollection> muonToken_;
  edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
  edm::EDGetTokenT<pat::JetCollection> jetToken_;
  edm::EDGetTokenT<pat::JetCollection> oldjetToken_;
  edm::EDGetTokenT<pat::METCollection> metToken_;

  double MuonLeadingPtCut, MuonSubLeadingPtCut , MuonIsoCut, MuonEtaCut , DiMuLowMassCut ;
  int DiMuCharge;
  double JetPtCut , JetEtaCut , BTagWPL , BTagWPM , BTagWPT ;
  std::vector<int> BTagCuts; // atm only 2 are accepted, first for selection, second for veto
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
  DiMuLowMassCut( iConfig.getParameter<double>( "DiMuLowMassCut" ) ),
  DiMuCharge( iConfig.getParameter<int>( "DiMuCharge" ) ),

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

  BTagCuts = iConfig.getParameter<std::vector<int> > ( "BTagCuts" );
  if(BTagCuts.size() > 2){
    std::cout<<"FATAL ERROR: The current code accepts up to two WP's, one for selection one for veto"<<std::endl;
    return;
  } else if(BTagCuts.size() < 2) BTagCuts.push_back(-1);


  if( !IsData ){
    oldjetToken_=consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("oldjets")) ;
    LumiWeights_ = edm::LumiReWeighting( SetupDir + "/pileUpMC.root" ,
					 SetupDir + "/pileUpData.root", 
					 std::string("pileup"), std::string("pileup") );
    PileupToken_ = consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileupSrc")) ;

    if( LHEWeight )
      lheToken_ = consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer") );

    //**************************************************************
    //********* To be adjusted for different WP & bTagAlgo Choices *
    //**************************************************************
    btw = new BTagWeight("CSVv2", BTagCuts[0], SetupDir, BTagWPL, BTagWPM, BTagWPT,BTagCuts[1]);
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
  W = 1.0;

  if( LHEWeight ){
    iEvent.getByToken(lheToken_, lhes);
    W = (lhes->hepeup().XWGTUP > 0) ? 1.0 : -1.0 ; 
  }

  nCut = 1;
  hCutFlowTable->Fill( nCut , W );

  iEvent.getByToken(trigResultsToken_,trigResults);
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);
  bool passTrig = false;
  for(auto hlt : HLT_To_Or){
    uint hltindex = trigNames.triggerIndex(hlt);
    if( hltindex < trigNames.size() )
      passTrig |= trigResults->accept(hltindex);
  }

  //if( !passTrig )
  //  return;
  hCutFlowTable->Fill( ++nCut , W );


  iEvent.getByToken(vtxToken_, vertices);
  if (vertices->empty()) return; // skip the event if no PV found
  PV = NULL;
  int vtxMult = 0;
  for(auto vtx : *vertices){
    if(vtx.ndof() < 4 ) continue;
    if(vtx.position().z() > 24 ) continue;
    if(vtx.position().rho() > 2 ) continue;
    vtxMult++;
    if( !PV )
      PV = &vtx ;
  }
  
  //if( !PV )
  //  return;
  const reco::Vertex& PV2= vertices->front();
  hCutFlowTable->Fill( ++nCut , W );

  iEvent.getByToken(muonToken_, muons);

  goodMus.clear();
  goodMusOS.clear();
  pat::MuonCollection tmpgoodMus;
  for (const pat::Muon &mu : *muons) {
    if (mu.pt() < 20 || fabs(mu.eta()) > 2.4 ) continue;
    if (!mu.isTightMuon(PV2)) continue;
    tmpgoodMus.push_back(mu);
    reco::MuonPFIsolation iso = mu.pfIsolationR04();
    double reliso = (iso.sumChargedHadronPt+TMath::Max(0.,iso.sumNeutralHadronEt+iso.sumPhotonEt-0.5*iso.sumPUPt))/mu.pt();
    if( reliso > 0.15 ) continue;
    goodMus.push_back( mu );
  }

  hMuMult->Fill(goodMus.size(), W);

  if( goodMus.size() < 2 ) return;

  
  int mu0charge=0;
  for(auto mu : goodMus){
    if( goodMusOS.size() == 0) {
      goodMusOS.push_back( mu );
      mu0charge = mu.charge();
    }
    else if( mu.charge()*mu0charge == DiMuCharge ){
      goodMusOS.push_back( mu );
      break;
    }
  }
  if( goodMusOS.size() != 2 )
    return;
  hCutFlowTable->Fill( ++nCut , W );

  if( (goodMusOS[0].p4()+goodMusOS[1].p4()).M() < DiMuLowMassCut ) return;
  hCutFlowTable->Fill( ++nCut , W );
  
  if( (goodMusOS[0].p4()+goodMusOS[1].p4()).M() > 76 && (goodMusOS[0].p4()+goodMusOS[1].p4()).M() < 106 ) return;
  hCutFlowTable->Fill( ++nCut , W );
  
  iEvent.getByToken(metToken_, mets);
  const pat::MET &met_ = mets->front();
  if(met_.pt() < 40) return;
  hCutFlowTable->Fill( ++nCut , W );

  if( !IsData ){
    if( MuonIsoCut == 0.25 )
      W *= MuonSFLoose(  goodMusOS[0].eta() , goodMusOS[0].pt() , goodMusOS[1].eta() , goodMusOS[1].pt() ); 
    else if( MuonIsoCut == 0.15 )
      W *= MuonSFMedium( goodMusOS[0].eta() , goodMusOS[0].pt() , goodMusOS[1].eta() , goodMusOS[1].pt() ); 
  }

  /***** Filling Histograms ******/
  hNPV_pv->Fill(vtxMult,W);
  if( !IsData ){
    iEvent.getByToken(PileupToken_, PupInfo);
    // auto PVI = PupInfo->begin();
    // for(; PVI != PupInfo->end(); ++PVI) {
    //   puBX->push_back(  PVI->getBunchCrossing() ); 
    //   puNInt->push_back( PVI->getPU_NumInteractions() );
    // }
    W *= LumiWeights_.weight(PupInfo->begin()->getTrueNumInteractions());
  }
  hNPV_final->Fill(vtxMult,W);
  hMuPt->Fill(goodMusOS[0].pt(), W); hMuPt->Fill(goodMusOS[1].pt(), W);
  hMuEta->Fill(goodMusOS[0].eta(), W); hMuEta->Fill(goodMusOS[1].eta(), W);
  hLeadMuPt->Fill(goodMusOS[0].pt(), W);
  hLeadMuEta->Fill(goodMusOS[0].eta(), W);
  hSubLeadMuPt->Fill(goodMusOS[1].pt(), W);
  hSubLeadMuEta->Fill(goodMusOS[1].eta(), W);
  hDiMuMass->Fill((goodMusOS[0].p4()+goodMusOS[1].p4()).M(), W);
  hDiMuPt->Fill((goodMusOS[0].p4()+goodMusOS[1].p4()).Pt(), W);
  hDiMuDr->Fill(reco::deltaR( goodMusOS[1].p4() , goodMusOS[0].p4() ), W);
  hCutFlowTable->Fill( ++nCut , W );
  /***** End Filling Histograms **/ 




  iEvent.getByToken(jetToken_, jets);

  if( ! IsData ){
    iEvent.getByToken(oldjetToken_, oldjets);
    oldht = HT4( *oldjets );
    newht = HT4( *jets );

    iEvent.getByToken(t_Rho_ ,rho);
    Rho = *rho;
  }


  selectedJets.clear();
  selectedBJets.clear();

  for ( pat::Jet j : *jets) {
    /*if( !IsData ){
      float pt = JER(j , Rho);
      Candidate::LorentzVector tmp(j.p4());
      tmp.SetPx( tmp.X()*pt/tmp.Pt() );
      tmp.SetPy( tmp.Y()*pt/tmp.Pt() );
      j.setP4(tmp);
    }*/
    if (j.pt() < JetPtCut) continue;
    if ( fabs(j.eta() ) > JetEtaCut ) continue;
    if ( !JetLooseID( j ) ) continue;
    double dr0 = reco::deltaR( j.p4() , goodMusOS[0].p4() );
    double dr1 = reco::deltaR( j.p4() , goodMusOS[1].p4() );
    if( dr0 < 0.4 || dr1 < 0.4 ) continue ;

    selectedJets.push_back(j);
 
   float btagval = j.bDiscriminator( BTagAlgo );
    if(BTagCuts[0] == 0) {
	if(btagval > BTagWPL) selectedBJets.push_back(j);
    } else if (BTagCuts[0] == 1) {
	if(btagval > BTagWPM) selectedBJets.push_back(j);
    } else if (BTagCuts[0] == 2) {
	if(btagval > BTagWPT) selectedBJets.push_back(j);
    }
  }
  ptSort<pat::Jet> mySort; 
  std::sort(selectedJets.begin(),selectedJets.end(),mySort);
  std::sort(selectedBJets.begin(),selectedBJets.end(),mySort);

  hJetMult->Fill(selectedJets.size(), W);

  if( selectedJets.size() < 2 ) return ;

  hCutFlowTable->Fill( ++nCut , W );

  for( unsigned int iJet = 0; iJet < selectedJets.size(); iJet++){
    hJetPt->Fill(selectedJets[iJet].pt(), W);
    hJetEta->Fill(selectedJets[iJet].eta(), W);
    hJetBTag->Fill(selectedJets[iJet].bDiscriminator(BTagAlgo), W);
  }

  hLeadJetPt->Fill(selectedJets[0].pt(), W); hSubLeadJetPt->Fill(selectedJets[1].pt(), W);
  hLeadJetEta->Fill(selectedJets[0].eta(), W); hSubLeadJetEta->Fill(selectedJets[1].eta(), W);
  hLeadJetBTag->Fill(selectedJets[0].bDiscriminator(BTagAlgo), W); hSubLeadJetBTag->Fill(selectedJets[1].bDiscriminator(BTagAlgo), W);

  hBJetMult->Fill(selectedBJets.size(), W);
  if(  selectedBJets.size() < 2 ) return;

  //Apply bTag Weight
  if(!IsData)
	W*=btw->weight(*jets);

  hDiBJetMass->Fill((selectedBJets[0].p4()+selectedBJets[1].p4()).M(),W);
  hDiBJetPt->Fill((selectedBJets[0].p4()+selectedBJets[1].p4()).Pt(),W);
  hDiBJetDr->Fill(reco::deltaR(selectedBJets[0].p4(),selectedBJets[1].p4()),W);
  hFourBodyMass->Fill((goodMusOS[0].p4()+goodMusOS[1].p4()+selectedBJets[0].p4()+selectedBJets[1].p4()).M(),W);
  hFourBodyPt->Fill((goodMusOS[0].p4()+goodMusOS[1].p4()+selectedBJets[0].p4()+selectedBJets[1].p4()).Pt(),W);
  hDiffMassMuB->Fill(fabs((goodMusOS[0].p4()+goodMusOS[1].p4()).M()- (selectedBJets[0].p4()+selectedBJets[1].p4()).M()),W);
  hRelDiffMassMuB->Fill(fabs((goodMusOS[0].p4()+goodMusOS[1].p4()).M()- (selectedBJets[0].p4()+selectedBJets[1].p4()).M())/(selectedBJets[0].p4()+selectedBJets[1].p4()).M(),W);
  hCutFlowTable->Fill( ++nCut , W );

  //iEvent.getByToken(metToken_, mets);
  //const pat::MET &met_ = mets->front();
  /*printf("MET: pt %5.1f, phi %+4.2f, sumEt (%.1f). genMET %.1f. MET with JES up/down: %.1f/%.1f\n",
	 met.pt(), met.phi(), met.sumEt(),
	 met.genMET()->pt(),
	 met.shiftedPt(pat::MET::JetEnUp), met.shiftedPt(pat::MET::JetEnDown));
  */
  Candidate::LorentzVector met = met_.p4() ;
  if( !IsData )
    met -= ( newht - oldht ); 
  
  hMET->Fill(met.Pt(),W);

  if( met.Pt() > 30 )
    hCutFlowTable->Fill( ++nCut , W );
}




// ------------ method called once each job just before starting event loop  ------------
void 
HaNaMiniAnalyzer::beginJob()
{
  hCutFlowTable = new Histograms( SampleName , "CutFlowTable" , 10 , 0.5 , 10.5 );
  this->initHistograms();

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
