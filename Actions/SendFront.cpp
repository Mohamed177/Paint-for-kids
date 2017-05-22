#include "SendFront.h"



SendFront::SendFront(ApplicationManager *pApp) :Action(pApp)
{
}


SendFront::~SendFront()
{
}

bool SendFront::ReadActionParameters()
{
	return true;
}

bool SendFront::Execute()
{
	bool t = pManager->Send(0);
	return false;
}

void SendFront::Undo()
{
}

void SendFront::Redo()
{
}
