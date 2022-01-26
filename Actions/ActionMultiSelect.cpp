#include "ActionMultiSelect.h"
ActionMultiSelect::ActionMultiSelect(ApplicationManager* pApp, int & _multiSelect) :Action(pApp){
	this->multiSelect = &_multiSelect;
};

void ActionMultiSelect::Execute() {
	if (*multiSelect) {
		*multiSelect = 0;
	}
	else {
		*multiSelect = 1;
	}
}