#ifndef _PASTE_H
#define _PASTE_H

#include "action.h"


class Paste : public Action
{
private:
	int Cx, Cy;	//a point belongs to the area of a component 

public:
	Paste(ApplicationManager* pApp);
	virtual ~Paste(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif