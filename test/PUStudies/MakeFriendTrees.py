#!/usr/bin/env python

from Haamm.HaNaMiniAnalyzer.ExtendedSample import *
from ROOT import TSystem, gSystem, gROOT, TCanvas, TH1D, TDirectory, gDirectory, TFile, TH1
import sys
import array
sys.path.append('../')

prefix = "tree"
nTuples = "/eos/user/h/hbakhshi/Personal/Projects/PU/02MarchPPD/"


fMC_In_SampleName = "ZmuMu"
fMCName_In = nTuples + fMC_In_SampleName + ".root"
fMC_In = TFile.Open( fMCName_In )
hMCName_In = "PUAnalyzer/nTruInteractions/nTruInteractions_" + fMC_In_SampleName
gROOT.cd()
hMC_In = fMC_In.Get( hMCName_In ).Clone()
fMC_In.Close()
hMC_In.Scale( 1.0 / hMC_In.Integral() )

xsec_variations={"nominal" , "up" , "down"}
json_files={"bestFit" , "latest"}
DataFiles = {}
for xsec in xsec_variations:
    for json in json_files:
        fdata = TFile.Open( "./data_%s_%s.root" % (json , xsec) )
        hdata = fdata.Get("pileup")
        hdata.Scale( 1.0 / hdata.Integral() )
        hdata.Divide( hMC_In )
        gROOT.cd()
        DataFiles[ "%s_%s" % (json , xsec) ] = hdata.Clone()
        fdata.Close()
        

from SamplesPU.Samples import *
for s in MINIAOD:
    if s.IsData: # not s.IsData: #not s.Name == "ttH"
        print "Skipping sample %s" % s.Name
        continue
    else:
        print s.Name

    es = ExtendedSample( s )
    es.LoadJobs( nTuples )
    es.LoadTree("PUAnalyzer/Trees/Events")

    vals_template = []
    leaves = ""
    for df in DataFiles:
        for oot in ["it", "oot"]:
            if not leaves == "" :
                leaves += ":"
            leaves += ("%s_%s" % (df, oot))
            vals_template.append( 0.0 )

    leafValues = array.array("f", vals_template )

    fNew = TFile( s.Name + ".root" , "recreate" )
    friendT = TTree("friend", "friend")

    friendT.Branch( "PUWeights"  , leafValues , leaves)
    
    for event in es.Tree:
        nInt = ord(event.nInt)
        print nInt
        nInt50ns = ord(event.nInt50ns)
        #print nInt
        #print nInt50ns
        counter = 0
        for df in DataFiles:
            wIn = 0.0
            wOut = 0.0
            if nInt >= 0:
                bin = DataFiles[df].FindBin( nInt )
                wIn = DataFiles[df].GetBinContent( bin )
                if nInt50ns >=0 :
                    wOut = wIn
                
            leafValues[counter] = wIn
            counter += 1
            leafValues[counter] = wOut
            counter += 1

        print leafValues
        friendT.Fill()

    friendT.Write()
    fNew.Close()
