from os import listdir
from os.path import isfile, join
from das_client import *
from subprocess import call
import os, ntpath


class Sample :
    def __init__(self , name , histocat , xsection , lheW , color , datasetname , appendix = "" ):
        self.Name = name
        self.HistoCat = histocat
        self.XSection = xsection
        self.IsData = (self.XSection <= 0)
        self.LHEWeight = lheW
        
        self.Color = color

        self.Files = []

        self.InitiateFilesFromListOrDAS( datasetname , appendix )

    def AddFiles( self , directory ):
        files = [join(directory, f) for f in listdir(directory) if isfile(join(directory, f))]
        self.Files.extend( files )

    def GetListFileName( self ):
        return self.Name + ".list"

    def WriteFileListToFile( self ):
        if os.path.exists(self.GetListFileName() ):
            os.remove( self.GetListFileName() )

        with open(self.GetListFileName() , 'w') as f :
            for fline in self.Files :
                f.write( fline + "\n" )

    def LoadFilesFromList(self):
        if os.path.exists( self.GetListFileName() ):
            with open(self.GetListFileName() , 'r') as f :
                for line in f.readlines() :
                    self.Files.append( line.strip() )

    def InitiateFilesFromListOrDAS( self , sample , prefix = "" ):
        self.Files = []
        self.LoadFilesFromList()

        if len(self.Files) == 0 :
            self.AddDASFiles( sample , prefix )
            self.WriteFileListToFile()

    def AddDASFiles( self , sample , prefix = "" ):
        jsondict = get_data( "https://cmsweb.cern.ch" , 
                             "file dataset=%(sample)s instance=prod/global"  %  {'sample':sample} ,
                             0 , #idx
                             0 , #limit
                             0 , #verbose
                             300 , #waiting time
                             "" ,  #ckey
                             "" , #cert
                             )
        
        cli_msg  = jsondict.get('client_message', None)
        if  cli_msg:
            print "DAS CLIENT WARNING: %s" % cli_msg
        if  'status' not in jsondict:
            print 'DAS record without status field:\n%s' % jsondict
            sys.exit(EX_PROTOCOL)
        if  jsondict['status'] != 'ok':
            print "status: %s, reason: %s" \
                % (jsondict.get('status'), jsondict.get('reason', 'N/A'))
            sys.exit(EX_TEMPFAIL)

        data = jsondict['data']
        iii = 1
        for jjj in data:
            #print "%d/%d : %s" % ( iii , len(data) , ntpath.basename(str(prim_value(jjj))) )
            iii += 1
            self.Files.append( prefix + str( prim_value(jjj) ) )

MiniAOD76Samples = []

SingleMu76 = Sample( "SingleMu" , "Data" , 0 , False , 0 , "/SingleMuon/Run2015D-16Dec2015-v1/MINIAOD" )
#MiniAOD76Samples.append( SingleMu76 )

DoubleMu76 = Sample("DoubleMu" , "Data" , 0 , False , 0 , "/DoubleMuon/Run2015D-16Dec2015-v1/MINIAOD" )
MiniAOD76Samples.append( DoubleMu76 )

WJetsMG76 = Sample( "WJetsMG" , "VJets" , 61526.7 , False , 0 , "/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM" )
MiniAOD76Samples.append( WJetsMG76 )

DYJets76 = Sample( "DYJets" , "VJets" , 6025.2 , True , 0 , "/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext4-v1/MINIAODSIM" )
MiniAOD76Samples.append( DYJets76 )

TTBar76 = Sample( "TTbar" , "Top" , 831.76 , False , 0 , "/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext3-v1/MINIAODSIM" )
MiniAOD76Samples.append( TTBar76 )

TChannel76 = Sample("TChannel" , "Top" , 70.3 , True , 0 , "/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext1-v1/MINIAODSIM" )
MiniAOD76Samples.append( TChannel76 )

TW76 = Sample("TW" , "Top" , 35.6 , False , 0 , "/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM" )
MiniAOD76Samples.append( TW76 )

TbarW76 = Sample("TbarW" , "Top" , 35.6 , False , 0 , "/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM" )
MiniAOD76Samples.append( TbarW76 )

QCDMuEnriched76 = Sample( "QCDMuEnriched" , "QCD" , 381304 , False , 0 , "/QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM" )

MiniAOD76Samples.append(QCDMuEnriched76)

