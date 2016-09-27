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

#include "Haamm/HaNaMiniAnalyzer/interface/BaseMiniAnalyzer.h"

BaseMiniAnalyzer::BaseMiniAnalyzer(const edm::ParameterSet& iConfig):
  SetupDir( iConfig.getParameter<string>("SetupDir") ),
  IsData( iConfig.getParameter< bool >("isData") ),
  SampleName(iConfig.getParameter< string >("sample") )
{
  LHEReader = NULL;
  geninfoReader = NULL;
  if( !IsData ){
    edm::ParameterSet LHE = iConfig.getParameter< edm::ParameterSet >("LHE");
    if( LHE.getParameter< bool >( "useLHEW" ) ){
      LHEReader = new LHEEventReader( LHE , consumesCollector() );
      
      edm::ParameterSet genPset;
      genPset.addParameter( "Input" , edm::InputTag( "generator" ) );
      geninfoReader = new GenEventInfoProductReader( genPset , consumesCollector() );
    }
  }  

  hltReader = new HLTReader( iConfig.getParameter< edm::ParameterSet >("HLT") , consumesCollector() );
  vertexReader = new VertexReader( iConfig.getParameter< edm::ParameterSet >("Vertex") , consumesCollector() , IsData , SetupDir );

  if( iConfig.exists( "DiMuon" ) ){
    diMuReader = new DiMuonReader( iConfig.getParameter< edm::ParameterSet >("DiMuon") , consumesCollector() , IsData , SetupDir );
  }else
    diMuReader = NULL;

  if( iConfig.exists( "MET" ) ){
    metReader = new METReader( iConfig.getParameter< edm::ParameterSet >("MET") , consumesCollector() , IsData );
  }else
    metReader = NULL;

  if( iConfig.exists( "Jets" ) ){
    jetReader = new JetReader( iConfig.getParameter< edm::ParameterSet >("Jets") , consumesCollector() , IsData , SetupDir );
  }else
    jetReader = NULL;

}

//
bool BaseMiniAnalyzer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  return true;
}




// ------------ method called once each job just before starting event loop  ------------
void BaseMiniAnalyzer::beginJob()
{
}
void BaseMiniAnalyzer::endJob() 
{
}

BaseMiniAnalyzer::~BaseMiniAnalyzer()
{
}
void BaseMiniAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

