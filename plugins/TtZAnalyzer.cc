#include "Haamm/HaNaMiniAnalyzer/interface/HaNaBaseMiniAnalyzer.h"
#include "Haamm/HaNaMiniAnalyzer/interface/TtGenEvent.h"
#include <iostream>

using namespace std;

class TtZAnalyzer : public HaNaBaseMiniAnalyzer{
public:
  explicit TtZAnalyzer(const edm::ParameterSet&);
  ~TtZAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions){ HaNaBaseMiniAnalyzer::fillDescriptions( descriptions ); }




  // ----------member data ---------------------------
	Histograms* hOptimalCosTheta;
	Histograms* hHelicityCosTheta;
	Histograms* hDiffDR;
  void initHistograms();
protected:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  edm::EDGetTokenT<std::vector<reco::GenParticle> > prunedGenToken_;
  edm::Handle< std::vector<reco::GenParticle> > prunedGens;
};

DEFINE_FWK_MODULE(TtZAnalyzer);

void TtZAnalyzer::initHistograms(){   
	hOptimalCosTheta = new Histograms(SampleName, "OptimalCosTheta", 20, -1., 1.);
	hHelicityCosTheta = new Histograms(SampleName, "HelicityCosTheta", 20, -1., 1.);
	hDiffDR = new Histograms(SampleName, "DiffDR", 50, 0., 10.);
  }




TtZAnalyzer::~TtZAnalyzer() {}
TtZAnalyzer::TtZAnalyzer( const edm::ParameterSet& ps ) :
  HaNaBaseMiniAnalyzer( ps ) ,
  prunedGenToken_(consumes<std::vector<reco::GenParticle> >(ps.getParameter<edm::InputTag>("prunedGen")))
{
}
// ------------ method called once each job just before starting event loop  ------------
void TtZAnalyzer::beginJob()
{
  initHistograms();
}

//
void TtZAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  iEvent.getByToken( prunedGenToken_ , prunedGens );
  const std::vector<reco::GenParticle>* gen = prunedGens.product();
  TtZ ttz(gen);
  if(!ttz.isSet) return;
  hOptimalCosTheta->Fill(ttz.CosTheta(-1));
  double costheta = ttz.CosTheta(-1,false);
  cout<<"----- " <<costheta<<endl;
  hHelicityCosTheta->Fill(costheta);
  hDiffDR->Fill(fabs(ttz.Top.TopP4().DeltaR(ttz.Z.ZP4()) - ttz.TopBar.TopP4().DeltaR(ttz.Z.ZP4())));
}
