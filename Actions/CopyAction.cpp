#include "CopyAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


CopyAction::CopyAction(ApplicationManager * pApp) :Action(pApp)
{

}
bool CopyAction::ReadActionParameters()
{
	return true;
}

bool CopyAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	bool t = ReadActionParameters();
	pManager->Copy();
	pOut->Clickeffect("copy", ITM_COPY * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	return false;
}

void CopyAction::Undo()
{
}

void CopyAction::Redo()
{
}




CopyAction::~CopyAction()
{
	
}
