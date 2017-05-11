#include"ChngDrwClr.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


ChangeDrawColor::ChangeDrawColor(ApplicationManager *pApp) : Action(pApp)
{
}

ChangeDrawColor::~ChangeDrawColor()
{
}

bool ChangeDrawColor::ReadActionParameters()
{
	return true;
}

void ChangeDrawColor::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->ClearToolBar();
	pOut->CreateColorToolBar();
	pManager->ChangeDrwColor();
}