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
#include <vector>

vector <string> fileNames;          // Declaring Vector of String type to carry all file Names 
int i =1;
ActionSave::ActionSave(ApplicationManager* pApp) :Action(pApp) {

}

void ActionSave::Execute()
{
	GUI* pGUI = pManager->GetGUI();
    
	file_name= pGUI->ReadFileName("Save: Enter file name to save...");
	if (fileNames.size() == 0) {
		fileNames.push_back(file_name);
	}
	else {
		// condition to check if user want to over ride exist file of make new file
		for (size_t i = 0; i < fileNames.size(); i++) {
			if (file_name.compare(fileNames[i]) == 0) {
				 
				//ask user to create new file
				string response = pGUI->Confirm("Sorry,This file is already exit .Do you want to make new copy (Y/N)?");
				if (response == "Y" || response == "y")
				{
					file_name = file_name + " [" +to_string(i) + "]"; // here i need to make counter -- still i have change here --Asmaa--
					i++;
				}
			}
			else {
				break;
			}
		}
	}
	file.open(file_name+".txt", ios::out);

	file << pGUI->ColorToString( UI.DrawColor) << " " << pGUI->ColorToString(UI.FillColor) << "  " << pGUI->ColorToString(UI.BkGrndColor )<< endl;
    pManager->SaveAll(file);


    file.close();

	pGUI->PrintMessage("File Saved Successfully");
	Sleep(500);
}

