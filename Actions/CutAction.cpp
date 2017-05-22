#include "CutAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


CutAction::CutAction(ApplicationManager * pApp) :Action(pApp)
{
}
bool CutAction::ReadActionParameters()
{
	return true;
}

bool CutAction::Execute()
{
	bool t = ReadActionParameters();
	pManager->Cut();
	pManager->Saved = false;
	pManager->first_zoom = true;

	Output* pOut = pManager->GetOutput();
	pOut->Clickeffect("Cut", ITM_CUT * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	if (pManager->Ccount >= 0)
	{
		while (!pManager->RedoList.empty())
			pManager->RedoList.pop();
		return true;
	}
	else return false;
}

void CutAction::Undo()
{
	pManager->Undo(CUT);
}

void CutAction::Redo()
{
	pManager->Redo(CUT);
}



CutAction::~CutAction()
{
}
