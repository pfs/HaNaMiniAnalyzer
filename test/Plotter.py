from Samples76.Samples import MiniAOD76Samples as samples
from Haamm.HaNaMiniAnalyzer.Plotter import *
import getpass
prefix = "out"
user = getpass.getuser()
import sys
from os.path import isfile, join, splitext, basename

from ROOT import TFile, TDirectory

f = TFile.Open("eos/cms/store/user/hbakhshi/Test/out_DYJets_6CA8797D-86CC-E511-B1A4-0CC47A78A3EC.root")
dir  = f.GetDirectory("HaNaAnalyzer/CutFlowTable/")
print dir.GetName()
hcft = Histogram( samples , dir )
hcftToShow = Histogram( samples , dir )
OutPath = "eos/cms/store/user/%s/%s/" % (user, sys.argv[1] )
for sample in samples:
    for fi in sample.Files :
        finame = splitext( basename( fi ))[0] + ".root"
        outfile = join( OutPath , prefix + "_" + sample.Name + "_" + finame )
        if outfile=="out_DYJets_6CA8797D-86CC-E511-B1A4-0CC47A78A3EC.root":
            continue

        ff = TFile.Open(outfile)
        dir  = ff.GetDirectory("HaNaAnalyzer/CutFlowTable/")
        hcft.AddFile( dir )
        hcftToShow.AddFile( dir )
        ff.Close()


hcftToShow.Draw( 2.2 , hcft )

fout = TFile.Open("out.root", "recreate")
hcft.Write(fout)
fout.Close()
