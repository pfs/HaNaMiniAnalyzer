#! /bin/sh
####################################
#        LaunchOnFarm Script       #
#     Loic.quertenmont@cern.ch     #
#            April 2010            #
####################################

export SCRAM_ARCH=slc5_amd64_gcc462
export BUILD_ARCH=slc5_amd64_gcc462
export HOME=/home/fynu/ajafari
export VO_CMS_SW_DIR=/nfs/soft/cms
source /nfs/soft/cms/cmsset_default.sh
cd /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/limitsWithPol0
eval `scramv1 runtime -sh`
cd -
/nfs/user/ajafari/work/CMSSW_7_1_5/bin/slc6_amd64_gcc481/combine -M Asymptotic /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/limitsWithPol0/hamb_shape_SigmaBr_ws.txt -m 57.5


mv higgsCombineTest.Asymptotic.mH*.root /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/limitsWithPol0/HalfGeV_SigmaBr_VPol0/HalfGeV_SigmaBr_VPol0/ 

mv limit_list_* /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/limitsWithPol0//nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/limitsWithPol0/FARM_HalfGeV_SigmaBr_VPol0/outputs/
