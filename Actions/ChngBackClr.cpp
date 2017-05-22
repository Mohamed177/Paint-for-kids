#include "ChngBackClr.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "SelectAction.h"

ChngBackClr::ChngBackClr(ApplicationManager *pApp):Action(pApp)
{
}

bool ChngBackClr::ReadActionParameters()
{

	return true;
}

bool ChngBackClr::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateColorToolBar();
	pOut->PrintMessage("Choose The New Back Ground Color. ");
	crntbkgrnd = UI.BkGrndColor;
	newclr = pIn->ChangeBackColor();
	pOut->setBackColor(newclr);
	pOut->ClearToolBar();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
	{
		pOut->CreateSelcted_ZoomToolBar();
		pOut->Clickeffect("Background", ZOOM_CHNG_BK_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	else if (UI.InterfaceMode == MODE_ZOOM)
	{
		pOut->CreateZoomToolBar();
		pOut->Clickeffect("Background", ZOOM_CHNG_BK_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	else
	{
		pOut->CreateDrawToolBar();
		pOut->Clickeffect("Background", ITM_CHNG_BK_CLR * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	pManager->Saved = false;
	if (UI.InterfaceMode == MODE_DRAW)
	{
		if (newclr != crntbkgrnd)
			while (!pManager->RedoList.empty())
				pManager->RedoList.pop();
		pManager->first_zoom = true;
		pManager->Saved = false;
		return true;
	}
	//pManager->UpdateInterface(TO_DRAW);
	
}

ChngBackClr::~ChngBackClr()
{
	
}

void ChngBackClr::Undo()
{
	pManager->Undo(CHNG_BK_CLR, crntbkgrnd);
}

void ChngBackClr::Redo()
{
	pManager->Redo(CHNG_BK_CLR, newclr);
}
