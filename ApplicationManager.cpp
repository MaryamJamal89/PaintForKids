#include <fstream>
#include "ApplicationManager.h"
#include "Actions/ActionAddSquare.h"
#include "Actions/ActionAddEllipse.h"
#include "Actions/ActionAddHexagon.h"
#include "Actions/ActionSave.h"
#include "Actions/ActionLoad.h"
#include "Actions/ActionChangeLocation.h"
#include "Actions/ActionExit.h"
#include "Actions/ActionSelect.h"
#include "Actions/ActionMultiSelect.h"
#include "Actions/ActionChangeColor.h"
#include "Actions/ActionPickImage.h"
#include "Actions/ActionPickColor.h"
#include "Actions/ActionPickImage_Color.h"
#include "Actions/ActionRestartPlay.h"
#include "Actions/ActionSwitchPlay.h"
#include "Actions/ActionSwitchDraw.h"
#include "Actions/ActionDelete.h"

#include <stdio.h>
#include <stdlib.h>  
#include <cstdlib>
#include <iostream>
#include <chrono>
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pGUI = new GUI;

	//delete all old figures
	ApplicationManager::ResetFigList();

	multiSelect = 0;
	numberOfDuplicatedFilesName = 1;
	inPlayMode = false;
	
	playType = 0;
	validCounter = 0;
	invalidCounter = 0;
	figType = 0;
	startPlay = 0;
}

// return numberOfDuplicatedFilesName
int ApplicationManager::ReturnNumberofDulicatedFile()
{
	return numberOfDuplicatedFilesName;
}

void ApplicationManager::increamentNumberofDulicatedFile()
{
	numberOfDuplicatedFilesName++;
}

