from Samples import MiniAOD80Samples 

import subprocess

for s in MiniAOD80Samples:
    #with open(, 'w' ) as f:
    command = " ".join( ['das_client','--limit=0' , '--query="file' , 'dataset=%s"'%(s.DS)] )
    print "%s > %s" % ( command ,  "%s.list" % (s.Name)  )
        #f.write( subprocess.check_output( [command] ) )

