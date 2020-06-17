// Class to manage files for b-tag scale factors, lepton scale factors, pileup weights, and other information

#ifndef LiteTreeMuonSystem_H
#define LiteTreeMuonSystem_H

#define N_MAX_LEPTONS 100
#define N_MAX_MUONS 100
#define N_MAX_JETS 100
#define N_MAX_CSC 2000
#define N_MAX_DT 2000
#define N_MAX_HO 1000
#define NTriggersMAX 601 //Number of trigger in the .dat file
#define N_CSC_CUT 20
#define JET_PT_CUT 10
#define MUON_PT_CUT 20
#define N_MAX_GPARTICLES 2000
#define N_MAX_RPC 2000

#include <iostream>
#include <string>
#include <sys/stat.h>
#include "assert.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TRandom.h"
#include "FactorizedJetCorrector.h"
#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"
#include "SimpleJetResolution.h"
#include "BTagCalibrationStandalone.h"
#include "TTree.h"

#include "RazorAnalyzer.h"

#include "RazorHelper.h"

class LiteTreeMuonSystem
{

public:
  LiteTreeMuonSystem();
  ~LiteTreeMuonSystem();
  // LiteTreeMuonSystem::LiteTreeMuonSystem()
  // {
  //   InitVariables();
  // };
  // LiteTreeMuonSystem::~LiteTreeMuonSystem()
  // {
  //   if (f_) f_->Close();
  // };
  TTree *tree_;
  TFile *f_;

  UInt_t  runNum, lumiSec, evtNum;
  UInt_t  category;
  UInt_t  npv, npu;
  float rho, weight;
  float higgsPtWeight;
  float higgsPtWeightSys[9];
  float sf_facScaleUp, sf_facScaleDown, sf_renScaleUp, sf_renScaleDown, sf_facRenScaleUp, sf_facRenScaleDown;
  float pileupWeight, pileupWeightUp, pileupWeightDown;
  float met, metPhi, HT, jetMet_dPhi, jetMet_dPhiMin,jetMet_dPhiMin4, metJESUp, metJESDown;
  float metXYCorr, metPhiXYCorr;
  bool Flag_HBHENoiseFilter, Flag_HBHEIsoNoiseFilter, Flag_BadPFMuonFilter, Flag_globalSuperTightHalo2016Filter,
    Flag_CSCTightHaloFilter, Flag_BadChargedCandidateFilter, Flag_eeBadScFilter, Flag_goodVertices, Flag_ecalBadCalibFilter, Flag_all;
  int mH, mX, ctau;

  bool Flag2_HBHENoiseFilter, Flag2_HBHEIsoNoiseFilter, Flag2_BadPFMuonFilter, Flag2_globalSuperTightHalo2016Filter,
    Flag2_globalTightHalo2016Filter, Flag2_BadChargedCandidateFilter, Flag2_EcalDeadCellTriggerPrimitiveFilter,
    Flag2_ecalBadCalibFilter, Flag2_eeBadScFilter, Flag2_all;

  int gLepId;
  float gLepPt, gLepPhi, gLepEta, gLepE;
  int nGenParticle;
  int gParticleId[N_MAX_GPARTICLES];
  int gParticleStatus[N_MAX_GPARTICLES];
  int gParticleMotherId[N_MAX_GPARTICLES];
  float gParticlePt[N_MAX_GPARTICLES];
  float gParticleEta[N_MAX_GPARTICLES];
  float gParticlePhi[N_MAX_GPARTICLES];
  float gParticleE[N_MAX_GPARTICLES];

  float genMetPtTrue;
  float genMetPhiTrue;
  float genMetPtCalo;
  float genMetPhiCalo;


  int nGenJets;
  float genJetE[N_MAX_GPARTICLES];
  float genJetPt[N_MAX_GPARTICLES];
  float genJetEta[N_MAX_GPARTICLES];
  float genJetPhi[N_MAX_GPARTICLES];



  float genJetMET[N_MAX_GPARTICLES];

