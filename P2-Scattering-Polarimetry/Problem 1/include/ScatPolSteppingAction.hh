
#ifndef ScatPolSteppingAction_h
#define ScatPolSteppingAction_h 1
#include <iostream>
#include <string>  
#include <fstream>
#include "G4UserSteppingAction.hh"
using namespace std;
class ScatPolDetectorConstruction;
class ScatPolEventAction;


class ScatPolSteppingAction : public G4UserSteppingAction
{
  public:
    ScatPolSteppingAction();
   ~ScatPolSteppingAction();

    void UserSteppingAction(const G4Step*);
    ofstream file;
    
  private:
    ScatPolDetectorConstruction* detector;
    ScatPolEventAction*          event;  
    G4SteppingManager*	   stpM;
};


#endif
