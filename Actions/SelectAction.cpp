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
	if (UI.InterfaceMode == MODE_ZOOM)
		pOut->DrawIMAGE("SelectCE", 232, 0, 58, 50);
	else
		pOut->DrawIMAGE("SelectCE", 244, 0, 61, 50);
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Select Any Figs. ");
	pIn->GetPointClicked(P.x,P.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);
	
	while(P.y > UI.ToolBarHeight )
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
				selected_IDs.push(P);
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
	if (UI.InterfaceMode == MODE_ZOOM)
		pOut->DrawIMAGE("SelectCE", 232, 0, 58, 50);
	else
		pOut->DrawIMAGE("SelectCE", 244, 0, 61, 50);
	pOut->ClearStatusBar();
	if (selected_IDs.size() > 0)
		return true;
	return false;
}

bool SelectAction::Execute()
{
	Output * pOut = pManager->GetOutput();
	bool test=ReadActionParameters();
	pManager->printselected(SCounter);
	if (UI.InterfaceMode == MODE_ZOOM && ZCounter > 0)
		pOut->CreateSelcted_ZoomToolBar();
	else if (UI.InterfaceMode == MODE_ZOOM)
		pOut->CreateZoomToolBar();
	temp = NULL;
	return test;
}

int SelectAction::getZoomSlctCount()
{
	return ZCounter;
}

void SelectAction::ResetZoomSlctCount()
{
	ZCounter = 0;
}

void SelectAction::setSCounter(int sc)
{
	SCounter = sc;
}

int SelectAction::getSlctCount()
{
	return SCounter;
}

void SelectAction::Undo()
{
	while (selected_IDs.size() > 0)
	{
		P = selected_IDs.top();
		temp = pManager->GetFigure(P.x, P.y);
		if (temp)
		{
			temp->SetSelected(!(temp->IsSelected()));
			if (temp->IsSelected())
				SCounter++;
			else
				SCounter--;
		}
		selected_IDs.pop();
		pManager->UpdateInterface(TO_SELECT);
	}
}
