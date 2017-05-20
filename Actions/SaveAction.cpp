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

void SaveAction::Undo()
{
}

bool SaveAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	if (pOut->getdrawint() == 0)
	{
		if (UI.InterfaceMode == MODE_ZOOM)
			pOut->DrawIMAGE("saveCE", 986, 0, 58, 50);
		else pOut->DrawIMAGE("saveCE", 1037, 0, 61, 50);
	}
	pOut->setdrawint(0);
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Please enter the save's file name");
	FileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	pOut->DrawIMAGE("save", 1037, 0, 61, 50);
	return true;
}

bool SaveAction::Execute()
{
	bool t = ReadActionParameters();
	if (!t)
		return false;
	pManager->Saved = true;
	pManager->first_zoom = true;
	OutFile.open(FileName);
	pManager->SaveAll(OutFile);
	OutFile.close();
	return false;
}