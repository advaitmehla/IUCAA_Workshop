#include "G4VUserActionInitialization.hh"
class HGCAL_ActionInitialization : public G4VUserActionInitialization
{
    public:
        HGCAL_ActionInitialization(){};
        virtual ~HGCAL_ActionInitialization(){};
        // virtual void BuildForMaster() const{};
        virtual void Build() const;
};