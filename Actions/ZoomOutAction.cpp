#include "ZoomOutAction.h"
#include "../ApplicationManager.h"
#include "..\GUI\Output.h"
#include "../GUI/Input.h"
#include "SelectAction.h"

ZoomOutAction::ZoomOutAction(ApplicationManager *pApp):Action(pApp)
{
}


ZoomOutAction::~ZoomOutAction()
{
}
bool ZoomOutAction::ReadActionParameters()
{
	return true;
}

void ZoomOutAction::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	if (pManager->Zcount == 0 && pManager->first_zoom)
	{
		pManager->ZoomCopy();
		pManager->first_zoom = false;
	}
	pManager->Zoom(1.0/2);
	pManager->Zcount--;
	pOut->ClearToolBar();
	if (pManager->Zcount != 0 && SelectAction::getZoomSlctCount() > 0)
		pOut->CreateSelcted_ZoomToolBar();
	else if (pManager->Zcount != 0)
		pOut->CreateZoomToolBar();
	
}