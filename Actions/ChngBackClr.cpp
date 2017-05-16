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

void ChngBackClr::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateColorToolBar();
	pOut->PrintMessage("Choose The New Back Ground Color. ");
	pOut->setBackColor(pIn->ChangeBackColor());
	pOut->ClearToolBar();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
		pOut->CreateZoomToolBar();
	else if (UI.InterfaceMode == MODE_ZOOM)
		pOut->CreateSelcted_ZoomToolBar();
	else
		pOut->CreateDrawToolBar();
	pManager->Saved = false;
	if (UI.InterfaceMode == MODE_DRAW)
		pManager->first_zoom = true;
}

ChngBackClr::~ChngBackClr()
{
}
