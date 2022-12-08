#include "HGCAL_ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomDirection.hh"
#include "G4Proton.hh"
HGCAL_PrimaryGeneratorAction :: HGCAL_PrimaryGeneratorAction()
{
    int num = 1;
    fParticleGun = new G4ParticleGun(num);
    // G4ParticleTable *ptable = G4ParticleTable::GetParticleTable();
    // G4ParticleDefinition *particle = ptable->FindParticle("proton");
    G4ParticleDefinition *particle = G4Proton::Definition();
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    fParticleGun->SetParticleEnergy(1*GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(55*cm,-85*cm,30.*cm));
}

void HGCAL_PrimaryGeneratorAction :: GeneratePrimaries(G4Event* evt)
{
    fParticleGun->GeneratePrimaryVertex(evt);
}

HGCAL_PrimaryGeneratorAction :: ~HGCAL_PrimaryGeneratorAction()
{
    delete fParticleGun;
}
