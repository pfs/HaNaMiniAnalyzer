from os import listdir

#variations = range( 84 , 117 )
jsons = {"All":"/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt"} 
dir="/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Era/ReReco/"
for f in listdir(dir):
    era = f.split("_")[-1].split(".")[0]
    jsons[era] = dir+f


queue = "8nm"
for era in jsons:
    command = "produceDataPU.sh {json:s} {era:s}"
    submit = ('bsub -q {que:s} -J "{era:s}[840-1170]" -o datapu/{era:s}_{var:s}.out ' + command).format( var="%I" , json=jsons[era] , era=era , que=queue )
    print submit
