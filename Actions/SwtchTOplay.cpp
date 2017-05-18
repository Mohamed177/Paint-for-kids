#include "SwtchTOplay.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


SwtchTOplay::SwtchTOplay(ApplicationManager *pApp):Action(pApp)
{

}

SwtchTOplay::~SwtchTOplay()
{

}

bool SwtchTOplay::ReadActionParameters()
{
	return true;
}

void SwtchTOplay::Execute()
{
	if (pManager->GetFig_Counter() <= 0) {
		return;
	}
	Output* pOut = pManager->GetOutput();
	pManager->switchtoplay(); // to Un-select any selected figs.
	pOut->ClearToolBar();
	pOut->CreatePlayToolBar();
	
	pOut->PrintMessage("Welcome To Play Mode :) ..  Please Choose Your Favourite Game .");
}
