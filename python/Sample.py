from os import listdir
from os.path import isfile, join
from das_client import *
from subprocess import call
import os, ntpath


class Sample :
    WD = './'

    def __init__(self , name , histocat , xsection , lheW , color , datasetname , appendix = "" ):
        self.Name = name
        self.HistoCat = histocat
        self.XSection = xsection
        self.IsData = (self.XSection <= 0)
        self.LHEWeight = lheW
        
        self.Color = color

        self.Files = []

        self.InitiateFilesFromListOrDAS( datasetname , appendix )

    def AddFiles( self , directory ):
        files = [join(directory, f) for f in listdir(directory) if isfile(join(directory, f))]
        self.Files.extend( files )

    def GetListFileName( self ):
        return Sample.WD + "/" + self.Name + ".list"

    def WriteFileListToFile( self ):
        if os.path.exists(self.GetListFileName() ):
            os.remove( self.GetListFileName() )

        with open(self.GetListFileName() , 'w') as f :
            for fline in self.Files :
                f.write( fline + "\n" )

    def LoadFilesFromList(self):
        if os.path.exists( self.GetListFileName() ):
            with open(self.GetListFileName() , 'r') as f :
                for line in f.readlines() :
                    self.Files.append( line.strip() )

    def InitiateFilesFromListOrDAS( self , sample , prefix = "" ):
        self.Files = []
        self.LoadFilesFromList()

        if len(self.Files) == 0 :
            self.AddDASFiles( sample , prefix )
            self.WriteFileListToFile()

    def AddDASFiles( self , sample , prefix = "" ):
        jsondict = get_data( "https://cmsweb.cern.ch" , 
                             "file dataset=%(sample)s instance=prod/global"  %  {'sample':sample} ,
                             0 , #idx
                             0 , #limit
                             0 , #verbose
                             300 , #waiting time
                             "" ,  #ckey
                             "" , #cert
                             )
        
        cli_msg  = jsondict.get('client_message', None)
        if  cli_msg:
            print "DAS CLIENT WARNING: %s" % cli_msg
        if  'status' not in jsondict:
            print 'DAS record without status field:\n%s' % jsondict
            sys.exit(EX_PROTOCOL)
        if  jsondict['status'] != 'ok':
            print "status: %s, reason: %s" \
                % (jsondict.get('status'), jsondict.get('reason', 'N/A'))
            sys.exit(EX_TEMPFAIL)

        data = jsondict['data']
        iii = 1
        for jjj in data:
            #print "%d/%d : %s" % ( iii , len(data) , ntpath.basename(str(prim_value(jjj))) )
            iii += 1
            self.Files.append( prefix + str( prim_value(jjj) ) )

