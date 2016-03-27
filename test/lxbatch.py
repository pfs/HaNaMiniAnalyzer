#!/usr/bin/env python
CheckFailedJobs=True
hname = "HaNaAnalyzer/CutFlowTable/CutFlowTable"
prefix = "out"

from ROOT import TFile, TH1
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
from os import listdir
from os.path import isfile, join, splitext, basename

workingdir = sys.argv[1]
while os.path.isdir( "./%s" % (workingdir) ):
    workingdir += "_"
os.mkdir( workingdir )

copy( "SetupAndRun.sh" , "./%s/" % (workingdir) )

from subprocess import call
call(["voms-proxy-init" , "--out" , "./%s/.x509up_u%d" % ( workingdir , os.getuid()) , "--voms" , "cms" , "--valid" , "1000:0"])


OutPath = "eos/cms/store/user/%s/%s/" % (user, sys.argv[2] )
FailedJobs = {}
if CheckFailedJobs:
    for sample in samples:
        counter = 0
        ListOfFailedJobs = []
        for fi in sample.Files :
            finame = splitext( basename( fi ))[0] + ".root"
            outfile = join( OutPath , prefix + "_" + sample.Name + "_" + finame )
            counter += 1

            if isfile( outfile ) :
                ff = TFile.Open(outfile)
                h = ff.Get("%s_%s"% ( hname , sample.Name) )
                if not h == None :
                    ntotal = h.GetBinContent(1)
                    if ntotal == 0:
                        if not sample.IsData : #data may be is null because of json
                            ListOfFailedJobs.append( str(counter))
                else :
                    ListOfFailedJobs.append(str( counter ))
                    #print outfile + " : Exists, without histogram"

            else :
                ListOfFailedJobs.append( str(counter))
                #print outfile + " : file doesn't exist  %d"  % (counter)

        FailedJobs[ sample.Name ] = ListOfFailedJobs
    print FailedJobs

file = open("%s/submit.sh" % (workingdir) , "w" )
for sample in samples:

    if CheckFailedJobs:
        if len(FailedJobs[ sample.Name ]) > 0:
            command = 'bsub -q 8nh -J "%(sample)s%(countor)s[%(list)s]" `pwd`/SetupAndRun.sh %(vomsaddress)s %(scram)s %(cmsver)s %(gitco)s %(sample)s %(out)s %(outdir)s' % {
                "vomsaddress":"`pwd`/.x509up_u%d" % (os.getuid()) ,
                "scram":os.getenv("SCRAM_ARCH") ,
                "cmsver":os.getenv("CMSSW_VERSION"),
                "gitco":"master" ,
                "sample":sample.Name ,
                "out":prefix ,
                "outdir":OutPath,
                "countor":"RS",
                "list":",".join( FailedJobs[sample.Name] )
                }
            print >> file, command
        

    else :
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
                "out":prefix ,
                "outdir":OutPath,
                "nfiles":steps[i+1],
                "init":steps[i]+1,
                "countor":i
                }
            print >> file, command


file.close()
print "to submit the jobs, you have to run the following commands :"
print "cd %s" % (workingdir)
print "source submit.sh"

