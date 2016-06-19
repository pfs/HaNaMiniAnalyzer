import FWCore.ParameterSet.Config as cms

process = cms.Process("HaNa")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring()
)

process.load("Haamm.HaNaMiniAnalyzer.TtZAnalyzer_cfi")
#process.TTH 

import FWCore.ParameterSet.VarParsing as opts
options = opts.VarParsing ('analysis')
options.register('sync',
                 0,
                 opts.VarParsing.multiplicity.singleton,
                 opts.VarParsing.varType.int ,
                 "")
options.register('sample',
		 'TtZ',
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
    from Samples76.TtZSamples import MiniAOD76Samples as samples


    for sample in samples:
        if sample.Name == options.sample :
            theSample = sample

    if not theSample.Name == options.sample:
        raise NameError("The correct sample is not found %s !+ %s" % (sample.Name , options.sample) )

    if theSample == None:
        raise NameError("Sample with name %s wasn't found" % (options.sample))

process.TtZ.sample = theSample.Name
process.TtZ.isData = theSample.IsData

if not ( options.job < theSample.MakeJobs( options.nFilesPerJob , options.output ) ):
    raise NameError("Job %d is not in the list of the jobs of sample %s with %d files per run" % (options.job , options.sample , options.nFilesPerJob ) )
job = theSample.Jobs[ options.job ]

process.source.fileNames.extend( job.Inputs )
process.TFileService.fileName = job.Output

process.maxEvents.input = options.maxEvents
process.p = cms.Path( process.TtZ)

