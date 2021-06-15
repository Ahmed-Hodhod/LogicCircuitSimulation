#include "BUFF.h"

BUFF::BUFF(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	BUFF_ID = GATE_ID;
}BUFF::BUFF(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(1, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	BUFF_ID = ID;
	GATE_ID = ID;
}

void BUFF::Operate()
{
	//caclulate the output status as the BUFFer of the input pin

	//Add you code here
	m_OutputPin.setStatus(m_InputPins[0].getStatus());
}


// Function Draw
// Draws 1-input BUFFer gate
void BUFF::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawBUFF(m_GfxInfo, isSelected);
}

//returns status of outputpin
int BUFF::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int BUFF::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

int BUFF::GetID()
{
	return BUFF_ID;
}

void BUFF::SetID(int ID)
{
	BUFF_ID = ID;
}

//Set status of an input pin ot HIGH or LOW
void BUFF::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void BUFF::SaveComponent(ofstream& outfile)
{
	outfile << "BUFF" << " " << BUFF_ID << " " << GetLabel() << " " << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

COPY_ITEMS BUFF::getType()
{
	return I_BUFF;
}
