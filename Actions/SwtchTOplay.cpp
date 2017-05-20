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

bool SwtchTOplay::Execute()
{
	Output* pOut = pManager->GetOutput();
	pManager->switchtoplay(); // to Un-select any selected figs.
	pOut->ClearToolBar();
	pOut->CreatePlayToolBar();
	
	pOut->PrintMessage("Welcome To Play Mode :) ..  Please Choose Your Favourite Game .");
	return false;
}

void SwtchTOplay::Undo()
{
}
