#include "AND3.h"

AND3::AND3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	AND3_ID = GATE_ID;
}

AND3::AND3(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(3, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	AND3_ID = ID;
	GATE_ID = ID;
}

void AND3::Operate()
{
	//caclulate the output status as the ANDing of the three input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() * m_InputPins[1].getStatus() * m_InputPins[2].getStatus()) == 1)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 3-input AND gate
void AND3::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawAND3(m_GfxInfo, isSelected);
}

//returns status of outputpin
int AND3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

int AND3::GetID()
{
	return AND3_ID;
}

//Set status of an input pin ot HIGH or LOW
void AND3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

void AND3::SaveComponent(ofstream& outfile)
{
	outfile << "AND3" << " " << AND3_ID <<" "<< GetLabel() << " " << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

void AND3::SetID(int ID)
{
	AND3_ID = ID;
}

COPY_ITEMS AND3::getType()
{
	return I_AND3;
}

