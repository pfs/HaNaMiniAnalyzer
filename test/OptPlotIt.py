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


nTuples = "/home/nadjieh/cernbox/Hamb13/Oct19_8020_Opt/"
print ">>>>"
from Haamm.HaNaMiniAnalyzer.SampleType import *
from ROOT import kGray, kGreen, kOrange, kRed, kBlack, kCyan, kBlue, kAzure, kTeal, kPink, kYellow
#dataSamples = SampleType("Data" , kBlack , [GetSample(s) for s in MiniAOD80Samples if s.IsData] , nTuples ) # the first item must be data
ci = TColor.GetColor("#ff6666")
DYSamples = SampleType("DY" , ci , [ GetSample(DYJets80) , GetSample(DYJetsLowMass80)] , nTuples )
ci = TColor.GetColor("#ffff66")
TopSamples = SampleType("Top" , ci , [ GetSample(TTBar80) , GetSample(TW80), GetSample(TbarW80) ] , nTuples )
ci = TColor.GetColor("#996633")
Mass = sys.argv[3]
lowmass = "15"
highmass = "70"
signalsamples = []
if(Mass == "20"):
#signalsamples.append(SampleType( "Signal15" , kRed+3 , [ GetSample(GGH1580) ] , nTuples , True ))
	signalsamples.append(SampleType( "Signal20" , kRed+2 , [ GetSample(GGH2080) ] , nTuples , True ))
	lowmass = "15"
	highmass = "25"
elif(Mass == "25"):	
	signalsamples.append(SampleType( "Signal25" , kRed+2 , [ GetSample(GGH2580) ] , nTuples , True ))
	lowmass = "20"
	highmass = "30"
elif(Mass == "30"):	
	signalsamples.append(SampleType( "Signal30" , kRed+2 , [ GetSample(GGH3080) ] , nTuples , True ))
	lowmass = "25"
	highmass = "35"
elif(Mass == "35"):	
	signalsamples.append(SampleType( "Signal35" , kRed+2 , [ GetSample(GGH3580) ] , nTuples , True ))
	lowmass = "30"
	highmass = "40"
elif(Mass == "40"):	
	signalsamples.append(SampleType( "Signal40" , kRed+2 , [ GetSample(GGH4080) ] , nTuples , True ))
	lowmass = "35"
	highmass = "45"
elif(Mass == "45"):	
	signalsamples.append(SampleType( "Signal45" , kRed+2 , [ GetSample(GGH4580) ] , nTuples , True ))
	lowmass = "40"
	highmass = "50"
elif(Mass == "55"):	
	signalsamples.append(SampleType( "Signal55" , kRed+2 , [ GetSample(GGH5580) ] , nTuples , True ))
	lowmass = "50"
	highmass = "60"
elif(Mass == "60"):	
	signalsamples.append(SampleType( "Signal60" , kRed+2 , [ GetSample(GGH6080) ] , nTuples , True ))
	lowmass = "55"
	highmass = "65"
