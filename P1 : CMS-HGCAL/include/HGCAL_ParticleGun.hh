#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class HGCAL_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        G4ParticleGun *fParticleGun;
        HGCAL_PrimaryGeneratorAction();
        ~HGCAL_PrimaryGeneratorAction();
        void GeneratePrimaries(G4Event* evt);
};