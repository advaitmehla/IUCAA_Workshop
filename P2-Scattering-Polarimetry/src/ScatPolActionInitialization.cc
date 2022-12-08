#include "ScatPolActionInitialization.hh"  
#include "ScatPolPrimaryGeneratorAction.hh"
#include "ScatPolRunAction.hh"
#include "ScatPolEventAction.hh"
#include "ScatPolSteppingAction.hh"

ScatPolActionInitialization::ScatPolActionInitialization()
    : G4VUserActionInitialization()
{
}

//***********************************************/

ScatPolActionInitialization::~ScatPolActionInitialization()
{
	
}

//***********************************************/

void ScatPolActionInitialization::Build() const
{

    // Set PrimaryGenerator action 
    SetUserAction(new ScatPolPrimaryGeneratorAction());
    SetUserAction(new ScatPolEventAction());
    SetUserAction(new ScatPolSteppingAction());
    SetUserAction(new ScatPolRunAction());


    // Set Run action, Event action stepping action

}
