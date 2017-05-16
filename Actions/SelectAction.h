#include "..\ApplicationManager.h"
#include"Action.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

class SelectAction:public Action
{
public:
	SelectAction(ApplicationManager *pApp);
	bool ReadActionParameters();
	void Execute();
	static int getZoomSlctCount();
	~SelectAction();
private:
	static int SCounter, ZCounter;
	CFigure* temp;
	Point P;
};

