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
                                      MuonSubLeadingPtCut = cms.double(20),
                                      MuonIsoCut = cms.double( 0.15 ),
                                      MuonEtaCut = cms.double( 2.4 ),
                                      DiMuLowMassCut = cms.double( 20. ),
                                      DiMuCharge = cms.int32( -1 ),
                                      MuonID = cms.int32( 3 ), #0:no id, 1:Loose , 2:Medium , 3:tight , 4 : soft
                                      DiMuZMassWindow = cms.double( 15.0 ),
                                      
                                      MetCut = cms.double( 40. ),
                                      
                                      ApplyJER = cms.bool( False ),
                                      JetPtCut = cms.double( 30 ),
                                      JetEtaCut = cms.double( 2.4 ),
                                      BTagAlgo = cms.string("pfCombinedInclusiveSecondaryVertexV2BJetTags"),
                                      BTagWPL = cms.double( 0.460 ),
                                      BTagWPM = cms.double( 0.800 ),
                                      BTagWPT = cms.double( 0.935 ),
				      #Which WP to use in selection: 0,1,2 ---> L, M, T
				      # -1 ---> no requirement
				      BTagCuts = cms.vint32(1,-1), # supporting up to two working point, the second is for veto

                                      MinNJets = cms.uint32( 2 ),
                                      MinNBJets = cms.uint32( 2 ),

                                      sample = cms.string( "WJets" ),

                                      LHE = cms.PSet (
        
        useLHEW = cms.bool( False ),
        Input = cms.InputTag("externalLHEProducer")
        ),
                                      isData = cms.bool( False ),

                                      HLT_To_Or = cms.vstring(),

                                      dataPUFile = cms.string("DistrFall15_25ns"),
                                      
                                      SetupDir = cms.string("Setup76")
                              )


import FWCore.ParameterSet.VarParsing as opts
options = opts.VarParsing ('analysis')
options.register('sync',
                 0,
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.int ,
                 "")
options.register('sample',
                 'WJetsMG',
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string,
                 'Sample to analyze')
options.register('job',
                 0,
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.int ,
                 "number of the job")
options.register('nFilesPerJob',
                 1,
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.int ,
                 "number of the files pre job")
options.register('output',
                 "out",
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.string ,
                 "could be root://eoscms//eos/cms/store/user/hbakhshi/out")

options.parseArguments()


theSample = None
import os

if options.sync == 0 :
    from Samples76.Samples import MiniAOD76Samples as samples


    for sample in samples:
        if sample.Name == options.sample :
            theSample = sample

    if not theSample.Name == options.sample:
        raise NameError("The correct sample is not found %s !+ %s" % (sample.Name , options.sample) )

    if theSample == None:
        raise NameError("Sample with name %s wasn't found" % (options.sample))
else:
    from Haamm.HaNaMiniAnalyzer.Sample import *
    theSample = Sample( "Sync" , "Sync" , 100 , False , 0 , "" )
    theSample.Files = ['/store/mc/RunIIFall15MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext3-v1/00000/0C5BB11A-E2C1-E511-8C02-002590A831B6.root']
    options.nFilesPerJob = 1
    options.output = "out" 
    options.job = 0

process.HaNaAnalyzer.sample = theSample.Name
process.HaNaAnalyzer.LHE.useLHEW = theSample.LHEWeight
process.HaNaAnalyzer.isData = theSample.IsData

if not ( options.job < theSample.MakeJobs( options.nFilesPerJob , options.output ) ):
    raise NameError("Job %d is not in the list of the jobs of sample %s with %d files per run" % (options.job , options.sample , options.nFilesPerJob ) )
job = theSample.Jobs[ options.job ]

process.source.fileNames.extend( job.Inputs )
process.TFileService.fileName = job.Output

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
    if options.sync == 0 :
        for v in range(0 , 10 ):
            process.HaNaAnalyzer.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v%d' % (v) )
            process.HaNaAnalyzer.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v%d' % (v) )
