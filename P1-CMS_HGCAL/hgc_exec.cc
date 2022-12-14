/**
 *  ********************************************************************
 *  * License and Disclaimer                                           *
 *  *                                                                  *
 *  * The  Geant4 software  is  copyright of the Copyright Holders  of *
 *  * the Geant4 Collaboration.  It is provided  under  the terms  and *
 *  * conditions of the Geant4 Software License,  included in the file *
 *  * LICENSE and available at  http://cern.ch/geant4/license .  These *
 *  * include a list of copyright holders.                             *
 *  *                                                                  *
 *  * Neither the authors of this software system, nor their employing *
 *  * institutes,nor the agencies providing financial support for this *
 *  * work  make  any representation or  warranty, express or implied, *
 *  * regarding  this  software system or assume any liability for its *
 *  * use.  Please see the license in the file  LICENSE  and URL above *
 *  * for the full disclaimer and the limitation of liability.         *
 *  *                                                                  *
 *  * This  code  implementation is the result of  the  scientific and *
 *  * technical work of the GEANT4 collaboration.                      *
 *  * By using,  copying,  modifying or  distributing the software (or *
 *  * any work based  on the software)  you  agree  to acknowledge its *
 *  * use  in  resulting  scientific  publications,  and indicate your *
 *  * acceptance of all terms of the Geant4 Software license.          *
 *  ********************************************************************
 *  
 *  G4Tutorial.cc
 *  
 *  This file is a part of the project Daksha
 * 
 */

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "HGCAL_Detector.hh"
#include "HGCAL_PhysicsList.hh"
#include "HGCAL_ActionInit.hh"
#include "HGCAL_ParticleGun.hh"
#include "G4VModularPhysicsList.hh"
#include "FTFP_BERT.hh"
int main(int argc, char** argv)
{
    // Detect interactive mode (if no arguments) and define UI session
    G4UIExecutive* ui = 0;
    if ( argc == 1 ){
        ui = new G4UIExecutive(argc, argv);
    }
     
    // Construct the run manager
    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new HGCAL_DetectorConstruction());
    runManager->SetUserInitialization(new FTFP_BERT);
    runManager->SetUserInitialization(new HGCAL_ActionInitialization());

    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Process macro or start UI session
    if ( ! ui ) { 
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else { 
        // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        if (ui->IsGUI()) {
            UImanager->ApplyCommand("/control/execute icons.mac");
        }
        ui->SessionStart();
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !
    
    delete ui;
    delete visManager;
    return 0; 
}