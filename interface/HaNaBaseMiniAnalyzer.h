#ifndef HaNaBaseMiniAnalyzer_H
#define HaNaBaseMiniAnalyzer_H

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "LHEEventReader.h"
#include "HLTReader.h"
#include "VertexReader.h"
#include "DiMuonReader.h"
#include "METReader.h"
#include "JetReader.h"

#include "Histograms.h"

//using namespace reco;
using namespace edm;
using namespace std;
//using namespace pat;

class HaNaBaseMiniAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit HaNaBaseMiniAnalyzer(const edm::ParameterSet&);
  ~HaNaBaseMiniAnalyzer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
protected:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  // ---------- Common variables needed for event analyzing in analyze method
  double W;
  double stepEventSelection;
  Histograms* hCutFlowTable;
  // --------- Common things to read from config file :
  string SetupDir;
  bool IsData;
  string SampleName;
  // --------- All Info needed in the event processing ---------------
  LHEEventReader* LHEReader;
  HLTReader* hltReader;
  VertexReader* vertexReader;
  DiMuonReader* diMuReader;
  METReader* metReader;
  JetReader* jetReader;
};

#endif
