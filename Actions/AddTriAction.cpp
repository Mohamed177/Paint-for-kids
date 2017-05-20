#include "AddTriAction.h"
#include "..\Figures\CTriangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddTriAction::AddTriAction(ApplicationManager *pApp):Action(pApp)
{}
bool AddTriAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateFigMenu();
	int x = pIn->IsFilled();
	if (x == 2)
	{
		pOut->ClearToolBar();
		pOut->CreateDrawToolBar();
		return false;
	}
	triGfxInfo.isFilled = x;	//default is not filled
	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();

	pOut->DrawIMAGE("TriangleCE", 122	, 0, 61, 50);

	pOut->PrintMessage("Drawing a New Triangle : Click at first point");

	//Read 1st point and store in point P1
	pIn->GetPointClicked(p1.x, p1.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	if ((p1.y > UI.ToolBarHeight) && (p1.y < (UI.height - UI.StatusBarHeight)))      pOut->DRAWPIXEL(p1);

	pOut->PrintMessage("Drawing a New Triangle : Click at second  point ");

	//Read 2nd point and store in point P2
	pIn->GetPointClicked(p2.x, p2.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	if ((p2.y > UI.ToolBarHeight) && (p2.y < (UI.height - UI.StatusBarHeight)))      pOut->DRAWPIXEL(p2);

	pOut->PrintMessage("Drawing a New Triangle : Click at third point ");


	//Read 2nd point and store in point P2
	pIn->GetPointClicked(p3.x, p3.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	if ((p3.y > UI.ToolBarHeight) && (p3.y < (UI.height - UI.StatusBarHeight)))      pOut->DRAWPIXEL(p3);

	//get drawing, filling colors and pen width from the interface
	triGfxInfo.DrawClr = pOut->getCrntDrawColor();
	triGfxInfo.FillClr = pOut->getCrntFillColor();
	triGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();
	return true;

}


bool AddTriAction::Execute()
{
	//This action needs to read some parameters first
	bool t = ReadActionParameters();
	if (!t)
		return false;
	//Create a Triangle with the parameters read from the user
	if (p1.y > UI.ToolBarHeight && p2.y > UI.ToolBarHeight && p3.y > UI.ToolBarHeight&& p1.y < (UI.height - UI.StatusBarHeight) && p2.y < (UI.height - UI.StatusBarHeight) && p3.y < (UI.height - UI.StatusBarHeight))
	{
		CTriangle *T = new CTriangle(p1, p2, p3 , triGfxInfo);

		//Add the rectangle to the list of figures
		pManager->AddFigure(T);
		pManager->Saved = false;
		pManager->first_zoom = true;

		Output* pOut = pManager->GetOutput();
		pOut->DrawIMAGE("Triangle", 122, 0, 61, 50);
		return true;
	}
	else
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error ! Please Draw at DrawArea");
		pOut->DrawIMAGE("Triangle", 122, 0, 61, 50);
		return false;
	}
}

AddTriAction::~AddTriAction()
{
}

void AddTriAction::Undo()
{
	pManager->Undo(DRAW_TRI);
}
