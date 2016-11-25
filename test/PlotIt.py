#!/usr/bin/env python
from ROOT import gROOT, TLatex, TCanvas, TFile, gROOT, TColor
import math

gROOT.SetBatch(True)

from Samples80.Samples import *
samples = None
runOnOutsOfAnotherJob = False
if runOnOutsOfAnotherJob :
    samples = samples24june
    samples += sampleswith24juneonly
else :
    samples = MiniAOD80Samples

def GetSample( s ):
    if runOnOutsOfAnotherJob:
        for ss in samples:
            if s.Name == ss.Name :
                return ss
        return None
    else:
        return s


nTuples = "/home/nadjieh/cernbox/Hamb13/Oct14_8020_MassProd/Trees/withReg"

from Haamm.HaNaMiniAnalyzer.SampleType import *
from ROOT import kGray, kGreen, kOrange, kRed, kBlack, kCyan, kBlue, kAzure, kTeal, kPink, kYellow
dataSamples = SampleType("Data" , kBlack , [GetSample(s) for s in MiniAOD80Samples if s.IsData] , nTuples ) # the first item must be data
ci = TColor.GetColor("#ff6666")
DYSamples = SampleType("DY" , ci , [ GetSample(DYJets80) , GetSample(DYJetsLowMass80), GetSample(WJetsMG80)] , nTuples )
ci = TColor.GetColor("#ffff66")
TopSamples = SampleType("Top" , ci , [ GetSample(TTBar80) , GetSample(TChannel80) , GetSample(TW80), GetSample(TbarW80) ] , nTuples )
DibosonSamples = SampleType("Diboson" , kAzure-9 , [ GetSample(ZZ80) , GetSample(WZ80) , GetSample(WW80)] , nTuples )

mySignals = []

mySignals.append (SampleType( "Signal15" , kAzure+10 , [ GetSample(GGH1580) ] , nTuples , True ))
mySignals.append (SampleType( "Signal20" , kBlue+2 , [ GetSample(GGH2080) ] , nTuples , True ))
mySignals.append (SampleType( "Signal25" , kCyan+2	, [ GetSample(GGH2580) ] , nTuples , True ))
mySignals.append (SampleType( "Signal30" , kTeal+10 , [ GetSample(GGH3080) ] , nTuples , True ))
mySignals.append (SampleType( "Signal35" , kGreen+2 , [ GetSample(GGH3580) ] , nTuples , True ))
mySignals.append (SampleType( "Signal40" , kYellow+2 , [ GetSample(GGH4080) ] , nTuples , True ))
mySignals.append (SampleType( "Signal45" , kOrange-2 , [ GetSample(GGH4580) ] , nTuples , True ))
mySignals.append (SampleType( "Signal50" , kOrange+10 , [ GetSample(GGH5080) ] , nTuples , True ))
mySignals.append (SampleType( "Signal55" , kRed+2 , [ GetSample(GGH5580) ] , nTuples , True ))
mySignals.append (SampleType( "Signal60" , kPink+10 , [ GetSample(GGH6080) ] , nTuples , True ))

nTotals = {}
            
from Haamm.HaNaMiniAnalyzer.Plotter import *
plotter = Plotter()
allSTs = [dataSamples ,DibosonSamples , TopSamples , DYSamples ]
for iSt in mySignals:
	allSTs.append(iSt)

for st in allSTs :
    plotter.AddSampleType( st )
    for s in st.Samples:
        if s.IsData :
            continue
        if s.Name in nTotals :
            s.SetNTotal( nTotals[s.Name] )
        else:
            print "total number for sample %s is not set" % s.Name

Cuts = {"Trigger":"",
		"MetSig":"metSig < 2",
		"OptimCuts":"jetsPt[0]>20 && jetsPt[0]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2",
}        
cSignalCount = CutInfo( "SigCount" , Cuts["MetSig"],"hltWeights.mu17mu8dz*bWs.W2L*Weight",False)
cSignalCount.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)
cSignalCount.AddHist( "LeadMuonPt" , "muPt[0]", 40 , 0. , 200.)

cDiMu = CutInfo( "Trigger" , Cuts["Trigger"],"hltWeights.mu17mu8dz*bWs.W2L*Weight",True)
cDiMu.AddHist( "LeadMuonPt" , "muPt[0]", 40 , 0. , 200.)
cDiMu.AddHist( "LeadMuonEta" , "muEta[0]", 60 , -3. , 3.)
cDiMu.AddHist( "SubLeadMuonPt" , "muPt[1]", 40 , 0. , 200.)
cDiMu.AddHist( "SubLeadMuonEta" , "muEta[1]", 60 , -3. , 3.)
cDiMu.AddHist( "LeadJetPt" , "jetsPt[0]", 40 , 0. , 200.)
cDiMu.AddHist( "LeadJetEta" , "jetsEta[0]", 60 , -3. , 3.)
cDiMu.AddHist( "SubLeadJetPt" , "jetsPt[1]", 40 , 0. , 200.)
cDiMu.AddHist( "SubLeadJetEta" , "jetsEta[1]", 60 , -3. , 3.)
cDiMu.AddHist( "MET" , "met", 20 , 0. , 200.)
cDiMu.AddHist( "metsig" , "metSig", 50 , 0. , 50.)
cDiMu.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)
cDiMu.AddHist( "aMuPt" , "aMu.pt", 50 , 0 , 200)
cDiMu.AddHist( "aBjetMass" , "aBjetPtOrdered.mass", 50 , 15 , 515)
cDiMu.AddHist( "aBjetPt" , "aBjetPtOrdered.pt", 100 , 0 , 500)
cDiMu.AddHist( "hMass" , "higgsjetPtOrdered.mass", 50 , 0 , 500)
cDiMu.AddHist( "hPt" , "higgsjetPtOrdered.pt", 100 , 0 , 500)
cDiMu.AddHist( "hMassReg" , "higgsReg.mass", 50, 15 , 515)
cDiMu.AddHist( "aBjetMassReg" , "abjetReg.mass", 50 , 15 , 515)

