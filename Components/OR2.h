#ifndef _OR2_H
#define _OR2_H

/*
  Class OR2
  -----------
  represent the 2-input OR gate
*/

#include "Gate.h"

class OR2 :public Gate
{
	int OR2_ID;
public:
	OR2(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	OR2(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//Calculates the output of the OR gate
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