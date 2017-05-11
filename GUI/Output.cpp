#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	
	UI.width = 1300;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;

	
	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 61;
	
	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::
CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearToolBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(LIGHTGOLDENRODYELLOW);
	pWind->DrawRectangle(0, 0, 1300, 50);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	ClearToolBar();
	PrintMessage("");
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way
	
	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_LINE]		   = "images\\MenuItems\\Line.jpg";
	MenuItemImages[ITM_RECT]           = "images\\MenuItems\\Rectangle.jpg";
	MenuItemImages[ITM_CIRC]		   = "images\\MenuItems\\Circle.jpg";
	MenuItemImages[ITM_TRI]            = "images\\MenuItems\\Triangle.jpg";
	MenuItemImages[ITM_CHNG_DRAW_CLR]  = "images\\MenuItems\\colors.jpg";
	MenuItemImages[ITM_CHNG_FILL_CLR]  = "images\\MenuItems\\Fill.jpg";
	MenuItemImages[ITM_CHNG_BK_CLR]    = "images\\MenuItems\\Background.jpg";
	MenuItemImages[ITM_DEL]            = "images\\MenuItems\\Delete.jpg";
	MenuItemImages[ITM_SAVE]           = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_LOAD]           = "images\\MenuItems\\Load.jpg";
	MenuItemImages[ITM_EXIT]           = "images\\MenuItems\\exit.jpg";
	MenuItemImages[ITM_SWITCH_PLAY]    = "images\\MenuItems\\to play.jpg";
	MenuItemImages[ITM_SELECT]		   = "images\\MenuItems\\Select.jpg";
	MenuItemImages[ITM_COPY]		   = "images\\MenuItems\\Copy.jpg";
	MenuItemImages[ITM_CUT]			   = "images\\MenuItems\\Cut.jpg";
	MenuItemImages[ITM_RESIZE]		   = "images\\MenuItems\\Resize.jpg";
	MenuItemImages[ITM_MOVE]		   = "images\\MenuItems\\Move.jpg";
	MenuItemImages[ITM_PASTE]		   = "images\\MenuItems\\Paste.jpg";
	MenuItemImages[ITM_ZOOMOUT]		   = "images\\MenuItems\\Zoom Out.jpg";
	MenuItemImages[ITM_ZOOMIN]		   = "images\\MenuItems\\Zoom In.jpg";
	MenuItemImages[ITM_CHNG_BRDR_WDTH] = "images\\MenuItems\\Line Width.jpg";
	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateColorToolBar() const
{
	ClearToolBar();

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[ITM_COLOR_COUNT];
	MenuItemImages[0] = "images\\MenuItems\\Black.jpg";
	MenuItemImages[1] = "images\\MenuItems\\Blue.jpg";
	MenuItemImages[2] = "images\\MenuItems\\Red.jpg";
	MenuItemImages[3] = "images\\MenuItems\\Green.jpg";
	MenuItemImages[4] = "images\\MenuItems\\Brown.jpg";
	MenuItemImages[5] = "images\\MenuItems\\BlueViolet.jpg";
	MenuItemImages[6] = "images\\MenuItems\\Cyan.jpg";
	MenuItemImages[7] = "images\\MenuItems\\DarkGreen.jpg";
	MenuItemImages[8] = "images\\MenuItems\\Violet.jpg";
	MenuItemImages[9] = "images\\MenuItems\\Gray.jpg";
	MenuItemImages[10] = "images\\MenuItems\\Orange.jpg";
	MenuItemImages[11] = "images\\MenuItems\\Pink.jpg";
	MenuItemImages[12] = "images\\MenuItems\\SeaGreen.jpg";
	MenuItemImages[13] = "images\\MenuItems\\Yellow.jpg";
	MenuItemImages[14] = "images\\MenuItems\\back.jpg";
	



	//Draw menu item one image at a time
	for (int i = 0; i<ITM_COLOR_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output:: CreateBorderToolbar() const
{
	ClearToolBar();

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[12];
	MenuItemImages[0] = "images\\MenuItems\\1.jpg";
	MenuItemImages[1] = "images\\MenuItems\\2.jpg";
	MenuItemImages[2] = "images\\MenuItems\\4.jpg";
	MenuItemImages[3] = "images\\MenuItems\\6.jpg";
	MenuItemImages[4] = "images\\MenuItems\\8.jpg";
	MenuItemImages[5] = "images\\MenuItems\\10.jpg";
	MenuItemImages[6] = "images\\MenuItems\\12.jpg";
	MenuItemImages[7] = "images\\MenuItems\\14.jpg";
	MenuItemImages[8] = "images\\MenuItems\\16.jpg";
	MenuItemImages[9] = "images\\MenuItems\\18.jpg";
	MenuItemImages[10] = "images\\MenuItems\\20.jpg";
	MenuItemImages[11] = "images\\MenuItems\\back.jpg";
	

	//Draw menu item one image at a time
	for (int i = 0; i<12; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreatePlayToolBar() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_PLAY;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_PICK_HIDE] = "images\\MenuItems\\pick.jpg";
	MenuItemImages[ITM_SCRAMBLE_FIND] = "images\\MenuItems\\scramble.jpg";
	MenuItemImages[ITM_EXIT_PLAY] = "images\\MenuItems\\exit.jpg";
	MenuItemImages[ITM_SWITCH_DRAW] = "images\\MenuItems\\to draw.jpg";


	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateFigMenu() const
{
	ClearToolBar();

	string MenuItemImages[3];
	MenuItemImages[0] = "images\\MenuItems\\NOT_Filled.jpg";
	MenuItemImages[1] = "images\\MenuItems\\Filled.jpg";
	MenuItemImages[2] = "images\\MenuItems\\back.jpg";
	for (int i = 0; i<3; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreatePickHideToolbar() const
{
	ClearToolBar();

	string MenuItemImages[5];
	MenuItemImages[0] = "images\\MenuItems\\NOT_Filled.jpg";
	MenuItemImages[1] = "images\\MenuItems\\Filled.jpg";
	MenuItemImages[2] = "images\\MenuItems\\back.jpg";
	MenuItemImages[3] = "images\\MenuItems\\back.jpg";
	MenuItemImages[4] = "images\\MenuItems\\back.jpg";
	for (int i = 0; i<5; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}



//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateResizeMenu() const
{
	ClearToolBar();

	string MenuItemImages[5];
	MenuItemImages[0] = "images\\MenuItems\\X4.jpg";
	MenuItemImages[1] = "images\\MenuItems\\X2.jpg";
	MenuItemImages[2] = "images\\MenuItems\\X0.5.jpg";
	MenuItemImages[3] = "images\\MenuItems\\X0.25.jpg";
	MenuItemImages[4] = "images\\MenuItems\\back.jpg";
	for (int i = 0; i<5; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::ScrambleScreen() const
{
	ClearDrawArea();
	pWind->SetPen(CYAN, 4);
	pWind->DrawLine(UI.width / 2, UI.ToolBarHeight, UI.width / 2, UI.height - UI.StatusBarHeight);
	PrintMessage("Choose the highlighted figures.");
}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::setCrntPenWidth(int p)
{
	UI.PenWidth = p;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::setBackColor(color k)
{
	UI.BkGrndColor = k;
}
//////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;
	
	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;

	
	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
	
}
void Output::DrawTRI(Point P1, Point P2,Point P3, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y,P3.x,P3.y, style);
}
void Output::DrawLINE(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);
}
void Output::DrawCIRC(Point P1, double r, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawCircle(P1.x, P1.y, r, style);
}

void Output::StoreImage(image &imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight)
{
	pWind->StoreImage(imgThis, usX,  usY, usWidth,  usHeight);
}

void Output::DrawImage(image &imgThis, const int iX, const int iY, const int iWidth, const int iHeight)
{
	pWind->DrawImage(imgThis, iX, iY, iWidth, iHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

