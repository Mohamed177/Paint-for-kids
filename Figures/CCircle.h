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

	void Resize(float K, bool zoom);
    Point GetCenter();
	bool ValidMove(Point, bool srcamble);
	void Move(Point);
	CFigure * copy() ;
	double GetArea();
private:
	Point Center,P2;
	double Radius;

	// Inherited via CFigure
	virtual void Zoom(float factor) override;

	// Inherited via CFigure
	virtual void PrintInfo(Output * pOut) override;
};

