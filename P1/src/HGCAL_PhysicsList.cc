#include "HGCAL_PhysicsList.hh"
#include "G4EmLivermorePolarizedPhysics.hh"

HGCAL_PhysicsList::HGCAL_PhysicsList()
    : G4VModularPhysicsList(), fHGCAL_PhysicsList(0)
{
    // Register a new physic list to the physics constructor
	fHGCAL_PhysicsList = new G4EmLivermorePolarizedPhysics();
    RegisterPhysics(fHGCAL_PhysicsList);
}

//***********************************************/

HGCAL_PhysicsList::~HGCAL_PhysicsList()
{
	delete fHGCAL_PhysicsList;
}

//***********************************************/

void HGCAL_PhysicsList::ConstructParticle()
{
	fHGCAL_PhysicsList->ConstructParticle();
}

//***********************************************/

void HGCAL_PhysicsList::ConstructProcess()
{
    AddTransportation();
    fHGCAL_PhysicsList->ConstructProcess();
}

//***********************************************/