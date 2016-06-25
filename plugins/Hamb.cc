#include "Haamm/HaNaMiniAnalyzer/interface/HaNaBaseMiniAnalyzer.h"
#include "Haamm/HaNaMiniAnalyzer/interface/Category.h"

#include <iostream>

using namespace std;

class Hamb : public HaNaBaseMiniAnalyzer{
public:
  explicit Hamb(const edm::ParameterSet&);
  ~Hamb();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions){ HaNaBaseMiniAnalyzer::fillDescriptions( descriptions ); }




  // ----------member data ---------------------------
  Category * HLT;
  Category * HLT_LL;
  Category * HLT_LL_2J;
  Category * HLT_LL_2J_2B;
  Category * HLT_LL_2J_2B_MetSig;
  std::vector<float> values;
  void initCategories();
protected:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
};

DEFINE_FWK_MODULE(Hamb);

void Hamb::initCategories(){   
    HLT = new Category("HLT",SampleName);
    HLT_LL = new Category("HLT_LL",SampleName);
    HLT_LL_2J = new Category("HLT_LL_2J",SampleName);
    HLT_LL_2J_2B = new Category("HLT_LL_2J_2B",SampleName);
    HLT_LL_2J_2B_MetSig = new Category("HLT_LL_2J_2B_MetSig",SampleName);
    for(int i  = 0; i < 34; i++)
	values.push_back(-999);
  }




Hamb::~Hamb() {}
Hamb::Hamb( const edm::ParameterSet& ps ) :
  HaNaBaseMiniAnalyzer( ps ) 
{
}
// ------------ method called once each job just before starting event loop  ------------
void Hamb::beginJob()
{
  hCutFlowTable = new Histograms( SampleName , "CutFlowTable" , 10 , 0.5 , 10.5 );
  initCategories();
}

//
void Hamb::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  W = 1.0;
  stepEventSelection = 0;
  
  if( LHEReader )
    W *= LHEReader->Read( iEvent );

  hCutFlowTable->Fill( ++stepEventSelection , W );

  if( hltReader->Read( iEvent ) < 0 )
    return;
   
  hCutFlowTable->Fill( ++stepEventSelection , W );

  if( vertexReader->Read( iEvent ) < 0 )
    return;
  W *= vertexReader->puWeight;
  hCutFlowTable->Fill( ++stepEventSelection , W );

  values[0] = vertexReader->vtxMult; 
  values[4] = vertexReader->vtxMult; 
  values[30] = metReader->Read(iEvent);
  values[31] = metReader->ReadMetSig(iEvent);

  //cout << vertexReader->PV()->ndof() << endl;
  switch( diMuReader->Read( iEvent , vertexReader->PV() ) ){
  case DiMuonReader::Pass :
    W *= (diMuReader->W) ;
    hCutFlowTable->Fill( ++stepEventSelection , W );
    hCutFlowTable->Fill( ++stepEventSelection , W );
    hCutFlowTable->Fill( ++stepEventSelection , W );
    hCutFlowTable->Fill( ++stepEventSelection , W );
    values[1] = diMuReader->goodMus.size();
    HLT->Fill(values, W, vertexReader->puWeight);
    break;
  case DiMuonReader::UnderTheZPeak:
    W *= (diMuReader->W) ;
    hCutFlowTable->Fill( ++stepEventSelection , W );
  case DiMuonReader::LowMassPair:
    hCutFlowTable->Fill( ++stepEventSelection , W );
  case DiMuonReader::NoPairWithChargeReq:
    hCutFlowTable->Fill( ++stepEventSelection , W );
  case DiMuonReader::LessThan2Muons :
    values[1] = diMuReader->goodMus.size();
    HLT->Fill(values, W, vertexReader->puWeight);
    return ;
  }
  
  /***** Filling Histograms ******/
  values[5] = diMuReader->goodMusOS[0].pt(); values[32] = diMuReader->goodMusOS[1].pt();
  values[6] = diMuReader->goodMusOS[0].eta(); values[33] = diMuReader->goodMusOS[1].eta();

  values[7] = diMuReader->goodMusOS[0].pt();
  values[8] = diMuReader->goodMusOS[0].eta();

  values[9] = diMuReader->goodMusOS[1].pt();
  values[10] = diMuReader->goodMusOS[1].eta();

  values[11] = diMuReader->DiMuon.totalP4().M();
  values[12] = diMuReader->DiMuon.totalP4().Pt(); 
  values[13] = diMuReader->DiMuon.deltaR(); 
  /***** End Filling Histograms **/ 



  switch( jetReader->Read( iEvent , &(diMuReader->DiMuon) ) ){
  case JetReader::Pass:
    hCutFlowTable->Fill( ++stepEventSelection , W );
    W *= jetReader->W ;
    hCutFlowTable->Fill( ++stepEventSelection , W );
    values[2] = jetReader->selectedJets.size();
    values[3] = jetReader->selectedBJets.size();
    HLT_LL->Fill(values, W, vertexReader->puWeight);
    break;
  case JetReader::NotEnoughBJets:
    hCutFlowTable->Fill( ++stepEventSelection , W );
  case JetReader::NotEnoughJets:
    values[2] = jetReader->selectedJets.size();
    values[3] = jetReader->selectedBJets.size();
    HLT_LL->Fill(values, W, vertexReader->puWeight);
    return;
  }

  values[14] = jetReader->selectedJets[0].pt();
  values[15] = jetReader->selectedJets[0].eta();
  values[16] = jetReader->selectedJets[0].bDiscriminator(jetReader->BTagAlgo);
  values[17] = jetReader->selectedJets[0].pt();
  values[18] = jetReader->selectedJets[0].eta();
  values[19] = jetReader->selectedJets[0].bDiscriminator(jetReader->BTagAlgo);
  values[20] = jetReader->selectedJets[1].pt();
  values[21] = jetReader->selectedJets[1].eta();
  values[22] = jetReader->selectedJets[1].bDiscriminator(jetReader->BTagAlgo);
 
  for( unsigned int iJet = 0; iJet < jetReader->selectedJets.size(); iJet++){
    if(iJet == 0) continue;
    values.push_back(jetReader->selectedJets[iJet].pt());
    values.push_back(jetReader->selectedJets[iJet].eta());
    values.push_back(jetReader->selectedJets[iJet].bDiscriminator(jetReader->BTagAlgo));
  }

  HLT_LL_2J->Fill(values, W, vertexReader->puWeight);

  pat::DiObjectProxy* DiBJets = NULL;

  if( jetReader->selectedBJets.size() > 1 ){
    DiBJets = new pat::DiObjectProxy( jetReader->selectedBJets[0] , jetReader->selectedBJets[1] );
    values[23] = DiBJets->totalP4().M();
    values[24] = DiBJets->totalP4().Pt();
    values[25] = DiBJets->deltaR();
    values[26] = (DiBJets->totalP4() + diMuReader->DiMuon.totalP4()).M();
    values[27] = (DiBJets->totalP4() + diMuReader->DiMuon.totalP4()).Pt();
    values[28] = fabs( DiBJets->totalP4().M() - diMuReader->DiMuon.totalP4().M() );
    values[29] = fabs( DiBJets->totalP4().M() - diMuReader->DiMuon.totalP4().M() )/ (DiBJets->totalP4() + diMuReader->DiMuon.totalP4()).M();
    HLT_LL_2J_2B->Fill(values, W, vertexReader->puWeight);
  }
  if (values[31] < 6)
    HLT_LL_2J_2B_MetSig->Fill(values, W, vertexReader->puWeight);

}
