#pragma once
#include "CFigure.h"

class CCircle: public CFigure
{
public:
	CCircle(Point P1, double R, GfxInfo FigureGfxInfo);
	void Draw(Output *pOut) const;
	bool Is_Selected( Point P)const;
	void Save(ofstream& OutFile);
	void Load(ifstream &Infile);
	void Resize(float K);
    Point GetCenter();
	bool ValidMove(Point);
	void Move(Point);
	CFigure * copy() ;
private:
	Point Center,P2;
	double Raduis;
};

