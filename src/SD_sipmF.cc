
#include "SD_sipmF.hh"
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

SD_sipmF::SD_sipmF(G4String name)
    : G4VSensitiveDetector(name)
{
}

SD_sipmF::~SD_sipmF() {}

void SD_sipmF::Initialize(G4HCofThisEvent *HCE)
{

}

G4bool
SD_sipmF::ProcessHits( G4Step*       theStep,
                                   G4TouchableHistory*  )
{
  G4Track *theTrack = theStep->GetTrack();
  G4ParticleDefinition *particleType = theTrack->GetDefinition();

  if (particleType != G4OpticalPhoton::OpticalPhotonDefinition()) return true;

  // we do no distunguish between C and S photons in the front SiPM
  float photWL = MyMaterials::fromEvToNm(theTrack->GetTotalEnergy() / eV);
  //only consider 300 to 1000nm
  if (photWL > 1000 || photWL < 300) {
    theTrack->SetTrackStatus(fKillTrackAndSecondaries);
    return true;
  }

  // count some stuff

 
    
  // OOPS!  don't kill track if particle interacts on the way into the front xtal!!!
  //G4cout  << "SD_simpF::ProcessHits  "/* << thePrePVName << " : " << thePostPVName*/ << endl;

  theTrack->SetTrackStatus(fKillTrackAndSecondaries);

  return true;
}
G4bool
SD_sipmF::ProcessHits_constStep( const G4Step* theStep, G4TouchableHistory* )
{



  return  false;
}



void SD_sipmF::EndOfEvent(G4HCofThisEvent*)
{

}

void SD_sipmF::clear() {}

void SD_sipmF::DrawAll() {}

void SD_sipmF::PrintAll() {}
