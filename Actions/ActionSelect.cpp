#include "ActionSelect.h"
#include <iostream>

using namespace std;

ActionSelect::ActionSelect(ApplicationManager* pApp, Point _P, bool _multiSelect) :Action(pApp)
{
	multiSelect = _multiSelect;
	P = _P;
	
}
void ActionSelect::Execute()
{
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();

	//check where this point :
	//and return selected figure or null 
	CFigure* fig = pManager->GetFigure(P.x, P.y);
	
	// no figure selected
	if (fig == NULL) {
		pGUI->PrintMessage("No Figure Selected");
		pManager->UnSelectFigures(2);
		//selectedFigures.clear();
	}
	else
	{
		if (fig->IsSelected()) 
		{
			fig->SetSelected(false);
			//cout << selectedFigures.size() <<"   1" << endl;
			//selectedFigures.erase(find(selectedFigures.begin(), selectedFigures.end(),fig));
			//cout << selectedFigures.size() <<"   2" << endl;
			/*if (!selectedFigures.empty()) {
				(selectedFigures.back())->PrintInfo(pGUI);
			}*/
			pGUI->ClearStatusBar();
		}
		else
		{
			// Enabling Multiple select
			if (!multiSelect) 
			{
				pManager->UnSelectFigures(2);
				//selectedFigures.clear();
			}
			fig->SetSelected(true);
			//selectedFigures.push_back(fig);
			//pGUI->PrintMessage(selectedFigures.pop_back());
			//cout << selectedFigures.size() <<"   3"<< endl;
			//(selectedFigures.back())->PrintInfo(pGUI);
			//cout << selectedFigures.size() <<"   4"<< endl;
			fig->PrintInfo(pGUI);
		}
		//cout << selectedFigures.size()<<endl;
	}
}