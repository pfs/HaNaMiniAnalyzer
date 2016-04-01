#!/usr/bin/env python
nFilesPerJob=10
prefix = "out"
import sys
user=""
if len(sys.argv) > 2 :
    user = sys.argv[2]
else:
    import getpass
    user = getpass.getuser()
OutPath = "eos/cms/store/user/%s/%s/" % (user, sys.argv[1] )

from ROOT import TFile, TDirectory
from Samples76.Samples import MiniAOD76Samples as samples
for sample in samples:
    sample.MakeJobs( nFilesPerJob , "%s/%s" % (OutPath , prefix) )

f = TFile.Open(samples[0].Jobs[0].Output)

from Haamm.HaNaMiniAnalyzer.Plotter import *
dir  = f.GetDirectory("HaNaAnalyzer/CutFlowTable/")
print dir.GetName()


hcft = Histogram( samples , f.GetDirectory("HaNaAnalyzer/CutFlowTable/") )
hcftToShow = Histogram( samples , f.GetDirectory("HaNaAnalyzer/CutFlowTable/") )

f.Close()

for sample in samples:
    print sample.Name + " : "
    for Job in sample.Jobs :
        finame = Job.Output
        sys.stdout.write("\r%d of %d" % (Job.Index , len(sample.Jobs)))
        sys.stdout.flush()
        ff = TFile.Open(finame)
        dir  = ff.GetDirectory("HaNaAnalyzer/CutFlowTable/")
        hcft.AddFile( dir )
        hcftToShow.AddFile( dir )
        ff.Close()


hcftToShow.Draw( 2.2 , hcft )

fout = TFile.Open("out.root", "recreate")
hcft.Write(fout)
fout.Close()
