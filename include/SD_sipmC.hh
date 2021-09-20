#ifndef SD_sipmC_h
#define SD_sipmC_h

#include "SD_sipmC.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class SD_sipmC : public G4VSensitiveDetector
{
public:

  SD_sipmC( G4String name );
  ~SD_sipmC();


  void Initialize( G4HCofThisEvent* HCE );
  G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  // A version of processHits that keeps aStep constant
  G4bool ProcessHits_constStep( const G4Step*       aStep,
                                G4TouchableHistory* ROhist );

  void EndOfEvent( G4HCofThisEvent* HCE );

  void clear();
  void DrawAll();
  void PrintAll();

private:



};

#endif
