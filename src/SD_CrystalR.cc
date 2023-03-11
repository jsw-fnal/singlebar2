
#include "SD_CrystalR.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"
#include "CreateTree.hh"

#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

SD_CrystalR::SD_CrystalR(G4String name)
    : G4VSensitiveDetector(name)
{
}

SD_CrystalR::~SD_CrystalR() {}

void SD_CrystalR::Initialize(G4HCofThisEvent *HCE){
}

G4bool
SD_CrystalR::ProcessHits( G4Step*       theStep,
                                   G4TouchableHistory*  )
{
  //G4cout << "SD_CrystalR::ProcessHits" << G4endl;
  G4Track *theTrack = theStep->GetTrack();
  G4ParticleDefinition *particleType = theTrack->GetDefinition();
  G4StepPoint *thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume *thePostPV = thePostPoint->GetPhysicalVolume();

  /*
  G4StepPoint *thePrePoint = theStep->GetPreStepPoint();
  const G4ThreeVector &thePrePosition = thePrePoint->GetPosition();
  G4VPhysicalVolume *thePrePV = thePrePoint->GetPhysicalVolume();
  G4String thePrePVName = "";
  */
  //if (thePrePV)
  //  thePrePVName = thePrePV->GetName();
  G4String thePostPVName = "";
  if (thePostPV)
    thePostPVName = thePostPV->GetName();


  G4int nStep = theTrack->GetCurrentStepNumber();
  //G4int TrPDGid = theTrack->GetDefinition()->GetPDGEncoding();

  // get position
  /*
  G4double global_x = thePrePosition.x() / mm;
  G4double global_y = thePrePosition.y() / mm;
  G4double global_z = thePrePosition.z() / mm;
  */

  G4double energy = theStep->GetTotalEnergyDeposit();
  G4double energyIon = energy - theStep->GetNonIonizingEnergyDeposit();
  //G4double energyElec = 0;
  //if (abs(TrPDGid) == 11) energyElec = energyIon; 

  CreateTree::Instance()->depositedEnergyECAL_r+=energy / GeV;
  CreateTree::Instance()->depositedIonEnergyECAL_r+=energyIon / GeV;


 //------------- optical photon -------------
  if (particleType == G4OpticalPhoton::OpticalPhotonDefinition()) {
    //if optics
    G4String processName="Scintillation";  // protect aginst optical photon gun option w/ no CreatorProcess
    if (theTrack->GetCreatorProcess()) processName = theTrack->GetCreatorProcess()->GetProcessName();

    float photWL = MyMaterials::fromEvToNm(theTrack->GetTotalEnergy() / eV);

    //only consider 300 to 1000nm
    if (photWL > 1000 || photWL < 300) {
      theTrack->SetTrackStatus(fKillTrackAndSecondaries);
      //G4cout << "Photon killed in SD" << G4endl;
      return true;
    }

    bool isCher = (processName == "Cerenkov");
    bool isScin = (processName == "Scintillation");

    // photon production info for test
    //static int countc=0;
    //static int counts=0;

    if (nStep == 1) {
      G4StepPoint *thePrePoint = theStep->GetPreStepPoint();
      G4double gTime = thePrePoint->GetGlobalTime();
      if (isScin) {
	CreateTree::Instance()->ECAL_r_total_S += 1;
	CreateTree::Instance()->h_phot_lambda_ECAL_r_produce_Scin->Fill(photWL);
	CreateTree::Instance()->h_phot_time_ECAL_r_produce_Scin->Fill(gTime);
	/*
	if (counts<20) {
	  G4ThreeVector pol=theTrack->GetPolarization();
	  G4ThreeVector mom=theTrack->GetMomentumDirection();
	  if (mom.y()>0.9){
	  G4cout << "Momentum S " << mom.x() << " " << mom.y() << " " << mom.z() << " " << theTrack->GetTotalEnergy() << G4endl;	  
	  G4cout << "Polarization S " << pol.x() << " " << pol.y() << " " << pol.z() << G4endl;
	  counts+=1;
	  }
	}
	*/

      }
      else if (isCher) {
	CreateTree::Instance()->ECAL_r_total_C += 1;
	CreateTree::Instance()->h_phot_lambda_ECAL_r_produce_Ceren->Fill(photWL);
	CreateTree::Instance()->h_phot_time_ECAL_r_produce_Ceren->Fill(gTime);
	/*
	if (countc<20) {
	  G4ThreeVector pol=theTrack->GetPolarization();
	  G4ThreeVector mom=theTrack->GetMomentumDirection();
	  if (mom.y()>0.9){
	    G4cout << "Momentum C " << mom.x() << " " << mom.y() << " " << mom.z() << " " << theTrack->GetTotalEnergy() << G4endl;
	    G4cout << "Polarization C " << pol.x() << " " << pol.y() << " " << pol.z() << G4endl;
	    countc+=1;
	  }
	}
	*/
      }
    }

    // is photon leaving rear face of xtal?
    if (thePostPVName.contains("matchBox") || thePostPVName.contains("baffle")){ 
      if (isScin) CreateTree::Instance()->ECAL_r_exit_S += 1;
      else if (isCher) CreateTree::Instance()->ECAL_r_exit_C += 1;
      // kill track at baffle for now, no reflection
      if (thePostPVName.contains("baffle")) theTrack->SetTrackStatus(fKillTrackAndSecondaries);
    }

  }
  return true;
}
G4bool
SD_CrystalR::ProcessHits_constStep( const G4Step* theStep, G4TouchableHistory* )
{
  G4cout << "SD_CrystalR::ProcessHits_constStep" << G4endl;
  return true;
}



void SD_CrystalR::EndOfEvent(G4HCofThisEvent*)
{

}

void SD_CrystalR::clear() {}

void SD_CrystalR::DrawAll() {}

void SD_CrystalR::PrintAll() {}
