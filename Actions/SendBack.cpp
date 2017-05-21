#include "SendBack.h"



SendBack::SendBack(ApplicationManager *pApp) :Action(pApp)
{

}


SendBack::~SendBack()
{
}

bool SendBack::ReadActionParameters()
{
	return true; 
}

bool SendBack::Execute()
{
	 bool t = pManager->Send(1);
	 return false;
}
