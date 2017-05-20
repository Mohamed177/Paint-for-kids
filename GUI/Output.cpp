#include "Output.h"
#include<Windows.h>
#include<mmsystem.h>

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
	UI.FillColor = LIGHTSKYBLUE;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = DODGERBLUE;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlighting only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 4;	//width of the figures frames

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
	
	PlaySound("loadfx.WAV", NULL, SND_LOOP | SND_ASYNC);
	DrawIMAGE("Welcome", 0, 0, 1300, 500);
	DrawIMAGE("loading0", 0, 500, 1300, 200);
	Sleep(250);
	int j = 0;
	for (int i = 0; i < 145; i++)
	{
		DrawIMAGE("loadD", 177+j, 500, 18, 112);
		Sleep(10);
		j += 6;
	}

	PlaySound(NULL, NULL,0);
	
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;
	ClearDrawArea();
	CreateDrawToolBar();
	CreateStatusBar();
	Sleep(500);
	PlaySound("drawost.WAV", NULL, SND_LOOP | SND_ASYNC);
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
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, 1300, 50);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	ClearToolBar();
	PrintMessage("Drawing Mode .. Enjoy Drawing :)");
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
	MenuItemImages[ITM_UNDO]		   = "images\\MenuItems\\Undo.jpg";
	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight+3, UI.width, UI.ToolBarHeight+3);	

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateColorToolBar() const
{
	ClearToolBar();
	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);

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
	MenuItemImages[14] = "images\\MenuItems\\backk.jpg";
	



	//Draw menu item one image at a time
	for (int i = 0; i<ITM_COLOR_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);


}
//////////////////////////////////////////////////////////////////////////////////////////
void Output:: CreateBorderToolbar() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_DRAW;
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
	MenuItemImages[11] = "images\\MenuItems\\backk.jpg";
	

	//Draw menu item one image at a time
	for (int i = 0; i<12; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreatePlayToolBar() const
{
	PlaySound(NULL, NULL, 0);
	PlaySound("gameost.WAV", NULL, SND_LOOP | SND_ASYNC);
	ClearToolBar();
	PrintMessage("Welcome To Play Mode :) ..  Please Choose Your Favourite Game .");
	UI.InterfaceMode = MODE_PLAY;
	
	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_PICK_HIDE] = "images\\MenuItems\\pick.jpg";
	MenuItemImages[ITM_SCRAMBLE_FIND] = "images\\MenuItems\\scramble.jpg";
	MenuItemImages[ITM_EXIT_PLAY] = "images\\MenuItems\\Exit.jpg";
	MenuItemImages[ITM_SWITCH_DRAW] = "images\\MenuItems\\backk.jpg";


	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	

}
void Output::CreateZoomToolBar() const
{
	ClearToolBar();
	PrintMessage("Zooming Mode .. Enjoy :)");
	UI.InterfaceMode = MODE_ZOOM;

	
	string MenuItemImages[ZOOM_COUNT];
	MenuItemImages[ZOOM_LINE] = "images\\MenuItems\\dimmed-Line.jpg";
	MenuItemImages[ZOOM_RECT] = "images\\MenuItems\\dimmed-rec.jpg";
	MenuItemImages[ZOOM_CIRC] = "images\\MenuItems\\dimmed-circle.jpg";
	MenuItemImages[ZOOM_TRI] = "images\\MenuItems\\dimmed-tri.jpg";
	MenuItemImages[ZOOM_CHNG_DRAW_CLR] = "images\\MenuItems\\dimmed-colors.jpg";
	MenuItemImages[ZOOM_CHNG_FILL_CLR] = "images\\MenuItems\\dimmed-Fill.jpg";
	MenuItemImages[ZOOM_CHNG_BK_CLR] = "images\\MenuItems\\Background.jpg";
	MenuItemImages[ZOOM_DEL] = "images\\MenuItems\\Delete.jpg";
	MenuItemImages[ZOOM_SAVE] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ZOOM_LOAD] = "images\\MenuItems\\Load.jpg";
	MenuItemImages[ZOOM_EXIT] = "images\\MenuItems\\exit.jpg";
	MenuItemImages[ZOOM_SWITCH_PLAY] = "images\\MenuItems\\dimmed-to play.jpg";
	MenuItemImages[ZOOM_SELECT] = "images\\MenuItems\\Select.jpg";
	MenuItemImages[ZOOM_COPY] = "images\\MenuItems\\dimmed-Copy.jpg";
	MenuItemImages[ZOOM_CUT] = "images\\MenuItems\\dimmed-Cut.jpg";
	MenuItemImages[ZOOM_RESIZE] = "images\\MenuItems\\dimmed-Resize.jpg";
	MenuItemImages[ZOOM_MOVE] = "images\\MenuItems\\dimmed-Move.jpg";
	MenuItemImages[ZOOM_PASTE] = "images\\MenuItems\\dimmed-Paste.jpg";
	MenuItemImages[ZOOM_ZOOMOUT] = "images\\MenuItems\\Zoom Out.jpg";
	MenuItemImages[ZOOM_ZOOMIN] = "images\\MenuItems\\Zoom In.jpg";
	MenuItemImages[ZOOM_CHNG_BRDR_WDTH] = "images\\MenuItems\\dimmed-Line Width.jpg";
	MenuItemImages[ZOOM_BACK_DRAW] = "images\\MenuItems\\Backk.jpg";

	int menuitmwidth = UI.MenuItemWidth - 3;
	for (int i = 0; i < ZOOM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*menuitmwidth, 0, menuitmwidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);

}
void Output::CreateSelcted_ZoomToolBar() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_ZOOM;


	string MenuItemImages[ZOOM_COUNT];
	MenuItemImages[ZOOM_LINE] = "images\\MenuItems\\dimmed-Line.jpg";
	MenuItemImages[ZOOM_RECT] = "images\\MenuItems\\dimmed-rec.jpg";
	MenuItemImages[ZOOM_CIRC] = "images\\MenuItems\\dimmed-circle.jpg";
	MenuItemImages[ZOOM_TRI] = "images\\MenuItems\\dimmed-tri.jpg";
	MenuItemImages[ZOOM_CHNG_DRAW_CLR] = "images\\MenuItems\\colors.jpg";
	MenuItemImages[ZOOM_CHNG_FILL_CLR] = "images\\MenuItems\\Fill.jpg";
	MenuItemImages[ZOOM_CHNG_BK_CLR] = "images\\MenuItems\\Background.jpg";
	MenuItemImages[ZOOM_DEL] = "images\\MenuItems\\Delete.jpg";
	MenuItemImages[ZOOM_SAVE] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ZOOM_LOAD] = "images\\MenuItems\\Load.jpg";
	MenuItemImages[ZOOM_EXIT] = "images\\MenuItems\\exit.jpg";
	MenuItemImages[ZOOM_SWITCH_PLAY] = "images\\MenuItems\\dimmed-to play.jpg";
	MenuItemImages[ZOOM_SELECT] = "images\\MenuItems\\Select.jpg";
	MenuItemImages[ZOOM_COPY] = "images\\MenuItems\\dimmed-Copy.jpg";
	MenuItemImages[ZOOM_CUT] = "images\\MenuItems\\dimmed-Cut.jpg";
	MenuItemImages[ZOOM_RESIZE] = "images\\MenuItems\\dimmed-Resize.jpg";
	MenuItemImages[ZOOM_MOVE] = "images\\MenuItems\\dimmed-Move.jpg";
	MenuItemImages[ZOOM_PASTE] = "images\\MenuItems\\dimmed-Paste.jpg";
	MenuItemImages[ZOOM_ZOOMOUT] = "images\\MenuItems\\Zoom Out.jpg";
	MenuItemImages[ZOOM_ZOOMIN] = "images\\MenuItems\\Zoom In.jpg";
	MenuItemImages[ZOOM_CHNG_BRDR_WDTH] = "images\\MenuItems\\dimmed-Line Width.jpg";
	MenuItemImages[ZOOM_BACK_DRAW] = "images\\MenuItems\\Backk.jpg";

	int menuitmwidth = UI.MenuItemWidth - 3;
	for (int i = 0; i < ZOOM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*menuitmwidth, 0, menuitmwidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateFigMenu() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_DRAW;
	string MenuItemImages[3];
	MenuItemImages[0] = "images\\MenuItems\\NOT_Filled.jpg";
	MenuItemImages[1] = "images\\MenuItems\\Filled.jpg";
	MenuItemImages[2] = "images\\MenuItems\\backk.jpg";
	for (int i = 0; i<3; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);
}

