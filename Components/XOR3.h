#ifndef _XOR3_H
#define _XOR3_H

/*
  Class XOR3
  -----------
  represent the 3-input XOR gate
*/

#include "Gate.h"

class XOR3 :public Gate
{
	int XOR3_ID;
public:
	XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	XOR3(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//Calculates the output of the XOR gate
	virtual void Draw(Output* pOut);	//Draws 3-input gate
	virtual void SaveComponent(ofstream& outfile);
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual int GetID();
	virtual void SetID(int ID);
	COPY_ITEMS getType();
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
};

#endif
