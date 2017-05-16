#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

bool AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateFigMenu();
	int x = pIn->IsFilled();
	if (x==2)
	{
		pOut->ClearToolBar();
		pOut->CreateDrawToolBar();
		return false;
	}
	RectGfxInfo.isFilled =x ;	//default is not filled
	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();

	pOut->DrawIMAGE("RectangleCE", 183, 0, 61, 50);

	pOut->PrintMessage("Drawing a New Rectangle : Click at first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	if ((P1.y > UI.ToolBarHeight) && (P1.y < (UI.height - UI.StatusBarHeight)))      pOut->DRAWPIXEL(P1);

	pOut->PrintMessage("Drawing a New Rectangle : Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	if ((P2.y > UI.ToolBarHeight) && (P2.y < (UI.height - UI.StatusBarHeight)))      pOut->DRAWPIXEL(P2);

	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();
	return true;

}

//Execute the action
void AddRectAction::Execute() 
{
	//This action needs to read some parameters first
	 bool t = ReadActionParameters();
	 if (!t)
		 return;
	 pManager->Saved = false;
	//Create a rectangle with the parameters read from the user
	 if (P1.y > UI.ToolBarHeight && P2.y > UI.ToolBarHeight && P1.y < (UI.height - UI.StatusBarHeight) && P2.y < (UI.height - UI.StatusBarHeight))
	 {
		 CRectangle *R = new CRectangle(P1, P2, RectGfxInfo);

		 //Add the rectangle to the list of figures
		 pManager->AddFigure(R);
		 Output* pOut = pManager->GetOutput();
		 pOut->DrawIMAGE("Rectangle", 183, 0, 61, 50);
	 }
	 else
	 {
		 Output* pOut = pManager->GetOutput();
		 pOut->DrawIMAGE("Rectangle", 183, 0, 61, 50);
		 pOut->PrintMessage("Error ! Please Draw at DrawArea");
	 }
}