void Output::CreatePHAreaToolbar() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_PLAY;
	string MenuItemImages[3];
	MenuItemImages[0] = "images\\MenuItems\\DE.jpg";
	MenuItemImages[1] = "images\\MenuItems\\ASC.jpg";
	MenuItemImages[2] = "images\\MenuItems\\backk.jpg";
	for (int i = 0; i<3; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);

}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreatePickHideToolbar() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_PLAY;
	string MenuItemImages[5];
	MenuItemImages[0] = "images\\MenuItems\\PH_Figs.jpg";
	MenuItemImages[1] = "images\\MenuItems\\PH_FillColor.jpg";
	MenuItemImages[2] = "images\\MenuItems\\PH_Both.jpg";
	MenuItemImages[3] = "images\\MenuItems\\PH_Area.jpg";
	MenuItemImages[4] = "images\\MenuItems\\backk.jpg";
	for (int i = 0; i<5; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);
}



//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateResizeMenu() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_DRAW;
	string MenuItemImages[5];
	MenuItemImages[0] = "images\\MenuItems\\X4.jpg";
	MenuItemImages[1] = "images\\MenuItems\\X2.jpg";
	MenuItemImages[2] = "images\\MenuItems\\X0.5.jpg";
	MenuItemImages[3] = "images\\MenuItems\\X0.25.jpg";
	MenuItemImages[4] = "images\\MenuItems\\backk.jpg";
	for (int i = 0; i<5; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);
}

