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
	LoadFile.close();
	pManager->Saved = true;
}

LoadAction::~LoadAction()
{
}
