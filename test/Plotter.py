#!/usr/bin/env python
############MAKE SAMPLE LIST : ###################

LUMI = 35.5

import os
import os.path
import math
import sys
import glob
from Haamm.HaNaMiniAnalyzer.Sample import *
from Haamm.HaNaMiniAnalyzer.SampleType import *
Sample.WD = os.path.dirname(os.path.abspath(__file__))
from ROOT import kGray, kGreen, kYellow, kOrange, kRed, kBlack, kCyan, kBlue, gROOT, TLatex, TCanvas, TFile, TColor, TSystem


puScenario=sys.argv[1]
era=sys.argv[2]
xsecvar=os.getenv( "LSB_JOBINDEX" , sys.argv[3] )


TreeTemN = "PUAnalyzer/Trees/Events"
DIR = "/home/hbakhshi/Downloads/CERNBox/Personal/Projects/PU/02MarchPPD/"
data_files = [ "%s%s" % (DIR,s) for s in [ #"SingleMuB1.root",
                                           "SingleMuB2.root",
                                           "SingleMuC.root",
                                           "SingleMuD.root",
                                           "SingleMuE.root",
                                           "SingleMuF.root",
                                           "SingleMuG.root",
                                           "SingleMuH2.root",
                                           "SingleMuH3.root"]]

dataSamples = SampleType("Data" , kBlack , [ Sample( os.path.basename(s).split('.')[0] , 0 , False , "" , treeName = TreeTemN  ) for s in data_files ] , DIR )

zmumu = SampleType("ZMuMu" , kCyan , [ Sample( "ZmuMu" , -1 , False , "", treeName=TreeTemN ) ] , DIR )
for s in zmumu.Samples:
    s.SetFriendTreeInfo( DIR + "weights3" , "friend" )

allSTs = [ dataSamples , zmumu ]


###############  SAMPLE LIST CREATED #############

outfname = ""
normtodata = True



if len(sys.argv) < 2:
    raise RuntimeError("at least one parameter has to be given")

appendix = puScenario+"_"+era+"_"+xsecvar
#appendix = sys.argv[1]
outfname = "out_%s_normtolumi.root" % appendix

gROOT.SetBatch(True)

from Haamm.HaNaMiniAnalyzer.Plotter import *            
plotter = Plotter()
plotter.AddSampleType (zmumu )
if era == "All" :
    plotter.AddSampleType( dataSamples )
elif era == "eraB":
    samples = []
    for s in dataSamples.Samples:
        if "B" in s.Name :
            samples.append( s )
    plotter.AddSampleType( SampleType("Data" , kBlack , samples , DIR ) )
elif era == "eraC":
    plotter.AddSampleType( SampleType("Data" , kBlack , [ Sample( os.path.basename(s).split('.')[0] , 0 , False , "" , treeName = TreeTemN  ) for s in data_files if "C" in s ] , DIR ) )
elif era == "eraD":
    plotter.AddSampleType( SampleType("Data" , kBlack , [ Sample( os.path.basename(s).split('.')[0] , 0 , False , "" , treeName = TreeTemN  ) for s in data_files if "D" in s ] , DIR ) )
elif era == "eraE":
    plotter.AddSampleType( SampleType("Data" , kBlack , [ Sample( os.path.basename(s).split('.')[0] , 0 , False , "" , treeName = TreeTemN  ) for s in data_files if "E" in s ] , DIR ) )
elif era == "eraF":
    plotter.AddSampleType( SampleType("Data" , kBlack , [ Sample( os.path.basename(s).split('.')[0] , 0 , False , "" , treeName = TreeTemN  ) for s in data_files if "F" in s ] , DIR ) )
elif era == "eraG":
    plotter.AddSampleType( SampleType("Data" , kBlack , [ Sample( os.path.basename(s).split('.')[0] , 0 , False , "" , treeName = TreeTemN  ) for s in data_files if "G" in s ] , DIR ) )
elif era == "eraH":
    plotter.AddSampleType( SampleType("Data" , kBlack , [ Sample( os.path.basename(s).split('.')[0] , 0 , False , "" , treeName = TreeTemN  ) for s in data_files if "H" in s ] , DIR ) )

# for st in allSTs :
#     plotter.AddSampleType( st )
# data_ranges = {}
# allPlotters = {"All":plotter}
# for ss in data_files:
#     dddname =  os.path.basename(ss[0:-5])
#     print dddname
#     s = None
#     for s1 in dataSamples.Samples:
#         if s1.Name == dddname:
#             s = s1
#     if not s:
#         print dddname, " not found"
#         continue
#     #[ Sample.Sample( os.path.basename(ss).split('.')[0] , 0 , False , "" , treeName = TreeTemN  )  ] 
#     data_ranges.setdefault( dddname , SampleType(dddname , kBlack , [s] , DIR )  )
#     allPlotters[ dddname ] = Plotter()
#     allPlotters[ dddname ].AddSampleType( data_ranges[ dddname ] )
#     allPlotters[ dddname ].AddSampleType( zmumu )

# weights = {}
# for xsec in ["nominal" , "up" , "down"]:
#     for json in ["bestFit" , "latest" , "pcc"]:
#         for oot in ["it"]:
#             weights["%s_%s" % ( json , xsec)]=  "PUWeights.%s_%s_%s" % ( json , xsec, oot)
# for w in weights:
#     print weights[w]
#     for pl in allPlotters:
#         c = CutInfo( pl + "_" + w , cut ,  weights[w] )
#         c.AddHist( "nVertices" , "nVertices", 60 , 0. , 60. , "#vertices" )
#         c.AddHist( "Rho" , "Rho", 60 , 0. , 60. , "#rho" )
#         c.AddHist( "nChargedParticles" , "nEles+nMus+nChargedHadrons+nLostTracks", 125 , 0 , 2500.  , "#tracks" )
#         allCuts.append( c )
#         allPlotters[pl].AddTreePlots( c )
    
Cuts = {"InvMass":"abs(InvMass-91.) < 15 ",
        "tight":"passDiMuTight" , 
        "iso":"reliso1 < 0.15 && reliso2 < 0.15"}

name = "%s_%s_%s" % (puScenario , xsecvar , era)   
cut =  "&&".join( [ Cuts[s] for s in [ "InvMass" ] ])
c = CutInfo( name , cut ,  "PUWeights."+name )
c.AddHist( "nVertices" , "nVertices", 50 , 0. , 50. , "#vertices" )
c.AddHist( "Rho" , "Rho", 50 , 0. , 50. , "#rho" )
c.AddHist( "nChargedParticles" , "nEles+nMus+nChargedHadrons+nLostTracks", 60 , 0 , 1200.  , "#tracks" )
c.AddHist( "InvMass" , "InvMass", 14 , 70 , 112  , "InvMass" )
plotter.AddTreePlots( c )

fout = TFile.Open( outfname , "recreate")

plotter.LoadHistos( LUMI  , "PUAnalyzer/" )
dir = fout.mkdir( name )
plotter.Write(dir, normtodata)

    
fout.Close()

