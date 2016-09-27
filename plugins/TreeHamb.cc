#include "Haamm/HaNaMiniAnalyzer/interface/BaseMiniAnalyzer.h"
#include "TTree.h"
#include <iostream>

using namespace std;

class TreeHamb : public BaseMiniAnalyzer{
public:
  explicit TreeHamb(const edm::ParameterSet&);
  ~TreeHamb();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions){ BaseMiniAnalyzer::fillDescriptions( descriptions ); }




  // ----------member data ---------------------------

protected:
  virtual void beginJob() override;
  virtual bool filter(edm::Event&, const edm::EventSetup&) override;
  unsigned int RunN;
  unsigned long long EventN;
  unsigned char nVertices;
  std::valarray<double> W;
  float* Weight;
  float puWeight, met , metPhi, metSig;
  float* bSelWeights;

  std::vector<float> jetsPt;
  std::vector<float> jetsEta;
  std::vector<float> jetsPhi;
  std::vector<float> jetsBtag;
  std::vector<float> jetsFlavour;

  std::vector<float> muPt;
  std::vector<float> muEta;
  std::vector<float> muPhi;
  std::vector<float> muIso;
  std::vector<bool> muId;
  std::vector<bool> muHLT;
  
  TTree* theSelectionResultTree;
  unsigned int nHistos;
  bool MakeTree;

  // ---------- methods ---------------------------

  void FillTree(){
    if( !MakeTree )
      return;

    for(unsigned int i=0 ; i < nHistos ; i++)
      Weight[i] = W[i];

    theSelectionResultTree->Fill();
  }

  void resetTreeVals(){
    RunN = 0;
    EventN = 0;
    nVertices = 250;

    W = 1.0;
    for(unsigned int i=0 ; i < nHistos ; i++)
      Weight[i] = 1.0 ;

    for(unsigned int i=0 ; i < 9 ; i++)
      bSelWeights[i] = 0.0;

    puWeight = met = metPhi = metSig = -999;
    jetsPt.clear();
    jetsEta.clear();
    jetsPhi.clear();
    jetsBtag.clear();
    jetsFlavour.clear();

    muPt.clear();
    muEta.clear();
    muPhi.clear();
    muIso.clear();
    muId.clear();
    muHLT.clear();

  }

};

DEFINE_FWK_MODULE(TreeHamb);





TreeHamb::~TreeHamb() {}
TreeHamb::TreeHamb( const edm::ParameterSet& ps ) :
  BaseMiniAnalyzer( ps ), 
  theSelectionResultTree( NULL ),
  nHistos(1),
  MakeTree( ps.getParameter<bool>( "StoreEventNumbers" ))
{
}


// ------------ method called once each job just before starting event loop  ------------
void TreeHamb::beginJob()
{
  if( SampleName == "Signal" )
    nHistos = 51;
  W = std::valarray<double>( 1.0 , nHistos);
  Weight = new float[nHistos];

  bSelWeights = new float[9];

  if( MakeTree ){
    edm::Service<TFileService> fs;
    TFileDirectory treeDir = fs->mkdir( "Trees" );
    theSelectionResultTree = treeDir.make<TTree>("Events" , "Events"); 
    theSelectionResultTree->Branch("EventNumber", &EventN );
    theSelectionResultTree->Branch("RunNumber", &RunN );
    //theSelectionResultTree->Branch("SelectionStep", &SelectionStep );
    theSelectionResultTree->Branch("nVertices" , &nVertices);

    std::string weightLeafList = "W0";
    for(unsigned int iii = 1 ; iii < nHistos ; iii++)
      weightLeafList += (":W" + std::to_string(iii) );

    theSelectionResultTree->Branch("Weight", Weight , weightLeafList.c_str() );
    theSelectionResultTree->Branch("puWeight", &puWeight);
    theSelectionResultTree->Branch("bWs", bSelWeights , "W1L:W1M:W1T:W1L1M:W1L1T:W1M1T:W2L:W2M:W2T");
    theSelectionResultTree->Branch("met", &met);
    theSelectionResultTree->Branch("metPhi", &metPhi);
    theSelectionResultTree->Branch("metSig", &metSig);

    theSelectionResultTree->Branch("jetsPt", (&jetsPt));
    theSelectionResultTree->Branch("jetsEta", (&jetsEta));
    theSelectionResultTree->Branch("jetsPhi", (&jetsPhi));
    theSelectionResultTree->Branch("jetsBtag", (&jetsBtag));
    theSelectionResultTree->Branch("jetsFlavour", (&jetsFlavour));

    theSelectionResultTree->Branch("muPt", (&muPt));
    theSelectionResultTree->Branch("muEta", (&muEta));
    theSelectionResultTree->Branch("muPhi", (&muPhi));
    theSelectionResultTree->Branch("muIso", (&muIso));
    theSelectionResultTree->Branch("muId", (&muId));
    theSelectionResultTree->Branch("muHLT", (&muHLT));


    resetTreeVals();
  }

  hCutFlowTable = new Histograms( SampleName , "CutFlowTable" , 10 , 0.5 , 10.5, nHistos );

}

