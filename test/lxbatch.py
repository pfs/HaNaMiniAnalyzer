#!/usr/bin/env python
import sys
import getpass
user = getpass.getuser()

if not len(sys.argv) == 3 :
    print "exactly two options are needed : "
    print "%s [working dir] [output dir on eos]" % (sys.argv[0])
    exit()

from Samples76.Samples import MiniAOD76Samples as samples
import os
from shutil import copy

workingdir = sys.argv[1]
while os.path.isdir( "./%s" % (workingdir) ):
    workingdir += "_"
os.mkdir( workingdir )

copy( "SetupAndRun.sh" , "./%s/" % (workingdir) )

from subprocess import call
call(["voms-proxy-init" , "--out" , "./%s/.x509up_u%d" % ( workingdir , os.getuid()) , "--voms" , "cms" , "--valid" , "1000:0"])

file = open("%s/submit.sh" % (workingdir) , "w" )
for sample in samples:
    initlen = len(sample.Files)
    steps = range( 0 , initlen , 1000)
    if not steps[-1] == initlen :
        steps.append( initlen )
    print "%s : %d"% ( sample.Name , initlen )
    print steps
    for i in range( 0 , len(steps)-1):
        command = 'bsub -q 1nh -J "%(sample)s%(countor)d[%(init)d-%(nfiles)d]" `pwd`/SetupAndRun.sh %(vomsaddress)s %(scram)s %(cmsver)s %(gitco)s %(sample)s %(out)s %(outdir)s' % {
            "vomsaddress":"`pwd`/.x509up_u%d" % (os.getuid()) ,
            "scram":os.getenv("SCRAM_ARCH") ,
            "cmsver":os.getenv("CMSSW_VERSION"),
            "gitco":"master" ,
            "sample":sample.Name ,
            "out":"out" ,
            "outdir":"eos/cms/store/user/%s/%s/" % (user, sys.argv[2] ),
            "nfiles":steps[i+1],
            "init":steps[i]+1,
            "countor":i
            }
        print >> file, command


file.close()
print "to submit the jobs, you have to run the following commands :"
print "cd %s" % (workingdir)
print "source submit.sh"

