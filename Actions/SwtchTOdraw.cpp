#include "SwtchTOdraw.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


SwtchTOdraw::SwtchTOdraw(ApplicationManager *pApp) :Action(pApp)
{

}

SwtchTOdraw::~SwtchTOdraw()
{

}

bool SwtchTOdraw::ReadActionParameters()
{
	return true;
}

void SwtchTOdraw::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Welcome To Draw Mode :) ");
}
