source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /afs/cern.ch/user/h/hbakhshi/work/PU/CMSSW_8_0_26_patch2/src/Haamm/HaNaMiniAnalyzer/test/PUStudies
eval `scramv1 runtime -sh`



if [ ! -z "$LSB_JOBINDEX" ];
then
    echo $LSB_JOBINDEX
    export xsecvariation=`expr $LSB_JOBINDEX - 0`
    echo $xsecvariation
fi

xsec=`echo 69200 \* $xsecvariation / 1000. | bc`
echo $xsec

nBins=100

ANJSON=$1
appendixName=$2
#/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt 

function produce {
    pileupCalc.py -i $ANJSON --inputLumiJSON $1  --calcMode true --minBiasXsec $xsec --maxPileupBin $nBins --numPileupBins $nBins --pileupHistName=h_${xsecvariation} ./datapu/data_$2_${xsecvariation}_${appendixName}.root
    #echo pileupCalc.py -i $ANJSON --inputLumiJSON $1  --calcMode true --minBiasXsec $xsecDown --maxPileupBin $nBins --numPileupBins $nBins ./data_$2_${xsecvariation}_down.root
    #echo pileupCalc.py -i $ANJSON --inputLumiJSON $1  --calcMode true --minBiasXsec $xsecUp --maxPileupBin $nBins --numPileupBins $nBins ./data_$2_${xsecvariation}_up.root
}

#produce ./datacert2016ReRecoByLS_Pre3puJSON.txt pcc
#produce /eos/cms/store/user/jsalfeld/datacert2016ReRecoByLSpuJSON.txt bestFit
produce /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt latest


