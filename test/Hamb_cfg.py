import FWCore.ParameterSet.Config as cms

process = cms.Process("HaNa")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring()
)

process.load("Haamm.HaNaMiniAnalyzer.Hamb_cfi")
#process.TTH 

import FWCore.ParameterSet.VarParsing as opts
options = opts.VarParsing ('analysis')
options.register('sync',
                 0,
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.int ,
                 "")
options.register('sample',
		 'TTbar',
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

process.Hamb.sample = theSample.Name
process.Hamb.LHE.useLHEW = theSample.LHEWeight
process.Hamb.isData = theSample.IsData

if not ( options.job < theSample.MakeJobs( options.nFilesPerJob , options.output ) ):
    raise NameError("Job %d is not in the list of the jobs of sample %s with %d files per run" % (options.job , options.sample , options.nFilesPerJob ) )
job = theSample.Jobs[ options.job ]

process.source.fileNames.extend( job.Inputs )
process.TFileService.fileName = job.Output

process.maxEvents.input = options.maxEvents

if theSample.IsData :
    import FWCore.PythonUtilities.LumiList as LumiList
    process.source.lumisToProcess = LumiList.LumiList(filename = (process.Hamb.SetupDir.value() + '/JSON.txt')).getVLuminosityBlockRange()
    process.GlobalTag.globaltag = '76X_dataRun2_v15'
    process.p = cms.Path( process.Hamb )
    for v in range(0 , 10 ):
        process.Hamb.HLT.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v%d' % (v) )
        process.Hamb.HLT.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v%d' % (v) )

else :
    process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0' #76X_mcRun2_asymptotic_RunIIFall15DR76_v1
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

    process.Hamb.Jets.Input = "patJetsReapplyJEC"
    process.p = cms.Path( process.patJetCorrFactorsReapplyJEC + process.patJetsReapplyJEC + process.Hamb)
    if options.sync == 0 :
        for v in range(0 , 10 ):
            process.Hamb.HLT.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v%d' % (v) )
            process.Hamb.HLT.HLT_To_Or.append( 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v%d' % (v) )
