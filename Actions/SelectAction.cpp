#include "SelectAction.h"

int SelectAction::ZCounter = 0;
int SelectAction::SCounter = 0;
SelectAction::SelectAction(ApplicationManager * pApp):Action(pApp)
{
	temp = NULL;
	
}

bool SelectAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Select Any Figs. ");
	pIn->GetPointClicked(P.x,P.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);

	while (P.y > UI.ToolBarHeight)
	{
		if (UI.InterfaceMode == MODE_ZOOM)
		{
			temp = pManager->getzoomfig(P.x, P.y);
			if (temp)
			{
				temp->SetSelected(!(temp->IsSelected()));
				if (temp->IsSelected())
					ZCounter++;
				else
					ZCounter--;
			}
		}
		else
		{
			temp = pManager->GetFigure(P.x, P.y);	
			if (temp)
			{
				temp->SetSelected(!(temp->IsSelected()));
				if (temp->IsSelected())
					SCounter++;
				else
					SCounter--;
			}
		}
		
		if (UI.InterfaceMode == MODE_ZOOM)
			pManager->UpdateInterface(ZOOMIN);
		else
			pManager->UpdateInterface(TO_SELECT);
		pIn->GetPointClicked(P.x, P.y);
		mciSendString(TEXT("play click.wav"), NULL, 0, NULL);
	}
	pOut->ClearStatusBar();
	return  true;
}

void SelectAction::Execute()
{
	Output * pOut = pManager->GetOutput();
	bool test=ReadActionParameters();
	pManager->printselected(SCounter);
	if (UI.InterfaceMode == MODE_ZOOM && ZCounter > 0)
		pOut->CreateSelcted_ZoomToolBar();
	else if (UI.InterfaceMode == MODE_ZOOM)
		pOut->CreateZoomToolBar();
	temp = NULL;
}

int SelectAction::getZoomSlctCount()
{
	return ZCounter;
}
