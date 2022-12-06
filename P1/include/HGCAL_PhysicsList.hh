#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;

class HGCAL_PhysicsList: public G4VModularPhysicsList
{
	public:

		HGCAL_PhysicsList(){};
		virtual ~HGCAL_PhysicsList(){};

		// virtual void ConstructParticle();
		// virtual void ConstructProcess();

	private:
		// G4VPhysicsConstructor* fHGCAL_PhysicsList;  // Define the physics constructor globally

};