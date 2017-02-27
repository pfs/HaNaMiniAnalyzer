from Haamm.HaNaMiniAnalyzer.Sample import *

import os
Sample.WD = os.path.dirname(os.path.abspath(__file__))
print Sample.WD

SingleMuonB1 = Sample( "SingleMuB1" ,  0 , False , "/SingleMuon/Run2016B-03Feb2017_ver1-v1/MINIAOD")

SingleMuonB2 = Sample( "SingleMuB2" ,  0 , False  , "/SingleMuon/Run2016B-03Feb2017_ver2-v2/MINIAOD")

SingleMuonC = Sample( "SingleMuC" ,  0 , False ,  "/SingleMuon/Run2016C-03Feb2017-v1/MINIAOD")
SingleMuonD = Sample( "SingleMuD" ,  0 , False ,  "/SingleMuon/Run2016D-03Feb2017-v1/MINIAOD")

SingleMuonE = Sample( "SingleMuE" ,  0 , False ,  "/SingleMuon/Run2016E-03Feb2017-v1/MINIAOD")

SingleMuonF = Sample( "SingleMuF" ,  0 , False ,  "/SingleMuon/Run2016F-03Feb2017-v1/MINIAOD")

SingleMuonG = Sample( "SingleMuG" ,  0 , False ,  "/SingleMuon/Run2016G-03Feb2017-v1/MINIAOD")

SingleMuonH2 = Sample( "SingleMuH2" ,  0 , False ,  "/SingleMuon/Run2016H-03Feb2017_ver2-v1/MINIAOD" )

SingleMuonH3 = Sample( "SingleMuH3" ,  0 , False ,  "/SingleMuon/Run2016H-03Feb2017_ver3-v1/MINIAOD" )


MINIAOD = [ SingleMuonB1 , SingleMuonB2 , SingleMuonC , SingleMuonD , SingleMuonE , SingleMuonF , SingleMuonG , SingleMuonH2 , SingleMuonH3 ]


ZMuMu = Sample( "ZmuMu" , 1 , False ,  "/ZToMuMu_NNPDF30_13TeV-powheg_M_50_120/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM" )

DYMuMu0J = Sample( "DYMuMu0J" , 1 , False ,  "/DYToLL_0J_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" )

DYMuMu1J = Sample( "DYMuMu1J" , 1 , False ,  "/DYToLL_1J_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" )

DYMuMu2J = Sample( "DYMuMu2J" , 1 , False ,  "/DYToLL_2J_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM" )

MINIAOD.extend( [ ZMuMu , DYMuMu0J , DYMuMu1J , DYMuMu2J ] )

