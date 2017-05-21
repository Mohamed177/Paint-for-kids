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
	bool t = pManager->Send(1);
	return false;
}
