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
  

            
LL = "(higgsReg.b1Index >= 0 ? jetsBtag[higgsReg.b1Index] > 0.460 : 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.460 : 0)"
ML = "((higgsReg.b1Index >= 0 ? jetsBtag[higgsReg.b1Index] > 0.800 : 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.460: 0)) | ((higgsReg.b1Index >=0 ? jetsBtag[higgsReg.b1Index] > 0.460: 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.800: 0))"
TL = "((higgsReg.b1Index >= 0 ? jetsBtag[higgsReg.b1Index] > 0.935 : 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.460: 0)) | ((higgsReg.b1Index >=0 ? jetsBtag[higgsReg.b1Index] > 0.460: 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.935: 0))"
MM = "((higgsReg.b1Index >= 0 ? jetsBtag[higgsReg.b1Index] > 0.800 : 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.800: 0)) | ((higgsReg.b1Index >=0 ? jetsBtag[higgsReg.b1Index] > 0.800: 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.800: 0))"
TM = "((higgsReg.b1Index >= 0 ? jetsBtag[higgsReg.b1Index] > 0.935 : 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.800: 0)) | ((higgsReg.b1Index >=0 ? jetsBtag[higgsReg.b1Index] > 0.800: 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.935: 0))"
TT = "((higgsReg.b1Index >= 0 ? jetsBtag[higgsReg.b1Index] > 0.935 : 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.935: 0)) | ((higgsReg.b1Index >=0 ? jetsBtag[higgsReg.b1Index] > 0.935: 0) && (higgsReg.b2Index >=0 ? jetsBtag[higgsReg.b2Index] > 0.935: 0))"         


mHcut = "abs(higgs.mass - 125) < 25"
width = "0.18 + (0.175* aMu.mass)"
chi2B = "pow((abjet.mass-aMu.mass),2)/pow(%s,2) < 5" %(width)
chi2H = "pow((higgs.mass-125),2)/pow(10.56,2) < 5"
chi2Sum = "(pow((abjet.mass-aMu.mass),2)/pow(%s,2)+pow((higgs.mass-125),2)/pow(10.56,2)) < 20" %(width)


Cuts = {"Trigger":"",
		"MuPt":"muPt[0]>25 && muPt[1]>10",
		"JetPt": "muPt[0]>25 && muPt[1]>10" + " && jetsPt[0]>20 && jetsPt[0]>15",
		#"MetSig":"metSig < 2",
		"OptimCuts":"jetsPt[0]>20 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2",
		"JetPt25":"jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2",
		"MET":"jetsPt[0]>20 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30",
		"METJet25":"jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30",
		"Chi2B":"jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(chi2B), 
		"Chi2H":"jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(chi2H),
		"Chi2Sum":"jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(chi2Sum),
		"LL" : "%s && jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(LL, chi2Sum),
		"ML" : "%s && jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(ML, chi2Sum),
		"TL" : "%s && jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(TL, chi2Sum),
		"MM" : "%s && jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(MM, chi2Sum),
		"TM" : "%s && jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(TM, chi2Sum),
		"TT" : "%s && jetsPt[0]>25 && jetsPt[1]>15 && muPt[0]>25 && muPt[1]>10 && metSig < 2 && met < 30 && %s" %(TT, chi2Sum),		
}

dphi_ = "abs(abjetReg.phi - aMu.phi)"
dphi = (dphi_ + ">= 3.14 ? 6.28 - "+ dphi_ + ": "+ dphi_) 
deta = "abs(abjetReg.eta - aMu.eta)"
DR = "sqrt(pow(%s,2) + pow(%s,2))" % (dphi , deta)

lb0Px = "muPt[0]*cos(muPhi[0])+jetsPt[0]*cos(jetsPhi[0])"
lb0Py = "muPt[0]*sin(muPhi[0])+jetsPt[0]*sin(jetsPhi[0])"
lb0Pz = "muPt[0]*sinh(muEta[0])+jetsPt[0]*sinh(jetsEta[0])"
mu0En = "sqrt((muPt[0]*muPt[0]) + (%s * %s))" %(lb0Pz,lb0Pz)
lb0En = "jetsE[0] + %s" %(mu0En)
lb0M = "sqrt(pow(%s,2)+pow(%s,2)+pow(%s,2)-pow(%s,2))" %(lb0Px, lb0Py, lb0Pz, lb0En)

