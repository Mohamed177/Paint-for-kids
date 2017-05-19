#include "Scramble.h"
#include "../ApplicationManager.h"
#include "..\GUI\Output.h"
#include "../GUI/Input.h"
#include <system_error>

Scramble::Scramble(ApplicationManager *pApp):Action(pApp)
{
	True_counts = 0;
	False_counts = 0;
	PlaySound(NULL, NULL, 0);
	PlaySound("sc.WAV", NULL, SND_LOOP | SND_ASYNC);

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
	pOut->DrawIMAGE("scrambleCE", 61, 0, 61, 50);
	bool playing;
	string score = "";
	pOut->PrintMessage("Choose the highlighted figures.");
	int z = pManager->getZ_No();
	while (pManager->getZ_No() > 0)
	{
		int z_id = pManager->highlight();
		pManager->UpdateInterface(TO_SCRAMBLE_FIND);
		pOut->DrawIMAGE("scrambleCE", 61, 0, 61, 50);
		pOut->PrintMessage(score);
		playing = ReadActionParameters();
		if (!playing)
			break;
		if (p.x < UI.width / 2 || p.y >= UI.height-UI.StatusBarHeight)
			continue;
		score = "";
		if (pManager->getScrmbleFig(p,z_id))
		{
			mciSendString("play correct.wav", NULL, 0, NULL);
			pManager->ScrambleDelete();
			True_counts++;
		}
		else
		{
			mciSendString("play wrong.wav", NULL, 0, NULL);
			False_counts++;
		}
		score += "RightClicks = " + to_string(True_counts) + " WrongClicks = " + to_string(False_counts);
		pOut->PrintMessage(score);
		//delete
	}
	PlaySound(NULL, NULL, 0);
	PlaySound("kids.WAV", NULL, SND_ASYNC);
	if (False_counts >= z) False_counts = z;
	for (int  i = 3; i >0; i--)
	{
		pOut->PrintMessage("Your Score Is = " + to_string(z - False_counts) + " , Thanks For Playing :)                   Restarting in " + to_string(i) + " Seconds ...");
		for (int i = 0; i < 10; i++)
		{
			pOut->DrawIMAGE("1frame_" + to_string(i) + "_delay-0.1s", 0, 55, 1300, 595);
			Sleep(100);
		}
	}
	pOut->DrawIMAGE("scramble", 61, 0, 61, 50);
	pOut->ClearStatusBar();

}