  //csc
  int           nCsc;
  int           cscLabels[N_MAX_CSC];
  int           cscITLabels[N_MAX_CSC];
  int           cscStation[N_MAX_CSC];
  int           cscChamber[N_MAX_CSC];
  float         cscPhi[N_MAX_CSC];   //[nCsc]
  float         cscEta[N_MAX_CSC];   //[nCsc]
  float         cscX[N_MAX_CSC];   //[nCsc]
  float         cscY[N_MAX_CSC];   //[nCsc]
  float         cscZ[N_MAX_CSC];   //[nCsc]
  float         cscDirectionX[N_MAX_CSC];   //[nCsc]
  float         cscDirectionY[N_MAX_CSC];   //[nCsc]
  float         cscDirectionZ[N_MAX_CSC];   //[nCsc]
  float         cscNRecHits[N_MAX_CSC];   //[nCsc]
  float         cscNRecHits_flag[N_MAX_CSC];   //[nCsc]
  float         cscNRecHits_jetveto0p4[N_MAX_CSC];   //[nCsc]
  float         cscNRecHits_jetveto0p8[N_MAX_CSC];   //[nCsc]
  float         cscT[N_MAX_CSC];   //[nCsc]
  float         cscChi2[N_MAX_CSC];   //[nCsc]

  int           nRpc;
  float         rpcPhi[N_MAX_RPC];   //[nRpc]
  float         rpcEta[N_MAX_RPC];   //[nRpc]
  float         rpcX[N_MAX_RPC];   //[nRpc]
  float         rpcY[N_MAX_RPC];   //[nRpc]
  float         rpcZ[N_MAX_RPC];   //[nRpc]
  int           rpcBx[N_MAX_RPC];   //[nRpc]

  int           nHORechits;
  float         hoRechit_Phi[N_MAX_HO];   //[nHORechits]
  float         hoRechit_Eta[N_MAX_HO];   //[nHORechits]
  float         hoRechit_X[N_MAX_HO];   //[nHORechits]
  float         hoRechit_Y[N_MAX_HO];   //[nHORechits]
  float         hoRechit_Z[N_MAX_HO];   //[nHORechits]
  float         hoRechit_T[N_MAX_HO];   //[nHORechits]
  float         hoRechit_E[N_MAX_HO];   //[nHORechits]

    int           nCscClusters;
    bool          cscCluster_match_gLLP[N_MAX_CSC];
    int           cscCluster_match_gLLP_index[N_MAX_CSC];
    int           cscCluster_match_gLLP_minDeltaR[N_MAX_CSC];
    float         cscClusterX[N_MAX_CSC];   //[nCsc]
    float         cscClusterY[N_MAX_CSC];   //[nCsc]
    float         cscClusterZ[N_MAX_CSC];   //[nCsc]
    float         cscClusterTime[N_MAX_CSC];   //[nCsc]
    float         cscClusterTimeSpread[N_MAX_CSC];
    float         cscClusterGenMuonDeltaR[N_MAX_CSC];
    float         cscClusterMajorAxis[N_MAX_CSC];
    float         cscClusterMinorAxis[N_MAX_CSC];
    float         cscClusterXSpread[N_MAX_CSC];   //[nCsc]
    float         cscClusterYSpread[N_MAX_CSC];   //[nCsc]
    float         cscClusterZSpread[N_MAX_CSC];   //[nCsc]
    float         cscClusterEtaPhiSpread[N_MAX_CSC];   //[nCsc]
    float         cscClusterEtaSpread[N_MAX_CSC];   //[nCsc]
    float         cscClusterPhiSpread[N_MAX_CSC];   //[nCsc]
    float         cscClusterEta[N_MAX_CSC];   //[nCsc]
    float         cscClusterPhi[N_MAX_CSC];   //[nCsc]
    int           cscClusterSize[N_MAX_CSC];
    float         cscClusterMe11Ratio[N_MAX_CSC];
    float         cscClusterMe12Ratio[N_MAX_CSC];

