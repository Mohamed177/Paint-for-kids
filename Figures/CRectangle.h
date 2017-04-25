#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"
#include <fstream>

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	bool Is_Selected(Point P) const;
	void Save(ofstream &OutFile);
};

#endif