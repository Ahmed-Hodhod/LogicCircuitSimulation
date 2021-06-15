#ifndef _CUT_H
#define _CUT_H

#include "action.h"


class Cut : public Action
{
private:
	int Cx, Cy;	//a point belongs to the area of a component 

public:
	Cut(ApplicationManager* pApp);
	virtual ~Cut(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif