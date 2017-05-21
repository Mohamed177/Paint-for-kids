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
void ZoomOutAction::Undo()
{
}
void ZoomOutAction::Redo()
{
}
bool ZoomOutAction::ReadActionParameters()
{
	return true;
}

bool ZoomOutAction::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->setdrawint(0);
	if (pManager->Zcount == 0 && pManager->first_zoom)
	{
		pManager->ZoomCopy();
		pManager->first_zoom = false;
		SelectAction::ResetZoomSlctCount();
	}
	pManager->Zoom(1.0/2);
	pManager->Zcount--;
	pOut->ClearToolBar();
	if (pManager->Zcount != 0 && SelectAction::getZoomSlctCount() > 0)
		pOut->CreateSelcted_ZoomToolBar();
	else if (pManager->Zcount != 0)
		pOut->CreateZoomToolBar();
	
	pOut->Clickeffect("Zoom Out", 870, 0, 58, 50);
	return false;
}