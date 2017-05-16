#include"ChngBrdrWdth.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "SelectAction.h"
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
	pOut->CreateBorderToolbar();
	pOut->PrintMessage("Choose The New Border Width. ");
	pManager->ChngeBrdrWdth(); 
	pOut->CreateDrawToolBar();
	pOut->Clickeffect("Line Width", 488, 0, 61, 50);
	pManager->Saved = false;
	pManager->first_zoom = true;

}