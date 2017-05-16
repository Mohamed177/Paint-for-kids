#include "AddLineAction.h"
#include "..\Figures\CLine.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddLineAction::AddLineAction(ApplicationManager *pApp) :Action(pApp)
{}

bool AddLineAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	

	pOut->PrintMessage("Drawing a New Line : Click at first point");

	//Read 1st point and store in point P1
	pIn->GetPointClicked(p1.x, p1.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	if ( (p1.y > UI.ToolBarHeight) && (p1.y < (UI.height - UI.StatusBarHeight)) )      pOut->DRAWPIXEL(p1);
	
	
	pOut->PrintMessage("Drawing a New Line : Click at second  point ");

	//Read 2nd point and store in point P2
	pIn->GetPointClicked(p2.x, p2.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	if ((p2.y > UI.ToolBarHeight) && (p2.y < (UI.height - UI.StatusBarHeight)))        pOut->DRAWPIXEL(p2);

	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pOut->getCrntDrawColor();
	LineGfxInfo.FillClr = pOut->getCrntFillColor();
	LineGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	LineGfxInfo.isFilled = false;

	pOut->ClearStatusBar();
	return true;

}

//Execute the action
void AddLineAction::Execute()
{
	//This action needs to read some parameters first
	bool t = ReadActionParameters();
	if (!t)
		return; // incase of false-painting trial
	//Create a Line with the parameters read from the user
	if (p1.y > UI.ToolBarHeight && p2.y > UI.ToolBarHeight && p1.y < (UI.height - UI.StatusBarHeight) && p2.y < (UI.height - UI.StatusBarHeight))
	{
		CLine *L = new CLine(p1, p2, LineGfxInfo);
		
		//Add the Line to the list of figures
		pManager->AddFigure(L);
		pManager->Saved = false;
		pManager->first_zoom = true;

	}
	else
	{
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Error ! Please Draw at DrawArea");
	}
}

AddLineAction::~AddLineAction()
{
}
