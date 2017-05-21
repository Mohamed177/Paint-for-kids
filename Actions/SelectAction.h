#include "..\ApplicationManager.h"
#include"Action.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <stack>
using namespace std;
class SelectAction:public Action
{
public:
	SelectAction(ApplicationManager *pApp);
	bool ReadActionParameters();
	bool Execute();
	static int getZoomSlctCount();
	static void ResetZoomSlctCount();
	static void setSCounter(int sc);
	static int getSlctCount();
	~SelectAction();
private:
	static int SCounter, ZCounter;
	stack<Point> selected_IDs, redo;
	CFigure* temp;
	Point P;

	// Inherited via Action
	virtual void Undo() override;

	// Inherited via Action
	virtual void Redo() override;
};

