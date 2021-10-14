#include "CreateTree.hh"
#include <algorithm>

using namespace std;

CreateTree *CreateTree::fInstance = NULL;

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

CreateTree::CreateTree(TString name)
{
  if (fInstance)
  {
    return;
  }

  this->fInstance = this;
  this->fname = name;
  this->ftree = new TTree(name, name);

  this->GetTree()->Branch("Event", &this->Event, "Event/I");
  /*
  this->GetTree()->Branch("inputTrackerX0", &this->inputTrackerX0, "inputTrackerX0/F");
  this->GetTree()->Branch("inputServiceAlmm", &this->inputServiceAlmm, "inputServiceAlmm/F");
  this->GetTree()->Branch("inputTimingThick", &this->inputTimingThick, "inputTimingThick/F");
  this->GetTree()->Branch("inputE1Thick", &this->inputE1Thick, "inputE1Thick/F");
  this->GetTree()->Branch("inputE2Thick", &this->inputE2Thick, "inputE2Thick/F");
  this->GetTree()->Branch("inputE1Width", &this->inputE1Width, "inputE1Width/F");
  this->GetTree()->Branch("inputTimingECAL_dist", &this->inputTimingECAL_dist, "inputTimingECAL_dist/F");
  */
  inputInitialPosition = new vector<float>(3, 0.);
  inputMomentum = new vector<float>(4, 0.);
  /*
  primaryPosT1 = new vector<float>(3, 0.);
  primaryMomT1 = new vector<float>(4, 0.);
  primaryPosE1 = new vector<float>(3, 0.);
  primaryMomE1 = new vector<float>(4, 0.);
  */

  this->GetTree()->Branch("inputInitialPosition", "vector<float>", &inputInitialPosition);
  this->GetTree()->Branch("inputMomentum", "vector<float>", &inputMomentum);
  this->GetTree()->Branch("primaryID", &this->primaryID, "primaryID/I");
  //  this->GetTree()->Branch("primaryPosT1", "vector<float>", &primaryPosT1);
  //  this->GetTree()->Branch("primaryMomT1", "vector<float>", &primaryMomT1);
  //  this->GetTree()->Branch("primaryPosE1", "vector<float>", &primaryPosE1);
  //  this->GetTree()->Branch("primaryMomE1", "vector<float>", &primaryMomE1);
  /*
  this->GetTree()->Branch("nTracksT1", &this->nTracksT1, "nTracksT1/I");
  this->GetTree()->Branch("nTracksT2", &this->nTracksT2, "nTracksT2/I");
  this->GetTree()->Branch("nTracksE1", &this->nTracksE1, "nTracksE1/I");
  this->GetTree()->Branch("nTracksE2", &this->nTracksE2, "nTracksE2/I");
  this->GetTree()->Branch("nTracksTRK", &this->nTracksTRK, "nTracksTRK[6]/F");
  */

  //integrated per longitudinal layer
  this->GetTree()->Branch("depositedEnergyEcalFront",&this->depositedEnergyEcalFront,"depositedEnergyEcalFront/F");


  this->GetTree()->Branch("depositedEnergyTotal", &this->depositedEnergyTotal, "depositedEnergyTotal/F");
  this->GetTree()->Branch("depositedEnergyEscapeWorld", &this->depositedEnergyEscapeWorld, "depositedEnergyEscapeWorld/F");
  //  this->GetTree()->Branch("depositedEnergyECAL_f", &this->depositedEnergyECAL_f, "depositedEnergyECAL_f[3]/F");
  //  this->GetTree()->Branch("depositedEnergyECAL_r", &this->depositedEnergyECAL_r, "depositedEnergyECAL_r[3]/F");
  this->GetTree()->Branch("depositedEnergyECAL_f", &this->depositedEnergyECAL_f, "depositedEnergyECAL_f/F");
  this->GetTree()->Branch("depositedEnergyECAL_r", &this->depositedEnergyECAL_r, "depositedEnergyECAL_r/F");
  //  this->GetTree()->Branch("depositedEnergyHCALAct", &this->depositedEnergyHCALAct, "depositedEnergyHCALAct/F");
  //  this->GetTree()->Branch("depositedEnergyHCALPas", &this->depositedEnergyHCALPas, "depositedEnergyHCALPas/F");
  this->GetTree()->Branch("depositedEnergyWorld", &this->depositedEnergyWorld, "depositedEnergyWorld/F");
  //  this->GetTree()->Branch("depositedEnergyServices", &this->depositedEnergyServices, "depositedEnergyServices/F");
  this->GetTree()->Branch("depositedEnergyEcalGap", &this->depositedEnergyEcalGap, "depositedEnergyEcalGap/F");
  this->GetTree()->Branch("depositedEnergyEcalDet", &this->depositedEnergyEcalDet, "depositedEnergyEcalDet/F");
  //  this->GetTree()->Branch("depositedEnergySolenoid", &this->depositedEnergySolenoid, "depositedEnergySolenoid/F");
  this->GetTree()->Branch("depositedIonEnergyTotal", &this->depositedIonEnergyTotal, "depositedIonEnergyTotal/F");
  /*
  this->GetTree()->Branch("depositedIonEnergyECAL_f", &this->depositedIonEnergyECAL_f, "depositedIonEnergyECAL_f[3]/F");
  this->GetTree()->Branch("depositedIonEnergyECAL_r", &this->depositedIonEnergyECAL_r, "depositedIonEnergyECAL_r[3]/F");
  */
  this->GetTree()->Branch("depositedIonEnergyECAL_f", &this->depositedIonEnergyECAL_f, "depositedIonEnergyECAL_f/F");
  this->GetTree()->Branch("depositedIonEnergyECAL_r", &this->depositedIonEnergyECAL_r, "depositedIonEnergyECAL_r/F");
  //  this->GetTree()->Branch("depositedIonEnergyHCALAct", &this->depositedIonEnergyHCALAct, "depositedIonEnergyHCALAct/F");
  //  this->GetTree()->Branch("depositedIonEnergyHCALPas", &this->depositedIonEnergyHCALPas, "depositedIonEnergyHCALPas/F");
  this->GetTree()->Branch("depositedIonEnergyWorld", &this->depositedIonEnergyWorld, "depositedIonEnergyWorld/F");
  //  this->GetTree()->Branch("depositedIonEnergyServices", &this->depositedIonEnergyServices, "depositedIonEnergyServices/F");
  this->GetTree()->Branch("depositedIonEnergyEcalGap", &this->depositedIonEnergyEcalGap, "depositedIonEnergyEcalGap/F");
  this->GetTree()->Branch("depositedIonEnergyEcalDet", &this->depositedIonEnergyEcalDet, "depositedIonEnergyEcalDet/F");
  //  this->GetTree()->Branch("depositedIonEnergySolenoid", &this->depositedIonEnergySolenoid, "depositedIonEnergySolenoid/F");
  this->GetTree()->Branch("depositedElecEnergyTotal", &this->depositedElecEnergyTotal, "depositedElecEnergyTotal/F");
  this->GetTree()->Branch("depositedElecEnergyECAL_f", &this->depositedElecEnergyECAL_f, "depositedElecEnergyECAL_f[3]/F");
  this->GetTree()->Branch("depositedElecEnergyECAL_r", &this->depositedElecEnergyECAL_r, "depositedElecEnergyECAL_r[3]/F");
  //  this->GetTree()->Branch("depositedElecEnergyHCALAct", &this->depositedElecEnergyHCALAct, "depositedElecEnergyHCALAct/F");
  //  this->GetTree()->Branch("depositedElecEnergyHCALPas", &this->depositedElecEnergyHCALPas, "depositedElecEnergyHCALPas/F");
  this->GetTree()->Branch("depositedElecEnergyWorld", &this->depositedElecEnergyWorld, "depositedElecEnergyWorld/F");
  //  this->GetTree()->Branch("depositedElecEnergyServices", &this->depositedElecEnergyServices, "depositedElecEnergyServices/F");
  this->GetTree()->Branch("depositedElecEnergyEcalGap", &this->depositedElecEnergyEcalGap, "depositedElecEnergyEcalGap/F");
  this->GetTree()->Branch("depositedElecEnergyEcalDet", &this->depositedElecEnergyEcalDet, "depositedElecEnergyEcalDet/F");
  //  this->GetTree()->Branch("depositedElecEnergySolenoid", &this->depositedElecEnergySolenoid, "depositedElecEnergySolenoid/F");

  //single channels
  //  this->GetTree()->Branch("Edep_Tracker_layer", &this->Edep_Tracker_layer, "Edep_Tracker_layer[6]/F");




  //S and C in crystal bar
  //total generated in front and rear part
  this->GetTree()->Branch("ECAL_f_total_S", &this->ECAL_f_total_S, "ECAL_f_total_S/I");
  this->GetTree()->Branch("ECAL_f_total_C", &this->ECAL_f_total_C, "ECAL_f_total_C/I");
  this->GetTree()->Branch("ECAL_r_total_S", &this->ECAL_r_total_S, "ECAL_r_total_S/I");
  this->GetTree()->Branch("ECAL_r_total_C", &this->ECAL_r_total_C, "ECAL_r_total_C/I");  

  //total exiting in front and rear part
  this->GetTree()->Branch("ECAL_f_exit_S", &this->ECAL_f_exit_S, "ECAL_f_exit_S/I");
  this->GetTree()->Branch("ECAL_f_exit_C", &this->ECAL_f_exit_C, "ECAL_f_exit_C/I");
  this->GetTree()->Branch("ECAL_r_exit_S", &this->ECAL_r_exit_S, "ECAL_r_exit_S/I");
  this->GetTree()->Branch("ECAL_r_exit_C", &this->ECAL_r_exit_C, "ECAL_r_exit_C/I");  



  //detected in three detectors
  this->GetTree()->Branch("SDFdetected_f_S", &this->SDFdetected_f_S, "SDFdetected_f_S/I");
  this->GetTree()->Branch("SDFdetected_f_C", &this->SDFdetected_f_C, "SDFdetected_f_C/I");
  this->GetTree()->Branch("SDCdetected_r_S", &this->SDCdetected_r_S, "SDCdetected_r_S/I");
  this->GetTree()->Branch("SDCdetected_r_C", &this->SDCdetected_r_C, "SDCdetected_r_C/I");
  this->GetTree()->Branch("SDSdetected_r_S", &this->SDSdetected_r_S, "SDSdetected_r_S/I");
  this->GetTree()->Branch("SDSdetected_r_C", &this->SDSdetected_r_C, "SDSdetected_r_C/I");

  //detected photons 
  h_phot_lambda_SiPMF_f_Scin = new TH1F("h_phot_lambda_SiPMF_f_Scin", "", 1250, 0., 1250.);
  h_phot_lambda_SiPMF_f_Ceren = new TH1F("h_phot_lambda_SiPMF_f_Ceren", "", 1250, 0., 1250.);
  h_phot_lambda_SiPMC_r_Scin = new TH1F("h_phot_lambda_SiPMC_r_Scin", "", 1250, 0., 1250.);
  h_phot_lambda_SiPMC_r_Ceren = new TH1F("h_phot_lambda_SiPMC_r_Ceren", "", 1250, 0., 1250.);
  h_phot_lambda_SiPMS_r_Scin = new TH1F("h_phot_lambda_SiPMS_r_Scin", "", 1250, 0., 1250.);
  h_phot_lambda_SiPMS_r_Ceren = new TH1F("h_phot_lambda_SiPMS_r_Ceren", "", 1250, 0., 1250.);
  //generated photons
  h_phot_lambda_ECAL_f_produce_Scin = new TH1F("h_phot_lambda_ECAL_f_produce_Scin", "", 1250, 0., 1250.);
  h_phot_lambda_ECAL_r_produce_Scin = new TH1F("h_phot_lambda_ECAL_r_produce_Scin", "", 1250, 0., 1250.);
  h_phot_lambda_ECAL_f_produce_Ceren = new TH1F("h_phot_lambda_ECAL_f_produce_Ceren", "", 1250, 0., 1250.);
  h_phot_lambda_ECAL_r_produce_Ceren = new TH1F("h_phot_lambda_ECAL_r_produce_Ceren", "", 1250, 0., 1250.);
  h_phot_time_ECAL_f_produce_Scin = new TH1F("h_phot_time_ECAL_f_produce_Scin", "", 500, 0., 50.);
  h_phot_time_ECAL_r_produce_Scin = new TH1F("h_phot_time_ECAL_r_produce_Scin", "", 500, 0., 50.);
  h_phot_time_ECAL_f_produce_Ceren = new TH1F("h_phot_time_ECAL_f_produce_Ceren", "", 500, 0., 50.);
  h_phot_time_ECAL_r_produce_Ceren = new TH1F("h_phot_time_ECAL_r_produce_Ceren", "", 500, 0., 50.);
  // detected photons
  h_phot_time_SiPMF_Ceren =  new TH1F("h_phot_time_SiPMF_Ceren", "", 500, 0., 50.);
  h_phot_time_SiPMF_Scin =  new TH1F("h_phot_time_SiPMF_Scin", "", 500, 0., 50.);
  h_phot_time_SiPMC_Ceren =  new TH1F("h_phot_time_SiPMC_Ceren", "", 500, 0., 50.);
  h_phot_time_SiPMC_Scin =  new TH1F("h_phot_time_SiPMC_Scin", "", 500, 0., 50.);
  h_phot_time_SiPMS_Ceren =  new TH1F("h_phot_time_SiPMS_Ceren", "", 500, 0., 50.);
  h_phot_time_SiPMS_Scin =  new TH1F("h_phot_time_SiPMS_Scin", "", 500, 0., 50.);


  this->Clear();
}
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

