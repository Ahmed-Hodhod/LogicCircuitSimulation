#ifndef _AND2_H
#define _AND2_H

/*
  Class AND2
  -----------
  represent the 2-input AND gate
*/

#include "Gate.h"

class AND2:public Gate
{
private :
	int AND2_ID;
public:
	AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	AND2(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate
	COPY_ITEMS getType();
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual void SaveComponent(ofstream& outfile);
	virtual  int GetID();
	virtual void SetID(int ID);
};

#endif