#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"


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
	void Load(ifstream &Infile);
	virtual void Resize(float, bool zoom);
	void PrintInfo(Output* pOut);
	void Move(Point nCorner);
	 double GetArea();
	Point GetCenter();
	bool ValidMove(Point,bool);
	CFigure *copy();

	// Inherited via CFigure
	virtual void Zoom(float factor) override;
	char GetType();
	
};

#endif