#include "ApplicationManager.h"
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
		AppManager.UpdateInterface();	

	}while(ActType != EXIT);
	

	
	return 0;
}

