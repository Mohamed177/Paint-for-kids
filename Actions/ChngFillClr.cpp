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
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() <= 0) return;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateColorToolBar();
	pOut->PrintMessage("Choose The New Fill Color. ");
	pManager->ChangeFllColor();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
	{
		pOut->CreateSelcted_ZoomToolBar();
		pOut->Clickeffect("Fill", 348, 0, 58, 50);
	}
	else if (UI.InterfaceMode == MODE_ZOOM)
	{
		pOut->CreateZoomToolBar();
		pOut->Clickeffect("Fill", 348, 0, 58, 50);
	}
	else
	{
		pOut->CreateDrawToolBar();
		pOut->Clickeffect("Fill", 366, 0, 61, 50);
	}
	pManager->Saved = false;
	if (UI.InterfaceMode == MODE_DRAW)
		pManager->first_zoom = true;
}