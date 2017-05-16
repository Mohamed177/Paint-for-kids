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
	pOut->DrawIMAGE("LoadCE", 1101, 0, 61, 50);
	pOut->setdrawint(1);
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Please enter the name of the text folder to load from : ");
	FileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	return true;
}
void LoadAction::Execute()
{
	bool t = ReadActionParameters();
	LoadFile.open(FileName);
	pManager->LoadAll(LoadFile);
	Output* pOut = pManager->GetOutput();
	pOut->DrawIMAGE("Load", 1101, 0, 61, 50);
	LoadFile.close();
	pManager->Saved = true;
	if (UI.InterfaceMode == MODE_DRAW)
		pManager->first_zoom = true;
	
}

LoadAction::~LoadAction()
{
}
