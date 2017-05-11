#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label+= Key;
		pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT:						{ return DRAW_RECT;} // look here ya taha ya 312.
			case ITM_CIRC:						{ return DRAW_CIRC;}
			case ITM_LINE:						{ return DRAW_LINE;}
			case ITM_TRI:						{ return DRAW_TRI;}
			case ITM_CHNG_DRAW_CLR:				{ return	CHNG_DRAW_CLR;}
			case ITM_CHNG_FILL_CLR:				{ return	CHNG_FILL_CLR;}	//Change the filling color
			case ITM_CHNG_BK_CLR:				{ return	CHNG_BK_CLR;} //Change background color
			case ITM_CHNG_BRDR_WDTH:			{ return CHNG_BRDR_WDTH; }
			case ITM_DEL:						{ return	DEL;	}	//Delete a figure(s)
			case ITM_SAVE:						{ return	SAVE;	}	//Save the whole graph to a file
			case ITM_LOAD:						{ return	LOAD;	}	//Load a graph from a file
			case ITM_SWITCH_PLAY:				{ return TO_PLAY; } // SWITCHES FROM DRAW MODE TO PLAY MODE YA RIAD YA 312
			case ITM_SELECT:					{ return TO_SELECT;}
			case ITM_CUT:						{ return CUT; }
			case ITM_COPY:						{ return COPY; }
			case ITM_RESIZE:					{ return RESIZE; }
			case ITM_MOVE:						{ return MOVE; }
			case ITM_ZOOMIN:					{ return ZOOMIN; }
			case ITM_ZOOMOUT:					{ return ZOOMOUT; }
			case ITM_PASTE:						{ return PASTE; }
			case ITM_EXIT:						{ return EXIT;}


				/*	//	case ITM_MOVE:  return	MOVE,			//Move a figure(s)
						//   case ITM_RESIZE:  return	RESIZE,			//Resize a figure(s)
			//    case ITM_ROTATE:  return	ROTATE,			//Rotate a figure(s)
					//	case ITM_SEND_BACK:  return	SEND_BACK,		//Send a figure to the back of all figures
					//	case ITM_BRNG_FRNT:  return	BRNG_FRNT,		//Bring a figure to the front of all figures*/
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_PLAY)	//GUI is in PLAY mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SCRAMBLE_FIND: return TO_SCRAMBLE_FIND;
			case ITM_PICK_HIDE: return TO_PICK_HIDE;
			case ITM_EXIT_PLAY: return EXIT;
			case ITM_SWITCH_DRAW: return TO_DRAW;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
			//[2] User clicks on the drawing area
			if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
			{
				return DRAWING_AREA;
			}

			//[3] User clicks on the status bar
			return STATUS;
			///TODO:
			//perform checks similar to Draw mode checks above
			//and return the correspoding action

		}

	}

}
/////////////////////////////////
color Input::ChangeBackColor() 
{

	f:
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	if (y >= 0 && y < UI.ToolBarHeight)
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
		if (ClickedItemOrder == 14) return UI.BkGrndColor;
		color c = SNOW;
		switch (ClickedItemOrder)
		{
		case ITM_BLACK: { c = BLACK;   }
						break;
		case ITM_BLUE: { c = BLUE; }
					   break;
		case ITM_RED: {  c = RED; }
					  break;
		case ITM_GREEN: { c = GREEN; }
						break;
		case ITM_BROWN: { c = BROWN; }
					   break;
		case ITM_BLUEVIOLET: {  c = BLUEVIOLET; }
					  break;
		case ITM_CYAN: { c = CYAN; }
						break;
		case ITM_DARKGREEN: { c = DARKGREEN; }
					   break;
		case ITM_VIOLET: {  c = VIOLET; }
					  break;
		case ITM_GRAY: { c = GRAY; }
						break;
		case ITM_ORANGE: { c = ORANGE; }
					   break;
		case ITM_PINK: {  c = PINK; }
					  break;
		case ITM_SEAGREEN: { c = SEAGREEN; }
						break;
		case ITM_YELLOW: { c = YELLOW; }
						break; 
		default:goto f;
		}
		return c;
	}
	else 
	{
		goto f;
	}
	
}

int Input::IsFilled() const
{
	f:
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	if (y >= 0 && y < UI.ToolBarHeight)
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		if (ClickedItemOrder<3)
		{
			return ClickedItemOrder;
		}
			goto f;
			
	}
	goto f;
}

int Input::ResizeFactor() const
{
f:
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	if (y >= 0 && y < UI.ToolBarHeight)
	{
		//Check whick Menu item was clicked
		//==> This assumes that menu items are lined up horizontally <==
		int ClickedItemOrder = (x / UI.MenuItemWidth);
		if (ClickedItemOrder<5)
		{
			return ClickedItemOrder;
		}
		goto f;

	}
	goto f;
}

Input::~Input()
{
}
