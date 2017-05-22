#include "LoadAction.h"
#include "SaveAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


LoadAction::LoadAction(ApplicationManager* pApp) :Action(pApp)
{
	FileName= "";
	
}
bool LoadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	if (UI.InterfaceMode == MODE_ZOOM)
		pOut->DrawIMAGE("LoadCE", ZOOM_LOAD * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	else
		pOut->DrawIMAGE("LoadCE", ITM_LOAD * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pOut->setdrawint(1);
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Please enter the name of the text folder to load from : ");
	FileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	return true;
}
bool LoadAction::Execute()
{
	bool t = ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	LoadFile.open(FileName);
	if (!LoadFile.is_open())
	{
		pOut->PrintMessage("Error file not found");
		if (UI.InterfaceMode == MODE_ZOOM)
			pOut->DrawIMAGE("Load", ZOOM_LOAD * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
		else
			pOut->DrawIMAGE("Load", ITM_LOAD * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
		return false;
	}
	pManager->LoadAll(LoadFile);
	if (UI.InterfaceMode == MODE_ZOOM)
		pOut->DrawIMAGE("Load", ZOOM_LOAD * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	else
		pOut->DrawIMAGE("Load", ITM_LOAD * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	LoadFile.close();
	pManager->Saved = true;
	if (UI.InterfaceMode == MODE_DRAW)
		pManager->first_zoom = true;
	return false;
}

LoadAction::~LoadAction()
{
}

void LoadAction::Undo()
{
}

void LoadAction::Redo()
{
}
