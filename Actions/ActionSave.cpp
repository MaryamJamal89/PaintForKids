#include<fstream>
#include <iostream>
#include<windows.h>
#include<string>
#include "ActionSave.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CEllipse.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\GUI\UI_Info.h"


ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp) {

}

bool ActionSave::ReadActionParameters()
{
	// return pointer to GUI 
	// in future i will make one instance from GUI
	GUI* pGUIOut = pManager->GetGUI();
	GUI* pGUIIN = pManager->GetGUI();
	// this massage will appeare in status bar
	pGUIOut->PrintMessage("Save: Enter file name");
	file_name = pGUIIN->GetSrting();
	pGUIOut->PrintMessage("File Saved Successfully");
	return true;
}


void ActionSave::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	ReadActionParameters();

	file.open(file_name+".txt", ios::out);

		file << pGUI->ColorToString( UI.DrawColor) << " " << pGUI->ColorToString(UI.FillColor) << "  " << pGUI->ColorToString(UI.BkGrndColor )<< endl;

	pManager->SaveAll(file);
	file.close();
}

