#include"Action.h"


class SwtchTOplay : public Action
{

public:
	SwtchTOplay(ApplicationManager *pApp);

	~SwtchTOplay();

	 bool ReadActionParameters() ;

	 void Execute() ;

};

