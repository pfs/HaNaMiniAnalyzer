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


nTuples = "/home/nadjieh/cernbox/Hamb13/Oct14_8020_MassProd/Trees"

from Haamm.HaNaMiniAnalyzer.SampleType import *
from ROOT import kGray, kGreen, kOrange, kRed, kBlack, kCyan, kBlue
dataSamples = SampleType("Data" , kBlack , [GetSample(s) for s in MiniAOD80Samples if s.IsData] , nTuples ) # the first item must be data
ci = TColor.GetColor("#ff6666")
DYSamples = SampleType("DY" , ci , [ GetSample(DYJets80) , GetSample(DYJetsLowMass80), GetSample(WJetsMG80)] , nTuples )
ci = TColor.GetColor("#ffff66")
TopSamples = SampleType("Top" , ci , [ GetSample(TTBar80) , GetSample(TChannel80) , GetSample(TW80), GetSample(TbarW80) ] , nTuples )
ci = TColor.GetColor("#996633")
DibosonSamples = SampleType("Diboson" , ci , [ GetSample(ZZ80) , GetSample(WZ80) , GetSample(WW80)] , nTuples )
signalSample = SampleType( "Signal" , kRed+3 , [ GetSample(GGH4080) ] , nTuples , True )

nTotals = {}
            
from Haamm.HaNaMiniAnalyzer.Plotter import *
plotter = Plotter()
allSTs = [dataSamples ,DibosonSamples , TopSamples , DYSamples , signalSample]
for st in allSTs :
    plotter.AddSampleType( st )
    for s in st.Samples:
        if s.IsData :
            continue
        if s.Name in nTotals :
            s.SetNTotal( nTotals[s.Name] )
        else:
            print "total number for sample %s is not set" % s.Name

Cuts = {"Trigger":""}        
cDiMu = CutInfo( "Trigger" , Cuts["Trigger"],"hltWeight_Mu17Mu8_DZ*bWs.W2L*Weight")
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
cDiMu.AddHist( "aBjetMass" , "aBjetPtOrdered.mass", 100 , 15 , 515)
cDiMu.AddHist( "aBjetPt" , "aBjetPtOrdered.pt", 100 , 0 , 500)
cDiMu.AddHist( "hMass" , "higgsjetPtOrdered.mass", 100 , 15 , 515)
cDiMu.AddHist( "hPt" , "higgsjetPtOrdered.pt", 100 , 0 , 500)
plotter.AddTreePlots( cDiMu )


# cNonIsoMu = CutInfo("nonIsoMu" , Cuts["DiMu"] + " && " + Cuts["nonIsoMu"] , "Weight.W%d * G1.w * G2.w" )
# for h in cDiMu.ListOfHists:
#     cNonIsoMu.AddHist( h )
# plotter.AddTreePlots( cNonIsoMu )

plotter.LoadHistos( 12900 )

#plotter.AddLabels( "CutFlowTable" , ["All" , "HLT" , "Vertex" , ">1Pair" , "LeadingPass" , "SubLeadingPass" , "PairCuts" ] )

fout = TFile.Open("out_cft_normtolumi.root", "recreate")
plotter.Write(fout, False)
fout.Close()
