#ifndef JetReader_H
#define JetReader_H


#include "BTagWeight.h"
#include "BaseEventReader.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "PhysicsTools/PatUtils/interface/PATDiObjectProxy.h"

#include "TRandom3.h"

using namespace edm;
using namespace pat;

class JetReader : public BaseEventReader< pat::JetCollection > {
public:
  JetReader( edm::ParameterSet const& iConfig, edm::ConsumesCollector && iC , bool isData , string SetupDir) ;
  const pat::JetCollection* GetAllJets();

  enum SelectionStatus {
    NotEnoughJets,
    NotEnoughBJets,
    Pass
  };

  SelectionStatus Read( const edm::Event& iEvent , pat::DiObjectProxy* diLepton = NULL );

  pat::JetCollection selectedJets;
  pat::JetCollection selectedJetsSortedByB;
  pat::JetCollection selectedBJets;
  double W;
  float weights[9];

private :
  std::vector<BTagWeight*> weighters;

  bool IsData;
  /* JET SELECTION PARAMS */
  bool ApplyJER;
  double JetPtCut , JetEtaCut ;
  unsigned int MinNJets;
  /* JET SELECTION PARAMS */


  /* b-JET SELECTION PARAMS */
  double BTagWPL , BTagWPM , BTagWPT ;
  std::vector<int> BTagCuts; // atm only 2 are accepted, first for selection, second for veto
public:
  string BTagAlgo ;
  float nNonTagged;
  float nLooseNotMed;
  float nMedNotTight;
  float nTight;
private:
  unsigned int MinNBJets; 
  int MaxNBJets ;
  /* b-JET SELECTION PARAMS */

  /* JET TOOLS */
  JME::JetResolution resolution;
  JME::JetResolutionScaleFactor resolution_sf;
  TRandom3* rndJER;

  float JER( pat::Jet jet , double rho , int syst = 0 );
  bool JetLooseID( pat::Jet j );
  /* JET TOOLS */

  edm::EDGetTokenT<double> t_Rho_;
  edm::Handle<double> rho;
  double Rho;
};

#endif
