#ifndef _NOR3_H
#define _NOR3_H

/*
  Class NOR3
  -----------
  represent the 3-input NOR gate
*/

#include "Gate.h"

class NOR3 :public Gate
{
	int NOR3_ID;
public:
	NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	NOR3(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//Calculates the output of the NOR gate
	virtual void Draw(Output* pOut);	//Draws 3-input gate
	virtual int GetID();
	virtual void SetID(int ID);
	COPY_ITEMS getType();
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void SaveComponent(ofstream& outfile);
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
};

#endif
