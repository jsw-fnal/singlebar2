#include "SteppingAction.hh"
#include "TrackingAction.hh"
//#include "DR_PMTSD.hh"
#include "DetectorConstruction.hh"
#include "TString.h"
#include "TRandom3.h"
//#include "TCint.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SteppingManager.hh"
#include <time.h>

#include "G4EventManager.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"

#include <iostream>
#include <fstream>
#include <vector>
#include "TTree.h"

//long int CreateSeed();

using namespace std;
using namespace CLHEP;
/*
SteppingAction::SteppingAction (const string& configFileName)
{
  //---------------------------------------
  //------------- Parameters --------------
  //---------------------------------------
  
  ConfigFile config (configFileName) ;

  config.readInto(core_material, "core_material"); 

  if (core_material == 0)
  {
	  config.readInto(toy_ly,	"toy_ly");
	  config.readInto(toy_decay,	"toy_decay");
	  config.readInto(toy_rise,	"toy_rise");
  }
  

}*/

int to_int(string name)
{
  int Result; // int which will contain the result
  stringstream convert(name);
  string dummy;
  convert >> dummy;
  convert >> Result;
  return Result;
}

//---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

SteppingAction::SteppingAction(DetectorConstruction *detectorConstruction,
                               const G4int &scint, const G4int &cher) : fDetectorConstruction(detectorConstruction),
                                                                        propagateScintillation(scint),
                                                                        propagateCerenkov(cher)
{
  maxtracklength = 500000. * mm;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

SteppingAction::~SteppingAction()
{
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

void SteppingAction::UserSteppingAction(const G4Step *theStep)
{
  //G4cout << "UserSteppingAction::ProcessHits" << G4endl;

  // this code does very little now 
  // it is being replaced with sensitive detector code
  // clean me up!  is it useful to have this to cut on photon lambda?
  // or not? then delete all code here
  G4Track *theTrack = theStep->GetTrack();

  G4ParticleDefinition *particleType = theTrack->GetDefinition();

  G4StepPoint *thePrePoint = theStep->GetPreStepPoint();
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

  G4int nStep = theTrack->GetCurrentStepNumber();
  G4int TrPDGid = theTrack->GetDefinition()->GetPDGEncoding();

  //        cout << " step length = " << theStep->GetStepLength() << endl;
  //-------------

  // get position
  G4double global_x = thePrePosition.x() / mm;
  G4double global_y = thePrePosition.y() / mm;
  G4double global_z = thePrePosition.z() / mm;

  G4double energy = theStep->GetTotalEnergyDeposit();
  G4double energyIon = energy - theStep->GetNonIonizingEnergyDeposit();
  G4double energyElec = 0;
  if (abs(TrPDGid) == 11) energyElec = energyIon;

  // global energy deposits should be very similar to sum of xtal deposits
  // in singlebar/module case
  CreateTree::Instance()->depositedEnergyTotal += energy / GeV;
  CreateTree::Instance()->depositedIonEnergyTotal += energyIon / GeV;
  CreateTree::Instance()->depositedElecEnergyTotal += energyElec / GeV;

  bool outworld = ((theStep->GetPostStepPoint())->GetStepStatus()) == fWorldBoundary;
  if (outworld)
  {
    CreateTree::Instance()->depositedEnergyEscapeWorld += (theStep->GetPostStepPoint())->GetKineticEnergy() / GeV;
  }
  ///
  if (particleType != G4OpticalPhoton::OpticalPhotonDefinition()) return;
  //if optics
  G4String processName="Scintillation";  // protect aginst optical photon gun option w/ no CreatorProcess
  if (theTrack->GetCreatorProcess()) processName = theTrack->GetCreatorProcess()->GetProcessName();

  float photWL = MyMaterials::fromEvToNm(theTrack->GetTotalEnergy() / eV);
  if (photWL > 1000 || photWL < 300) {
    theTrack->SetTrackStatus(fKillTrackAndSecondaries);
    //G4cout << "Photon killed in user stepping action" << G4endl;
    return;
  }

  if (!propagateCerenkov && (processName == "Cerenkov"))
    theTrack->SetTrackStatus(fKillTrackAndSecondaries);
  
  if (!propagateScintillation && (processName == "Scintillation"))
    theTrack->SetTrackStatus(fKillTrackAndSecondaries);


  return;

}
