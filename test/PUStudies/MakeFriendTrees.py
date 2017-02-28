#!/usr/bin/env python

from Haamm.HaNaMiniAnalyzer.ExtendedSample import *
from ROOT import TSystem, gSystem, gROOT, TCanvas, TH1D, TDirectory, gDirectory, TFile, TH1
import sys
import array
import os
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

xsec_variations = [ str(i) for i in range( 84 , 118 ) ]
jsons = {"All":"/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"} 
dir="/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/"
for f in listdir(dir):
    era = f.split("_")[-1].split(".")[0]
    jsons[era] = dir+f

json_files={"bestFit" , "latest" , "pcc"}
DataFiles = {}
for xsec in xsec_variations:
    for json in json_files:
        for pujson in jsons:
            name = "%s_%s_%s" % (json , xsec , pujson)
            fdata = None
            if os.path.isfile( "./data_" + name + ".root" ):
                fdata = TFile.Open( "./data_%s.root" % (name) )
            elif os.path.isfile( "./data_" + name + "2.root" ):
                fdata = TFile.Open( "./data_%s2.root" % (name) )
            else:
                print name, "doesn't exit"
                continue
            hdata = fdata.Get("pileup")
            hdata.Scale( 1.0 / hdata.Integral() )
            hdata.Divide( hMC_In )
            gROOT.cd()
            DataFiles[ name ] = hdata.Clone(name)
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
        for oot in ["it"]:
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
        #print nInt
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
            # leafValues[counter] = wOut
            # counter += 1

        #print leafValues
        friendT.Fill()

    friendT.Write()
    fNew.Close()
