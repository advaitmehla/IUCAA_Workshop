#include "HGCAL_ActionInit.hh"
#include "HGCAL_ParticleGun.hh"

void HGCAL_ActionInitialization::Build() const
{
    SetUserAction(new HGCAL_PrimaryGeneratorAction());
}