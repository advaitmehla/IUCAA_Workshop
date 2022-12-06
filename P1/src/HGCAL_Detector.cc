#include "HGCAL_Detector.hh"
// Necessary geometry classes
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// Includes for material and unit definitions
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

// Geometry shape header files
#include "G4Box.hh"

G4VPhysicalVolume* HGCAL_DetectorConstruction::Construct()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* air = nistManager->FindOrBuildMaterial("G4_Air");
    G4double wl = 2.*m;
    G4Box* worldS = new G4Box("world", wl, wl, wl);
    G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, air, "world");
    G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), "world", worldLV, 0, false, 0, true);
    return worldPV;
}



