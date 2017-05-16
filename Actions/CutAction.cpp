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

void CutAction::Execute()
{
	bool t = ReadActionParameters();
	pManager->Cut();
	pManager->Saved = false;
	pManager->first_zoom = true;

}



CutAction::~CutAction()
{
}
