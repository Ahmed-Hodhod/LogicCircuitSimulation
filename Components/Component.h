#ifndef _COMPONENT_H
#define _COMPONENT_H
#include<fstream>
#include<string>
#include "..\Defs.h"
#include "..\GUI\Output.h"
#include "InputPin.h"
#include "OutputPin.h"
//THIS IS AN ABSTRACT CLASS
//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	
		string m_Label; 
protected:
	static int GATE_ID;
	bool isSelected=0;
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
public:
	Component(const GraphicsInfo &r_GfxInfo);
	Component();	
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	
	GraphicsInfo GetGraphicsInfo();
	virtual void SetGraphics(GraphicsInfo G);
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	virtual bool CheckinputPins() = 0; //Returns true if and only if all Inpins are connected
	virtual bool Checkaround(int Cx, int Cy) =0; //Checks around the component

	virtual bool Checkinside(int Cx, int Cy) = 0; //Checks inside the component
	
	virtual InputPin* GetInputPin(int n) = 0; //Gets the inputpin of a component
	virtual  OutputPin* GetOutputPin() = 0;   //Gets the outputpin of a component

	virtual void Select();                   //Selects the comp and highlights it 
	virtual string GetLabel();
	virtual bool SetLabel(string x, Output* pOut);
	virtual void SetLabel(string x);
	virtual void EditLabel(string x, Output* pOut);
	virtual void PrintLabel(Output* pOut);
	//Destructor must be virtual
	virtual void SaveComponent(ofstream& outfile) = 0; //Saves both gates and connections
	virtual int GetID() = 0;
	virtual void SetID(int ID) = 0;
	virtual ~Component();
};

#endif
