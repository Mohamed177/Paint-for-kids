#include"ChngFillClr.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


ChangeFillColor::ChangeFillColor(ApplicationManager *pApp) : Action(pApp)
{
}

ChangeFillColor::~ChangeFillColor()
{
}

bool ChangeFillColor::ReadActionParameters()
{
	return true;
}

void ChangeFillColor::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->ClearToolBar();
	pOut->CreateColorToolBar();
	pManager->ChangeFllColor();
}