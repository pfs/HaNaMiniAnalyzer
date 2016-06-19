from Haamm.HaNaMiniAnalyzer.Sample import *
from ROOT import kGray, kGreen, kOrange, kRed, kBlack, kCyan

import os
Sample.WD = os.path.dirname(os.path.abspath(__file__))
print Sample.WD

MiniAOD76Samples = []



TtZ76 = Sample( "TtZ" , "ttZ" , 0.2529 , False ,kGreen-2 , "/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM" )
MiniAOD76Samples.append( TtZ76 )



