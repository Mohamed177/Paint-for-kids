
#include "..\DefS.h"
#include "..\ApplicationManager.h"
#include "Action.h"

class DeleteAction:public Action
{
public:
	DeleteAction(ApplicationManager* p);
	bool ReadActionParameters();
	bool Execute();
	~DeleteAction();
private:
	


	// Inherited via Action
	virtual void Undo() override;


	// Inherited via Action
	virtual void Redo() override;

};

