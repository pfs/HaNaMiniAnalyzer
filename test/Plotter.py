#!/usr/bin/env python
nFilesPerJob=15
prefix = "out"
import sys
import os
user=""
if len(sys.argv) > 2 :
    user = sys.argv[2]
else:
    import getpass
    user = getpass.getuser()
OutPath = "eos/cms/store/user/%s/%s/" % (user, sys.argv[1] )

from ROOT import TFile, TDirectory, gDirectory, gROOT
gROOT.SetBatch(True)

from Samples76.Samples import MiniAOD76Samples as samples
for sample in samples:
    sample.MakeJobs( nFilesPerJob , "%s/%s" % (OutPath , prefix) )

f = TFile.Open(samples[0].Jobs[0].Output)

from Haamm.HaNaMiniAnalyzer.Plotter import *
hcft = Histogram( samples , f.GetDirectory("Hamb/CutFlowTable/") )

f.cd("Hamb")
AllProps = {}
for dir in gDirectory.GetListOfKeys() :
    if dir.IsFolder() and dir.GetName() == "CutFlowTable":
        AllProps[ dir.GetName() ] = Histogram( samples , f.GetDirectory("Hamb/%s/" % (dir.GetName() )) )

f.Close()

for sample in samples:
    for Job in sample.Jobs :
        finame = Job.Output
        sys.stdout.write("\r%s : %d of %d" % (sample.Name , Job.Index , len(sample.Jobs)))
        sys.stdout.flush()
        ff = None
        if os.path.isfile( finame ):
            ff = TFile.Open(finame)
        else:
            print "File %d of sample %s doesn't exist, skip it" % (Job.Index , sample.Name)
            continue
        dir = ff.GetDirectory("Hamb/")
        hcft.AddFile( dir )
        for prop in AllProps:
            AllProps[prop].AddFile(dir) 
        ff.Close()
    print " "




for prop in AllProps:
    AllProps[prop].Draw( 2200 , hcft )

fout = TFile.Open("out.root", "recreate")

for prop in AllProps:
    AllProps[prop].Write(fout)

fout.Close()
