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
	newclr = pManager->ChangeDrwColor();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
	{
		pOut->CreateSelcted_ZoomToolBar();
		pOut->Clickeffect("colors", ZOOM_CHNG_DRAW_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	else if (UI.InterfaceMode == MODE_ZOOM)
	{
		pOut->CreateZoomToolBar();
		pOut->Clickeffect("colors", ZOOM_CHNG_DRAW_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	else
	{
		if (newclr == crntdrwclr)
			while (!pManager->RedoList.empty())
				pManager->RedoList.pop();
		pOut->CreateDrawToolBar();
		pOut->Clickeffect("colors", ITM_CHNG_DRAW_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
		pManager->first_zoom = true;
		pManager->Saved = false;
		return true;
	}
	return false; 
}

void ChangeDrawColor::Undo()
{
	pManager->Undo(CHNG_DRAW_CLR, crntdrwclr);
}

void ChangeDrawColor::Redo()
{
	pManager->Redo(CHNG_DRAW_CLR, newclr);
}
