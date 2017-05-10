#include "ZoomOutAction.h"
#include "../ApplicationManager.h"
#include "..\GUI\Output.h"
#include "../GUI/Input.h"


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
	pManager->ZoomCopy();
	pManager->Zoom(1.0/2);
	pManager->Zcount--;
	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();
}