#include "HGCAL_SensitiveDetector.hh"
using namespace std;
#include "G4SystemOfUnits.hh"
HGCAL_SensitiveDetector::HGCAL_SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    // fEventAction = new HGCAL_EventAction();
}

G4bool HGCAL_SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
    G4double edep = aStep->GetTotalEnergyDeposit();
    if (edep>0)
    {
        G4StepPoint* pt = aStep->GetPreStepPoint();
        G4ThreeVector pos = pt->GetPosition();
        G4cout <<"Particle position: " << pos << G4endl;
        G4String cp = pt->GetTouchable()->GetVolume()->GetName();
        G4ThreeVector detpos = pt->GetTouchable()->GetVolume()->GetObjectTranslation();
        G4cout <<"Detector position: " << detpos << G4endl;
    }

    return true;
}