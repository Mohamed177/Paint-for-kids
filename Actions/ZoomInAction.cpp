#include "ZoomInAction.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
#include "ZoomOutAction.h"

ZoomIn::ZoomIn(ApplicationManager *pApp):Action(pApp)
{
}

bool ZoomIn::ReadActionParameters()
{
	return true;
}

//Execute the action
void ZoomIn::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pManager->ZoomCopy();
	pManager->Zoom(2.0);
	pManager->Zcount++;
}


ZoomIn::~ZoomIn()
{
}
