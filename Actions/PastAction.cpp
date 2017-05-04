#include "PastAction.h"

PastAction::PastAction(ApplicationManager * pApp):Action(pApp)
{

}

bool PastAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Click To past");
	pIn->GetPointClicked(P.x, P.y);
	if (P.y > UI.ToolBarHeight && P.y > UI.ToolBarHeight && P.y < (UI.height - UI.StatusBarHeight))
	{
		return true;
	}
	return false;
}

void PastAction::Execute()
{
	if (ReadActionParameters())
	{
		pManager->past(P);
	}
	pManager->GetOutput()->ClearStatusBar();
}
