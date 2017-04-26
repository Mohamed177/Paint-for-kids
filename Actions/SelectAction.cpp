#include "SelectAction.h"

SelectAction::SelectAction(ApplicationManager * pApp):Action(pApp)
{
	Counter = 0;
	temp = NULL;
}

bool SelectAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Select Any Figs. ");
	pIn->GetPointClicked(P.x,P.y);

	temp = pManager->GetFigure(P.x, P.y);
	if (P.y > UI.ToolBarHeight && P.y < (UI.height - UI.StatusBarHeight))
	{
		if (temp)
		{
			temp->SetSelected(!(temp->IsSelected()));
			pOut->ClearStatusBar();
			return temp;
		}
	}
	temp = NULL;
	pOut->ClearStatusBar();
	return temp;
}

void SelectAction::Execute()
{
	do {
		CFigure* temp = NULL;
		bool test=ReadActionParameters();
	} while (P.y > UI.ToolBarHeight && P.y < (UI.height - UI.StatusBarHeight));

}
