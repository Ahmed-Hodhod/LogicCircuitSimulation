#pragma once
#include"Gate.h"
class Led : public Gate{
	private:
		Pin m_InputPin;
		int LED_ID;
		public:
	Led(const GraphicsInfo& r_GfxInfo , int r_FanOut);
	Led(const GraphicsInfo& r_GfxInfo, int ID, string label, int r_FanOut);
	virtual void Operate();	//Calculates the output of the LED
	virtual void Draw(Output* pOut);	//Draws 1-input LED
	virtual void SaveComponent(ofstream& outfile);
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual bool Checkaround(int x, int y);
	virtual int GetID();
	virtual void SetID(int ID);
	COPY_ITEMS getType();
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
};

