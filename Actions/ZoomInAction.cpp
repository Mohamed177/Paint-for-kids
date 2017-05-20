#include "ZoomInAction.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
#include "ZoomOutAction.h"
#include "SelectAction.h"

ZoomIn::ZoomIn(ApplicationManager *pApp):Action(pApp)
{
}

bool ZoomIn::ReadActionParameters()
{
	return true;
}

//Execute the action
bool ZoomIn::Execute()
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
	pManager->Zoom(2.0);
	pManager->Zcount++;
	if (pManager->Zcount != 0 && SelectAction::getZoomSlctCount() > 0)
		pOut->CreateSelcted_ZoomToolBar();
	else if (pManager->Zcount != 0)
		pOut->CreateZoomToolBar();
	
	pOut->Clickeffect("Zoom In", 812, 0, 58, 50);
	return false;
}


ZoomIn::~ZoomIn()
{
}

void ZoomIn::Undo()
{
}
