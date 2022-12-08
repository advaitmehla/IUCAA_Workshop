#include "G4VSensitiveDetector.hh"
#include <iostream>
class HGCAL_SensitiveDetector : public G4VSensitiveDetector
{
    public:
        HGCAL_SensitiveDetector(G4String);
        ~HGCAL_SensitiveDetector(){};
    private:
        virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
        // void Initialize(G4HCofThisEvent*)
        // {
        // //Initialize required data members
        // }
        // void EndOfEvent(G4HCofThisEvent*)
        // {
        // //Things to do at the end of event
        // }
};