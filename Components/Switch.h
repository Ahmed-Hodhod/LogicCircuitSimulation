#pragma once
#include"Gate.h"
class Switch : public Gate {
private:
	Pin m_OutputPin;
	int SWITCH_ID;
public:
	Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	Switch(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//output of switch
	virtual void Draw(Output* pOut);	//Draws switch
	virtual void SaveComponent(ofstream& outfile);
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual bool Checkaround(int x, int y);
	virtual int GetID();
	virtual void SetID(int ID);
	COPY_ITEMS getType();
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
};

