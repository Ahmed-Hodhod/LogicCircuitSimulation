#ifndef _TRUTH_H
#define _TRUTH_H
#include"..\ApplicationManager.h"
#include "Action.h"
#include<fstream>
#include<string>
class CreateTT :
    public Action
{
private :
    ofstream truth;
public:
	CreateTT(ApplicationManager* pApp);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

	~CreateTT();
};
#endif
