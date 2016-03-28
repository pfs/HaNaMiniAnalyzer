#!/usr/bin/env python
nFilesPerJob=10
import sys
import getpass
user = getpass.getuser()
if not len(sys.argv) == 3 :
    print "exactly two options are needed : "
    print "%s [working dir] [output dir on eos]" % (sys.argv[0])
    exit()

prefix = "out"
OutPath = "eos/cms/store/user/%s/%s/" % (user, sys.argv[2] )

from Samples76.Samples import MiniAOD76Samples as samples
for sample in samples:
    sample.MakeJobs( nFilesPerJob , "%s/%s" % (OutPath , prefix) )

import os
from shutil import copy

workingdir = sys.argv[1]
while os.path.isdir( "./%s" % (workingdir) ):
    workingdir += "_"
os.mkdir( workingdir )

copy( "SetupAndRun.sh" , "./%s/" % (workingdir) )

from subprocess import call
call(["voms-proxy-init" , "--out" , "./%s/.x509up_u%d" % ( workingdir , os.getuid()) , "--voms" , "cms" , "--valid" , "1000:0"])

file = open("%s/Submit.cmd" % (workingdir) , "w" )

print >> file, "Universe                = vanilla"
print >> file, "Environment             = CONDORJOBID=$(Process)"
print >> file, "notification            = Error"
print >> file, "requirements            = (CMSFARM=?=True)&&(Memory > 200)"
print >> file, "should_transfer_files   = YES"
print >> file, "when_to_transfer_output = ON_EXIT"
print >> file, "Executable              = ./SetupAndRun.sh"
print >> file, ""

for sample in samples:
    print >> file, "output                  = %s$(Process).out" % (sample.Name)
    print >> file, "error                   = %s$(Process).err" % (sample.Name)
    print >> file, "log                     = /dev/null"
    print >> file, "Arguments               = %(vomsaddress)s %(scram)s %(cmsver)s %(gitco)s %(sample)s %(out)s %(outdir)s %(nFilesPerJob)d" % { 
        "vomsaddress":"%s/%s/.x509up_u%d" % (os.getcwd() , workingdir , os.getuid()) ,
        "scram":os.getenv("SCRAM_ARCH") ,
        "cmsver":os.getenv("CMSSW_VERSION"),
        "gitco":"master" ,
        "sample":sample.Name ,
        "out":prefix,
        "outdir":OutPath,
        "nFilesPerJob":nFilesPerJob
        }

    print >> file, "Queue %d" % (len(sample.Jobs))

    print >> file, ""

file.close()
print "to submit the jobs, you have to run the following commands :"
print "cd %s" % (workingdir)
print "condor_submit Submit.cmd"


