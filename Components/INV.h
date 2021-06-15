#ifndef _INV_H
#define _INV_H

/*
  Class INV
  -----------
  represent the 1-input INV gate
*/

#include "Gate.h"

class INV :public Gate
{
	int INV_ID;
public:
	INV(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	INV(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//Calculates the output of the INV gate
	virtual void Draw(Output* pOut);	//Draws 1-input gate
	virtual int GetID();
	virtual void SetID(int ID);
	COPY_ITEMS getType();
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void SaveComponent(ofstream& outfile);
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
};

#endif