//
bool TreeHamb::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  resetTreeVals();

  EventN = iEvent.eventAuxiliary().event() ;
  RunN = iEvent.eventAuxiliary().run() ;


  
  if( nHistos > 1 && SampleName == "Signal" ) {
    LHEReader->Read( iEvent );
    //W = LHEReader->ExtractWeightsInRange( 446 , 495 ); // To be checked for HiggsExo
  }

  stepEventSelection = 0;

  if( geninfoReader )
    W *= geninfoReader->Read( iEvent );
  hCutFlowTable->Fill( ++stepEventSelection , W );

//---------- HLT --------
  if( hltReader->Read( iEvent ) < 0 )
    return false;
  hCutFlowTable->Fill( ++stepEventSelection , W );

//---------- PV --------
  if( vertexReader->Read( iEvent ) < 0 )
    return false;
  W *= vertexReader->puWeight;
  puWeight = vertexReader->puWeight;
  nVertices = vertexReader->vtxMult;
  hCutFlowTable->Fill( ++stepEventSelection , W );

  //To be checked whether corrections are needed?
  met = metReader->Read(iEvent);
  metSig = metReader->ReadMetSig(iEvent);
  metPhi = metReader->metphi;

  DiMuonReader::SelectionStatus myDimuStat = diMuReader->Read( iEvent , vertexReader->PV() );

  for(unsigned int iMu = 0; iMu < diMuReader->goodMus.size(); iMu++){
    muPt.push_back(diMuReader->goodMus[iMu].pt());
    muEta.push_back(diMuReader->goodMus[iMu].eta());
    muPhi.push_back(diMuReader->goodMus[iMu].phi());
    muIso.push_back(diMuReader->goodMuIso[iMu]);
    muId.push_back(diMuReader->goodMuId[iMu]);
    muHLT.push_back(-1);	// To be completed
  }

  switch( myDimuStat ){
  case DiMuonReader::Pass:
    W *= (diMuReader->W) ;
    hCutFlowTable->Fill( ++stepEventSelection , W );
    hCutFlowTable->Fill( ++stepEventSelection , W );
    hCutFlowTable->Fill( ++stepEventSelection , W );
    hCutFlowTable->Fill( ++stepEventSelection , W );
    break;
  case DiMuonReader::UnderTheZPeak:
    W *= (diMuReader->W) ;
    hCutFlowTable->Fill( ++stepEventSelection , W );
  case DiMuonReader::LowMassPair:
    hCutFlowTable->Fill( ++stepEventSelection , W );
  case DiMuonReader::NoPairWithChargeReq:
    hCutFlowTable->Fill( ++stepEventSelection , W );
  case DiMuonReader::LessThan2Muons:
    FillTree();
    return false;
  }
  

  JetReader::SelectionStatus myJetsStat = jetReader->Read( iEvent , &(diMuReader->DiMuon) );
  for(unsigned int iJet = 0; iJet < jetReader->selectedJets.size(); iJet++){
    jetsPt.push_back(jetReader->selectedJets[iJet].pt());
    jetsEta.push_back(jetReader->selectedJets[iJet].eta());
    jetsPhi.push_back(jetReader->selectedJets[iJet].phi());
    jetsBtag.push_back(jetReader->selectedJets[iJet].bDiscriminator(jetReader->BTagAlgo));
    jetsFlavour.push_back(jetReader->selectedJets[iJet].hadronFlavour());
  }

  for(int i = 0; i < 9; i++){
	bSelWeights[i] = jetReader->weights[i];
  }
  switch( myJetsStat ){
  case JetReader::Pass:
    hCutFlowTable->Fill( ++stepEventSelection , W );
    W *= jetReader->W ;
    hCutFlowTable->Fill( ++stepEventSelection , W );
    break;
  case JetReader::NotEnoughBJets:
    hCutFlowTable->Fill( ++stepEventSelection , W );
  case JetReader::NotEnoughJets:
    FillTree();
    return false;
  }
  
  FillTree();
  return true;
}
