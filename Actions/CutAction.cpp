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

	Output* pOut = pManager->GetOutput();
	pOut->Clickeffect("Cut", 732, 0, 61, 50);
}



CutAction::~CutAction()
{
}
