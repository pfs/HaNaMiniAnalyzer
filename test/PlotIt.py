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


nTuples = "/home/nadjieh/cernbox/Hamb13/Oct5_8020_v2/Trees"

from Haamm.HaNaMiniAnalyzer.SampleType import *
from ROOT import kGray, kGreen, kOrange, kRed, kBlack, kCyan, kBlue
dataSamples = SampleType("Data" , kBlack , [GetSample(s) for s in MiniAOD80Samples if s.IsData] , nTuples ) # the first item must be data
ci = TColor.GetColor("#ff6666")
DYSamples = SampleType("DY" , ci , [ GetSample(DYJets80) , GetSample(DYJetsLowMass80)] , nTuples )
ci = TColor.GetColor("#ffff66")
TopSamples = SampleType("Top" , ci , [ GetSample(TTBar80) , GetSample(TChannel80) , GetSample(TW80), GetSample(TbarW80) ] , nTuples )
ci = TColor.GetColor("#996633")
DibosonSamples = SampleType("Diboson" , ci , [ GetSample(ZZ80) , GetSample(WZ80) , GetSample(WW80)] , nTuples )
signalSample = SampleType( "Signal" , kRed+3 , [ GetSample(GGH4080) ] , nTuples , True )

nTotals76 = { "GluGluH":546308 ,
            "VBFH":612352 ,
            "VHGG":162247 ,
            "DiPhoton_":58532906 ,
            "DiPhoton":58532906 ,
            "GJet7640M80":38557025 ,
            "GJet76M80_2040":24739909 ,
            "GJet76M80_40":71613298 ,
            "ZG2LG76":3027812 ,
            "QCDDoubleEM76_m4080_pt30":37835430 ,
            "QCDDoubleEM76_m80_pt3040":17831367 ,
            "QCDDoubleEM76_m80_pt40":19958876 ,
            "TTGG":798500 ,
            "TTGJ":1578840 ,
            "TGJ":55704 ,
            "ttH":52169 ,
            "WJetsMG_FGG":47161328,
            "TTbar_FGG":97994442,
            "ZZ_FGG":9660541,
            "WZ_FGG" :15560489,
            "WW_FGG":988418,
            "WG_FGG":47275,
            "dyEE":49653546
            }

nTotals = {}
            
from Haamm.HaNaMiniAnalyzer.Plotter import *
plotter = Plotter()
allSTs = [dataSamples ,DYSamples , TopSamples , DibosonSamples , signalSample]
for st in allSTs :
    plotter.AddSampleType( st )
    for s in st.Samples:
        if s.IsData :
            continue
        if s.Name in nTotals :
            s.SetNTotal( nTotals[s.Name] )
        else:
            print "total number for sample %s is not set" % s.Name

Cuts = {"Init":"muPt@.size()>1",
	    "DiMu":"muPt[0]>24",
        "atLeastTwoJets":"jetsPt.size>1" ,
        "TwoMediumB":"(nMedNotTight+nTight)==2" ,
        "MetSig" : "metSig < 6"}
        
cDiMu = CutInfo( "PreSelection" , Cuts["Init"])
cDiMu.AddHist( "LeadMuonPt" , "muPt[0]", 40 , 0. , 200. )
cDiMu.AddHist( "SubLeadMuonPt" , "muPt[1]", 40 , 0. , 200. )
# cDiMu.AddHist( "jPt" , "oneB.forward < 0 ? -1 : jetsPt[oneB.forward]",  29 , 10. , 300. )
# cDiMu.AddHist( "jEta" , "oneB.forward < 0 ? -8 : abs(jetsEta[oneB.forward])",  18 , -1. , 5.0 )
# cDiMu.AddHist( "jPhi" , "oneB.forward < 0 ? 10 : jetsPhi[oneB.forward]" , 17 , -3.2 , 3.6 )
# cDiMu.AddHist( "bjPt" , "(nJets>200 || nJets==0) ? -1 : jetsPt[0]",  9 , 20. , 200. )
# cDiMu.AddHist( "bjEta" , "(nJets>200 || nJets==0) ? -8 : abs(jetsEta[0])",  5 , -0.7 , 2.8 )
# cDiMu.AddHist( "bjPhi" , "(nJets>200 || nJets==0) ? 10 : jetsPhi[0]" , 5 , -3.2 , 4.8 )
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
