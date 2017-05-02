#include "ApplicationManager.h"
#include <fstream>
int CrossProuct(Point p1, Point p2) 
{
	return (p1.x * p2.y) - (p2.x * p1.y);
}
Point pPoint(Point p1, Point p2)  
{
	Point v;
	v.x = p2.x - p1.x;
	v.y = p2.y - p1.y ;
	return v;
}
/*ofstream& operator<<(ofstream& OutFile, color a)
{
	if (a == BLACK)
		OutFile << "BLACK ";
	else if (a == BLUE)
		OutFile << "BLUE ";
	else if (a == RED)
		OutFile << "RED ";
	else if (a == DARKGREEN)
		OutFile << "DARKGREEN ";
	else if (a == GREEN)
		OutFile << "GREEN ";
	else if (a == BROWN)
		OutFile << "BROWN ";
	else if (a == BLUEVIOLET)
		OutFile << "BLUEVIOLET ";
	else if (a == CYAN)
		OutFile << "CYAN ";
	else if (a == VIOLET)
		OutFile << "VIOLET ";
	else if (a == GRAY)
		OutFile << "GRAY ";
	else if (a == ORANGE)
		OutFile << "ORANGE ";
	else if (a == PINK)
		OutFile << "PINK ";
	else if (a == SEAGREEN)
		OutFile << "SEAGREEN ";
	else if (a == YELLOW)
		OutFile << "YELLOW ";
	return OutFile;
}*/
int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	do
	{		
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		AppManager.ExecuteAction(ActType);

		//Update the interface
		if (ActType == ZOOMIN || ActType == ZOOMOUT)
			continue;
		else
			AppManager.UpdateInterface();	

	}while(ActType != EXIT);
	

	
	return 0;
}

