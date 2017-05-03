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

void CopyAction::Execute()
{
	bool t = ReadActionParameters();
	pManager->Copy();
}




CopyAction::~CopyAction()
{
	
}
