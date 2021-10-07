
#include "SD_CrystalF.hh"
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

SD_CrystalF::SD_CrystalF(G4String name)
    : G4VSensitiveDetector(name)
{
}

SD_CrystalF::~SD_CrystalF() {}

void SD_CrystalF::Initialize(G4HCofThisEvent *HCE)
{

}

G4bool
SD_CrystalF::ProcessHits( G4Step*       theStep,
                                   G4TouchableHistory*  )
{   
  G4Track *theTrack = theStep->GetTrack();
  G4ParticleDefinition *particleType = theTrack->GetDefinition();
  G4StepPoint *thePrePoint = theStep->GetPreStepPoint();  /// not needed!!!
  G4StepPoint *thePostPoint = theStep->GetPostStepPoint();
  const G4ThreeVector &thePrePosition = thePrePoint->GetPosition();
  G4VPhysicalVolume *thePrePV = thePrePoint->GetPhysicalVolume();
  G4VPhysicalVolume *thePostPV = thePostPoint->GetPhysicalVolume();
  G4String thePrePVName = "";
  if (thePrePV)
    thePrePVName = thePrePV->GetName();
  G4String thePostPVName = "";
  if (thePostPV)
    thePostPVName = thePostPV->GetName();

  //cout  << "SD_CrystalF::ProcessHits  " << thePrePVName << " : " << thePostPVName << endl;

  G4int nStep = theTrack->GetCurrentStepNumber();
  G4int TrPDGid = theTrack->GetDefinition()->GetPDGEncoding();

  // get position
  /*
  G4double global_x = thePrePosition.x() / mm;
  G4double global_y = thePrePosition.y() / mm;
  G4double global_z = thePrePosition.z() / mm;
  */

  G4double energy = theStep->GetTotalEnergyDeposit();
  G4double energyIon = energy - theStep->GetNonIonizingEnergyDeposit();
  G4double energyElec = 0;
  if (abs(TrPDGid) == 11) energyElec = energyIon; 

  CreateTree::Instance()->depositedEnergyECAL_f+=energy;
  CreateTree::Instance()->depositedIonEnergyECAL_f+=energyIon;

  //------------- optical photon -------------
  if (particleType == G4OpticalPhoton::OpticalPhotonDefinition()) {
    //if optics
    G4String processName = theTrack->GetCreatorProcess()->GetProcessName();
    float photWL = MyMaterials::fromEvToNm(theTrack->GetTotalEnergy() / eV);
    
    //only consider 300 to 1000nm:  probably not needed if it's already killed in userstepping action
    if (photWL > 1000 || photWL < 300) {
      theTrack->SetTrackStatus(fKillTrackAndSecondaries);
      return true;
    }
    
    bool isCher = (processName == "Cerenkov");
    bool isScin = (processName == "Scintillation");

    // photon production info
    if (nStep == 1) {
      if (isScin) CreateTree::Instance()->ECAL_f_total_S += 1;
      else if (isCher) CreateTree::Instance()->ECAL_f_total_C += 1;
    }

    // is photon leaving front face of xtal?
    if (thePostPVName.contains("matchBox") || thePostPVName.contains("baffle")){ 
      if (isScin) CreateTree::Instance()->ECAL_f_exit_S += 1;
      else if (isCher) CreateTree::Instance()->ECAL_f_exit_C += 1;
      // kill track at baffle for now
      if (thePostPVName.contains("baffle")) theTrack->SetTrackStatus(fKillTrackAndSecondaries);
    }

  }
  return true;
}


G4bool
SD_CrystalF::ProcessHits_constStep( const G4Step* theStep, G4TouchableHistory* )
{
  G4cout << "SD_CrystalF::ProcessHits_constStep" << G4endl;
  return true;
}



void SD_CrystalF::EndOfEvent(G4HCofThisEvent*)
{

}

void SD_CrystalF::clear() {}

void SD_CrystalF::DrawAll() {}

void SD_CrystalF::PrintAll() {}
