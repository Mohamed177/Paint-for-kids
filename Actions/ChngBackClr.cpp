#include "ChngBackClr.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


ChngBackClr::ChngBackClr(ApplicationManager *pApp):Action(pApp)
{
}

bool ChngBackClr::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateColorToolBar();
	UI.BkGrndColor = pIn->ChangeColor();
	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();
	return true;
}

void ChngBackClr::Execute()
{
	bool t = ReadActionParameters();
	pManager->Saved = false;
}

ChngBackClr::~ChngBackClr()
{
}