lb1Px = "muPt[0]*cos(muPhi[0])+jetsPt[1]*cos(jetsPhi[1])"
lb1Py = "muPt[0]*sin(muPhi[0])+jetsPt[1]*sin(jetsPhi[1])"
lb1Pz = "muPt[0]*sinh(muEta[0])+jetsPt[1]*sinh(jetsEta[1])"
mu1En = "sqrt((muPt[0]*muPt[0]) + (%s * %s))" %(lb1Pz,lb1Pz)
lb1En = "jetsE[1] + %s" %(mu1En)
lb1M = "sqrt(pow(%s,2)+pow(%s,2)+pow(%s,2)-pow(%s,2))" %(lb1Px, lb1Py, lb1Pz, lb1En)

lb2Px = "muPt[1]*cos(muPhi[1])+jetsPt[0]*cos(jetsPhi[0])"
lb2Py = "muPt[1]*sin(muPhi[1])+jetsPt[0]*sin(jetsPhi[0])"
lb2Pz = "muPt[1]*sinh(muEta[1])+jetsPt[0]*sinh(jetsEta[0])"
mu2En = "sqrt((muPt[1]*muPt[1]) + (%s * %s))" %(lb2Pz,lb2Pz)
lb2En = "jetsE[0] + %s" %(mu2En)
lb2M = "sqrt(pow(%s,2)+pow(%s,2)+pow(%s,2)-pow(%s,2))" %(lb2Px, lb2Py, lb2Pz, lb2En)

lb3Px = "muPt[1]*cos(muPhi[1])+jetsPt[1]*cos(jetsPhi[1])"
lb3Py = "muPt[1]*sin(muPhi[1])+jetsPt[1]*sin(jetsPhi[1])"
lb3Pz = "muPt[1]*sinh(muEta[1])+jetsPt[1]*sinh(jetsEta[1])"
mu3En = "sqrt((muPt[1]*muPt[1]) + (%s * %s))" %(lb3Pz,lb3Pz)
lb3En = "jetsE[1] + %s" %(mu3En)
lb3M = "sqrt(pow(%s,2)+pow(%s,2)+pow(%s,2)-pow(%s,2))" %(lb3Px, lb3Py, lb3Pz, lb3En)

cDiMu = CutInfo( "Trigger" , Cuts["Trigger"],"bWs.W2L*Weight",False)
cDiMu.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)
cDiMu.AddHist( "DR" , DR, 50 , 0 , 5)