//delete all old figures
void ApplicationManager::ResetFigList()
{
	FigCount = 0;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

void ApplicationManager::Run()
{
	ActionType ActType;
	do
	{
		//1- Read user action
		ActType = pGUI->MapInputToActionType(x, y);

		//2- Create the corresponding Action
		Action* pAct = CreateAction(ActType);

		//3- Execute the action
		ExecuteAction(pAct);

		//4- Update the interface
		UpdateInterface();
	} while (ActType != EXIT);
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
//Creates an action
Action* ApplicationManager::CreateAction(ActionType ActType)
{
	Action* newAct = NULL;
	int selectedIndex, selectedNum;
	CFigure* figure = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAW_SQUARE:
		newAct = new ActionAddSquare(this);
		break;

	case DRAW_ELPS:
		newAct = new ActionAddEllipse(this);
		break;

	case DRAW_HEX:
		newAct = new ActionAddHexagon(this);
		break;

	case DRAW_SHAPES:
		pGUI->ClearToolBar();
		pGUI->CreateShapesBar();
		pGUI->PrintTempMessge("Select a figure to draw!", 1000);
		break;

	case MUL_SELECT:
		/*if (multiSelect) {
			multiSelect = 0;
		}
		else {
			multiSelect = 1;
		}*/
		newAct = new ActionMultiSelect(this, multiSelect);
		break;

	case DEL:
		newAct = new ActionDelete(this);
		break;

	case SEND_BACK:
		newAct = new ActionChangeLocation(this, false);
		break;

	case BRNG_FRNT:
		newAct = new ActionChangeLocation(this, true);
		break;

	case COLOR_TOMATO:
		figure = GetSelectedFigureByFlag(selectedIndex, selectedNum);
		newAct = new ActionChangeColor(this, TOMATO, DORF, figure);
		pGUI->ClearToolBar();
		pGUI->CreateDrawToolBar();
		break;

	case COLOR_DEEPSKYBLUE:
		figure = GetSelectedFigureByFlag(selectedIndex, selectedNum);
		newAct = new ActionChangeColor(this, DEEPSKYBLUE, DORF, figure);
		pGUI->ClearToolBar();
		pGUI->CreateDrawToolBar();
		break;

	case COLOR_LIGHTGREEN:
		figure = GetSelectedFigureByFlag(selectedIndex, selectedNum);
		newAct = new ActionChangeColor(this, LIGHTGREEN, DORF, figure);
		pGUI->ClearToolBar();
		pGUI->CreateDrawToolBar();
		break;

	case COLOR_ORANGE:
		figure = GetSelectedFigureByFlag(selectedIndex, selectedNum);
		newAct = new ActionChangeColor(this, ORANGE, DORF, figure);
		pGUI->ClearToolBar();
		pGUI->CreateDrawToolBar();
		break;

	case CHNG_DRAW_CLR:
		DORF = 1;
		pGUI->ClearToolBar();
		pGUI->CreateDrawColorBar();
		pGUI->PrintTempMessge("Select drawing color!", 1000);
		break;

	case CHNG_FILL_CLR:
		DORF = 2;
		pGUI->ClearToolBar();
		pGUI->CreateDrawColorBar();
		pGUI->PrintTempMessge("Select filling color!", 1000);
		break;

	case CHNG_BK_CLR:
		DORF = 3;
		pGUI->ClearToolBar();
		pGUI->CreateDrawColorBar();
		pGUI->PrintTempMessge("Select background color!", 1000);
		break;

	case SAVE:
		newAct = new ActionSave(this);
		break;

	case LOAD:
		newAct = new ActionLoad(this);
		break;

	case TO_PICK_IMAGE:
		newAct = new ActionPickImage(this, playType);
		break;

	case TO_PICK_COLOR:
		newAct = new ActionPickColor(this);
		break;

	case TO_PICK_IMAGE_COLOR:
		newAct = new ActionPickImage_Color(this);
		break;
	case RESTART:
		newAct = new ActionRestartPlay(this);
		break;
	case TO_PLAY:
		newAct = new ActionSwitchPlay(this);
		break;

	case TO_DRAW:
		playType = 0;
		newAct = new ActionSwitchDraw(this);
		break;

	case EXIT:
		newAct = new ActionExit(this);
		break;

	case STATUS:	//a click on the status bar ==> no action
		return NULL;
		break;

	case DRAWING_AREA: //select
		newAct = new ActionSelect(this, { x, y }, multiSelect);
		break;
	}
	return newAct;
}

//////////////////////////////////////////////////////////////////////

//Executes the created Action
void ApplicationManager::ExecuteAction(Action*& pAct)
{
	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}

int ApplicationManager::GetFigCount()
{
	return FigCount;
}

//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//
//multiSelect filed
//bool ApplicationManager::multiSelect = false;

CFigure* ApplicationManager::getFigByIndex(int i) {
	return FigList[i];
}

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
}

//unSelect Figures
void ApplicationManager::UnSelectFigures(int mul) const
{
	if (mul == 1 && multiSelect)
	{
		return;
	}
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->SetSelected(false);
	}
};

///////////////////////////////////////////////////////

// func to return Selected Figure
CFigure* ApplicationManager::GetFigure(int x, int y) const         //get one selected figure by clicked point indexes
{
	// if the point in figure will return Pointer on Figure
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i]->InFig(x, y))
		{
			return FigList[i];
		}
	}
	// if point not in any figure will return NULL
	return NULL;
}

CFigure* ApplicationManager::GetSelectedFigureByFlag(int& selectedIndex, int& selectedNum)     //get one selected figure by checking isSelected prop
{
	selectedNum = 0;
	for (int i = FigCount - 1; i >= 0; i--) {
		if (FigList[i]->IsSelected())
		{
			selectedIndex = i;
			selectedNum++;
		}
	}
	if (selectedNum == 0)
	{
		// if no figure is selected return null
		return NULL;
	}
	else
	{
		return FigList[selectedIndex];
	}
}

