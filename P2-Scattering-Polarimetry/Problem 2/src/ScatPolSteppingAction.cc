#include "ScatPolSteppingAction.hh"

#include "ScatPolDetectorConstruction.hh"
#include "ScatPolEventAction.hh"

#include "G4SteppingManager.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <iostream>
#include <string>  

#include "G4String.hh"
#include "G4ThreeVector.hh"
#include "ScatPolEventAction.hh"
class G4VProcess;

class G4SteppingManager;


ScatPolSteppingAction::ScatPolSteppingAction()
{ 
  detector = (ScatPolDetectorConstruction*)G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  event = (ScatPolEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
  // ofstream file;
  // file.open("../data/out_pol_50.csv");
  // file<<"Process;"<<"Scattered Energy;"<<"Scattered Direction"<<G4endl;
}


ScatPolSteppingAction::~ScatPolSteppingAction()
{ 
  // file.close();
}


void ScatPolSteppingAction::UserSteppingAction(const G4Step* aStep)
{

  G4int trackID = aStep->GetTrack()->GetTotalEnergy();
  
  G4String LV_name = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName();
  if (LV_name == "rod_LV")
  {
    G4double rod_edep = aStep->GetTotalEnergyDeposit();
    event->addEdep_rod(rod_edep);
  }
  if (LV_name == "detboxLV")
  {
    G4double det_edep = aStep->GetTotalEnergyDeposit();
    event->addEdep_det(det_edep);
    G4int ang = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo();
    G4bool isminus1, is_equal;
    std::tuple <G4bool,G4bool> bools;
    bools = event -> comp_ang(ang);
    isminus1 = get<0>(bools);
    is_equal = get<1>(bools);
    if (isminus1)
    {
      event->set_scint(ang);
    }
    else
    {
      if (!is_equal)
      {
        aStep->GetTrack()->SetTrackStatus(fStopAndKill);
      }
    }
  }
  

}

