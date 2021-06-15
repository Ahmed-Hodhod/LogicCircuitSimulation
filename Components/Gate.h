#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate :public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate.
public:
	Gate(int r_Inputs, int r_FanOut);
	virtual bool Checkaround(int x, int y); //Checks around the gate
	virtual bool Checkinside(int x, int y); //Checks inside the gate
	virtual COPY_ITEMS getType();
	
	virtual bool CheckinputPins();   //Checks if all input pins are connected returns true
	virtual void DeleteGate();

	InputPin* GetInputPin(int n);
	OutputPin* GetOutputPin();
	~Gate();
};

#endif
