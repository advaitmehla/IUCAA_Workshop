#ifndef ScatPolEventAction_h
#define ScatPolEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "ScatPolRunAction.hh"
#include <tuple>

class ScatPolRunAction;


class ScatPolEventAction : public G4UserEventAction
{
 public:
   ScatPolEventAction();
  ~ScatPolEventAction();

 public:
   void  BeginOfEventAction(const G4Event*);
   void  EndOfEventAction(const G4Event*);
   void addEdep_rod(G4double edep);
   void addEdep_det(G4double edep);
   G4double fEdep_rod = 0;
   G4double fEdep_det = 0;
   G4double scint_ang = -1;
   std::tuple <G4bool,G4bool> comp_ang(G4int);
   void set_scint(G4int);

    
 private:
   ScatPolRunAction*  runAct;
};


#endif
