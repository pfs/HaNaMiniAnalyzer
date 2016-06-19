#include "Haamm/HaNaMiniAnalyzer/interface/TtGenEvent.h"
#include <iostream>

TtZ::~TtZ(){

}

TtZ::TtZ( const TtZ* ttbar , bool JustTransverse  ){
  isSet = ttbar->isSet;
  if( !isSet )
    return ;

  if( !JustTransverse ){
    Top = ttbar->Top;
    TopBar = ttbar->TopBar;
  }

}
TtZ::TtZ( const std::vector<reco::GenParticle>* gen  )
{
  int top = getLastCopy( gen , 6 );
  int topbar = getLastCopy( gen , -6 );

  int wm = getLastCopy( gen , -24 , -6 , true , true );
  int wp = getLastCopy( gen , 24 , 6 , true , true);

  int lm = getLastCopy( gen , 11 , -24 );
  int neutrinobar = getLastCopy( gen , -12 , -24 );

  int lp = getLastCopy( gen , -11 , 24 );
  int neutrino = getLastCopy( gen , 12 , 24 );

  if(lm < 0){
    lm = getLastCopy( gen , 13 , -24 );
    neutrinobar = getLastCopy( gen , -14 , -24 );
  }
  if(lp < 0){
    lp = getLastCopy( gen , -13 , 24 );
    neutrino = getLastCopy( gen , 14 , 24 );
  }


  if(lm < 0){
    lm = getLastCopy( gen , 13 , -24 , true , true);
    neutrinobar = getLastCopy( gen , -14 , -24  , true , true);
  }
  if(lp < 0){
    lp = getLastCopy( gen , -13 , 24  , true , true);
    neutrino = getLastCopy( gen , 14 , 24  , true , true);
  }

  if(lm < 0){
    lm = getLastCopy( gen , 11 , -24 , true , true);
    neutrinobar = getLastCopy( gen , -12 , -24  , true , true);
  }
  if(lp < 0){
    lp = getLastCopy( gen , -11 , 24  , true , true);
    neutrino = getLastCopy( gen , 12 , 24  , true , true);
  }


  int b = getLastCopy( gen , 5 , 6 , true );
  if( b < 0 )
    b = getLastCopy( gen , 5 , 6 , true , true );

  int bbar = getLastCopy( gen , -5 , -6 , true );
  if( bbar < 0)
    bbar = getLastCopy( gen , -5 , -6 , true , true );

  if( lm < 0 || lp < 0 ){
    isSet = false;
    return;
  }
  
  //std::cout << top << "->" << b << "+(" << wm << "->" << lm << "," << neutrinobar << ") ,,,  " ;
  //std::cout << topbar << "->" << bbar << "+(" << wp << "->" << lp << "," << neutrino << ")" << std::endl ;

  TopBar.Set(
	     &(gen->at( topbar )),
	     &(gen->at( wp )),
	     &(gen->at(bbar)),
	     &(gen->at( lp )),
	     &(gen->at( neutrino )) );
 
  Top.Set(
	  &(gen->at( top )),
	  &(gen->at( wm )),
	  &(gen->at( b )),
	  &(gen->at( lm )),
	  &(gen->at( neutrinobar )) );

  isSet = true;
}

int TtZ::getLastCopy(const std::vector<reco::GenParticle>* gens, int pdgId , int parentId , bool beforeFSR , bool noCheckLastCopy ){
  int index=-1;
  for(auto genPart : *gens ){
    index ++ ;
    int pdgid = genPart.pdgId();
    if( pdgid != pdgId )
      continue;
    if( parentId != 0 )
      if( genPart.mother()->pdgId() != parentId )
	continue;
    if( noCheckLastCopy )
      return index;
    else if( beforeFSR ){
      if( genPart.isLastCopyBeforeFSR() )
	return index;
    }else if( genPart.isLastCopy() )
      return index;
  }
  return -1;
}
