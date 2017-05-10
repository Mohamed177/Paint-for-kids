#include"ChngBrdrWdth.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChngBrdrWdth::ChngBrdrWdth(ApplicationManager *pApp) : Action(pApp)

{
}

ChngBrdrWdth::~ChngBrdrWdth()
{
}

bool ChngBrdrWdth ::  ReadActionParameters()
{
	return true;
}

void ChngBrdrWdth :: Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->ClearToolBar();
	pOut->CreateBorderToolbar();
	pManager->ChngeBrdrClr(); 
}