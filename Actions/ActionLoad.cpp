#include<fstream>
#include<windows.h>
#include "ActionLoad.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CHexagon.h"
#include "..\Figures\CEllipse.h"
#include "..\ApplicationManager.h"
#include "..\GUI\GUI.h"
#include "ActionChangeColor.h"
#include "ActionSave.h"

ActionLoad::ActionLoad(ApplicationManager* pApp) :Action(pApp)
{}

//Execute the action
void ActionLoad::Execute()
{
	GUI* pGUI = pManager->GetGUI();

	//ask user if they want to save current graph
	string response = pGUI->Confirm("Do you want save current file (Y/N)?");
	if (response == "Y" || response == "y")
	{
		//saving curreng graph
		Action* save = new ActionSave(pManager);
		save->Execute();
	}

	//deleting old figures
	pManager->ResetFigList();

	//loading the file
	string drawColor, fillColor, bgColor, figType;
	int figsNum;
	ifstream loadedFile;
	do {
		string fileName = pGUI->ReadFileName("Load: Enter file name to load from...");
		loadedFile.open(fileName + ".txt");
		if (loadedFile.fail())
		{
			pGUI->PrintMessage("File does not exist!");
			Sleep(800);
		}
	} while (loadedFile.fail());

	//reading window colors
	loadedFile >> drawColor >> fillColor >> bgColor;

	//using coloring actions to apply new colors
	Action* changeDrawColor = new ActionChangeColor(pManager, pGUI->StringToColor(drawColor), 1);
	changeDrawColor->Execute();

	if (fillColor != "NO_FILL")
	{
		Action* changeFillColor = new ActionChangeColor(pManager, pGUI->StringToColor(fillColor), 2);
		changeFillColor->Execute();
	}

	Action* changeBgColor = new ActionChangeColor(pManager, pGUI->StringToColor(bgColor), 3);
	changeBgColor->Execute();

	loadedFile >> figsNum;
	while (figsNum > 0)
	{
		CFigure* fig;
		loadedFile >> figType;
		if (figType == "SQR") fig = new CSquare;
		else if (figType == "HEX") fig = new CHexagon;
		else if (figType == "ELPS") fig = new CEllipse;
		//add other figures
		//----
		fig->Load(loadedFile, pGUI);
		pManager->AddFigure(fig);
		figsNum--;
	}
	pManager->UpdateInterface();
	pGUI->PrintMessage("file loaded successfully!");
	Sleep(1000);
	pGUI->ClearStatusBar();
}
