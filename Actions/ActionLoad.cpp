#include<fstream>
#include<windows.h>
#include "ActionLoad.h"
#include "..\Figures\CSquare.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"

ActionLoad::ActionLoad(ApplicationManager* pApp) :Action(pApp)
{}

//Read target file name
string ActionLoad::ReadFileName()
{
	GUI* pGUI = pManager->GetGUI();
	pGUI->PrintMessage("Enter file name...");
	return pGUI->GetSrting();
}



//Execute the action
void ActionLoad::Execute()
{
	//ask user to save first
	// ---
	GUI* pGUI = pManager->GetGUI();
	string drawColor, fillColor, bgColor, figType;
	int figsNum;
	ifstream loadedFile;
	do {
		string fileName = ReadFileName();
		loadedFile.open(fileName + ".txt");
		if (loadedFile.fail())
		{
			pGUI->PrintMessage("File does not exist!");
			Sleep(800);
		}
	} while (loadedFile.fail());

	//reading and setting window colors
	loadedFile >> drawColor >> fillColor >> bgColor;
	UI.DrawColor = pGUI->StringToColor(drawColor);
	UI.FillColor = pGUI->StringToColor(fillColor);
	UI.BkGrndColor = pGUI->StringToColor(bgColor);

	//update window to change background color
	pGUI->ClearDrawArea();
	//delete all old figures
	pManager->ResetFigList();

	loadedFile >> figsNum;
	while (figsNum>0)
	{
		CFigure* fig;
		loadedFile >> figType;
		if (figType == "SQR") fig = new CSquare;
		//add other figures
		//----
		fig->Load(loadedFile,pGUI);
		pManager->AddFigure(fig);
		figsNum--;
	}
	pManager->UpdateInterface();
	pGUI->PrintMessage("file loaded successfully!");
	Sleep(1000);
	pGUI->ClearStatusBar();
}
