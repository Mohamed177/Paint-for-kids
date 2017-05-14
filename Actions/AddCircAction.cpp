#include "AddCircAction.h"
#include "..\Figures\CCircle.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
AddCircAction::AddCircAction(ApplicationManager * pApp) :Action(pApp)
{
}

bool AddCircAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateFigMenu();     //Filled Or Not
	int x = pIn->IsFilled();
	if (x == 2)
	{
		pOut->ClearToolBar();
		pOut->CreateDrawToolBar();
		return false;
	}
	RectGfxInfo.isFilled = x;	//default is not filled
	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Drawing a New Circle : Click at first corner");


	//Read Center and store in point P1
	pIn->GetPointClicked(Center.x, Center.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	if ((Center.y > UI.ToolBarHeight) && (Center.y < (UI.height - UI.StatusBarHeight)))      pOut->DRAWPIXEL(Center);

	pOut->PrintMessage("Drawing a New Circle : Click at second corner");

	//Read P2 on Surface and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

									//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	pOut->ClearStatusBar();
	return true;
}

void AddCircAction::Execute()
{
	//This action needs to read some parameters first
	bool t = ReadActionParameters();
	if (!t)
		return;
	pManager->Saved = false;
	double Radius = sqrt(((P2.y - Center.y) *(P2.y - Center.y)) + ((P2.x - Center.x)*(P2.x - Center.x)));
	if ((Center.y-Radius) >= UI.ToolBarHeight   && Center.y>UI.ToolBarHeight && Center.y<(UI.height - UI.StatusBarHeight) && (UI.height - UI.StatusBarHeight)>(Center.y + Radius) && Center.x - Radius > 0 && Center.x + Radius < UI.width)
	{
		//Create a rectangle with the parameters read from the user
		CCircle *C = new CCircle(Center, Radius, RectGfxInfo);
		//Add the rectangle to the list of figures
		pManager->AddFigure(C);
	}
	else {
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error ! Please Draw at DrawArea");
	}
}

