#include "SelectAction.h"


SelectAction::SelectAction(ApplicationManager * pApp):Action(pApp)
{
	temp = NULL;
	Counter = 0;
}

bool SelectAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	pOut->DrawIMAGE("SelectCE",244, 0, 61, 50);
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Select Any Figs. ");
	pIn->GetPointClicked(P.x,P.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);
	
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
		pManager->UpdateInterface(TO_SELECT);
		pIn->GetPointClicked(P.x, P.y);
		mciSendString(TEXT("play click.wav"), NULL, 0, NULL);
	}
	pOut->DrawIMAGE("Select", 244, 0, 61, 50);
	pOut->ClearStatusBar();
	return  true;
}

void SelectAction::Execute()
{
	Output * pOut = pManager->GetOutput();
	bool test=ReadActionParameters();
	if (Counter == 1) 
	{
		pOut->DrawIMAGE("Select", 244, 0, 61, 50);
		temp->PrintInfo(pOut);
	}
	else if (Counter >1)
	{
		pOut->DrawIMAGE("Select", 244, 0, 61, 50);
		string s = "";
		s = to_string(Counter);
		pOut->PrintMessage("You selected " + s + " figures");
	}
	temp = NULL;
}
