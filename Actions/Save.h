#ifndef _SAVE_H
#define _SAVE_H
#include"..\ApplicationManager.h"
#include "Action.h"
#include<fstream>
#include<string>

class Save :
    public Action
{
private:
    ofstream outwrite;
public:
	
	Save(ApplicationManager* pAppMan);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();

	
	virtual ~Save();
};

#endif

