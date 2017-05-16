#include "PasteAction.h"

PasteAction::PasteAction(ApplicationManager * pApp):Action(pApp)
{

}

bool PasteAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->DrawIMAGE("PasteCE", 793, 0, 61, 50);
	pOut->PrintMessage("Click To paste");
	pIn->GetPointClicked(P.x, P.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);
	pOut->DrawIMAGE("Paste", 793, 0, 61, 50);
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
