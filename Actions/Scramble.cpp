#include "Scramble.h"
#include "../ApplicationManager.h"
#include "..\GUI\Output.h"
#include "../GUI/Input.h"
#include <system_error>
Scramble::Scramble(ApplicationManager *pApp):Action(pApp)
{
	True_counts = 0;
	Fasle_counts = 0;
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
	pManager->UpdateInterface(TO_SCRAMBLE_FIND);
	pOut->ScrambleScreen();
	int pause;
	cout << "Press any key to continue...";
	cin >> pause;

}