cMetSig = CutInfo( "MetSig" , Cuts["MetSig"],"hltWeights.mu17mu8dz*bWs.W2L*Weight",True)
cMetSig.AddHist( "bTagDisc1" , "muPt[0]", 100 , 0. , 1.)
cMetSig.AddHist( "bTagDisc2" , "muPt[0]", 100 , 0. , 1.)
cMetSig.AddHist( "LeadMuonPt" , "muPt[0]", 40 , 0. , 200.)
cMetSig.AddHist( "LeadMuonEta" , "muEta[0]", 60 , -3. , 3.)
cMetSig.AddHist( "SubLeadMuonPt" , "muPt[1]", 40 , 0. , 200.)
cMetSig.AddHist( "SubLeadMuonEta" , "muEta[1]", 60 , -3. , 3.)
cMetSig.AddHist( "LeadJetPt" , "jetsPt[0]", 40 , 0. , 200.)
cMetSig.AddHist( "LeadJetEta" , "jetsEta[0]", 60 , -3. , 3.)
cMetSig.AddHist( "SubLeadJetPt" , "jetsPt[1]", 40 , 0. , 200.)
cMetSig.AddHist( "SubLeadJetEta" , "jetsEta[1]", 60 , -3. , 3.)
cMetSig.AddHist( "MET" , "met", 20 , 0. , 200.)
cMetSig.AddHist( "metsig" , "metSig", 50 , 0. , 50.)
cMetSig.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)
cMetSig.AddHist( "aMuPt" , "aMu.pt", 50 , 0 , 200)
cMetSig.AddHist( "aBjetMass" , "aBjetPtOrdered.mass", 50 , 15 , 515)
cMetSig.AddHist( "aBjetPt" , "aBjetPtOrdered.pt", 100 , 0 , 500)
cMetSig.AddHist( "hMass" , "higgsjetPtOrdered.mass", 50 , 0 , 500)
cMetSig.AddHist( "hPt" , "higgsjetPtOrdered.pt", 100 , 0 , 500)
cMetSig.AddHist( "hMassReg" , "higgsReg.mass", 50, 15 , 515)
cMetSig.AddHist( "aBjetMassReg" , "abjetReg.mass", 50 , 15 , 515)

cOptimCuts = CutInfo( "MetSig" , Cuts["OptimCuts"],"hltWeights.mu17mu8dz*bWs.W2L*Weight",False)
cOptimCuts.AddHist( "LeadMuonPt" , "muPt[0]", 40 , 0. , 200.)
cOptimCuts.AddHist( "LeadMuonEta" , "muEta[0]", 60 , -3. , 3.)
cOptimCuts.AddHist( "SubLeadMuonPt" , "muPt[1]", 40 , 0. , 200.)
cOptimCuts.AddHist( "SubLeadMuonEta" , "muEta[1]", 60 , -3. , 3.)
cOptimCuts.AddHist( "LeadJetPt" , "jetsPt[0]", 40 , 0. , 200.)
cOptimCuts.AddHist( "LeadJetEta" , "jetsEta[0]", 60 , -3. , 3.)
cOptimCuts.AddHist( "SubLeadJetPt" , "jetsPt[1]", 40 , 0. , 200.)
cOptimCuts.AddHist( "SubLeadJetEta" , "jetsEta[1]", 60 , -3. , 3.)
cOptimCuts.AddHist( "MET" , "met", 20 , 0. , 200.)
cOptimCuts.AddHist( "metsig" , "metSig", 50 , 0. , 50.)
cOptimCuts.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)
cOptimCuts.AddHist( "aMuPt" , "aMu.pt", 50 , 0 , 200)
cOptimCuts.AddHist( "aBjetMass" , "aBjetPtOrdered.mass", 50 , 15 , 515)
cOptimCuts.AddHist( "aBjetPt" , "aBjetPtOrdered.pt", 100 , 0 , 500)
cOptimCuts.AddHist( "hMass" , "higgsjetPtOrdered.mass", 50 , 0 , 500)
cOptimCuts.AddHist( "hPt" , "higgsjetPtOrdered.pt", 100 , 0 , 500)
cOptimCuts.AddHist( "hMassReg" , "higgsReg.mass", 50, 15 , 515)
cOptimCuts.AddHist( "aBjetMassReg" , "abjetReg.mass", 50 , 15 , 515)


plotter.AddTreePlots( cDiMu )
#plotter.AddTreePlots( cOptimCuts )
plotter.AddTreePlots( cMetSig )
#plotter.AddTreePlots( cSignalCount )

# cNonIsoMu = CutInfo("nonIsoMu" , Cuts["DiMu"] + " && " + Cuts["nonIsoMu"] , "Weight.W%d * G1.w * G2.w" )
# for h in cDiMu.ListOfHists:
#     cNonIsoMu.AddHist( h )
# plotter.AddTreePlots( cNonIsoMu )

plotter.LoadHistos( 12900 )

#plotter.AddLabels( "CutFlowTable" , ["All" , "HLT" , "Vertex" , ">1Pair" , "LeadingPass" , "SubLeadingPass" , "PairCuts" ] )

fout = TFile.Open("out_cft_normtolumi_RegBlindCorrectHLTweight.root", "recreate")
plotter.Write(fout, False)
fout.Close()
