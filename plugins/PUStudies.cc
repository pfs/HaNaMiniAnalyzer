#include "Haamm/HaNaMiniAnalyzer/interface/HaNaBaseMiniAnalyzer.h"

#include <iostream>
#include "TTree.h"

using namespace std;

class PUAnalyzer : public HaNaBaseMiniAnalyzer{
public:
  explicit PUAnalyzer(const edm::ParameterSet&);
  ~PUAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions){ HaNaBaseMiniAnalyzer::fillDescriptions( descriptions ); }

  edm::EDGetTokenT<double> t_Rho_;
  edm::Handle<double> rho;
  Histograms* hnTruInt;

  TTree* theTree;
  //TREE VALS
  // unsigned int RunN;
  // unsigned long long EventN;
  char nVertices, nGoodVertices , nInt , nInt50ns ;
  int nEles , nMus , nChargedHadrons , nLostTracks;
  float Rho, InvMass , reliso1 , reliso2;
  bool passDiMuMedium, passDiMuTight;
  //-------------
protected:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
};

DEFINE_FWK_MODULE(PUAnalyzer);

PUAnalyzer::~PUAnalyzer() {}
PUAnalyzer::PUAnalyzer( const edm::ParameterSet& ps ) :
  HaNaBaseMiniAnalyzer( ps ) 
{
    t_Rho_ = (consumes<double>( edm::InputTag( "fixedGridRhoFastjetAll" ) ) );
}
// ------------ method called once each job just before starting event loop  ------------
void PUAnalyzer::beginJob()
{
  hnTruInt = new Histograms( SampleName , "nTruInteractions" , 100 , 0 , 100);
  hCutFlowTable = new Histograms( SampleName , "CutFlowTable" , 10 , 0.5 , 10.5);


  edm::Service<TFileService> fs;
  //fs->cd();
  TFileDirectory treeDir = fs->mkdir( "Trees" );
  //treeDir.cd();

  // TFile* f = TFile::Open("tree.root" , "RECREATE");
  // f->cd();
  // gDirectory->Print();
  theTree = treeDir.make<TTree>("Events" , "Events");
  //fs->make<TTree>("SelectedEventNumbers" , "SelectedEventNumbers");
    
  // gDirectory->Print();
  theTree->Branch("passDiMuTight", &passDiMuTight );
  theTree->Branch("passDiMuMedium", &passDiMuMedium );
  theTree->Branch("nVertices" , &nVertices);
  theTree->Branch("nInt" , &nInt);
  theTree->Branch("nInt50ns" , &nInt50ns);
  theTree->Branch("nEles" , &nEles);
  theTree->Branch("nMus" , &nMus);
  theTree->Branch("nChargedHadrons" , &nChargedHadrons);
  theTree->Branch("nLostTracks" , &nLostTracks);

  theTree->Branch("Rho" , &Rho);
  theTree->Branch("InvMass" , &InvMass);
  theTree->Branch("reliso2" , &reliso2);
  theTree->Branch("reliso1" , &reliso1);
  theTree->Branch("W" , &W);
}

//
void PUAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  W = 1.0;
  stepEventSelection = 0;

  if( !IsData )
    W *= geninfoReader->Read( iEvent );
  hCutFlowTable->Fill( ++stepEventSelection , W );

  if(hltReader->Read( iEvent ) < 0 ){
    return;
  }
  hCutFlowTable->Fill( ++stepEventSelection , W );

  if( vertexReader->Read( iEvent ) < 0 )
    return;
  hCutFlowTable->Fill( ++stepEventSelection , W );

  if(!IsData)
    hnTruInt->Fill( vertexReader->npv  , 1.0 );

  
  nInt = vertexReader->npv;
  nInt50ns = vertexReader->npv50ns;
  nVertices = vertexReader->vtxMult;
  nGoodVertices = vertexReader->nGoodVtx;
  
  packedReader->Read( iEvent );
  nEles = packedReader->nEles;
  nMus = packedReader->nMus;
  nChargedHadrons = packedReader->nChargedHadrons;

  lostReader->Read( iEvent );
  nLostTracks = lostReader->size();


  iEvent.getByToken(t_Rho_ ,rho);
  Rho = *rho;

  //cout << vertexReader->PV()->ndof() << endl;
  switch( diMuReader->Read( iEvent , vertexReader->PV() ) ){
  case DiMuonReader::Pass :
  case DiMuonReader::UnderTheZPeak:   
    W *= (diMuReader->W) ;
    hCutFlowTable->Fill( ++stepEventSelection , W );
    break;
  case DiMuonReader::LowMassPair:
  case DiMuonReader::NoPairWithChargeReq:
  case DiMuonReader::LessThan2Muons :
    return ;
  }
  
  InvMass = diMuReader->DiMuon.totalP4().M();
  passDiMuMedium = true;

  passDiMuTight = ( muon::isTightMuon( diMuReader->DiMuon.mu1() , *vertexReader->PV() )
		    && muon::isTightMuon( diMuReader->DiMuon.mu2() , *vertexReader->PV() ) );

  reco::MuonPFIsolation iso = diMuReader->DiMuon.mu1().pfIsolationR04();
  reliso1 = (iso.sumChargedHadronPt+TMath::Max(0.,iso.sumNeutralHadronEt+iso.sumPhotonEt-0.5*iso.sumPUPt))/diMuReader->DiMuon.mu1().pt();
  iso = diMuReader->DiMuon.mu2().pfIsolationR04();
  reliso2 = (iso.sumChargedHadronPt+TMath::Max(0.,iso.sumNeutralHadronEt+iso.sumPhotonEt-0.5*iso.sumPUPt))/diMuReader->DiMuon.mu1().pt();

  theTree->Fill();
}

