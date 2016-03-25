cd $1
eval `scramv1 runtime -sh`
cmsRun ConfFile_cfg.py sample=$2 file=$3 output=$4 >& $2_$3.log

