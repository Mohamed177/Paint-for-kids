#include "SaveAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


SaveAction::SaveAction(ApplicationManager* pApp):Action(pApp)
{
	FileName = "";
}


SaveAction::~SaveAction()
{
}

bool SaveAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	if (pOut->getdrawint() == 0 ) pOut->DrawIMAGE("saveCE", 1037, 0, 61, 50);
	pOut->setdrawint(0);
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Please enter the save's file name");
	FileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	pOut->DrawIMAGE("save", 1037, 0, 61, 50);
	return true;
}

void SaveAction::Execute()
{
	bool t = ReadActionParameters();
	if (!t)
		return;
	pManager->Saved = true;
	OutFile.open(FileName);
	pManager->SaveAll(OutFile);
	OutFile.close();
}