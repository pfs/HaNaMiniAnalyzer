import FWCore.ParameterSet.Config as cms
TtZ = cms.EDAnalyzer('TtZAnalyzer',
                     prunedGen = cms.InputTag("prunedGenParticles"),
                     sample = cms.string("WJetsMG"),
                     isData = cms.bool( False ),
                     SetupDir = cms.string("Setup76")
                     )
