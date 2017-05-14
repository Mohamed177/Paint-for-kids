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
	mciSendString(TEXT("stop gameost.wav"), NULL, 0, NULL);
	mciSendString(TEXT("play drawost.wav"), NULL, 0, NULL);
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Drawing Mode .. Enjoy Drawing :) ");
}
