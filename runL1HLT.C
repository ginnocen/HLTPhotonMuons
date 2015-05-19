#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TString.h>
#include <TLegendEntry.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>

#include <vector>
#include <iostream>

//#include "EventMatchingCMS.h"

const int MAXL1JETS = 8;
const int MAXJETS = 500;
const Int_t THRESHOLDS = 200; // This will correspond to 0 to 199.5 GeV in 0.5 GeV increments


void runL1HLT(TString inL1Name="openHLT.root")
{

  int L1_SingleMu3_BptxAND;
  int L1_SingleJet16_BptxAND;
  int L1_SingleJet16_BptxANDfake;
  int L1_SingleEG18;
  int L1_SingleEG18fake;
   
  TFile*inf=new TFile(inL1Name.Data());
  TTree *hltTree = (TTree*)inf->Get("hltbitanalysis/HltTree");
  hltTree->SetBranchAddress("L1_SingleMu3_BptxAND",&L1_SingleMu3_BptxAND);
  hltTree->SetBranchAddress("L1_SingleJet16_BptxAND",&L1_SingleJet16_BptxAND);
  hltTree->SetBranchAddress("L1_SingleEG18",&L1_SingleEG18);


  TTree *l1Tree = (TTree*)inf->Get("L1UpgradeAnalyzer/L1UpgradeTree");
  Int_t l1_event, l1_run, l1_lumi;
  Int_t l1_hwPt[MAXL1JETS], l1_hwEta[MAXL1JETS], l1_hwPhi[MAXL1JETS];
  Double_t l1_pt[MAXL1JETS];
  Int_t l1_egamma_hwPt[MAXL1JETS];

  l1Tree->SetBranchAddress("event",&l1_event);
  l1Tree->SetBranchAddress("run",&l1_run);
  l1Tree->SetBranchAddress("lumi",&l1_lumi);
  l1Tree->SetBranchAddress("jet_hwPt",l1_hwPt);
  l1Tree->SetBranchAddress("jet_hwEta",l1_hwEta);
  l1Tree->SetBranchAddress("jet_hwPhi",l1_hwPhi);
  l1Tree->SetBranchAddress("jet_pt",l1_pt);
  l1Tree->SetBranchAddress("egamma_hwPt",l1_egamma_hwPt);

  Long64_t entries = hltTree->GetEntries();
  
  int counter_L1_SingleMu3_BptxAND=0;
  int counter_L1_SingleJet16_BptxANDfake=0;
  int counter_L1_SingleJet16_BptxAND=0;
  
  int counter_L1_SingleEG18fake=0;
  int counter_L1_SingleEG18=0;
  
  
  int total=0;
  
  for(Long64_t j = 0; j < entries; ++j)
  {
    hltTree->GetEntry(j);
    l1Tree->GetEntry(j);

    if(j % 10000 == 0)
      printf("%lld / %lld\n",j,entries);
      total++;
      
      double maxl1pt = 0;
      for(int i = 0; i < MAXL1JETS; ++i){
        if(l1_pt[i] > maxl1pt)
	    maxl1pt = l1_pt[i];
      }

      double maxl1ptegamma = 0;
      for(int i = 0; i < MAXL1JETS; ++i){
        if(l1_egamma_hwPt[i] > maxl1ptegamma)
	    maxl1ptegamma = l1_egamma_hwPt[i];
      }

	    //cout<<"maxl1pt="<<maxl1pt<<endl;
      L1_SingleJet16_BptxANDfake=0;
      L1_SingleEG18fake=0;
      
      if(maxl1pt>=16) { L1_SingleJet16_BptxANDfake=1;}
      if(maxl1ptegamma>=18) { L1_SingleEG18fake=1;}
      
      if(L1_SingleJet16_BptxAND) counter_L1_SingleJet16_BptxAND++;
      if(L1_SingleJet16_BptxANDfake) counter_L1_SingleJet16_BptxANDfake++;
      
      if(L1_SingleEG18) counter_L1_SingleEG18++;
      if(L1_SingleEG18fake) counter_L1_SingleEG18fake++;
      
      //if(L1_SingleMu3_BptxAND==1 && L1_SingleJet16_BptxANDfake==1) { cout<<"look here"<<std::endl; counter_L1_SingleMu3_BptxAND++; }
  }
  //cout<<"look counter_L1_SingleMu3_BptxAND="<<counter_L1_SingleMu3_BptxAND<<std::endl;
  //cout<<"look total="<<total<<std::endl;
  //double rate=(float)counter_L1_SingleMu3_BptxAND/(float)total;
  //cout<<"look rate (Hz)="<<rate*30000<<std::endl;
  
  cout<<"counter_L1_SingleJet16_BptxANDfake="<<counter_L1_SingleJet16_BptxANDfake<<std::endl;
  cout<<"counter_L1_SingleJet16_BptxAND="<<counter_L1_SingleJet16_BptxAND<<std::endl;
  cout<<"counter_L1_SingleEG18fake="<<counter_L1_SingleEG18fake<<std::endl;
  cout<<"counter_L1_SingleEG18="<<counter_L1_SingleEG18<<std::endl;

}
