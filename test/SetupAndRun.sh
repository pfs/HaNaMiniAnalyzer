export X509_USER_PROXY=$1
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=$2
scramv1 project CMSSW $3
cd $3/src/
eval `scramv1 runtime -sh`
mkdir Haamm/
cd Haamm
git clone https://github.com/nadjieh/HaNaMiniAnalyzer/
cd HaNaMiniAnalyzer/
git checkout $4
scram b
cd test
cmsRun ConfFile_cfg.py sample=$5 file=$6 output=$7 maxEvents=-1
if [[ $8 == eos* ]] ;
then
    echo is mounting eos
    mkdir eos
    /afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select -b fuse mount eos
fi
mv $7*$5*.root $8
if [[ $8 == eos* ]] ;
then
    /afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select -b fuse umount eos
    rm -rf eos
fi
