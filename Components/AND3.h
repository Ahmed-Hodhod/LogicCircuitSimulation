#ifndef _AND3_H
#define _AND3_H

/*
  Class AND3
  -----------
  represent the 3-input AND gate
*/

#include "Gate.h"

class AND3 :public Gate
{
	int AND3_ID;
public:
	AND3(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	AND3(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 3-input gate
	COPY_ITEMS getType();
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual int GetID();
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual void SaveComponent(ofstream& outfile);
	virtual void SetID(int ID);
};

#endif