#include "PasteAction.h"

PasteAction::PasteAction(ApplicationManager * pApp):Action(pApp)
{

}

bool PasteAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Click To paste");
	pIn->GetPointClicked(P.x, P.y);
	if (P.y > UI.ToolBarHeight && P.y > UI.ToolBarHeight && P.y < (UI.height - UI.StatusBarHeight))
	{
		return true;
	}
	return false;
}

void PasteAction::Execute()
{
	if (ReadActionParameters())
	{
		pManager->paste(P);
	}
	pManager->GetOutput()->ClearStatusBar();
}
