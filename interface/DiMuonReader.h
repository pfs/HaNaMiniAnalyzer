#ifndef DiMuonReader_H
#define DiMuonReader_H

#include "BaseEventReader.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "PhysicsTools/PatUtils/interface/PATDiObjectProxy.h"

#include "TH2.h"
#include "TROOT.h"
#include "TFile.h"

using namespace edm;
using namespace pat;

class DiMuonReader : public BaseEventReader< pat::MuonCollection > {
public:
  DiMuonReader( edm::ParameterSet const& iConfig, edm::ConsumesCollector && iC , bool isData , string SetupDir);
  enum SelectionStatus{
    LessThan2Muons,
    NoPairWithChargeReq,
    LowMassPair,
    UnderTheZPeak,
    Pass
  };
  SelectionStatus Read( const edm::Event& iEvent, const reco::Vertex* PV );

  pat::MuonCollection goodMus;
  pat::MuonCollection goodMusOS;
  pat::DiObjectProxy DiMuon;
  double W;

  std::vector<bool> goodMuId;
  std::vector<float> goodMuIso;

  std::vector<float> goodMuIsoChargedHadronPt;
  std::vector<float> goodMuIsoNeutralHadronEt;
  std::vector<float> goodMuIsoPhotonEt;
  std::vector<float> goodMuIsoPUPt;
  inline bool SignalStudy(){
	return isSignalStudy;
  }
private :
  /* MUON SF TOOLS */
  double MuonSFMedium( double etaL , double ptL , double etaSL , double ptSL );
  double MuonSFLoose( double etaL , double ptL , double etaSL , double ptSL );
public:
  double MuonSFHltMu17Mu8( double ptL , double ptSL );
  double MuonSFHltMu17Mu8_DZ( double ptL , double ptSL );
private:
  TH2* hMuSFID;
  TH2* hMuSFIso;
  TH2* hMuHltMu17Mu8;
  TH2* hMuHltMu17Mu8_DZ;
  /* MUON SF TOOLS */

  /* MUON SELECTION PARAMS */
  double MuonLeadingPtCut, MuonSubLeadingPtCut , MuonIsoCut, MuonEtaCut , DiMuLowMassCut, DiMuZMassWindow ;
  int MuonID , DiMuCharge;
  bool IsData, isHamb, isSignalStudy;
  /* MUON SELECTION PARAMS */


};
#endif
