from ROOT import TDirectory, TFile, TCanvas , TH1D , TH1 , THStack, TList, gROOT, TLegend

class Histogram:
    def __init__(self, Samples , directory):
        self.PropName = directory.GetName()
        
        dircontents = directory.GetListOfKeys()
        firsthisto = directory.Get( dircontents.At(0).GetName() )
        #firsthisto.Print("ALL")
        self.ForLegend = {}
        self.XSections = {}
        self.AllSampleHistos = {}

        for sample in Samples:
            if sample.IsData:
                self.DataSName = sample.Name


            # h_in_dir = directory.Get( "%s_%s" % ( self.PropName , sample.Name ) )
            # if h_in_dir :
            #     h_in_dir.reset()
            #     setattr( self , sample.Name , h_in_dir )
            # else:
            gROOT.cd()
            hnew = firsthisto.Clone("%s_%s" % ( self.PropName , sample.Name ) )
            hnew.Reset()
            setattr( self , sample.Name , hnew )
                
            hhh = getattr( self , sample.Name )
            hhh.SetLineColor( 1 )
            hhh.SetLineWidth( 2 )
            if not sample.IsData :
                hhh.SetFillColor( sample.Color )
                hhh.SetFillStyle( 1001 )
            else:
                hhh.SetStats(0)
		hhh.SetMarkerStyle(20)

            self.AllSampleHistos[sample.Name] = hhh    
                
            if( self.ForLegend.get(sample.HistoCat) ):
                self.ForLegend[sample.HistoCat].append( sample.Name )
            else:
                self.ForLegend[sample.HistoCat] = [ sample.Name ]

            self.XSections[sample.Name] = sample.XSection

    def AddFile(self , directory):
        ##find all relevant histograms in the file and add them to your histos
        for sample in self.AllSampleHistos:
            h_in_dir = directory.Get( "%s/%s_%s" % ( self.PropName , self.PropName , sample ) )
            if h_in_dir :
                self.AllSampleHistos[sample].Add( h_in_dir )
                

    def Write(self, fout ):
        fout.mkdir( self.PropName ).cd()
        for sample in self.AllSampleHistos:
            self.AllSampleHistos[sample].Write()
        if hasattr( self, "Canvas" ):
            self.Canvas.Write()
        fout.cd()
        

    def Draw(self , lumi , cft):
        self.FinalHistos={}
        for sample in self.AllSampleHistos:
            if sample == self.DataSName :
                continue
            ntotal = getattr( cft , sample ).GetBinContent( 1 )
            if ntotal == 0:
                print "Sample %s has no entries" % (sample)
                continue
            factor = lumi*self.XSections[sample]/ntotal
            #print "%s factor : (%.2f*%.2f)/%.0f = %.3f" % (sample , lumi , self.XSections[sample] , ntotal  , factor)
            self.AllSampleHistos[sample].Scale(factor)

        self.Stack = THStack("%s_stack" % (self.PropName) , self.PropName )
        for finalh in self.ForLegend:
            if finalh == "Data" :
                continue

            for hname in self.ForLegend[finalh]:
                #print "Adding %s to %s" % ( hname , finalh )
                if self.FinalHistos.get(finalh) :
                    self.FinalHistos[finalh].Add( self.AllSampleHistos[hname] )
                else:
                    self.FinalHistos[finalh] = self.AllSampleHistos[hname].Clone( "%s_%s" % (self.PropName , finalh) )
                    
                    #self.FinalHistos[finalh].SetLineColor( 0 )
                    self.FinalHistos[finalh].SetTitle( finalh )
            self.Stack.Add( self.FinalHistos[finalh] )
        

        self.Canvas = TCanvas("%s_C" % (self.PropName) )
        getattr( self , self.DataSName ).Draw("E")
        self.Stack.Draw("HIST SAME")
        getattr( self , self.DataSName ).Draw("E SAME")

        self.Legend = TLegend(0.5,0.67,0.88,0.88,"","brNDC")
        entry=self.Legend.AddEntry( getattr( self , self.DataSName ) , "Data" , "lp" )
        for finalh in reversed( self.ForLegend.keys() ):
            if finalh == "Data" :
                continue
            self.Legend.AddEntry( self.FinalHistos[finalh] , finalh , "f" )
        self.Legend.Draw()




