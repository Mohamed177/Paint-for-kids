#include "AddCircAction.h"
#include "..\Figures\CCircle.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
AddCircAction::AddCircAction(ApplicationManager * pApp) :Action(pApp)
{
}

void AddCircAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at first corner");

	//Read Center and store in point P1
	pIn->GetPointClicked(Center.x, Center.y);

	pOut->PrintMessage("New Circle: Click at second corner");

	//Read P2 on Surface and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	RectGfxInfo.isFilled = false;	//default is not filled
									//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	pOut->ClearStatusBar();

}

void AddCircAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	double Raduis = sqrt(((P2.y - Center.y) *(P2.y - Center.y)) + ((P2.x - Center.x)*(P2.x - Center.x)));
	if ((Center.y-Raduis) >= UI.ToolBarHeight   && Center.y>UI.ToolBarHeight && Center.y<(UI.height - UI.StatusBarHeight) && (UI.height - UI.StatusBarHeight)>(Center.y + Raduis))
	{
		//Create a rectangle with the parameters read from the user
		CCircle *C = new CCircle(Center, P2, RectGfxInfo);

		//Add the rectangle to the list of figures
		pManager->AddFigure(C);
	}
	else {
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error ! Draw at DrawArea");
	}
}

