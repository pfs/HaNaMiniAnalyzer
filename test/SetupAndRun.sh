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

if [ ! -z "$LSB_JOBINDEX" ];
then
    echo $LSB_JOBINDEX
    export FILEID=`expr $LSB_JOBINDEX - 1`
    echo $FILEID
else
    if [ ! -z "$CONDORJOBID" ];
    then
	export FILEID=$CONDORJOBID
	echo $FILEID
    fi
fi


echo cmsRun ConfFile_cfg.py sample=$5 file=$FILEID output=$6 maxEvents=-1
cmsRun ConfFile_cfg.py sample=$5 file=$FILEID output=$6 maxEvents=-1
if [[ $7 == eos* ]] ;
then
    echo is mounting eos
    mkdir eos
    /afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select -b fuse mount eos
fi
mkdir -p $7
mv $6*$5*.root $7
if [[ $7 == eos* ]] ;
then
    /afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select -b fuse umount eos
    rm -rf eos
fi
