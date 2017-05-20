#include"ChngDrwClr.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "SelectAction.h"

ChangeDrawColor::ChangeDrawColor(ApplicationManager *pApp) : Action(pApp)
{
}

ChangeDrawColor::~ChangeDrawColor()
{
}

bool ChangeDrawColor::ReadActionParameters()
{
	return true;
}

bool ChangeDrawColor::Execute()
{
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() <= 0) return false;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateColorToolBar();
	pOut->PrintMessage("Choose The New Draw Color. ");
	crntdrwclr = UI.DrawColor;
	pManager->ChangeDrwColor();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
	{
		pOut->CreateSelcted_ZoomToolBar();
		pOut->Clickeffect("colors", 290, 0, 58, 50);
	}
	else if (UI.InterfaceMode == MODE_ZOOM)
	{
		pOut->CreateZoomToolBar();
		pOut->Clickeffect("colors", 290, 0, 58, 50);
	}
	else
	{
		pOut->CreateDrawToolBar();
		pOut->Clickeffect("colors", 305, 0, 61, 50);
		pManager->first_zoom = true;
	}
	pManager->Saved = false;
	if (crntdrwclr == UI.DrawColor)
		return false;
	return true;
}

void ChangeDrawColor::Undo()
{
	pManager->Undo(CHNG_DRAW_CLR, crntdrwclr);
}
