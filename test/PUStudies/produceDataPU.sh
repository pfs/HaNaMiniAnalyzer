xsec=69200
xsecDown=62453
xsecUp=69027

nBins=100

ANJSON=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt 

function produce {
    pileupCalc.py -i $ANJSON --inputLumiJSON $1  --calcMode true --minBiasXsec $xsec --maxPileupBin $nBins --numPileupBins $nBins ./data_$2_nominal.root
    pileupCalc.py -i $ANJSON --inputLumiJSON $1  --calcMode true --minBiasXsec $xsecDown --maxPileupBin $nBins --numPileupBins $nBins ./data_$2_down.root
    pileupCalc.py -i $ANJSON --inputLumiJSON $1  --calcMode true --minBiasXsec $xsecUp --maxPileupBin $nBins --numPileupBins $nBins ./data_$2_up.root
}

produce /eos/cms/store/user/jsalfeld/datacert2016ReRecoByLSpuJSON.txt bestFit
produce /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt latest
