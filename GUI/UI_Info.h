#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY,	//Playing mode
	MODE_ZOOM
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_LINE,
	ITM_CIRC,		//Circle item in menu
	ITM_TRI,
	ITM_RECT,		//Recangle item in menu
	ITM_SELECT,   
	ITM_CHNG_DRAW_CLR,
	ITM_CHNG_FILL_CLR,
	ITM_CHNG_BK_CLR,
	ITM_CHNG_BRDR_WDTH,
	ITM_RESIZE,
	ITM_MOVE,
	ITM_UNDO,
	ITM_COPY,
	ITM_CUT,
	ITM_PASTE,
	ITM_ZOOMIN,
	ITM_ZOOMOUT,
	ITM_DEL,
	ITM_SAVE,
	ITM_LOAD,
	ITM_SWITCH_PLAY,
	
	//TODO: Add more items names here

	ITM_EXIT,		//Exit item
	
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here

	ITM_PICK_HIDE,
	ITM_SCRAMBLE_FIND,
	ITM_SWITCH_DRAW,
	ITM_EXIT_PLAY,		//Exit item
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum
	
};

enum ColorMenu 
{
	ITM_BLACK,
	ITM_BLUE,
	ITM_RED,
	ITM_GREEN,
	ITM_BROWN,
	ITM_BLUEVIOLET,
	ITM_CYAN,
	ITM_DARKGREEN,
	ITM_VIOLET,
	ITM_GRAY,
	ITM_ORANGE,
	ITM_PINK,
	ITM_SEAGREEN,
	ITM_YELLOW,
	ITM_BACK,

	ITM_COLOR_COUNT
};

enum ZoomMenuItemy //The items of the Draw menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ZOOM_LINE,
	ZOOM_CIRC,		//Circle item in menu
	ZOOM_TRI,
	ZOOM_RECT,		//Recangle item in menu
	ZOOM_SELECT,
	ZOOM_CHNG_DRAW_CLR,
	ZOOM_CHNG_FILL_CLR,
	ZOOM_CHNG_BK_CLR,
	ZOOM_CHNG_BRDR_WDTH,
	ZOOM_RESIZE,
	ZOOM_MOVE,
	ZOOM_COPY,
	ZOOM_CUT,
	ZOOM_PASTE,
	ZOOM_ZOOMIN,
	ZOOM_ZOOMOUT,
	ZOOM_DEL,
	ZOOM_SAVE,
	ZOOM_LOAD,
	ZOOM_SWITCH_PLAY,
	ZOOM_BACK_DRAW,

	ZOOM_EXIT,		//Exit item

	ZOOM_COUNT

};



__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	//Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	/// Add more members if needed
	
}UI;	//create a global object UI

#endif