cMetSig = CutInfo( "MuPt" , Cuts["MuPt"],"bWs.W2L*Weight",False)
cMetSig.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cJetPt = CutInfo( "JetPt" , Cuts["JetPt"],"bWs.W2L*Weight",False)
cJetPt.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cOptimCuts = CutInfo( "OptimCuts" , Cuts["OptimCuts"],"bWs.W2L*Weight",False)
cOptimCuts.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)
cOptimCuts.AddHist( "DR" , DR, 10 , 0 , 5)
cOptimCuts.AddHist( "DMass" , "abs(aMu.mass-abjet.mass)", 50 , 0 , 100)
cOptimCuts.AddHist( "Dphi" , dphi, 8 , 0 , 4)
cOptimCuts.AddHist( "Deta" , deta, 10 , 0 , 5)
cOptimCuts.AddHist( "hPtReg" , "higgsReg.pt", 50 , 0 , 500)
cOptimCuts.AddHist( "hPt" , "higgs.pt", 50 , 0 , 500)
cOptimCuts.AddHist( "hMassReg" , "higgsReg.mass", 30 , 0 , 300)
cOptimCuts.AddHist( "hMass" , "higgs.mass", 30 , 0 , 300)
cOptimCuts.AddHist( "LeadmuLeadbMass" ,lb0M , 30 , 0 , 300)
cOptimCuts.AddHist( "LeadmuSubleadbMass" ,lb1M , 30 , 0 , 300)
cOptimCuts.AddHist( "SubmuLeadbMass" ,lb2M , 30 , 0 , 300)
cOptimCuts.AddHist( "SubmuSubleadbMass" ,lb3M , 30 , 0 , 300)
cOptimCuts.AddHist( "Chi2B", "pow((abjet.mass-aMu.mass),2)/pow(%s,2)" %(width), 50, 0, 50)
cOptimCuts.AddHist( "Chi2H", "pow((higgs.mass-125),2)/pow(10.56,2)", 50, 0, 50)
cOptimCuts.AddHist( "Chi2Sum", "pow((higgs.mass-125),2)/pow(10.56,2) + pow((abjet.mass-aMu.mass),2)/pow(%s,2)" %(width), 50, 0, 50)
cJetPt25 = CutInfo( "JetPt25" , Cuts["JetPt25"],"bWs.W2L*Weight",False)
cJetPt25.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cMET = CutInfo( "MET" , Cuts["MET"],"bWs.W2L*Weight",False)
cMET.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cMETJet25 = CutInfo( "METJet25" , Cuts["METJet25"],"bWs.W2L*Weight",False)
cMETJet25.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cLL = CutInfo( "LL" , Cuts["LL"],"bWs.W2L*Weight",False)
cLL.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cML = CutInfo( "ML" , Cuts["ML"],"bWs.W1L1M*Weight",False)
cML.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cTL = CutInfo( "TL" , Cuts["TL"],"bWs.W1L1T*Weight",False)
cTL.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cMM = CutInfo( "MM" , Cuts["MM"],"bWs.W2L*Weight",False)
cMM.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cTM = CutInfo( "TM" , Cuts["TM"],"bWs.W1M1T*Weight",False)
cTM.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cTT = CutInfo( "TT" , Cuts["TT"],"bWs.W2T*Weight",False)
cTT.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cChi2B = CutInfo( "Chi2B" , Cuts["Chi2B"],"bWs.W2T*Weight",False)
cChi2B.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cChi2H = CutInfo( "Chi2H" , Cuts["Chi2H"],"bWs.W2T*Weight",False)
cChi2H.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

cChi2Sum = CutInfo( "Chi2Sum" , Cuts["Chi2Sum"],"bWs.W2T*Weight",False)
cChi2Sum.AddHist( "aMuMass" , "aMu.mass", 55 , 15 , 70)

plotter.AddTreePlots( cDiMu )
plotter.AddTreePlots( cMetSig )
plotter.AddTreePlots( cJetPt )
plotter.AddTreePlots( cOptimCuts )
plotter.AddTreePlots( cJetPt25 )
plotter.AddTreePlots( cMET )
plotter.AddTreePlots( cMETJet25 )

plotter.AddTreePlots( cLL )
plotter.AddTreePlots( cML )
plotter.AddTreePlots( cTL )
plotter.AddTreePlots( cMM )
plotter.AddTreePlots( cTM )
plotter.AddTreePlots( cTT )
plotter.AddTreePlots( cChi2B )
plotter.AddTreePlots( cChi2H )
plotter.AddTreePlots( cChi2Sum )
#plotter.AddTreePlots( cSignalCount )

# cNonIsoMu = CutInfo("nonIsoMu" , Cuts["DiMu"] + " && " + Cuts["nonIsoMu"] , "Weight.W%d * G1.w * G2.w" )
# for h in cDiMu.ListOfHists:
#     cNonIsoMu.AddHist( h )
# plotter.AddTreePlots( cNonIsoMu )

plotter.LoadHistos( 12900 )

#plotter.AddLabels( "CutFlowTable" , ["All" , "HLT" , "Vertex" , ">1Pair" , "LeadingPass" , "SubLeadingPass" , "PairCuts" ] )

fout = TFile.Open("out_cft_normtolumi_unblind_checkYields.root", "recreate")
plotter.Write(fout, False)
fout.Close()
