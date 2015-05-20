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
  int L1_SingleMu5_BptxAND;

  int L1_SingleJet16_BptxAND;
  int L1_SingleJet18_BptxAND;
  int L1_SingleJet20_BptxAND;
  int L1_SingleJet24_BptxAND;
  int L1_SingleJet28_BptxAND;
  int L1_SingleJet32_BptxAND;
  int L1_SingleJet36_BptxAND;
  int L1_SingleJet40_BptxAND;

  int L1_SingleEG18;
  int L1_SingleEG20;
  int L1_SingleEG16;
  int L1_SingleEG14;
  int L1_SingleEG12;
  

  TFile*inf=new TFile(inL1Name.Data());
  TTree *hltTree = (TTree*)inf->Get("hltbitanalysis/HltTree");
  hltTree->SetBranchAddress("L1_SingleMu3_BptxAND",&L1_SingleMu3_BptxAND);
  hltTree->SetBranchAddress("L1_SingleMu5_BptxAND",&L1_SingleMu5_BptxAND);


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
  int counter_L1_SingleMu5_BptxAND=0;
  
  int counter_L1_SingleJet16_BptxAND=0;
  int counter_L1_SingleJet18_BptxAND=0;
  int counter_L1_SingleJet20_BptxAND=0;
  int counter_L1_SingleJet24_BptxAND=0;
  int counter_L1_SingleJet28_BptxAND=0;
  int counter_L1_SingleJet32_BptxAND=0;
  int counter_L1_SingleJet36_BptxAND=0;
  int counter_L1_SingleJet40_BptxAND=0;  
  
  int counter_L1_SingleEG20=0;
  int counter_L1_SingleEG18=0;
  int counter_L1_SingleEG16=0;
  int counter_L1_SingleEG14=0;
  int counter_L1_SingleEG12=0;
  
  int counter_L1_SingleMu3_AND_SingleJet16=0;  
  int counter_L1_SingleMu3_AND_SingleJet32=0;  
  int counter_L1_SingleMu3_AND_SingleJet36=0;  
  int counter_L1_SingleMu3_AND_SingleJet40=0;  
  
  int counter_L1_SingleMu5_AND_SingleJet16=0;  
  int counter_L1_SingleMu5_AND_SingleJet32=0;  
  int counter_L1_SingleMu5_AND_SingleJet36=0;  
  int counter_L1_SingleMu5_AND_SingleJet40=0;  
  
  int counter_L1_SingleEG20_AND_SingleMu3=0;
  int counter_L1_SingleEG18_AND_SingleMu3=0;
  int counter_L1_SingleEG16_AND_SingleMu3=0;
  int counter_L1_SingleEG14_AND_SingleMu3=0;
  int counter_L1_SingleEG12_AND_SingleMu3=0;

  int counter_L1_SingleEG20_AND_SingleMu5=0;
  int counter_L1_SingleEG18_AND_SingleMu5=0;
  int counter_L1_SingleEG16_AND_SingleMu5=0;
  int counter_L1_SingleEG14_AND_SingleMu5=0;
  int counter_L1_SingleEG12_AND_SingleMu5=0;

  
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

      L1_SingleJet20_BptxAND=0;
      L1_SingleJet24_BptxAND=0;
      L1_SingleJet28_BptxAND=0;
      L1_SingleJet32_BptxAND=0;
      L1_SingleJet36_BptxAND=0;
      L1_SingleJet40_BptxAND=0;
      
      L1_SingleEG20=0;      
      L1_SingleEG18=0;
      L1_SingleEG16=0;
      L1_SingleEG14=0;
      L1_SingleEG12=0;
      
      if(maxl1pt>=16) L1_SingleJet16_BptxAND=1;
      if(maxl1pt>=18) L1_SingleJet18_BptxAND=1;
      if(maxl1pt>=20) L1_SingleJet20_BptxAND=1;
      if(maxl1pt>=24) L1_SingleJet24_BptxAND=1;
      if(maxl1pt>=28) L1_SingleJet28_BptxAND=1;
      if(maxl1pt>=32) L1_SingleJet32_BptxAND=1;
      if(maxl1pt>=36) L1_SingleJet36_BptxAND=1;
      if(maxl1pt>=40) L1_SingleJet40_BptxAND=1;

      if(maxl1ptegamma>=20) L1_SingleEG20=1;
      if(maxl1ptegamma>=18) L1_SingleEG18=1;
      if(maxl1ptegamma>=16) L1_SingleEG16=1;
      if(maxl1ptegamma>=14) L1_SingleEG14=1;
      if(maxl1ptegamma>=12) L1_SingleEG12=1;
      
      if(L1_SingleJet16_BptxAND) counter_L1_SingleJet16_BptxAND++;
      if(L1_SingleJet18_BptxAND) counter_L1_SingleJet18_BptxAND++;
      if(L1_SingleJet20_BptxAND) counter_L1_SingleJet20_BptxAND++;
      if(L1_SingleJet24_BptxAND) counter_L1_SingleJet24_BptxAND++;
      if(L1_SingleJet28_BptxAND) counter_L1_SingleJet28_BptxAND++;
      if(L1_SingleJet32_BptxAND) counter_L1_SingleJet32_BptxAND++;
      if(L1_SingleJet36_BptxAND) counter_L1_SingleJet36_BptxAND++;
      if(L1_SingleJet40_BptxAND) counter_L1_SingleJet40_BptxAND++;
      
      if(L1_SingleEG18) counter_L1_SingleEG18++;
      if(L1_SingleEG20) counter_L1_SingleEG20++;
      if(L1_SingleEG16) counter_L1_SingleEG16++;
      if(L1_SingleEG14) counter_L1_SingleEG14++;
      if(L1_SingleEG12) counter_L1_SingleEG12++;
      
      if(L1_SingleMu3_BptxAND) counter_L1_SingleMu3_BptxAND++;
      if(L1_SingleMu5_BptxAND) counter_L1_SingleMu5_BptxAND++;
      
      if(L1_SingleMu3_BptxAND&&L1_SingleJet16_BptxAND) counter_L1_SingleMu3_AND_SingleJet16++;
      if(L1_SingleMu3_BptxAND&&L1_SingleJet32_BptxAND) counter_L1_SingleMu3_AND_SingleJet32++;
      if(L1_SingleMu3_BptxAND&&L1_SingleJet36_BptxAND) counter_L1_SingleMu3_AND_SingleJet36++;
      if(L1_SingleMu3_BptxAND&&L1_SingleJet40_BptxAND) counter_L1_SingleMu3_AND_SingleJet40++;

      if(L1_SingleMu5_BptxAND&&L1_SingleJet16_BptxAND) counter_L1_SingleMu5_AND_SingleJet16++;
      if(L1_SingleMu5_BptxAND&&L1_SingleJet32_BptxAND) counter_L1_SingleMu5_AND_SingleJet32++;
      if(L1_SingleMu5_BptxAND&&L1_SingleJet36_BptxAND) counter_L1_SingleMu5_AND_SingleJet36++;
      if(L1_SingleMu5_BptxAND&&L1_SingleJet40_BptxAND) counter_L1_SingleMu5_AND_SingleJet40++;
      
      if(L1_SingleMu3_BptxAND&&L1_SingleEG20) counter_L1_SingleEG20_AND_SingleMu3++;
      if(L1_SingleMu3_BptxAND&&L1_SingleEG18) counter_L1_SingleEG18_AND_SingleMu3++;
      if(L1_SingleMu3_BptxAND&&L1_SingleEG16) counter_L1_SingleEG16_AND_SingleMu3++;
      if(L1_SingleMu3_BptxAND&&L1_SingleEG14) counter_L1_SingleEG14_AND_SingleMu3++;
      if(L1_SingleMu3_BptxAND&&L1_SingleEG12) counter_L1_SingleEG12_AND_SingleMu3++;
      
      if(L1_SingleMu5_BptxAND&&L1_SingleEG20) counter_L1_SingleEG20_AND_SingleMu5++;
      if(L1_SingleMu5_BptxAND&&L1_SingleEG18) counter_L1_SingleEG18_AND_SingleMu5++;
      if(L1_SingleMu5_BptxAND&&L1_SingleEG16) counter_L1_SingleEG16_AND_SingleMu5++;
      if(L1_SingleMu5_BptxAND&&L1_SingleEG14) counter_L1_SingleEG14_AND_SingleMu5++;
      if(L1_SingleMu5_BptxAND&&L1_SingleEG12) counter_L1_SingleEG12_AND_SingleMu5++;

  }
  
  cout<<"*****************************="<<endl;
  cout<<"rate_L1_SingleJet16_BptxAND="<<counter_L1_SingleJet16_BptxAND/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleJet18_BptxAND="<<counter_L1_SingleJet18_BptxAND/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleJet20_BptxAND="<<counter_L1_SingleJet20_BptxAND/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleJet24_BptxAND="<<counter_L1_SingleJet24_BptxAND/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleJet28_BptxAND="<<counter_L1_SingleJet28_BptxAND/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleJet32_BptxAND="<<counter_L1_SingleJet32_BptxAND/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleJet36_BptxAND="<<counter_L1_SingleJet36_BptxAND/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleJet40_BptxAND="<<counter_L1_SingleJet40_BptxAND/(float)total*30000<<std::endl;
  
  cout<<"*****************************="<<endl;
  cout<<"rate_L1_SingleMu3_BptxAND="<<counter_L1_SingleMu3_BptxAND/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleMu3_BptxAND="<<counter_L1_SingleMu5_BptxAND/(float)total*30000<<std::endl;
  
  cout<<"*****************************="<<endl;
  cout<<"rate_L1_SingleEG12="<<counter_L1_SingleEG12/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG14="<<counter_L1_SingleEG14/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG16="<<counter_L1_SingleEG16/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG18="<<counter_L1_SingleEG18/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG20="<<counter_L1_SingleEG20/(float)total*30000<<std::endl;
  
  cout<<"*****************************="<<endl;
  cout<<"rate_L1_SingleMu3_AND_SingleJet16="<<counter_L1_SingleMu3_AND_SingleJet16/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleMu3_AND_SingleJet32="<<counter_L1_SingleMu3_AND_SingleJet32/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleMu3_AND_SingleJet36="<<counter_L1_SingleMu3_AND_SingleJet36/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleMu3_AND_SingleJet40="<<counter_L1_SingleMu3_AND_SingleJet40/(float)total*30000<<std::endl;
  cout<<"*****************************="<<endl;
  cout<<"rate_L1_SingleMu5_AND_SingleJet16="<<counter_L1_SingleMu5_AND_SingleJet16/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleMu5_AND_SingleJet32="<<counter_L1_SingleMu5_AND_SingleJet32/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleMu5_AND_SingleJet36="<<counter_L1_SingleMu5_AND_SingleJet36/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleMu5_AND_SingleJet40="<<counter_L1_SingleMu5_AND_SingleJet40/(float)total*30000<<std::endl;
  cout<<"*****************************="<<endl;
  cout<<"rate_L1_SingleEG12_AND_SingleMu3="<<counter_L1_SingleEG12_AND_SingleMu3/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG14_AND_SingleMu3="<<counter_L1_SingleEG14_AND_SingleMu3/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG16_AND_SingleMu3="<<counter_L1_SingleEG16_AND_SingleMu3/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG18_AND_SingleMu3="<<counter_L1_SingleEG18_AND_SingleMu3/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG20_AND_SingleMu3="<<counter_L1_SingleEG20_AND_SingleMu3/(float)total*30000<<std::endl;
  cout<<"*****************************="<<endl;
  cout<<"rate_L1_SingleEG12_AND_SingleMu5="<<counter_L1_SingleEG12_AND_SingleMu5/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG14_AND_SingleMu5="<<counter_L1_SingleEG14_AND_SingleMu5/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG16_AND_SingleMu5="<<counter_L1_SingleEG16_AND_SingleMu5/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG18_AND_SingleMu5="<<counter_L1_SingleEG18_AND_SingleMu5/(float)total*30000<<std::endl;
  cout<<"rate_L1_SingleEG20_AND_SingleMu5="<<counter_L1_SingleEG20_AND_SingleMu5/(float)total*30000<<std::endl;



}
