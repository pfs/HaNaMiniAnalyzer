from ROOT import TH1, TFile, TH2

f_BCDEF_ = TFile.Open("EfficienciesAndSF_BCDEF.root")
f_GH_ = TFile.Open("EfficienciesAndSF_GH.root")

fOut = TFile.Open("EfficienciesAndSF_ISO_W2016.root" , "RECREATE")

def MergeIDHistos( ID ):

    dir = "MC_NUM_%sID_DEN_genTracks_PAR_pt_eta" % (ID)
    h_BCDEF_ = f_BCDEF_.Get(dir + "/pt_abseta_ratio")
    h_GH_ = f_GH_.Get( dir + "/pt_abseta_ratio")

    hFinal = h_BCDEF_.Clone("pt_abseta_ratio")
    hFinal.Add( h_BCDEF_ , h_GH_ , 0.5498 , 0.4502 )

    fOut.mkdir( dir ).cd()
    hFinal.Write()

def MergeISOHistos( ISO, ID):
    dir = "%sISO_%sID_pt_eta" % (ISO , ID)
    print dir
    h_BCDEF_ = f_BCDEF_.Get(dir + "/pt_abseta_ratio")
    h_GH_ = f_GH_.Get( dir + "/pt_abseta_ratio")
    if h_BCDEF_ == None :
        print "\t not found"
        return
    hFinal = h_BCDEF_.Clone("pt_abseta_ratio")
    hFinal.Add( h_BCDEF_ , h_GH_ , 0.5498 , 0.4502 )

    fOut.mkdir( dir ).cd()
    hFinal.Write()


for id in ["Tight", "Medium" , "Loose"]:
    #MergeIDHistos( id )
    for iso in ["Tight" , "Loose"]:
        MergeISOHistos( iso , id )

fOut.Close()
