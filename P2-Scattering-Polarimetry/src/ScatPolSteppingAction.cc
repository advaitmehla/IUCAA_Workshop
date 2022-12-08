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
class G4VProcess;

class G4SteppingManager;


ScatPolSteppingAction::ScatPolSteppingAction()
{ 
  detector = (ScatPolDetectorConstruction*)G4RunManager::GetRunManager()->GetUserDetectorConstruction();
  event = (ScatPolEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
  // ofstream file;
  file.open("../data/out_pol_50.csv");
  file<<"Process;"<<"Scattered Energy;"<<"Scattered Direction"<<G4endl;
}


ScatPolSteppingAction::~ScatPolSteppingAction()
{ 
  file.close();
}


void ScatPolSteppingAction::UserSteppingAction(const G4Step* aStep)
{

  G4int trackID = aStep->GetTrack()->GetTrackID();
  if(trackID == 1){
    const G4VProcess* proc = (aStep->GetPreStepPoint()->GetProcessDefinedStep());

    if (proc!=0)
    {
      G4String procname = proc->GetProcessName() ;
      if (procname == "compt" or procname == "Rayl")
      {
        G4double escat = aStep->GetPostStepPoint()->GetTotalEnergy();
        G4ThreeVector pscat = aStep->GetPostStepPoint()->GetMomentumDirection();
        file << procname << ";"<< escat/keV <<";"<<pscat<<G4endl;
      }
    }

  }
    

  
    // Get particle name, process name,prestepvolume name,trackid, post step energy, and post step momentum for aStep
   
    // If process is compt or Rayl for primary gamma (what would the trackid?), record the 
    // scattered photon energy and momentum. 

}

