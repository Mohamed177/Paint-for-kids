#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();		
	void Output::CreateColorToolBar() const;
	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateBorderToolbar() const;
	void CreateStatusBar() const;	//create the status bar
	void CreatePickHideToolbar() const;
	void CreateFigMenu() const;
	void CreateResizeMenu() const;
	void ScrambleScreen() const;
	void ClearToolBar() const; //        E7NA ELLY 3MLNAHA.
	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a rectangle
	void DrawTRI(Point P1, Point P2,Point P3, GfxInfo RectGfxInfo, bool selected=false) const;	
	void DrawLINE(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;
	void DrawCIRC(Point P1, double r, GfxInfo RectGfxInfo, bool selected) const;
	///Make similar functions for drawing all other figures.
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	void setCrntPenWidth(int p); // hand-made 
	void setBackColor(color k);

	void StoreImage(image &imgThis, const unsigned usX, const unsigned short usY, const unsigned short usWidth, const unsigned short usHeight); // momken tt3'yr lw 3'alt

	void DrawImage(image &imgThis, const int iX, const int iY, const int iWidth, const int iHeight);

	~Output();
};

#endif