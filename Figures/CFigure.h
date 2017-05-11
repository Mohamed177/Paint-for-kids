#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>
//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	static int counter ;
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo);
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	 virtual bool Is_Selected(Point v) const = 0; 
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	virtual void Zoom(float factor) = 0;
	void ChngBrdWdt(int p);         //changes the figure's border width
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	virtual char GetType() = 0;
	virtual Point GetCenter()=0;
	//virtual void Rotate() = 0;	//Rotate the figure
	virtual void Resize(float, bool zoom = false) = 0;	//Resize the figure
	virtual void Move(Point) = 0;		//Move the figure
	virtual bool ValidMove(Point)=0;
	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file
	virtual CFigure * copy() = 0;
	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif