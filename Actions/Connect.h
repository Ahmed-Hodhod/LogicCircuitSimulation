#ifndef _CONNECT_H
#define _CONNECT_H

#include "action.h"
#include "..\Components\Connection.h"

class CONNECT : public Action
{
private:
	//Parameters The two terminals of the connection 
	ApplicationManager* pManager;
	int IPn;
	int x1, y1, x2, y2;  //Two corners of the rectangluar area
public:
	CONNECT(ApplicationManager* pApp);
	virtual ~CONNECT(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif