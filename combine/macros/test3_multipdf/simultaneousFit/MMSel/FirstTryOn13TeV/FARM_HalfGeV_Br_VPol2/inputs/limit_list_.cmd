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

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0000_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0000_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0000_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0000_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0001_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0001_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0001_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0001_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0002_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0002_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0002_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0002_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0003_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0003_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0003_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0003_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0004_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0004_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0004_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0004_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0005_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0005_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0005_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0005_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0006_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0006_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0006_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0006_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0007_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0007_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0007_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0007_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0008_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0008_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0008_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0008_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0009_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0009_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0009_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0009_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0010_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0010_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0010_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0010_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0011_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0011_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0011_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0011_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0012_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0012_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0012_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0012_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0013_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0013_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0013_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0013_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0014_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0014_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0014_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0014_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0015_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0015_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0015_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0015_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0016_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0016_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0016_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0016_limit_list_.log
Queue 1

Executable              = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/inputs/0017_limit_list_.sh
output                  = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0017_limit_list_.out
error                   = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0017_limit_list_.err
log                     = /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FirstTryOn13TeV/FARM_HalfGeV_Br_VPol2/logs/0017_limit_list_.log
Queue 1
