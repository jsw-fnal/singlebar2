
#include "SD_sipmS.hh"
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

SD_sipmS::SD_sipmS(G4String name)
    : G4VSensitiveDetector(name)
{
}

SD_sipmS::~SD_sipmS() {}

void SD_sipmS::Initialize(G4HCofThisEvent *HCE)
{

}

G4bool
SD_sipmS::ProcessHits( G4Step*       theStep,
                                   G4TouchableHistory*  )
{
  //G4cout << "SD_sipmS::ProcessHits" << G4endl;
    return true;
}
G4bool
SD_sipmS::ProcessHits_constStep( const G4Step* theStep, G4TouchableHistory* )
{
  G4cout << "SD_sipmS::ProcessHits_constStep" << G4endl;
  return true;
}



void SD_sipmS::EndOfEvent(G4HCofThisEvent*)
{

}

void SD_sipmS::clear() {}

void SD_sipmS::DrawAll() {}

void SD_sipmS::PrintAll() {}
