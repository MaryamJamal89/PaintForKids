#include "ActionPickImage_Color.h"
#include "../ApplicationManager.h"
#include "../GUI/GUI.h"
#include <iostream>

ActionPickImage_Color::ActionPickImage_Color(ApplicationManager* pApp) : Action(pApp)
{
	validCounter = 0;
	invalidCounter = 0;
} 

// return selected Figure
CFigure* ActionPickImage_Color::ReadesFigures() {
	Point point;
	GUI* pGUI = pManager->GetGUI();
	pGUI->pWind->WaitMouseClick(point.x, point.y);
	return  pManager->GetFigure(point.x, point.y);
}


void ActionPickImage_Color::Execute()
{
	Point point;
	GUI* pGUI = pManager->GetGUI();
	// get Rondom figure
	fig = pManager->GetRandomFigure();
	// update status Bar
	UpdateStatusBar(fig);
	// if fig not null
	if (fig) {
		figCount = MatchedFigsCount(fig);
		while (figCount) {
			CFigure* selectedFig = ReadesFigures();
			pManager->UnSelectFigures(2);
			if (selectedFig) {
				
				selectedFig->SetSelected(true);
				pManager->DeleteSelectedFigures();
				pGUI->ClearDrawArea();
				pManager->UpdateInterface();

				// Matchs
				if (figureMatches(fig, selectedFig)) {
					validCounter++;
					figCount--;
					string msg = " valid Choises: " + to_string(validCounter);
					string msg2 = " invalid Choises: " + to_string(invalidCounter);

					pGUI->PrintMessage(msg + msg2);
				}
				// not Match
				else {
					invalidCounter++;					
					string msg = " valid Choises: " + to_string(validCounter);
					string msg2 = " invalid Choises: " + to_string(invalidCounter);

					pGUI->PrintMessage(msg + msg2);
				}
			}
			else {
				pGUI->PrintMessage("No Figure Selected");
			}
		}

		// game over
		pGUI->PrintMessage("Game Over Your valid Choises : " + to_string(validCounter)+" and invalid Choises : "+ to_string(invalidCounter));

	}
}


// update status 
void ActionPickImage_Color::UpdateStatusBar(CFigure* fig) {
	GUI* pGUI = pManager->GetGUI();
	string figure;
	if (fig) {
		switch (fig->FigType)
		{
		case 1:
			figure = "Squares";
			break;
		case 2:
			figure = "Ellipse";
			break;
		case 3:
			figure = "Hexagone";
			break;
		}
		// don't forget to make function to get color  
		pGUI->PrintMessage("Game Started : Choose all " + figure + " with Color  count: " + to_string(fig->GetCount()));
	}
	else {
		pGUI->PrintMessage("There are no Figures to play with please draw some Figures or load a file ");
	}
}

// check if figure Matches or not
bool ActionPickImage_Color::figureMatches(CFigure* figure, CFigure* selectedFigure) {
	if (figure->FigType== selectedFigure->FigType) {
		return true;
	}
	return false ;
}

// get matched vigures 
// getFigsArray


int ActionPickImage_Color::MatchedFigsCount(CFigure* fig) {
	int count = 0;
	int figCount = pManager->GetFigCount();
	
	for (int i = 0; i < figCount; i++) {
		if (pManager->getFigByIndex(i)) {
			if (figureMatches(fig, pManager->getFigByIndex(i))) {
				count++;
			}
		}
	}
	return count;
}

// void picFigures();
//void ActionPickImage_Color::picFigures(CFigure* fig) {
//	string figure;
//	if (fig) {
//		if (startPlay == 0) {
//			figType = fig->FigType;
//			startPlay = fig->GetCount();
//		}
//		else {
//			if (fig->FigType == figType && startPlay == 1) {
//				string msg = /*to_string(--startPlay)+*/" Game Over valid Choises: " + to_string(validCounter + 1);
//				string msg2 = " invalid Choises: " + to_string(invalidCounter);
//
//				pGUI->PrintMessage(msg + msg2);
//				startPlay = 0;
//				playType = 0;
//				validCounter = 0;
//				invalidCounter = 0;
//			}
//			else if (fig->FigType == figType) {
//				validCounter++;
//				startPlay--;
//				string msg = /*to_string(startPlay)+*/" Figures => valid Choises: " + to_string(validCounter);
//				string msg2 = " invalid Choises: " + to_string(invalidCounter);
//				pGUI->PrintMessage(msg + msg2);
//			}
//			else {
//				invalidCounter++;
//				string msg = /*to_string(startPlay)+*/" Figures => valid Choises: " + to_string(validCounter);
//				string msg2 = " invalid Choises: " + to_string(invalidCounter);
//				pGUI->PrintMessage(msg + msg2);
//			}
//		}
//	}
//	else {
//		string msg = /*to_string(startPlay) +*/ " Figures => valid Choises: " + to_string(validCounter);
//		string msg2 = " invalid Choises: " + to_string(invalidCounter);
//		pGUI->PrintMessage(msg + msg2);
//	}
//};






