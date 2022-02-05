#include "ActionMultiSelect.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"

ActionMultiSelect::ActionMultiSelect(ApplicationManager* pApp, int& _multiSelect) :Action(pApp)
{
	this->multiSelect = &_multiSelect;
};

void ActionMultiSelect::Execute() {
	GUI* pGUI = pManager->GetGUI();

	if (*multiSelect)
	{
		*multiSelect = 0;
		pGUI->PrintTempMessge("Multiselect mode off!", 1000);
	}
	else
	{
		*multiSelect = 1;
		pGUI->PrintTempMessge("Multiselect mode on!", 1000);
	}
}