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

void ChangeFillColor::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateColorToolBar();
	pOut->PrintMessage("Choose The New Fill Color. ");
	pManager->ChangeFllColor();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
		pOut->CreateSelcted_ZoomToolBar();
	else if (UI.InterfaceMode == MODE_ZOOM)
		pOut->CreateZoomToolBar();
	else
		pOut->CreateDrawToolBar();
	pManager->Saved = false;
	if (UI.InterfaceMode == MODE_DRAW)
		pManager->first_zoom = true;
}