    float         cscClusterVertexR[N_MAX_CSC];   //[nCsc]
    float         cscClusterVertexZ[N_MAX_CSC];   //[nCsc]
    int           cscClusterVertexN[N_MAX_CSC];   //[nCsc]
    int           cscClusterVertexN1[N_MAX_CSC];   //[nCsc]
    int           cscClusterVertexN5[N_MAX_CSC];   //[nCsc]
    int           cscClusterVertexN10[N_MAX_CSC];   //[nCsc]
    int           cscClusterVertexN15[N_MAX_CSC];   //[nCsc]
    int           cscClusterVertexN20[N_MAX_CSC];   //[nCsc]
    float         cscClusterVertexChi2[N_MAX_CSC];   //[nCsc]
    float         cscClusterVertexDis[N_MAX_CSC];   //[nCsc]
    float         cscClusterMaxStationRatio[N_MAX_CSC];   //[nCsc]
    int           cscClusterMaxStation[N_MAX_CSC];   //[nCsc]
    int           cscClusterNStation[N_MAX_CSC];
    float         cscClusterMaxChamberRatio[N_MAX_CSC];   //[nCsc]
    int           cscClusterMaxChamber[N_MAX_CSC];   //[nCsc]
    int           cscClusterNChamber[N_MAX_CSC];
    float         cscClusterJetVetoPt[N_MAX_CSC];
    float         cscClusterJetVetoE[N_MAX_CSC];
    float         cscClusterMuonVetoPt[N_MAX_CSC];
    float         cscClusterMuonVetoE[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus11[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus12[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus13[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus21[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus22[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus31[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus32[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus41[N_MAX_CSC];
    int           cscClusterNSegmentChamberPlus42[N_MAX_CSC];

    int           cscClusterNSegmentChamberMinus11[N_MAX_CSC];
    int           cscClusterNSegmentChamberMinus12[N_MAX_CSC];
    int           cscClusterNSegmentChamberMinus13[N_MAX_CSC];
    int           cscClusterNSegmentChamberMinus21[N_MAX_CSC];
    int           cscClusterNSegmentChamberMinus22[N_MAX_CSC];
    int           cscClusterNSegmentChamberMinus31[N_MAX_CSC];
    int           cscClusterNSegmentChamberMinus32[N_MAX_CSC];
    int           cscClusterNSegmentChamberMinus41[N_MAX_CSC];
    int           cscClusterNSegmentChamberMinus42[N_MAX_CSC];
    float         cscClusterMet_dPhi[N_MAX_CSC];

  int           nCscSegClusters;
  float         cscSegClusterX[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterY[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterZ[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterTime[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterTimeSpread[N_MAX_CSC];
  float         cscSegClusterGenMuonDeltaR[N_MAX_CSC];
  float         cscSegClusterMajorAxis[N_MAX_CSC];
  float         cscSegClusterMinorAxis[N_MAX_CSC];
  float         cscSegClusterXSpread[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterYSpread[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterZSpread[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterEtaPhiSpread[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterEtaSpread[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterPhiSpread[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterEta[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterPhi[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterSize[N_MAX_CSC];
  float         cscSegClusterMe11Ratio[N_MAX_CSC];
  float         cscSegClusterMe12Ratio[N_MAX_CSC];

  float         cscSegClusterVertexR[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterVertexZ[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterVertexN[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterVertexN1[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterVertexN5[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterVertexN10[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterVertexN15[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterVertexN20[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterVertexChi2[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterVertexDis[N_MAX_CSC];   //[nCsc]
  float         cscSegClusterMaxStationRatio[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterMaxStation[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterNStation[N_MAX_CSC];
  float         cscSegClusterMaxChamberRatio[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterMaxChamber[N_MAX_CSC];   //[nCsc]
  int           cscSegClusterNChamber[N_MAX_CSC];
  float         cscSegClusterJetVetoPt[N_MAX_CSC];
  float         cscSegClusterJetVetoE[N_MAX_CSC];
  float         cscSegClusterMuonVetoPt[N_MAX_CSC];
  float         cscSegClusterMuonVetoE[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus11[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus12[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus13[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus21[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus22[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus31[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus32[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus41[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberPlus42[N_MAX_CSC];

  int           cscSegClusterNSegmentChamberMinus11[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberMinus12[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberMinus13[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberMinus21[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberMinus22[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberMinus31[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberMinus32[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberMinus41[N_MAX_CSC];
  int           cscSegClusterNSegmentChamberMinus42[N_MAX_CSC];


  int           cscSegCluster_match_gParticle_id[N_MAX_CSC];
  int           cscSegCluster_match_gParticle_index[N_MAX_CSC];
  float         cscSegCluster_match_gParticle_minDeltaR[N_MAX_CSC];

  int           nCsc_JetVetoCluster0p4;
  int           nCsc_JetMuonVetoCluster0p4;
  int           nCsc_JetVetoCluster0p4_Me1112Veto;
  int           nCsc_JetMuonVetoCluster0p4_Me1112Veto;
  float         cscSegClusterMet_dPhi[N_MAX_CSC];

  int           nCsc_JetMuonVetoRechitCluster0p4_Me1112Veto;
  int           nCscRechitClusters;
  int           cscRechitCluster_match_gParticle_id[N_MAX_CSC];

  bool          cscRechitCluster_match_gLLP[N_MAX_CSC];
  int           cscRechitCluster_match_gLLP_index[N_MAX_CSC];
  float         cscRechitCluster_match_gLLP_minDeltaR[N_MAX_CSC];
  float         cscRechitClusterX[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterY[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterZ[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterTime[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterTimeSpread[N_MAX_CSC];
  float         cscRechitClusterGenMuonDeltaR[N_MAX_CSC];
  float         cscRechitClusterMajorAxis[N_MAX_CSC];
  float         cscRechitClusterMinorAxis[N_MAX_CSC];
  float         cscRechitClusterXSpread[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterYSpread[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterZSpread[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterEtaPhiSpread[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterEtaSpread[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterPhiSpread[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterEta[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterPhi[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterSize[N_MAX_CSC];
  float         cscRechitClusterMe11Ratio[N_MAX_CSC];
  float         cscRechitClusterMe12Ratio[N_MAX_CSC];

  float         cscRechitClusterVertexR[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterVertexZ[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterVertexN[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterVertexN1[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterVertexN5[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterVertexN10[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterVertexN15[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterVertexN20[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterVertexChi2[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterVertexDis[N_MAX_CSC];   //[nCsc]
  float         cscRechitClusterMaxStationRatio[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterMaxStation[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterNStation[N_MAX_CSC];
  float         cscRechitClusterMaxChamberRatio[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterMaxChamber[N_MAX_CSC];   //[nCsc]
  int           cscRechitClusterNChamber[N_MAX_CSC];
  float         cscRechitClusterJetVetoPt[N_MAX_CSC];
  float         cscRechitClusterJetVetoE[N_MAX_CSC];
  float         cscRechitClusterMuonVetoPt[N_MAX_CSC];
  float         cscRechitClusterMuonVetoE[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus11[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus12[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus13[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus21[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus22[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus31[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus32[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus41[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberPlus42[N_MAX_CSC];

  int           cscRechitClusterNRechitChamberMinus11[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberMinus12[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberMinus13[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberMinus21[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberMinus22[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberMinus31[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberMinus32[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberMinus41[N_MAX_CSC];
  int           cscRechitClusterNRechitChamberMinus42[N_MAX_CSC];
  float         cscRechitClusterMet_dPhi[N_MAX_CSC];
  
  //dt
  int           nDt;
  int           dtLabels[N_MAX_DT];
  int           dtITLabels[N_MAX_DT];
  int           dtStation[N_MAX_DT];
  int           dtChamber[N_MAX_DT];

  float         dtPhi[N_MAX_DT];   //[nDt]
  float         dtEta[N_MAX_DT];   //[nDt]
  float         dtX[N_MAX_DT];   //[nDt]
  float         dtY[N_MAX_DT];   //[nDt]
  float         dtZ[N_MAX_DT];   //[nDt]
  float         dtDirectionX[N_MAX_DT];   //[nDt]
  float         dtDirectionY[N_MAX_DT];   //[nDt]
  float         dtDirectionZ[N_MAX_DT];   //[nDt]
  float         dtNRecHits[N_MAX_DT];   //[nDt]
  float         dtNRecHits_flag[N_MAX_DT];   //[nDt]
  float         dtNRecHits_jetveto0p4[N_MAX_DT];   //[nDt]
  float         dtNRecHits_jetveto0p8[N_MAX_DT];   //[nDt]
  float         dtT[N_MAX_DT];   //[nDt]
  float         dtChi2[N_MAX_DT];   //[nDt]

  int           nDtRechits;
  int           dtRechitStation[N_MAX_DT];   //[nDtRechits]
  int           dtRechitWheel[N_MAX_DT];   //[nDtRechits]
  float         dtRechitPhi[N_MAX_DT];   //[nDtRechits]
  float         dtRechitEta[N_MAX_DT];   //[nDtRechits]
  float         dtRechitX[N_MAX_DT];   //[nDtRechits]
  float         dtRechitY[N_MAX_DT];   //[nDtRechits]
  float         dtRechitZ[N_MAX_DT];   //[nDtRechits]

    int           nDtClusters;
    bool          dtCluster_match_gLLP[N_MAX_DT];
    int           dtCluster_match_gLLP_index[N_MAX_DT];
    int           dtCluster_match_gLLP_minDeltaR[N_MAX_DT];
    float         dtClusterX[N_MAX_DT];   //[nDt]
    float         dtClusterY[N_MAX_DT];   //[nDt]
    float         dtClusterZ[N_MAX_DT];   //[nDt]
    float         dtClusterTime[N_MAX_DT];   //[nDt]
    float         dtClusterTimeSpread[N_MAX_DT];
    float         dtClusterGenMuonDeltaR[N_MAX_DT];
    float         dtClusterMajorAxis[N_MAX_DT];
    float         dtClusterMinorAxis[N_MAX_DT];
    float         dtClusterXSpread[N_MAX_DT];   //[nDt]
    float         dtClusterYSpread[N_MAX_DT];   //[nDt]
    float         dtClusterZSpread[N_MAX_DT];   //[nDt]
    float         dtClusterEtaPhiSpread[N_MAX_DT];   //[nDt]
    float         dtClusterEtaSpread[N_MAX_DT];   //[nDt]
    float         dtClusterPhiSpread[N_MAX_DT];   //[nDt]
    float         dtClusterEta[N_MAX_DT];   //[nDt]
    float         dtClusterPhi[N_MAX_DT];   //[nDt]
    int           dtClusterSize[N_MAX_DT];
    float         dtClusterMe11Ratio[N_MAX_DT];
    float         dtClusterMe12Ratio[N_MAX_DT];

    float         dtClusterVertexR[N_MAX_DT];   //[nDt]
    float         dtClusterVertexZ[N_MAX_DT];   //[nDt]
    int           dtClusterVertexN[N_MAX_DT];   //[nDt]
    int           dtClusterVertexN1[N_MAX_DT];   //[nDt]
    int           dtClusterVertexN5[N_MAX_DT];   //[nDt]
    int           dtClusterVertexN10[N_MAX_DT];   //[nDt]
    int           dtClusterVertexN15[N_MAX_DT];   //[nDt]
    int           dtClusterVertexN20[N_MAX_DT];   //[nDt]
    float         dtClusterVertexChi2[N_MAX_DT];   //[nDt]
    float         dtClusterVertexDis[N_MAX_DT];   //[nDt]
    float         dtClusterMaxStationRatio[N_MAX_DT];   //[nDt]
    int           dtClusterMaxStation[N_MAX_DT];   //[nDt]
    int           dtClusterNStation[N_MAX_DT];
    float         dtClusterMaxChamberRatio[N_MAX_DT];   //[nDt]
    int           dtClusterMaxChamber[N_MAX_DT];   //[nDt]
    int           dtClusterNChamber[N_MAX_DT];
    float         dtClusterJetVetoPt[N_MAX_DT];
    float         dtClusterJetVetoE[N_MAX_DT];
    float         dtClusterMuonVetoPt[N_MAX_DT];
    float         dtClusterMuonVetoE[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus11[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus12[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus13[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus21[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus22[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus31[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus32[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus41[N_MAX_DT];
    int           dtClusterNSegmentChamberPlus42[N_MAX_DT];

    int           dtClusterNSegmentChamberMinus11[N_MAX_DT];
    int           dtClusterNSegmentChamberMinus12[N_MAX_DT];
    int           dtClusterNSegmentChamberMinus13[N_MAX_DT];
    int           dtClusterNSegmentChamberMinus21[N_MAX_DT];
    int           dtClusterNSegmentChamberMinus22[N_MAX_DT];
    int           dtClusterNSegmentChamberMinus31[N_MAX_DT];
    int           dtClusterNSegmentChamberMinus32[N_MAX_DT];
    int           dtClusterNSegmentChamberMinus41[N_MAX_DT];
    int           dtClusterNSegmentChamberMinus42[N_MAX_DT];

  int           nDtSegClusters;
  float         dtSegClusterX[N_MAX_DT];   //[nDt]
  float         dtSegClusterY[N_MAX_DT];   //[nDt]
  float         dtSegClusterZ[N_MAX_DT];   //[nDt]
  float         dtSegClusterTime[N_MAX_DT];   //[nDt]
  float         dtSegClusterTimeSpread[N_MAX_DT];
  float         dtSegClusterGenMuonDeltaR[N_MAX_DT];
  float         dtSegClusterMajorAxis[N_MAX_DT];
  float         dtSegClusterMinorAxis[N_MAX_DT];
  float         dtSegClusterXSpread[N_MAX_DT];   //[nDt]
  float         dtSegClusterYSpread[N_MAX_DT];   //[nDt]
  float         dtSegClusterZSpread[N_MAX_DT];   //[nDt]
  float         dtSegClusterEtaPhiSpread[N_MAX_DT];   //[nDt]
  float         dtSegClusterEtaSpread[N_MAX_DT];   //[nDt]
  float         dtSegClusterPhiSpread[N_MAX_DT];   //[nDt]
  float         dtSegClusterEta[N_MAX_DT];   //[nDt]
  float         dtSegClusterPhi[N_MAX_DT];   //[nDt]
  int           dtSegClusterSize[N_MAX_DT];
  float         dtSegClusterMe11Ratio[N_MAX_DT];
  float         dtSegClusterMe12Ratio[N_MAX_DT];

  float         dtSegClusterVertexR[N_MAX_DT];   //[nDt]
  float         dtSegClusterVertexZ[N_MAX_DT];   //[nDt]
  int           dtSegClusterVertexN[N_MAX_DT];   //[nDt]
  int           dtSegClusterVertexN1[N_MAX_DT];   //[nDt]
  int           dtSegClusterVertexN5[N_MAX_DT];   //[nDt]
  int           dtSegClusterVertexN10[N_MAX_DT];   //[nDt]
  int           dtSegClusterVertexN15[N_MAX_DT];   //[nDt]
  int           dtSegClusterVertexN20[N_MAX_DT];   //[nDt]
  float         dtSegClusterVertexChi2[N_MAX_DT];   //[nDt]
  float         dtSegClusterVertexDis[N_MAX_DT];   //[nDt]
  float         dtSegClusterMaxStationRatio[N_MAX_DT];   //[nDt]
  int           dtSegClusterMaxStation[N_MAX_DT];   //[nDt]
  int           dtSegClusterNStation[N_MAX_DT];
  float         dtSegClusterMaxChamberRatio[N_MAX_DT];   //[nDt]
  int           dtSegClusterMaxChamber[N_MAX_DT];   //[nDt]
  int           dtSegClusterNChamber[N_MAX_DT];
  float         dtSegClusterJetVetoPt[N_MAX_DT];
  float         dtSegClusterJetVetoE[N_MAX_DT];
  float         dtSegClusterMuonVetoPt[N_MAX_DT];
  float         dtSegClusterMuonVetoE[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus11[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus12[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus13[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus21[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus22[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus31[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus32[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus41[N_MAX_DT];
  int           dtSegClusterNSegmentChamberPlus42[N_MAX_DT];

  int           dtSegClusterNSegmentChamberMinus11[N_MAX_DT];
  int           dtSegClusterNSegmentChamberMinus12[N_MAX_DT];
  int           dtSegClusterNSegmentChamberMinus13[N_MAX_DT];
  int           dtSegClusterNSegmentChamberMinus21[N_MAX_DT];
  int           dtSegClusterNSegmentChamberMinus22[N_MAX_DT];
  int           dtSegClusterNSegmentChamberMinus31[N_MAX_DT];
  int           dtSegClusterNSegmentChamberMinus32[N_MAX_DT];
  int           dtSegClusterNSegmentChamberMinus41[N_MAX_DT];
  int           dtSegClusterNSegmentChamberMinus42[N_MAX_DT];
  int           nDt_JetVetoCluster0p4;
  int           nDt_JetMuonVetoCluster0p4;
  int           nDt_JetVetoCluster0p4_Me1112Veto;
  int           nDt_JetMuonVetoCluster0p4_Me1112Veto;

  int           nDtRechitClusters;

  float         dtRechitCluster_match_gParticle_minDeltaR[N_MAX_DT];
  int           dtRechitCluster_match_gParticle_index[N_MAX_DT];
  int           dtRechitCluster_match_gParticle_id[N_MAX_DT];
  float         dtRechitClusterX[N_MAX_DT];   //[nDt]
  float         dtRechitClusterY[N_MAX_DT];   //[nDt]
  float         dtRechitClusterZ[N_MAX_DT];   //[nDt]
  float         dtRechitClusterTime[N_MAX_DT];   //[nDt]
  float         dtRechitClusterTimeSpread[N_MAX_DT];
  float         dtRechitClusterGenMuonDeltaR[N_MAX_DT];
  float         dtRechitClusterMajorAxis[N_MAX_DT];
  float         dtRechitClusterMinorAxis[N_MAX_DT];
  float         dtRechitClusterXSpread[N_MAX_DT];   //[nDt]
  float         dtRechitClusterYSpread[N_MAX_DT];   //[nDt]
  float         dtRechitClusterZSpread[N_MAX_DT];   //[nDt]
  float         dtRechitClusterEtaPhiSpread[N_MAX_DT];   //[nDt]
  float         dtRechitClusterEtaSpread[N_MAX_DT];   //[nDt]
  float         dtRechitClusterPhiSpread[N_MAX_DT];   //[nDt]
  float         dtRechitClusterEta[N_MAX_DT];   //[nDt]
  float         dtRechitClusterPhi[N_MAX_DT];   //[nDt]
  int           dtRechitClusterSize[N_MAX_DT];
  //float         dtRechitClusterMe11Ratio[N_MAX_DT];
  //float         dtRechitClusterMe12Ratio[N_MAX_DT];

  //float         dtRechitClusterVertexR[N_MAX_DT];   //[nDt]
  //float         dtRechitClusterVertexZ[N_MAX_DT];   //[nDt]
  //int           dtRechitClusterVertexN[N_MAX_DT];   //[nDt]
  //int           dtRechitClusterVertexN1[N_MAX_DT];   //[nDt]
  //int           dtRechitClusterVertexN5[N_MAX_DT];   //[nDt]
  //int           dtRechitClusterVertexN10[N_MAX_DT];   //[nDt]
  //int           dtRechitClusterVertexN15[N_MAX_DT];   //[nDt]
  //int           dtRechitClusterVertexN20[N_MAX_DT];   //[nDt]
  //float         dtRechitClusterVertexChi2[N_MAX_DT];   //[nDt]
  //float         dtRechitClusterVertexDis[N_MAX_DT];   //[nDt]
  float         dtRechitClusterMaxStationRatio[N_MAX_DT];   //[nDt]
  int           dtRechitClusterMaxStation[N_MAX_DT];   //[nDt]
  int           dtRechitClusterNStation[N_MAX_DT];
  float         dtRechitClusterMaxChamberRatio[N_MAX_DT];   //[nDt]
  int           dtRechitClusterMaxChamber[N_MAX_DT];   //[nDt]
  int           dtRechitClusterNChamber[N_MAX_DT];
  float         dtRechitClusterJetVetoPt[N_MAX_DT];
  float         dtRechitClusterJetVetoE[N_MAX_DT];
  float         dtRechitClusterMuonVetoPt[N_MAX_DT];
  float         dtRechitClusterMuonVetoE[N_MAX_DT];
  float         dtRechitClusterCaloJetVeto[N_MAX_DT];

  int           dtRechitClusterNSegmentStation1[N_MAX_DT];
  int           dtRechitClusterNSegmentStation2[N_MAX_DT];
  int           dtRechitClusterNSegmentStation3[N_MAX_DT];
  int           dtRechitClusterNSegmentStation4[N_MAX_DT];
/*int           dtRechitClusterNRechitChamberPlus11[N_MAX_DT];
  int           dtRechitClusterNRechitChamberPlus12[N_MAX_DT];
  int           dtRechitClusterNRechitChamberPlus13[N_MAX_DT];
  int           dtRechitClusterNRechitChamberPlus21[N_MAX_DT];
  int           dtRechitClusterNRechitChamberPlus22[N_MAX_DT];
  int           dtRechitClusterNRechitChamberPlus31[N_MAX_DT];
  int           dtRechitClusterNRechitChamberPlus32[N_MAX_DT];
  int           dtRechitClusterNRechitChamberPlus41[N_MAX_DT];
  int           dtRechitClusterNRechitChamberPlus42[N_MAX_DT];

  int           dtRechitClusterNRechitChamberMinus11[N_MAX_DT];
  int           dtRechitClusterNRechitChamberMinus12[N_MAX_DT];
  int           dtRechitClusterNRechitChamberMinus13[N_MAX_DT];
  int           dtRechitClusterNRechitChamberMinus21[N_MAX_DT];
  int           dtRechitClusterNRechitChamberMinus22[N_MAX_DT];
  int           dtRechitClusterNRechitChamberMinus31[N_MAX_DT];
  int           dtRechitClusterNRechitChamberMinus32[N_MAX_DT];
  int           dtRechitClusterNRechitChamberMinus41[N_MAX_DT];
  int           dtRechitClusterNRechitChamberMinus42[N_MAX_DT];
  */
  // //csc intime cluster
  // int           nCscITClusters;
  // float         cscITClusterJetVeto[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterCaloJetVeto[N_MAX_CSC];
  // float         cscITClusterMuonVeto[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterJetVetoE[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterCaloJetVetoE[N_MAX_CSC];
  // float         cscITClusterMuonVetoE[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterX[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterY[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterZ[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterRadius[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterTime[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterTimeSpread[N_MAX_CSC];
  // float         cscITClusterTimeRMS[N_MAX_CSC];
  // float         cscITClusterGenMuonDeltaR[N_MAX_CSC];
  // float         cscITClusterMajorAxis[N_MAX_CSC];
  // float         cscITClusterMinorAxis[N_MAX_CSC];
  // float         cscITClusterXSpread[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterYSpread[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterZSpread[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterEtaPhiSpread[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterEtaSpread[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterPhiSpread[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterEta[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterPhi[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterSize[N_MAX_CSC];
  // float         cscITClusterMe11Ratio[N_MAX_CSC];
  // float         cscITClusterMe12Ratio[N_MAX_CSC];
  //
  // float         cscITClusterVertexR[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterVertexZ[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterVertexN[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterVertexN1[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterVertexN5[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterVertexN10[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterVertexN15[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterVertexN20[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterVertexChi2[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterVertexDis[N_MAX_CSC];   //[nCsc]
  // float         cscITClusterMaxStationRatio[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterMaxStation[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterNStation[N_MAX_CSC];
  // float         cscITClusterMaxChamberRatio[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterMaxChamber[N_MAX_CSC];   //[nCsc]
  // int           cscITClusterNChamber[N_MAX_CSC];
  // int           cscITCluster_match_cscCluster_index[N_MAX_CSC];
  // float         cscITCluster_cscCluster_SizeRatio[N_MAX_CSC];
  // int           nCsc_JetVetoITCluster0p4;
  // int           nCsc_JetMuonVetoITCluster0p4;
  // int           nCsc_JetVetoITCluster0p4_Me1112Veto;
  // int           nCsc_JetMuonVetoITCluster0p4_Me1112Veto;
  //gLLP
  float gLLP_eta[2];
  float gLLP_phi[2];
  float gLLP_csc[2];
  float gLLP_dt[2];
  float gLLP_beta[2];
  float gLLP_ctau[2];
  float gLLP_decay_vertex_r[2];
  float gLLP_decay_vertex_x[2];
  float gLLP_decay_vertex_y[2];
  float gLLP_decay_vertex_z[2];
  float gHiggsPt;
  float gHiggsEta;
  float gHiggsPhi;
  float gHiggsE;

  //leptons
  int nMuons;
  float muonE[N_MAX_MUONS];
  float muonPt[N_MAX_MUONS];
  float muonEta[N_MAX_MUONS];
  float muonPhi[N_MAX_MUONS];

  //leptons
  int nLeptons;
  float lepE[N_MAX_LEPTONS];
  float lepPt[N_MAX_LEPTONS];
  float lepEta[N_MAX_LEPTONS];
  float lepPhi[N_MAX_LEPTONS];
  int  lepPdgId[N_MAX_LEPTONS];
  float lepDZ[N_MAX_LEPTONS];
  // bool lepLoosePassId[N_MAX_LEPTONS];
  // bool lepMediumPassId[N_MAX_LEPTONS];
  // bool lepTightPassId[N_MAX_LEPTONS];
  bool lepPassVetoId[N_MAX_LEPTONS];

  bool lepPassId[N_MAX_LEPTONS];

  //Z-candidate
  float MT;
  float ZMass;
  float ZPt;
  float ZEta;
  float ZPhi;
  int ZleptonIndex1;
  int ZleptonIndex2;
  //jets
  int nJets;
  float jetE[N_MAX_JETS];
  float jetPt[N_MAX_JETS];
  float jetEta[N_MAX_JETS];
  float jetPhi[N_MAX_JETS];
  float jetTime[N_MAX_JETS];
  float ecalNRechits[N_MAX_JETS];
  float ecalRechitE[N_MAX_JETS];
  float jetChargedEMEnergyFraction[N_MAX_JETS];
  float jetNeutralEMEnergyFraction[N_MAX_JETS];
  float jetChargedHadronEnergyFraction[N_MAX_JETS];
  float jetNeutralHadronEnergyFraction[N_MAX_JETS];
  bool jetPassMuFrac[N_MAX_JETS];
  float jet_match_genJet_minDeltaR[N_MAX_JETS];
  int jet_match_genJet_index[N_MAX_JETS];
  float jet_match_genJet_pt[N_MAX_JETS];

  // bool jetLoosePassId[N_MAX_JETS];
  bool jetPassId[N_MAX_JETS];
  // bool jetTightPassId[N_MAX_JETS];
  bool HLTDecision[NTriggersMAX];
  UInt_t wzevtNum,trig, trig_lepId, trig_lepId_dijet; //number of events that pass each criteria




  void InitVariables();
  void InitTree();
  void LoadTree(const char* file);
  void CreateTree();

};
#endif
