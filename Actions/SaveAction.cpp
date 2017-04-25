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
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Please enter the save's file name");
	FileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	return true;
}

void SaveAction::Execute()
{
	bool t = ReadActionParameters();
	if (!t)
		return;
	OutFile.open(FileName);
	pManager->SaveAll(OutFile);
	OutFile.close();
}