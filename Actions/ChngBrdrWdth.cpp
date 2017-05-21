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

bool ChngBrdrWdth :: Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateBorderToolbar();
	pOut->PrintMessage("Choose The New Border Width. ");
	crntbrdr = UI.PenWidth;
	newbrdr = pManager->ChngeBrdrWdth();
	if (newbrdr == crntbrdr)
		while (!pManager->RedoList.empty())
			pManager->RedoList.pop();
	pOut->CreateDrawToolBar();
	pOut->Clickeffect("Line Width", 488, 0, 61, 50);
	pManager->Saved = false;
	pManager->first_zoom = true;
	return true;
}

void ChngBrdrWdth::Undo()
{
	pManager->Undo(CHNG_BRDR_WDTH, BLACK, crntbrdr);
}

void ChngBrdrWdth::Redo()
{
	pManager->Redo(CHNG_BRDR_WDTH, BLACK, newbrdr);
}
