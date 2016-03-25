from Samples import MiniAOD76Samples as samples
import os

for sample in samples:
    for f in range(0,len(sample.Files)):
        print "bsub -q 1nh ./run.sh %s %s %d %s" % ( os.getcwd() , sample.Name , f  , "out" )
