#ifndef _PROBE_H
#define _PROBE_H

#include "action.h"


class Probe : public Action
{
private:
	int Cx, Cy;
public:
	Probe(ApplicationManager* pApp);
	virtual ~Probe(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif