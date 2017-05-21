#include"Action.h"


class SwtchTOplay : public Action
{

public:
	SwtchTOplay(ApplicationManager *pApp);

	~SwtchTOplay();

	 bool ReadActionParameters() ;

	 bool Execute() ;


	 // Inherited via Action
	 virtual void Undo() override;


	 // Inherited via Action
	 virtual void Redo() override;

};

