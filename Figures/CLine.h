#pragma once
#include "CFigure.h"
#include <fstream>
class CLine :
	public CFigure
{
private:
	Point p1;
	Point p2;
public:
	CLine(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	bool Is_Selected(Point P) const;

	void Save(ofstream &OutFile);
	void Load(ifstream &Infile);
	bool Resize(float factor, bool zoom);
	 Point GetCenter();
	 bool ValidMove(Point, bool scramble);
	 CFigure *copy();
	 void Move(Point v);
	 char GetType();
	 double GetArea();

	~CLine();

	// Inherited via CFigure
	virtual void Zoom(float factor) override;

	// Inherited via CFigure
	virtual void PrintInfo(Output * pOut) override;
};

