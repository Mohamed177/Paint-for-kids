#pragma once
#include "CFigure.h"
Point pPoint(Point p1, Point p2) ;
int CrossProuct(Point p1, Point p2) ;
class CTriangle :
	public CFigure
{
	Point p1;
	Point p2;
	Point p3;
public:
	CTriangle(Point, Point,Point , GfxInfo FigureGfxInfo);
	 void Draw(Output* pOut) const;
	bool Is_Selected(Point P) const;
	bool IsValid(Point, Point, Point);
	void Save(ofstream &OutFile);
	void Resize(float factor);
	 void Load(ifstream &Infile) ;
	void PrintInfo(Output* pOut);
	~CTriangle();
};

