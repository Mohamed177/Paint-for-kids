#include "CFigure.h"
class CCircle: public CFigure
{
public:
	CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo);
	void Draw(Output *pOut) const;
	bool Is_Selected( Point P)const;

private:
	Point Center;
	Point P2;
};

