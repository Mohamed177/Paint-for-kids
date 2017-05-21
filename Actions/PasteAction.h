#include"Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
class PasteAction:public Action
{
public:
	PasteAction(ApplicationManager* pApp);

private:
	Point P;
	int count;
	// Inherited via Action
	virtual bool ReadActionParameters() override;

	virtual bool Execute() override;


	// Inherited via Action
	virtual void Undo() override;


	// Inherited via Action
	virtual void Redo() override;

};
