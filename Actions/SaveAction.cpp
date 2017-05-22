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

void SaveAction::Redo()
{
}

bool SaveAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	if (pOut->getdrawint() == 0)
	{
		if (UI.InterfaceMode == MODE_ZOOM)
			pOut->DrawIMAGE("saveCE", ZOOM_SAVE * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
		else pOut->DrawIMAGE("saveCE", ITM_SAVE * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	}
	pOut->setdrawint(0);
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Please enter the save's file name");
	FileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	if (UI.InterfaceMode == MODE_ZOOM)
		pOut->DrawIMAGE("save", ZOOM_SAVE * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	else pOut->DrawIMAGE("save", ITM_SAVE * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
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