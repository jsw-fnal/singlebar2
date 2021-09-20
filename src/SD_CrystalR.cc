
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

void SD_CrystalR::Initialize(G4HCofThisEvent *HCE)
{

}

G4bool
SD_CrystalR::ProcessHits( G4Step*       theStep,
                                   G4TouchableHistory*  )
{
  G4cout << "SD_CrystalR::ProcessHits" << G4endl;
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
