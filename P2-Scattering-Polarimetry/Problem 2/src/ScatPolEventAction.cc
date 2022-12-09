
#include "ScatPolEventAction.hh"
#include "ScatPolRunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>
#include "G4ThreeVector.hh"

ScatPolEventAction::ScatPolEventAction()
{  
    runAct = (ScatPolRunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
}

void ScatPolEventAction :: addEdep_rod(G4double edep)
{
    fEdep_rod += edep/keV;
}

void ScatPolEventAction :: addEdep_det(G4double edep)
{
    fEdep_det += edep/keV;
}

std::tuple <G4bool,G4bool>  ScatPolEventAction :: comp_ang(G4int ang)
{
    return {scint_ang == -1, scint_ang == ang};
}

void ScatPolEventAction :: set_scint(G4int ang)
{
    scint_ang = ang;
}

ScatPolEventAction::~ScatPolEventAction()
{
}

void ScatPolEventAction::BeginOfEventAction(const G4Event* evt)
{
    fEdep_det = 0.;
    fEdep_rod = 0.;
    scint_ang = -1;
}


void ScatPolEventAction::EndOfEventAction(const G4Event* evt)
{
    G4cout << fEdep_rod << " det:" << fEdep_det << "angle:" << scint_ang << G4endl;
}  

