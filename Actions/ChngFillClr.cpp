#include"ChngFillClr.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "SelectAction.h"

ChangeFillColor::ChangeFillColor(ApplicationManager *pApp) : Action(pApp)
{
}

ChangeFillColor::~ChangeFillColor()
{
}

bool ChangeFillColor::ReadActionParameters()
{
	return true;
}

bool ChangeFillColor::Execute()
{
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() <= 0) return false;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateColorToolBar();
	pOut->PrintMessage("Choose The New Fill Color. ");
	crntfllclr = UI.FillColor;
	newclr = pManager->ChangeFllColor();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
	{
		pOut->CreateSelcted_ZoomToolBar();
		pOut->Clickeffect("Fill", ZOOM_CHNG_FILL_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	else if (UI.InterfaceMode == MODE_ZOOM)
	{
		pOut->CreateZoomToolBar();
		pOut->Clickeffect("Fill", ZOOM_CHNG_FILL_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	else
	{
		pOut->CreateDrawToolBar();
		pOut->Clickeffect("Fill", ITM_CHNG_FILL_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	if (UI.InterfaceMode == MODE_DRAW)
	{
		if (newclr == crntfllclr)
			while (!pManager->RedoList.empty())
				pManager->RedoList.pop();
		pManager->first_zoom = true;
		pManager->Saved = false;
		return true;
	}
}

void ChangeFillColor::Undo()
{
	pManager->Undo(CHNG_FILL_CLR, crntfllclr);
}

void ChangeFillColor::Redo()
{
	pManager->Redo(CHNG_FILL_CLR, newclr);
}
