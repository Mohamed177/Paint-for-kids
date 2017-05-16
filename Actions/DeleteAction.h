
#include "..\DefS.h"
#include "..\ApplicationManager.h"
#include "Action.h"

class DeleteAction:public Action
{
public:
	DeleteAction(ApplicationManager* p);
	bool ReadActionParameters();
	void Execute();
	~DeleteAction();
private:
	

};

