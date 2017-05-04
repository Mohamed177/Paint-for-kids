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

	// Inherited via Action
	virtual bool ReadActionParameters() override;

	virtual void Execute() override;

};
