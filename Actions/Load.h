#ifndef _LOAD_H
#define _LOAD_H
#include "Action.h"
#include "../ApplicationManager.h"
#include<fstream>
#include<string>

class Load :
    public Action
{
    ifstream readout;
	string filename;
public:
	/* Constructor */
	Load(ApplicationManager* pAppMan);

	/* Reads parameters required for action to execute */
	virtual void ReadActionParameters();

	/* Executes action */
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

	/* Destructor */
	virtual ~Load();
};
#endif