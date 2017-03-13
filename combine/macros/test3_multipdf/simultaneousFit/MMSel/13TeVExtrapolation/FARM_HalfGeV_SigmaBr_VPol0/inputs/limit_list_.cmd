####################################
#        LaunchOnFarm Script       #
#     Loic.quertenmont@cern.ch     #
#            April 2010            #
####################################

Universe                = vanilla
Environment             = CONDORJOBID=$(Process)
notification            = Error
requirements            = (CMSFARM=?=True)&&(Memory > 200)
should_transfer_files   = YES
when_to_transfer_output = ON_EXIT

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0000_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0000_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0000_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0000_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0001_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0001_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0001_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0001_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0002_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0002_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0002_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0002_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0003_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0003_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0003_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0003_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0004_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0004_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0004_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0004_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0005_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0005_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0005_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0005_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0006_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0006_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0006_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0006_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0007_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0007_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0007_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0007_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0008_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0008_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0008_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0008_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0009_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0009_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0009_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0009_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0010_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0010_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0010_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0010_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0011_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0011_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0011_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0011_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0012_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0012_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0012_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0012_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0013_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0013_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0013_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0013_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0014_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0014_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0014_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0014_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0015_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0015_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0015_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0015_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0016_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0016_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0016_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0016_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0017_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0017_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0017_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0017_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0018_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0018_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0018_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0018_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0019_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0019_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0019_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0019_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0020_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0020_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0020_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0020_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0021_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0021_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0021_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0021_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0022_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0022_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0022_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0022_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0023_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0023_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0023_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0023_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0024_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0024_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0024_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0024_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0025_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0025_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0025_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0025_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0026_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0026_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0026_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0026_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0027_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0027_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0027_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0027_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0028_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0028_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0028_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0028_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0029_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0029_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0029_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0029_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0030_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0030_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0030_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0030_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0031_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0031_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0031_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0031_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0032_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0032_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0032_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0032_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0033_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0033_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0033_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0033_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0034_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0034_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0034_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0034_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0035_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0035_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0035_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0035_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0036_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0036_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0036_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0036_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0037_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0037_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0037_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0037_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0038_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0038_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0038_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0038_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0039_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0039_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0039_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0039_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0040_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0040_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0040_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0040_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0041_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0041_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0041_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0041_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0042_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0042_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0042_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0042_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0043_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0043_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0043_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0043_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0044_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0044_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0044_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0044_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0045_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0045_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0045_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0045_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0046_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0046_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0046_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0046_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0047_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0047_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0047_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0047_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0048_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0048_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0048_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0048_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0049_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0049_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0049_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0049_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0050_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0050_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0050_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0050_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0051_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0051_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0051_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0051_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0052_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0052_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0052_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0052_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0053_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0053_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0053_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0053_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0054_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0054_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0054_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0054_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0055_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0055_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0055_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0055_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0056_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0056_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0056_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0056_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0057_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0057_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0057_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0057_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0058_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0058_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0058_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0058_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0059_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0059_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0059_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0059_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0060_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0060_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0060_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0060_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0061_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0061_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0061_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0061_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0062_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0062_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0062_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0062_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0063_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0063_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0063_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0063_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0064_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0064_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0064_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0064_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0065_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0065_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0065_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0065_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0066_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0066_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0066_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0066_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0067_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0067_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0067_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0067_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0068_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0068_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0068_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0068_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0069_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0069_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0069_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0069_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0070_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0070_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0070_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0070_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0071_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0071_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0071_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0071_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0072_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0072_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0072_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0072_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0073_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0073_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0073_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0073_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0074_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0074_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0074_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0074_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0075_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0075_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0075_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0075_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0076_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0076_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0076_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0076_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0077_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0077_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0077_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0077_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0078_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0078_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0078_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0078_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/inputs/0079_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0079_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0079_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/13TeVExtrapolation/FARM_HalfGeV_SigmaBr_VPol0/logs/0079_limit_list_.log
Queue 1