void ApplicationManager::InsertFigure(bool isFront)          //insert figure in front or back of all figuers
{
	int selectedIndex, selectedNum;
	CFigure* temp = GetSelectedFigureByFlag(selectedIndex, selectedNum);
	if (temp == NULL)
	{
		pGUI->PrintTempMessge("No selected figure to move!", 1000);
	}
	else if (selectedNum > 1)
	{
		pGUI->PrintTempMessge("Select only one figure to move!", 1000);
	}
	else
	{
		if (isFront)
		{
			for (int i = selectedIndex; i < FigCount; i++) {
				FigList[i] = FigList[i + 1];
			}
			FigList[FigCount - 1] = temp;
			pGUI->PrintTempMessge("Figure brought to front!", 1000);
		}
		else
		{
			for (int i = selectedIndex; i >= 0; i--) {
				FigList[i] = FigList[i - 1];
			}
			FigList[0] = temp;
			pGUI->PrintTempMessge("Figure sent to back!", 1000);
		}
	}
}


void ApplicationManager::RearrangingFigList()         //removing null refrences from FigList
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] == NULL)
		{
			//shifting all upcoming figures to remove the null refrenece
			for (int j = i; j < FigCount; j++)
			{
				FigList[j] = FigList[j + 1];
			}
		}
	}
}

void ApplicationManager::DeleteSelectedFigures()           //delete all selected figures
{
	int deletedNum = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{

			/*CFigure* temp;
			temp = FigList[i];
			delete temp;*/
			FigList[i] = NULL;
			deletedNum++;
		}
	}
	RearrangingFigList();
	FigCount -= deletedNum;
}

void ApplicationManager::SaveAll(ofstream& File) const
{
	File << FigCount << endl;
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(File, GetGUI());
	}
}

// Backup FigList
void ApplicationManager::TakeCopyOfFigures()
{
	//bool inPlayMode = false;
	if (UI.InterfaceMode == MODE_PLAY) {
		// backup original figures
		for (int i = 0; i < FigCount; i++)
		{
			cout << "s" << endl;
			CopyFigList[i] = FigList[i]->CloneFig();
		}
		copyArrayLength = FigCount;
		inPlayMode = true;
	}
	else
	{
		if (inPlayMode == true) 
		{
			cout << "sss" << endl;
			// delete old pointers first
			for (int i = 0; i < FigCount; i++)
			{
				delete FigList[i];
			}

			// restore the original size of the array
			FigCount = copyArrayLength;

			// restore figures from the backup array
			for (int i = 0; i < FigCount; i++)
			{
				FigList[i] = CopyFigList[i]->CloneFig();
				FigList[i]->IncCount();
				//cout << CopyFigList[i] << " : " << FigList[i]->GetCount() << endl;
			}

			// delete pointers in the backup array to free ram
			for (int i = 0; i < FigCount; i++)
			{
				FigList[i]->IncCount();
				delete CopyFigList[i];
				inPlayMode = false;
			}
		}
	}
}

/////////////
 //To Restart Play
void ApplicationManager::TakeFigOfDrawMode()
{
	// restore the original size of the array
	FigCount = copyArrayLength;

	// delete old pointers first
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
	}

	// restore figures from the backup array
	for (int i = 0; i < FigCount; i++)
	{
		cout << "sssss" << endl;
		FigList[i] = CopyFigList[i]->CloneFig();
		FigList[i]->IncCount();
		//cout << CopyFigList[i] << " : " << FigList[i]->GetCount() << endl;
	}
}

CFigure* ApplicationManager::GetRandomFigure() {
	if (FigCount)
	{
		srand(time(NULL));
		return FigList[rand() % FigCount];
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	for (int i = 0; i < FigCount; i++)
		FigList[i]->DrawMe(pGUI);		//Call Draw function (virtual member fn)
}

////////////////////////////////////////////////////////////////////////////////////

//Return a pointer to the interface
GUI* ApplicationManager::GetGUI() const
{
	return pGUI;
}

////////////////////////////////////////////////////////////////////////////////////

//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pGUI;

}
