#!/usr/bin/env python
from ROOT import gROOT, TLatex, TCanvas, TFile, gROOT, TColor
import math
import string

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


nTuples = "/home/nadjieh/cernbox/Hamb13/Oct14_8020_Opt/Trees"

from Haamm.HaNaMiniAnalyzer.SampleType import *
from ROOT import kGray, kGreen, kOrange, kRed, kBlack, kCyan, kBlue
dataSamples = SampleType("Data" , kBlack , [GetSample(s) for s in MiniAOD80Samples if s.IsData] , nTuples ) # the first item must be data
ci = TColor.GetColor("#ff6666")
DYSamples = SampleType("DY" , ci , [ GetSample(DYJets80) , GetSample(DYJetsLowMass80)] , nTuples )
ci = TColor.GetColor("#ffff66")
TopSamples = SampleType("Top" , ci , [ GetSample(TTBar80) , GetSample(TW80), GetSample(TbarW80) ] , nTuples )
ci = TColor.GetColor("#996633")

signalsamples = []
signalsamples.append(SampleType( "Signal15" , kRed+3 , [ GetSample(GGH1580) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal20" , kRed+2 , [ GetSample(GGH2080) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal25" , kRed+2 , [ GetSample(GGH2580) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal30" , kRed+2 , [ GetSample(GGH3080) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal35" , kRed+2 , [ GetSample(GGH3580) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal40" , kRed+2 , [ GetSample(GGH4080) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal45" , kRed+2 , [ GetSample(GGH4580) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal50" , kRed+2 , [ GetSample(GGH5080) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal55" , kRed+2 , [ GetSample(GGH5580) ] , nTuples , True ))
signalsamples.append(SampleType( "Signal60" , kRed+2 , [ GetSample(GGH6080) ] , nTuples , True ))



nTotals = {}
            
from Haamm.HaNaMiniAnalyzer.Plotter import *
plotter = Plotter()
listofdata = [GetSample(s) for s in MiniAOD80Samples if s.IsData]
dataSamples2 = SampleType("Data" , kBlack , [ listofdata[0] ]  , nTuples ) # the first item must be data
allSTs = [ dataSamples2 , TopSamples, DYSamples]
#allSTs = [ dataSamples2 , TopSamples]
#allSTs = [ dataSamples2 , DYSamples]
allSTs.extend(signalsamples)
for st in allSTs :
    plotter.AddSampleType( st )
    for s in st.Samples:
        if s.IsData :
            continue
        if s.Name in nTotals :
            s.SetNTotal( nTotals[s.Name] )
        else:
            print "total number for sample %s is not set" % s.Name

amuPx = "muPt[0]*cos(muPhi[0])+muPt[1]*cos(muPhi[1])"
amuPy = "muPt[0]*sin(muPhi[0])+muPt[1]*sin(muPhi[1])"
amuPz = "muPt[0]*sinh(muEta[0])+muPt[1]*sinh(muEta[1])"
amuEn = "sqrt(pow(muPt[0]*cos(muPhi[0]),2)+pow(muPt[0]*sin(muPhi[0]),2)+pow(muPt[0]*sinh(muEta[0]),2))+sqrt(pow(muPt[1]*cos(muPhi[1]),2)+pow(muPt[1]*sin(muPhi[1]),2)+pow(muPt[1]*sinh(muEta[1]),2))"

amuMass = "sqrt(pow("+amuPx+",2) + pow("+amuPy+",2) + pow("+amuPz+",2) - pow("+amuEn+",2))"


#masscut =  "sqrt(pow(muPt[0]*cos(muPhi[0])+muPt[1]*cos(muPhi[1]),2)+pow(muPt[0]*sin(muPhi[0])+muPt[1]*sin(muPhi[1]),2)+pow(muPt[0]*sinh(muEta[0])+muPt[1]*sinh(muEta[1]),2)-pow(sqrt(pow(muPt[0]*cos(muPhi[0]),2)+pow(muPt[0]*sin(muPhi[0]),2)+pow(muPt[0]*sinh(muEta[0]),2))+sqrt(pow(muPt[1]*cos(muPhi[1]),2)+pow(muPt[1]*sin(muPhi[1]),2)+pow(muPt[1]*sinh(muEta[1]),2)),2)) < 70 && sqrt(pow(muPt[0]*cos(muPhi[0])+muPt[1]*cos(muPhi[1]),2)+pow(muPt[0]*sin(muPhi[0])+muPt[1]*sin(muPhi[1]),2)+pow(muPt[0]*sinh(muEta[0])+muPt[1]*sinh(muEta[1]),2)-pow(sqrt(pow(muPt[0]*cos(muPhi[0]),2)+pow(muPt[0]*sin(muPhi[0]),2)+pow(muPt[0]*sinh(muEta[0]),2))+sqrt(pow(muPt[1]*cos(muPhi[1]),2)+pow(muPt[1]*sin(muPhi[1]),2)+pow(muPt[1]*sinh(muEta[1]),2)),2)) > 15"

masscut = amuMass+" < 70 && "+amuMass+" > 15"
mupt = masscut+" && muPt[0]>24 && muPt[1]>10"
jetpt = mupt + "&& jetsPt[0]>20 && jetsPt[1]>15"
metSig = jetpt+" && metSig < 2"
trueb = metSig + " && fabs(jetsFlavour[0]) == 5 && fabs(jetsFlavour[1]) == 5"


Cuts = {"MassRange":masscut,
	    "MuPt":mupt,
	    "JetPt": jetpt,
	    "MetSig": metSig,
	    "TrueB": trueb
	    }
        

cPresel = CutInfo( "PreSelection" , Cuts["MassRange"])
cMuPt = CutInfo( "MuPt" , Cuts["MuPt"])
cJetPt = CutInfo( "JetPt" , Cuts["JetPt"])
cMetSig = CutInfo( "MetSig" , Cuts["MetSig"])
cTrueB = CutInfo( "TrueB" , Cuts["TrueB"])



#cPresel.AddHist( "LeadMuonPt" , "muPt[0]", 40 , 0. , 200. )
cMetSig.AddHist( "LeadJetBTag" , "jetsBtag[0]", 100 , 0. , 1. )
cMetSig.AddHist( "SubLeadJetBTag" , "jetsBtag[1]", 100 , 0. , 1. )
#cTrueB.AddHist( "LeadJetBTag" , "jetsBtag[0]", 100 , 0. , 1. )
#cTrueB.AddHist( "SubLeadJetBTag" , "jetsBtag[1]", 100 , 0. , 1. )


plotter.AddTreePlots( cMetSig )
#plotter.AddTreePlots( cTrueB )

# cNonIsoMu = CutInfo("nonIsoMu" , Cuts["DiMu"] + " && " + Cuts["nonIsoMu"] , "Weight.W%d * G1.w * G2.w" )
# for h in cDiMu.ListOfHists:
#     cNonIsoMu.AddHist( h )
# plotter.AddTreePlots( cNonIsoMu )

plotter.LoadHistos( 12900 )

plotter.CalcSignificances(2)
plotter.CalcSignificances(3)
plotter.CalcSignificances(4)
plotter.CalcExpLimits()
#plotter.AddLabels( "CutFlowTable" , ["All" , "HLT" , "Vertex" , ">1Pair" , "LeadingPass" , "SubLeadingPass" , "PairCuts" ] )

fout = TFile.Open("out_btag_ttdy.root", "recreate")
plotter.Write(fout, False)
fout.Close()
