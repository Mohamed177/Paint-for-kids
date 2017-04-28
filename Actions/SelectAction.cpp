#include "SelectAction.h"


SelectAction::SelectAction(ApplicationManager * pApp):Action(pApp)
{
	temp = NULL;
	Counter = 0;
}

bool SelectAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Select Any Figs. ");
	pIn->GetPointClicked(P.x,P.y);
	while(P.y > UI.ToolBarHeight )
	{
		temp = pManager->GetFigure(P.x, P.y);
		if (temp)
		{
			temp->SetSelected(!(temp->IsSelected()));
			if (temp->IsSelected())
				Counter++;
			else
				Counter--;
		}
		pIn->GetPointClicked(P.x, P.y);
	}
	pOut->ClearStatusBar();
	return  true;
}

void SelectAction::Execute()
{
 Output * pOut= pManager->GetOutput();
	bool test=ReadActionParameters();
	if (Counter == 1) 
	{
		//temp->PrintInfo(pOut);
	}
	else if (Counter >1)
	{
		string s = "";
		s = to_string(Counter);
		pOut->PrintMessage( "You selected " +s + " figures");
	}
	temp = NULL;
}
