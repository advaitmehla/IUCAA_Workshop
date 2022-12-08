#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

class HGCAL_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        HGCAL_DetectorConstruction(){};
        ~HGCAL_DetectorConstruction(){};
        G4VPhysicalVolume* Construct();
        virtual void ConstructSDandField();
        G4LogicalVolume* Si_pix_LV;
};