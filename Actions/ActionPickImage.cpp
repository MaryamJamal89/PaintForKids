#include "ActionPickImage.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionPickImage::ActionPickImage(ApplicationManager* pApp,int & _playType) : Action(pApp)
{
	playType = & _playType;
}

void ActionPickImage::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	/*pManager->UnSelectFigures(2);
	pManager->picFiguresStatus();
	if(pManager->GetRandomFigure()){
		*playType = 1;
		pManager->picFigures(pManager->GetRandomFigure());
	}*/





}
