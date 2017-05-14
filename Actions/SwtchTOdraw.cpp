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
	PlaySound(NULL, NULL, 0);
	PlaySound("drawost.WAV", NULL, SND_LOOP | SND_ASYNC);
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Drawing Mode .. Enjoy Drawing :) ");
}
