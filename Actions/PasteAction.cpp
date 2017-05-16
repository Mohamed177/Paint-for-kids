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
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

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
		pManager->Saved = false;
		pManager->first_zoom = true;
	}
	pManager->GetOutput()->ClearStatusBar();
}
