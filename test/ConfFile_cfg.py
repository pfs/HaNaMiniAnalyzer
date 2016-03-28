import FWCore.ParameterSet.Config as cms

process = cms.Process("HaNa")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring()
)

process.HaNaAnalyzer = cms.EDAnalyzer('HaNaMiniAnalyzer',
                                      pileupSrc = cms.InputTag("slimmedAddPileupInfo"),
                                      
                                      vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                      muons = cms.InputTag("slimmedMuons"),
                                      jets = cms.InputTag("slimmedJets"),
                                      oldjets = cms.InputTag("slimmedJets"),
                                      mets = cms.InputTag("slimmedMETs"),
                                      
                                      MuonLeadingPtCut = cms.double(20),
                                      MuonSubLeadingPtCut = cms.double(8),
                                      MuonIsoCut = cms.double( 0.25 ),
                                      MuonEtaCut = cms.double( 2.4 ),

                                      JetPtCut = cms.double( 15 ),
                                      JetEtaCut = cms.double( 2.4 ),
                                      BTagAlgo = cms.string("pfCombinedInclusiveSecondaryVertexV2BJetTags"),
                                      BTagWPL = cms.double( 0.460 ),
                                      BTagWPM = cms.double( 0.800 ),
                                      BTagWPT = cms.double( 0.935 ),
				      #Which WP to use in selection: 0,1,2 ---> L, M, T
				      # -1 ---> no requirement
				      BTagCuts = cms.vint32(0,-1), # supporting up to two working point, the second is for veto

                                      sample = cms.string( "WJets" ),
                                      useLHEW = cms.bool( False ),
                                      isData = cms.bool( False ),

                                      HLT_To_Or = cms.vstring(),

                                      dataPUFile = cms.string("DistrFall15_25ns"),
                                      
                                      SetupDir = cms.string("Setup76")
                              )


import FWCore.ParameterSet.VarParsing as opts
options = opts.VarParsing ('analysis')
options.register('sample',
                 'WJetsMG',
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'Sample to analyze')
options.register('file',
                 0,
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.int ,
                 "number of the input file in the list of sample-files")
options.register('output',
                 "out",
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string ,
                 "could be root://eoscms//eos/cms/store/user/hbakhshi/out")

options.parseArguments()


from Samples76.Samples import MiniAOD76Samples as samples
import os
theSample = None
for sample in samples:
    if sample.Name == options.sample :
        theSample = sample

process.HaNaAnalyzer.sample = theSample.Name
process.HaNaAnalyzer.useLHEW = theSample.LHEWeight
process.HaNaAnalyzer.isData = theSample.IsData

process.source.fileNames.append( theSample.Files[ options.file ] )
process.TFileService.fileName = options.output + "_" + options.sample + "_" +  os.path.splitext( os.path.basename( theSample.Files[ options.file ] ))[0] + ".root"

process.maxEvents.input = options.maxEvents

if theSample.IsData :
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = (process.HaNaAnalyzer.SetupDir.value() + '/JSON.txt')).getVLuminosityBlockRange()
    process.GlobalTag.globaltag = '76X_dataRun2_v15'
    process.p = cms.Path( process.HaNaAnalyzer )
    for v in range(0 , 10 ):
        process.HaNaAnalyzer.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v%d' % (v) )
        process.HaNaAnalyzer.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v%d' % (v) )
else :
    process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'
    from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import *
    process.patJetCorrFactorsReapplyJEC = updatedPatJetCorrFactors.clone(
        src = cms.InputTag("slimmedJets"),
        levels = ['L1FastJet', 
                  'L2Relative', 
                  'L3Absolute'],
        payload = 'AK4PFchs' ) # Make sure to choose the appropriate levels and payload here!

    process.patJetsReapplyJEC = updatedPatJets.clone(
        jetSource = cms.InputTag("slimmedJets"),
        jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
        )

    process.HaNaAnalyzer.jets = "patJetsReapplyJEC"
    process.p = cms.Path( process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC + process.HaNaAnalyzer )
    for v in range(0 , 10 ):
        process.HaNaAnalyzer.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v%d' % (v) )
        process.HaNaAnalyzer.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v%d' % (v) )