CreateTree::~CreateTree()
{
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

int CreateTree::Fill()
{
//  this->GetTree()->Write(NULL, TObject::kOverwrite );
  return this->GetTree()->Fill();
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

bool CreateTree::Write(TFile *outfile)
{
  outfile->cd();
  ftree->Write();


  h_phot_lambda_ECAL_f_produce_Ceren->Write();
  h_phot_lambda_ECAL_f_produce_Scin->Write();
  h_phot_lambda_ECAL_r_produce_Ceren->Write();
  h_phot_lambda_ECAL_r_produce_Scin->Write();
  h_phot_time_ECAL_f_produce_Ceren->Write();
  h_phot_time_ECAL_f_produce_Scin->Write();
  h_phot_time_ECAL_r_produce_Ceren->Write();
  h_phot_time_ECAL_r_produce_Scin->Write();
  h_phot_time_SiPMF_Ceren->Write();
  h_phot_time_SiPMF_Scin->Write();
  h_phot_time_SiPMC_Ceren->Write();
  h_phot_time_SiPMC_Scin->Write();
  h_phot_time_SiPMS_Ceren->Write();
  h_phot_time_SiPMS_Scin->Write();
  h_phot_lambda_SiPMF_f_Ceren->Write();
  h_phot_lambda_SiPMF_f_Scin->Write();
  h_phot_lambda_SiPMC_r_Ceren->Write();
  h_phot_lambda_SiPMC_r_Scin->Write(); 
  h_phot_lambda_SiPMS_r_Ceren->Write();
  h_phot_lambda_SiPMS_r_Scin->Write(); 



  //h_photon_2D_produce_Ceren->Write();
  //h_photon_2D_receive_Ceren->Write();

  return true;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

void CreateTree::Clear()
{
  Event = 0;

  /*
  nTracksT1 = 0;
  nTracksT2 = 0;
  nTracksE1 = 0;
  nTracksE2 = 0;

  for (int iLayer = 0; iLayer < 6; iLayer++)
  {
    nTracksTRK[iLayer] = 0;
  }
  */

  depositedEnergyEscapeWorld = 0.;

  depositedEnergyTotal = 0.;
  /*
  for (int i = 0; i < 3; i++){
    depositedEnergyECAL_f[i] = 0.;
    depositedEnergyECAL_r[i] = 0.;
  }
*/
  depositedEnergyECAL_f = 0.;
  depositedEnergyECAL_r = 0.;
  //  depositedEnergyHCALAct = 0.;
  //  depositedEnergyHCALPas = 0.;
  depositedEnergyWorld = 0.;
  //  depositedEnergyServices = 0.;
  depositedEnergyEcalGap = 0.;
  depositedEnergyEcalDet = 0.;
  //  depositedEnergySolenoid = 0.;

  depositedIonEnergyTotal = 0.;
  depositedIonEnergyECAL_f=0;
  depositedIonEnergyECAL_r=0;
  /*
  for (int i = 0; i < 3; i++){
    depositedIonEnergyECAL_f[i] = 0.;
    depositedIonEnergyECAL_r[i] = 0.;
    }
*/
  //  depositedIonEnergyHCALAct = 0.;
  //  depositedIonEnergyHCALPas = 0.;
  depositedIonEnergyWorld = 0.;
  //  depositedIonEnergyServices = 0.;
  depositedIonEnergyEcalGap = 0.;
  depositedIonEnergyEcalDet = 0.;
  //  depositedIonEnergySolenoid = 0.;

  depositedElecEnergyTotal = 0.;
  for (int i = 0; i < 3; i++){
    depositedElecEnergyECAL_f[i] = 0.;
    depositedElecEnergyECAL_r[i] = 0.;
  }
  //  depositedElecEnergyHCALAct = 0.;
  //  depositedElecEnergyHCALPas = 0.;
  depositedElecEnergyWorld = 0.;
  //  depositedElecEnergyServices = 0.;
  depositedElecEnergyEcalGap = 0.;
  depositedElecEnergyEcalDet = 0.;
  //  depositedElecEnergySolenoid = 0.;

  ECAL_f_total_C = 0.;
  ECAL_r_total_S = 0.;
  ECAL_f_total_S = 0.;
  ECAL_r_total_C = 0.;
  ECAL_f_exit_C = 0.;
  ECAL_r_exit_S = 0.;
  ECAL_f_exit_S = 0.;
  ECAL_r_exit_C = 0.;

  SDFdetected_f_S = 0.;
  SDFdetected_f_C = 0.;
  SDCdetected_r_S = 0.;
  SDCdetected_r_C = 0.; 
  SDSdetected_r_S = 0.;
  SDSdetected_r_C = 0.;


  tot_phot_cer_HCAL = 0.;
  /*
  for (int iLayer = 0; iLayer < 6; iLayer++)
  {
    Edep_Tracker_layer[iLayer] = 0.;
  }
  */
  
  for (int i = 0; i < 3; ++i)
  {
    inputInitialPosition->at(i) = 0.;
    //primaryPosT1->at(i) = 0.;
    //primaryPosE1->at(i) = 0.;
  }
  
  
  for (int i = 0; i < 4; ++i)
  {
    inputMomentum->at(i) = 0.;
    //primaryMomT1->at(i) = 0.;
    //primaryMomE1->at(i) = 0.;
  }
  primaryID=0;
  /*
  for (int i = 0; i < 3; ++i)
  {
    inputInitialPosition->at(i) = 0.;
    primaryPosT1->at(i) = 0.;
    primaryPosE1->at(i) = 0.;
  }
  */
}
