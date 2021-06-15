#ifndef _CUTA_H
#define _CUTA_H

#include "action.h"


class CutA : public Action
{
private:
	int Cx, Cy;	//a point belongs to the area of a component 

public:
	CutA(ApplicationManager* pApp);
	virtual ~CutA(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif