#ifndef _EDIT_H
#define _EDIT_H

#include "action.h"
#include <string>

class Edit : public Action
{
private:
	int Cx, Cy;	//Center point of the Edit
	int x1, y1, x2, y2; //integers to store the 2 clicks of the gates;
	std::string L;
	int IPn;  //pin number
	bool LabelorPins; //a bool to determine which action does the user want to do 
public:
	Edit(ApplicationManager* pApp);
	virtual ~Edit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif