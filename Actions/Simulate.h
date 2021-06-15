#ifndef _SIMULATE_H
#define _SIMULATE_H

#include "action.h"
#include "..\Components\Component.h"

class Simulate : public Action
{
private:
	int Cx, Cy;	//User click
	Component* Simlist[200]; //200 is chosen as an arbitrary number
	int Count; //Count is the acutal number of gates, i is just a loop counter
public:
	Simulate(ApplicationManager* pApp);
	virtual ~Simulate(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif