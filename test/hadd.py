#!/usr/bin/env python
from ROOT import gROOT
gROOT.SetBatch(True)

from Samples80.Samples import *
samples = None
runOnOutsOfAnotherJob = False
if runOnOutsOfAnotherJob :
    samples = samples24june
    samples += sampleswith24juneonly
else :
    samples = MiniAOD80Samples

for sample in samples:
    #if sample.Name in [s.Name for s in sampleswith24juneonly]:
        #job is already created : sample.MakeJobs( 20 , "%s/%s" % (OutPath24June , prefix) )
    #    print sample.Name 
    #else:
    sample.MakeJobs( 5 , "eos/cms/store/user/%s/%s/%s" % (GetUserName(), "Oct5_8020_v2" , "out" ) ) 

from Haamm.HaNaMiniAnalyzer.ExtendedSample import *
for sample in samples:
    #if sample.Name in ["QCDDoubleEM76_m4080_pt30"] : #["TTbar_FGG"]
    #    print "skipping " + sample.Name
    #    continue
    ss = ExtendedSample(sample)
    #export EOS_MGM_URL=root://eosuser.cern.ch
    #eosmount eos_cb
    ss.fhadd("eos_cb/user/a/ajafari/Hamb13/Oct5_8020_v2/Trees/")
