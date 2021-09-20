
#include "SD_sipmC.hh"
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


SD_sipmC::SD_sipmC(G4String name)
    : G4VSensitiveDetector(name)
{
}

SD_sipmC::~SD_sipmC() {}

void SD_sipmC::Initialize(G4HCofThisEvent *HCE)
{

}

G4bool
SD_sipmC::ProcessHits( G4Step*       theStep,
                                   G4TouchableHistory*  )
{
  G4cout << "SD_sipmC::ProcessHits" << G4endl;
    return true;
}
G4bool
SD_sipmC::ProcessHits_constStep( const G4Step* theStep, G4TouchableHistory* )
{
  G4cout << "SD_sipmC::ProcessHits_constStep" << G4endl;
  return true;
}



void SD_sipmC::EndOfEvent(G4HCofThisEvent*)
{

}

void SD_sipmC::clear() {}

void SD_sipmC::DrawAll() {}

void SD_sipmC::PrintAll() {}
