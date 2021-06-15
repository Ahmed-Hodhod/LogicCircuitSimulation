#include "XOR2.h"

XOR2::XOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	XOR2_ID = GATE_ID;
}
XOR2::XOR2(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(2, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	XOR2_ID = ID;
	GATE_ID = ID;
}

void XOR2::Operate()
{
	//caclulate the output status as the XORing of the two input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() == m_InputPins[1].getStatus()))
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 2-input XOR gate
void XOR2::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawXOR2(m_GfxInfo, isSelected);
}

int XOR2::GetID()
{
	return XOR2_ID;
}

void XOR2::SetID(int ID)
{
	XOR2_ID = ID;
}

//returns status of outputpin
int XOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

void XOR2::SaveComponent(ofstream& outfile)
{
	outfile << "XOR2" << XOR2_ID << " " << GetLabel() << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

//Set status of an input pin ot HIGH or LOW
void XOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

COPY_ITEMS XOR2::getType()
{
	return I_XOR2;
}