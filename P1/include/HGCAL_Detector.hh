#include "G4VUserDetectorConstruction.hh"

class HGCAL_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        HGCAL_DetectorConstruction(){};
        ~HGCAL_DetectorConstruction(){};
        G4VPhysicalVolume* Construct();
};