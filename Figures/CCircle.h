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
	char GetType();
	color GetColor();
	void Resize(float K, bool zoom);
    Point GetCenter();
	bool ValidMove(Point);
	void Move(Point);
	CFigure * copy() ;
private:
	Point Center,P2;
	double Raduis;

	// Inherited via CFigure
	virtual void Zoom(float factor) override;
};

