#include "Scramble.h"
#include "../ApplicationManager.h"
#include "..\GUI\Output.h"
#include "../GUI/Input.h"
#include <system_error>
Scramble::Scramble(ApplicationManager *pApp):Action(pApp)
{
	True_counts = 0;
	False_counts = 0;
}

bool Scramble::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(p.x, p.y);
	if (p.y > UI.ToolBarHeight)
		return true;
	return false;
}

void Scramble::Execute()
{
	Output* pOut = pManager->GetOutput();
	pManager->Zcount = 0;
	pManager->ZoomCopy();
	pManager->Zoom(1.0 / 2);
	pManager->ScrambleCopy();
	pManager->ScrambleMove();
	pManager->RandomOrder();
	pManager->RandomPoint();
	pManager->UpdateInterface(TO_SCRAMBLE_FIND);
	bool playing;
	while (pManager->getZ_No() > 0)
	{
		int z_id = pManager->highlight();
		pManager->UpdateInterface(TO_SCRAMBLE_FIND);
		playing = ReadActionParameters();
		if (!playing)
			break;
		if (p.x < UI.width / 2 || p.y >= UI.height-UI.StatusBarHeight)
			continue;
		if (pManager->getScrmbleFig(p,z_id))
		{
			pManager->ScrambleDelete();
			True_counts++;
		}
		else
		{
			False_counts++;
		}
		pManager->UpdateInterface(TO_SCRAMBLE_FIND);
		//delete
	}
}
