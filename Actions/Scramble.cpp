#include "Scramble.h"
#include "../ApplicationManager.h"
#include "..\GUI\Output.h"
#include "../GUI/Input.h"

Scramble::Scramble(ApplicationManager *pApp):Action(pApp)
{
}

bool Scramble::ReadActionParameters()
{
	return true;
}

void Scramble::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->ScrambleScreen();
	pManager->Zcount = 0;
	pManager->ZoomCopy();
	pManager->Zoom(1.0/2);
	pManager->ScrambleMove();

}
