#include "ScatPolDetectorConstruction.hh"

#include "G4SystemOfUnits.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "G4AssemblyVolume.hh"
#include "G4AssemblyTriplet.hh"

#include "G4VSolid.hh"


#include <iostream>
#include <fstream>
using namespace std;

ScatPolDetectorConstruction::ScatPolDetectorConstruction()
{
}

ScatPolDetectorConstruction::~ScatPolDetectorConstruction()
{
}

//DETECTOR CONSTRUCTION

G4VPhysicalVolume* ScatPolDetectorConstruction::Construct()
{

// Use this for material filling world volume - G4_Galactic

  G4NistManager*  nist = G4NistManager::Instance();
  G4Material* galacticMat = nist->FindOrBuildMaterial("G4_Galactic");

// Define world volume large enough to accomodate the detector    

  G4double world_x,world_y,world_z;
  world_x=100.,world_y=100.,world_z=100.;

  G4Box* solidWorld = new G4Box("Polarimeter_box",world_x,world_y,world_z);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,galacticMat,"Polarimeter_log",0,0,0);
  G4VisAttributes* logicWorld_VisAtt = new G4VisAttributes(false);
  logicWorld->SetVisAttributes(logicWorld_VisAtt);
  G4VPhysicalVolume* physiWorld = new G4PVPlacement(0,G4ThreeVector(),
                                      logicWorld,"World",0,false,0,true);

  // Plastic scintillator material definition: Vinyl Toluene. 
  G4Material* vintol = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4VSolid* rods = new G4Tubs("rod",0,10*mm,25*mm,0.,2*M_PI*rad);
  G4LogicalVolume* rod_LV = new G4LogicalVolume(rods,vintol,"rod_LV");
  G4VPhysicalVolume* rod_PV = new G4PVPlacement(0,G4ThreeVector(0,0,0),rod_LV,"rod_PV",logicWorld,false,0,true);
  G4VisAttributes* rod_VisAtt = new G4VisAttributes(G4Color(1,0,0));
  rod_LV->SetVisAttributes(rod_VisAtt);

  G4Material* Cs = nist->FindOrBuildMaterial("G4_Cs");
  G4Material* I = nist->FindOrBuildMaterial("G4_I");
  G4Material* Tl = nist->FindOrBuildMaterial("G4_Tl");
  G4Material* csitl = new G4Material('CsITl',4.51*g/cm3,3);
  csitl->AddMaterial(Cs,0.510549);
  csitl->AddMaterial(I,.480451);
  csitl->AddMaterial(Tl,0.009);
  G4Box* detboxS = new G4Box('detbox',5*mm,20*mm,50*mm);
  G4LogicalVolume* detboxLV = new G4LogicalVolume(detboxS,csitl,"detboxLV");

  G4VisAttributes* det_VisAtt = new G4VisAttributes(G4Color(0,1,0));
  detboxLV->SetVisAttributes(det_VisAtt);
  G4double R = 80*mm;
  G4VPhysicalVolume* detboxPVs[12];
  
  for(int i = 0;i<12;i++)
  {
    G4RotationMatrix * RotMat = new G4RotationMatrix();
    RotMat->rotate(M_PI/2.+2*i*M_PI/12.,G4ThreeVector(0,0,1));
    detboxPVs[i] = new G4PVPlacement(RotMat,G4ThreeVector(R*sin(2*M_PI/12*i),R*cos(2*M_PI/12*i),0),detboxLV,"detboxPV",logicWorld,true,i,true);
  }


	return physiWorld;
}
