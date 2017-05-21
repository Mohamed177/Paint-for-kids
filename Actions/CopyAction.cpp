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
	pOut->Clickeffect("copy", 671, 0, 61, 50);
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
