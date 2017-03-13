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
cd /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel
eval `scramv1 runtime -sh`
cd -
/nfs/user/ajafari/work/CMSSW_7_1_5/bin/slc6_amd64_gcc481/combine -M Asymptotic /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/hamb_shape_Br_ws.txt -m 52.5


mv higgsCombineTest.Asymptotic.mH*.root /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/HalfGeV_Br_V5/HalfGeV_Br_V5/ 

mv limit_list_* /nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel//nfs/user/ajafari/work/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/macros/test3_multipdf/simultaneousFit/MMSel/FARM_HalfGeV_Br_V5/outputs/
