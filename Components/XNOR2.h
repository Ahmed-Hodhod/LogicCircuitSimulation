#ifndef _XNOR2_H
#define _XNOR2_H

/*
  Class XNOR2
  -----------
  represent the 2-input XNOR gate
*/

#include "Gate.h"

class XNOR2 :public Gate
{
	int XNOR2_ID;
public:
	XNOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	XNOR2(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//Calculates the output of the XNOR gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate
	virtual int GetID();
	virtual void SetID(int ID);
	COPY_ITEMS getType();
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void SaveComponent(ofstream& outfile);
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
};

#endif