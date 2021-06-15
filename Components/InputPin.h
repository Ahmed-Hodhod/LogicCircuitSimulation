#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"

class Component; //Forward class declaration
class Connection;
class InputPin : public Pin	//inherited from class Pin
{
	Component* pComp; //Component at which this pin is associated
	int IPn;
	Connection* m_Connection;
public:
	InputPin();
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent();	//returns the component of this input pin
	void setConnection(Connection* c);
	void Disconnect();
	bool isConnected();
	Connection* GetConnection();
	void setNumber(int n);
	int getNumber();
};

#endif