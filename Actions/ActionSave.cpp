#include<fstream>
#include<iostream>
#include<windows.h>
#include<string>
#include "ActionSave.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CEllipse.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "..\GUI\UI_Info.h"
#include<windows.h>


ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp) {

}

void ActionSave::Execute()
{
	GUI* pGUI = pManager->GetGUI();
	file_name= pGUI->ReadFileName("Save: Enter file name to save...");

	file.open(file_name+".txt", ios::out);

	file << pGUI->ColorToString( UI.DrawColor) << " " << pGUI->ColorToString(UI.FillColor) << "  " << pGUI->ColorToString(UI.BkGrndColor )<< endl;
    pManager->SaveAll(file);
    file.close();

	pGUI->PrintMessage("File Saved Successfully");
	Sleep(500);
}