void Output::ScrambleScreen() const
{
	pWind->SetPen(DEEPSKYBLUE, 4);
	pWind->DrawLine(UI.width / 2, UI.ToolBarHeight, UI.width / 2, UI.height - UI.StatusBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(DEEPSKYBLUE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 3, UI.width, UI.ToolBarHeight + 3);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::DRAWPIXEL(Point P1) const
{
	
	pWind->SetPen(UI.DrawColor,3);	//Set Drawing color & width

	pWind->DrawPixel(P1.x, P1.y);

}

void Output::DrawIMAGE(string s,int x, int y, int wid, int hyt) const
{
	if (s.at(0) == '1') pWind->DrawImage("images\\WellDoneWindow\\" + s.erase(0, 1) + ".jpg", x, y, wid, hyt);
	else  pWind->DrawImage("images\\MenuItems\\" + s + ".jpg", x, y, wid, hyt);
}

void Output::Clickeffect(string s, int x, int y, int wid, int hyt) const
{
	pWind->DrawImage("images\\MenuItems\\"+s+"CE1.jpg", x, y, wid, hyt);
	Sleep(70);
	pWind->DrawImage("images\\MenuItems\\" + s + "CE2.jpg", x, y, wid, hyt);
	Sleep(50);
	pWind->DrawImage("images\\MenuItems\\" + s + "CE3.jpg", x, y, wid, hyt);
	Sleep(50);
	pWind->DrawImage("images\\MenuItems\\" + s + ".jpg", x, y, wid, hyt);
}

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(32, BOLD, BY_NAME, "Segoe Print");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5)-12, msg);
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
int Output::getdrawint()
{
	return drawint;
}
void Output::setdrawint(int x)
{
	drawint = x;
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


void Output::DrawLINE(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width
	
	drawstyle style;
	if (LineGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(LineGfxInfo.FillClr);
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

