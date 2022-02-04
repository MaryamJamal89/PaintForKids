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
	CFigure* figure = NULL;

	//check if there are any drawn figures
	if (pManager->GetFigCount() > 0)
	{
		//ask user if they want to save current graph
		string response = pGUI->Confirm("Do you want save current file (Y/N)?");
		if (response == "Y" || response == "y")
		{
			//saving curreng graph
			Action* save = new ActionSave(pManager);
			save->Execute();
			//delete save;
		}
		//deleting old figures
		pManager->ResetFigList();
	}

	//loading the file
	string drawColor, fillColor, bgColor, figType;
	int figsNum;
	ifstream loadedFile;

	string fileName = pGUI->ReadFileName("Load: Enter file name to load from...");
	loadedFile.open("Saves\\" + fileName + ".txt");
	if (loadedFile.fail())
	{
		pGUI->PrintTempMessge("File '" +fileName+ "' does not exist!", 1000);
	}
	else
	{
		//reading window colors
		loadedFile >> drawColor >> fillColor >> bgColor;

		//using coloring actions to apply new colors
		//changing window drawing color
		Action* changeDrawColor = new ActionChangeColor(pManager, pGUI->StringToColor(drawColor), 1, figure);
		changeDrawColor->Execute();

		if (fillColor != "NO_FILL")
		{
			UI.isFilled = true;
			//changing window filling color if it was set
			Action* changeFillColor = new ActionChangeColor(pManager, pGUI->StringToColor(fillColor), 2, figure);
			changeFillColor->Execute();
		}
		else
		{
			UI.isFilled = false;
		}
		//changing window background color
		Action* changeBgColor = new ActionChangeColor(pManager, pGUI->StringToColor(bgColor), 3, figure);
		changeBgColor->Execute();

		loadedFile >> figsNum;
		//loading figures
		while (figsNum > 0)
		{
			CFigure* fig;
			loadedFile >> figType;
			if (figType == "SQR") fig = new CSquare;
			else if (figType == "HEX") fig = new CHexagon;
			else if (figType == "ELPS") fig = new CEllipse;

			//calling load function for each figure
			fig->Load(loadedFile, pGUI);
			pManager->AddFigure(fig);
			figsNum--;
		}
		//update drawing area with loaded figures
		pManager->UpdateInterface();
		//cofirmation message
		pGUI->PrintTempMessge("file loaded successfully!", 1000);
	}
}
