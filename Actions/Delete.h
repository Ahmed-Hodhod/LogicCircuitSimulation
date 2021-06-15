#ifndef _DELETE_H
#define _DELETE_H

#include "action.h"


class Delete : public Action
{
private:
	int Cx, Cy;	//a point belongs to the area of a component 

public:
	Delete(ApplicationManager* pApp);
	virtual ~Delete(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif
