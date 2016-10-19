//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 19 10:37:29 2016 by ROOT version 5.34/19
// from TTree Events/Events
// found on file: /home/nadjieh/cernbox/Hamb13/Oct14_8020_Opt/Trees/GGH60.root
//////////////////////////////////////////////////////////

#ifndef OptimTrees_h
#define OptimTrees_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class OptimTrees {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   ULong64_t       EventNumber;
   UInt_t          RunNumber;
   Float_t         met;
   Float_t         metSig;
   vector<float>   *jetsPt;
   vector<float>   *jetsEta;
   vector<float>   *jetsE;
   vector<float>   *jetsPhi;
   vector<float>   *jetsE;
   vector<float>   *jetsBtag;
   vector<float>   *jetsFlavour;
   Float_t         nNonTagged;
   Float_t         nLooseNotMed;
   Float_t         nMedNotTight;
   Float_t         nTight;
   vector<float>   *muPt;
   vector<float>   *muEta;
   vector<float>   *muPhi;
   vector<float>   *muIso;
   vector<bool>    *muId;
   vector<bool>    *muCharge;
   vector<bool>    *muHLT;

   // List of branches
   TBranch        *b_EventNumber;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metSig;   //!
   TBranch        *b_jetsPt;   //!
   TBranch        *b_jetsEta;   //!
   TBranch        *b_jetsE;   //!
   TBranch        *b_jetsPhi;   //!
   TBranch        *b_jetsE;   //!
   TBranch        *b_jetsBtag;   //!
   TBranch        *b_jetsFlavour;   //!
   TBranch        *b_nNonTagged;   //!
   TBranch        *b_nLooseNotMed;   //!
   TBranch        *b_nMedNotTight;   //!
   TBranch        *b_nTight;   //!
   TBranch        *b_muPt;   //!
   TBranch        *b_muEta;   //!
   TBranch        *b_muPhi;   //!
   TBranch        *b_muIso;   //!
   TBranch        *b_muId;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muHLT;   //!

   OptimTrees(TTree *tree=0);
   virtual ~OptimTrees();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef OptimTrees_cxx
OptimTrees::OptimTrees(TTree *tree, TString dirName, TString treeName, TFile * f) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {  
	if(f == 0){
		cout<<"FATAL ERROR! Provide a valid tree or input file ... "<<endl;
		return;
	}
   	TDirectory * dir = (TDirectory*)f->Get(dirName);
      	dir->GetObject(treeName,tree);

   }
   Init(tree);
}

OptimTrees::~OptimTrees()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t OptimTrees::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t OptimTrees::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void OptimTrees::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jetsPt = 0;
   jetsEta = 0;
   jetsE = 0;
   jetsPhi = 0;
   jetsE = 0;
   jetsBtag = 0;
   jetsFlavour = 0;
   muPt = 0;
   muEta = 0;
   muPhi = 0;
   muIso = 0;
   muId = 0;
   muCharge = 0;
   muHLT = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metSig", &metSig, &b_metSig);
   fChain->SetBranchAddress("jetsPt", &jetsPt, &b_jetsPt);
   fChain->SetBranchAddress("jetsEta", &jetsEta, &b_jetsEta);
   fChain->SetBranchAddress("jetsE", &jetsE, &b_jetsE);
   fChain->SetBranchAddress("jetsPhi", &jetsPhi, &b_jetsPhi);
   fChain->SetBranchAddress("jetsBtag", &jetsBtag, &b_jetsBtag);
   fChain->SetBranchAddress("jetsFlavour", &jetsFlavour, &b_jetsFlavour);
   fChain->SetBranchAddress("nNonTagged", &nNonTagged, &b_nNonTagged);
   fChain->SetBranchAddress("nLooseNotMed", &nLooseNotMed, &b_nLooseNotMed);
   fChain->SetBranchAddress("nMedNotTight", &nMedNotTight, &b_nMedNotTight);
   fChain->SetBranchAddress("nTight", &nTight, &b_nTight);
   fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
   fChain->SetBranchAddress("muEta", &muEta, &b_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
   fChain->SetBranchAddress("muIso", &muIso, &b_muIso);
   fChain->SetBranchAddress("muId", &muId, &b_muId);
   fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
   fChain->SetBranchAddress("muHLT", &muHLT, &b_muHLT);
   Notify();
}

Bool_t OptimTrees::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void OptimTrees::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t OptimTrees::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void OptimTrees::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
#endif // #ifdef OptimTrees_cxx
