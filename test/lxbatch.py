from Samples import MiniAOD76Samples as samples
import os

from subprocess import call
call(["voms-proxy-init" , "--out" , "./x509up_u%d" % (os.getuid()) , "--voms" , "cms" , "--valid" , "1000:0"])

for sample in samples:
    for f in range(0,len(sample.Files)):
        print "bsub -q 1nh ./SetupAndRun.sh %(vomsaddress)s %(scram)s %(cmsver)s %(gitco)s %(sample)s %(file)d %(out)s %(outdir)s" % { 
            "vomsaddress":"%s/x509up_u%d" % (os.getcwd() , os.getuid()) ,
            "scram":os.getenv("SCRAM_ARCH") ,
            "cmsver":os.getenv("CMSSW_VERSION"),
            "gitco":"head" ,
            "sample":sample.Name ,
            "file":f  , 
            "out":"out" ,
            "outdir":"eos/cms/store/user/hbakhshi/TestPackage/"
            }
