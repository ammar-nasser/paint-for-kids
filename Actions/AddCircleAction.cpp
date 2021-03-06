#include "AddCircleAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

//
AddCircleAction::AddCircleAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddCircleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at first edge");

	//Read 1st edge and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	//convert from screen coordinates to world coordinates
	screenToWorld(P1);

	pOut->PrintMessage("New Circle: Click at second edge");

	//Read 2nd edge and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	//convert from screen coordinates to world coordinates
	screenToWorld(P2);

	CircleGfxInfo.isFilled = false;	//default is not filled
	CircleGfxInfo.FillClr = WHITE;	//default to White, to make the colorType notFilled, this is a must
	//get drawing color and pen width from the interface
	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->drawCleanStatusBar();

}

//Execute the action
void AddCircleAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a circle with the parameters read from the user
	CCircle* R = new CCircle(P1, P2, CircleGfxInfo);

	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
}

AddCircleAction::~AddCircleAction()
{
	pManager->GetOutput()->UnhighlightItem(ITM_CIRC);
}
