#include "HGCAL_Detector.hh"
// Necessary geometry classes
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// Includes for material and unit definitions
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "HGCAL_SensitiveDetector.hh"
// Geometry shape header files
#include "G4Box.hh"

G4VPhysicalVolume* HGCAL_DetectorConstruction::Construct()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* air = nistManager->FindOrBuildMaterial("G4_Galactic");
    G4double wl = 5.*m;
    G4Box* worldS = new G4Box("world", wl, wl, wl);
    G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, air, "world");
    G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), "world", worldLV, 0, false, 0, true);

    G4Material* Cu = nistManager->FindOrBuildMaterial("G4_Cu");
    G4Material* W = nistManager->FindOrBuildMaterial("G4_W");
    G4Material* Pb = nistManager->FindOrBuildMaterial("G4_Pb");
    G4Material* Si = nistManager->FindOrBuildMaterial("G4_Si");
    G4Material* CuW = new G4Material("CuW", 14.979*g/cm3, 2);
    CuW->AddMaterial(Cu, 0.25);
    CuW->AddMaterial(W, 0.75);

    G4double s = 302/2.*cm;
    G4double h = 3.0345/2.*cm;
    G4Box* detbox = new G4Box("detbox", s, s, h);
    G4LogicalVolume* detboxLV = new G4LogicalVolume(detbox, air, "detbox");

    G4Box* Si_slice = new G4Box("Si_slice",s,s,0.3/2.*mm);
    G4Box* Cu_slice = new G4Box("Cu_slice",s,s,6.05/2.*mm);
    G4Box* CuW_slice = new G4Box("CuW_slice",s,s,1.4/2.*mm);
    G4Box* Pb_slice = new G4Box("Pb_slice",s,s,4.97/2.*mm);

    G4LogicalVolume* Si_LV = new G4LogicalVolume(Si_slice, Si, "Si_slice");
    G4LogicalVolume* Cu_LV = new G4LogicalVolume(Cu_slice, Cu, "Cu_slice");
    G4LogicalVolume* CuW_LV = new G4LogicalVolume(CuW_slice, CuW, "CuW_slice");
    G4LogicalVolume* Pb_LV = new G4LogicalVolume(Pb_slice, Pb, "Pb_slice");
    G4double s2 = 30*cm/2;
    G4Box* Si_pix = new G4Box("Si_pix",s2,s2,0.3/2.*mm);
    Si_pix_LV = new G4LogicalVolume(Si_pix, Si, "Si_pixLV");
    G4VPhysicalVolume* Si_pix_PVs[100];
    G4int pcopy = 0;
    for (int i =0; i<10; i++)
    {
        for (int j = 0; j<10; j++)
        {
            Si_pix_PVs[pcopy] = new G4PVPlacement(0, G4ThreeVector(-s + s2 + 2*i*s2,-s + s2 + 2*j*s2,0), Si_pix_LV, "Si_pix", Si_LV, true, pcopy, true);
            pcopy++;
        }
    }


    G4VPhysicalVolume* Si_PV[2];
    G4VPhysicalVolume* CuW_PV[2];
    G4double d = -h;
    Si_PV[0] = new G4PVPlacement(0, G4ThreeVector(0,0,d + 0.3/2.*mm), Si_LV, "SiPV", detboxLV, true, 0, true);
    d += 0.3*mm;
    CuW_PV[0] = new G4PVPlacement(0, G4ThreeVector(0,0,d + 1.4/2.*mm), CuW_LV, "CuWPV", detboxLV, true, 0, true);
    d += 1.4*mm;
    G4VPhysicalVolume* Cu_PV = new G4PVPlacement(0, G4ThreeVector(0,0,d + 6.05/2.*mm), Cu_LV, "CuPV", detboxLV, false, 0, true);
    d += 6.05*mm;
    CuW_PV[1] = new G4PVPlacement(0, G4ThreeVector(0,0,d + 1.4/2.*mm), CuW_LV, "CuWPV2", detboxLV, true, 0, true);
    d += 1.4*mm;
    Si_PV[1] = new G4PVPlacement(0, G4ThreeVector(0,0,d + 0.3/2.*mm), Si_LV, "SiPV", detboxLV, true, 1, true);
    d += 0.3*mm;
    G4VPhysicalVolume* Pb_PV = new G4PVPlacement(0, G4ThreeVector(0,0,d + 4.97/2.*mm), Pb_LV, "PbPV", detboxLV, false, 0, true);

    G4VPhysicalVolume* detboxPVs[26];
    for (int i = 0; i<26; i++)
    {
        detboxPVs[i] = new G4PVPlacement(0, G4ThreeVector(0,0,4.5*m - 2*h*i), "detbox", detboxLV, worldPV, true, i, true);
    }
        



    return worldPV;
}


void HGCAL_DetectorConstruction::ConstructSDandField()
{
    HGCAL_SensitiveDetector* sens_Si = new HGCAL_SensitiveDetector("sens_Si");
    G4SDManager *sdman = G4SDManager::GetSDMpointer();
    sdman->AddNewDetector(sens_Si); 
    // Si_pix_LV->SetSensitiveDetector(sens_Si);
    SetSensitiveDetector("Si_pixLV", sens_Si);
}
