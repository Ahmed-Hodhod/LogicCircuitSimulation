#ifndef _LABEL_H
#define _LABEL_H

#include "action.h"
#include <string>

class Label : public Action
{
private:
	int Cx, Cy;	//Center point of the Label
	std:: string L;
public:
	Label(ApplicationManager* pApp);
	virtual ~Label(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif