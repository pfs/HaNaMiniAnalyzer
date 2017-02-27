#include "Haamm/HaNaMiniAnalyzer/interface/PackedCandidateReader.h"

PackedCandidateReader::PackedCandidateReader( edm::ParameterSet const& iPS, edm::ConsumesCollector && iC) :
  BaseEventReader< pat::PackedCandidateCollection >( iPS , &iC )
{
  
}

double PackedCandidateReader::Read( const edm::Event& iEvent ){
  BaseEventReader< pat::PackedCandidateCollection >::Read( iEvent );
  
  nEles = nMus = nChargedHadrons = 0;

  for(auto cand : *handle){
    int id = abs(cand.pdgId());
    if( id == 11 )
      nEles ++;
    else if(id == 13)
      nMus ++;
    else if( id == 211 )
      nChargedHadrons++;
  }

  return (nEles+nMus+nChargedHadrons);

}