else:
	signalsamples.append (SampleType( "Signal15" , kAzure+10 , [ GetSample(GGH1580) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal20" , kBlue+2 , [ GetSample(GGH2080) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal25" , kCyan+2	, [ GetSample(GGH2580) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal30" , kTeal+10 , [ GetSample(GGH3080) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal35" , kGreen+2 , [ GetSample(GGH3580) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal40" , kYellow+2 , [ GetSample(GGH4080) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal45" , kOrange-2 , [ GetSample(GGH4580) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal50" , kOrange+10 , [ GetSample(GGH5080) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal55" , kRed+2 , [ GetSample(GGH5580) ] , nTuples , True ))
	signalsamples.append (SampleType( "Signal60" , kPink+10 , [ GetSample(GGH6080) ] , nTuples , True ))



nTotals = {}
            
from Haamm.HaNaMiniAnalyzer.Plotter import *
plotter = Plotter()
listofdata = [GetSample(s) for s in MiniAOD80Samples if s.IsData]
dataSamples2 = SampleType("Data" , kBlack , [ listofdata[0] ]  , nTuples ) # the first item must be data
allSTs = [ dataSamples2 , TopSamples, DYSamples]
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

amuMass = "sqrt(pow(%s,2) + pow(%s,2) + pow(%s,2) - pow(%s,2))" %(amuPx,amuPy,amuPz,amuEn)

abPx = "jetsPt[mH.b1Index]*cos(jetsPhi[mH.b1Index])+jetsPt[mH.b2Index]*cos(jetsPhi[mH.b2Index])"
abPy = "jetsPt[mH.b1Index]*sin(jetsPhi[mH.b1Index])+jetsPt[mH.b2Index]*sin(jetsPhi[mH.b2Index])"
abPz = "jetsPt[mH.b1Index]*sinh(jetsEta[mH.b1Index])+jetsPt[mH.b2Index]*sinh(jetsEta[mH.b2Index])"
abEn = "jetsE[mH.b1Index] + jetsE[mH.b2Index]"

abMass = "sqrt(pow(%s,2) + pow(%s,2) + pow(%s,2) - pow(%s,2))" %(abPx,abPy,abPz,abEn)
width = "0.18 + 0.175* %s" %(amuMass)
chi2B = "pow((%s-%s),2)/(%s*%s)" %(amuMass,abMass,width,width)
chi2H = "pow((mH.mass-125),2)/(10.56*10.56)" 
chi2Sum = "%s+%s" %(chi2B, chi2H)


masscut = "%s < %s && %s > %s" %(amuMass,highmass,amuMass,lowmass)
mupt = masscut+" && muPt[0]>24 && muPt[1]>10"
jetpt = mupt + "&& jetsPt[0]>25 && jetsPt[1]>15"
metSig = jetpt+" && metSig < 2 && met < 30"
trueb = metSig + " && abs(jetsFlavour[0]) == 5 && abs(jetsFlavour[1]) == 5"

LL =  "jetsBtag[0] > 0.460 && jetsBtag[1] > 0.460"
ML =  "(jetsBtag[0] > 0.800 && jetsBtag[1] > 0.460) | (jetsBtag[0] > 0.460 && jetsBtag[1] > 0.800)"
TL =  "(jetsBtag[0] > 0.935 && jetsBtag[1] > 0.460) | (jetsBtag[0] > 0.460 && jetsBtag[1] > 0.935)"
MM =  "(jetsBtag[0] > 0.800 && jetsBtag[1] > 0.800) | (jetsBtag[0] > 0.800 && jetsBtag[1] > 0.800)"
TM =  "(jetsBtag[0] > 0.935 && jetsBtag[1] > 0.800) | (jetsBtag[0] > 0.800 && jetsBtag[1] > 0.935)"
TT =  "(jetsBtag[0] > 0.935 && jetsBtag[1] > 0.935) | (jetsBtag[0] > 0.935 && jetsBtag[1] > 0.935)"


LLb =  "(mHb.b1Index >= 0 ? jetsBtag[mHb.b1Index] > 0.460 : 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.460 : 0)"
MLb =  "((mHb.b1Index >= 0 ? jetsBtag[mHb.b1Index] > 0.800 : 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.460: 0)) | ((mHb.b1Index >=0 ? jetsBtag[mHb.b1Index] > 0.460: 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.800: 0))"
TLb =  "((mHb.b1Index >= 0 ? jetsBtag[mHb.b1Index] > 0.935 : 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.460: 0)) | ((mHb.b1Index >=0 ? jetsBtag[mHb.b1Index] > 0.460: 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.935: 0))"
MMb =  "((mHb.b1Index >= 0 ? jetsBtag[mHb.b1Index] > 0.800 : 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.800: 0)) | ((mHb.b1Index >=0 ? jetsBtag[mHb.b1Index] > 0.800: 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.800: 0))"
TMb =  "((mHb.b1Index >= 0 ? jetsBtag[mHb.b1Index] > 0.935 : 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.800: 0)) | ((mHb.b1Index >=0 ? jetsBtag[mHb.b1Index] > 0.800: 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.935: 0))"
TTb =  "((mHb.b1Index >= 0 ? jetsBtag[mHb.b1Index] > 0.935 : 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.935: 0)) | ((mHb.b1Index >=0 ? jetsBtag[mHb.b1Index] > 0.935: 0) && (mHb.b2Index >=0 ? jetsBtag[mHb.b2Index] > 0.935: 0))"

Cuts = {"LL":LL,
	    "ML":ML,
	    "TL":TL,
	    "MM":MM,
	    "TM":TM,
	    "TT":TT,
	    "LLb":LLb,
	    "MLb":MLb,
	    "TLb":TLb,
	    "MMb":MMb,
	    "TMb":TMb,
	    "TTb":TTb,
	    "metSig":metSig,
	    }

cLL = CutInfo( "LL" , Cuts["LL"])
cML = CutInfo( "ML" , Cuts["ML"])
cTL = CutInfo( "TL" , Cuts["TL"])
cMM = CutInfo( "MM" , Cuts["MM"])
cTM = CutInfo( "TM" , Cuts["TM"])
cTT = CutInfo( "TT" , Cuts["TL"])

cLLb = CutInfo( "LLb" , Cuts["LLb"])
cMLb = CutInfo( "MLb" , Cuts["MLb"])
cTLb = CutInfo( "TLb" , Cuts["TLb"])
cMMb = CutInfo( "MMb" , Cuts["MMb"])
cTMb = CutInfo( "TMb" , Cuts["TMb"])
cTTb = CutInfo( "TTb" , Cuts["TLb"])
cMetSig = CutInfo( "metSig" , Cuts["metSig"])


cLL.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cLL.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cLL.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cLL.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cLL.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cML.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cML.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cML.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cML.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cML.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cTL.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cTL.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cTL.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cTL.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cTL.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cMM.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cMM.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cMM.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cMM.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cMM.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )


cTM.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cTM.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cTM.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cTM.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cTM.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cTT.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cTT.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cTT.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cTT.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cTT.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cLLb.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cLLb.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cLLb.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cLLb.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cLLb.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cMLb.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cMLb.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cMLb.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cMLb.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cMLb.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cTLb.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cTLb.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cTLb.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cTLb.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cTLb.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cMMb.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cMMb.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cMMb.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cMMb.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cMMb.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cTMb.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cTMb.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cTMb.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cTMb.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cTMb.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cTTb.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cTTb.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cTTb.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cTTb.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cTTb.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

cMetSig.AddHist( "HiggsMDiff" , "abs(mH.mass-125)", 20 , 0. , 100., False )
#cMetSig.AddHist( "bHiggsMDiff" , "abs(mHb.mass-125)", 20 , 0. , 100., False )
cMetSig.AddHist( "chi2B" , chi2B, 25 , 0. , 50., False )
cMetSig.AddHist( "chi2H" , chi2H, 25 , 0. , 50., False )
cMetSig.AddHist( "chi2Sum" , chi2Sum, 25 , 0. , 50., False )

import sys
method = sys.argv[1]
print "I'm going to apply %s" % (method)
cuttoapply = sys.argv[2] 
allcuts = []

allcuts.append( cLL )
allcuts.append( cML )
allcuts.append( cTL )
allcuts.append( cMM )
allcuts.append( cTM )
allcuts.append( cTT )

allcuts.append( cLLb )
allcuts.append( cMLb )
allcuts.append( cTLb )
allcuts.append( cMMb )
allcuts.append( cTMb )
allcuts.append( cTTb )
allcuts.append( cMetSig )

if method == "significance":
	for i in range(0, len(allcuts)):
		plotter.AddTreePlots( allcuts[i] )
	plotter.LoadHistos( 12900 )
	#plotter.CalcSignificances(2)
	#plotter.CalcSignificances(3)
	plotter.CalcSignificances(4)
	plotter.CalcSignificances(5)
elif method == "limit":
	for i in range(0, len(allcuts)):
		if cuttoapply == allcuts[i].Name :
			plotter.AddTreePlots( allcuts[i] )
			plotter.LoadHistos( 12900 )
			break
	plotter.CalcExpLimits()
else:
	print "not implemented"
	exit()

fout = TFile.Open("out_mH_ttdy_%s_%s_%s.root" %(method,cuttoapply,Mass), "recreate")
plotter.Write(fout, False)
fout.Close()
