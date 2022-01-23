#include "ActionSelect.h"

//#include "..\Figures\CSquare.h"
//
//#include "..\ApplicationManager.h"
//
//#include "..\GUI\GUI.h"
#include <iostream>



ActionSelect::ActionSelect(ApplicationManager* pApp, Point _P) :Action(pApp)
{
	P = _P;
}
void ActionSelect::Execute()
{
	//bug 2 click ??? why
	//Get a Pointer to the Interface
	GUI* pGUI = pManager->GetGUI();
	//pGUI->ClearStatusBar();

	//check where this point :
	CFigure* fig = pManager->GetFigure(P.x, P.y);
	//pManager->set_Clipboard(NULL);
	pGUI->PrintMessage("No Figure Selected");
	if (fig != NULL) {
		//fig->SetSelected(true);
		pGUI->PrintMessage(fig->PrintInfo());
		cout << (fig->PrintInfo()) << endl;
	}
	/*std::cout << P.x << endl << P.y << endl;
	pGUI->PrintMessage(to_string(P.x)+" : "+ to_string(P.y));*/
}