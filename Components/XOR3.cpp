#include "XOR3.h"

XOR3::XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	XOR3_ID = GATE_ID;
}
XOR3::XOR3(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(3, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	XOR3_ID = ID;
	GATE_ID = ID;
}

void XOR3::Operate()
{
	//caclulate the output status as the XORing of the three input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() + m_InputPins[1].getStatus() + m_InputPins[2].getStatus()) % 2 == 0)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}


// Function Draw
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawXOR3(m_GfxInfo, isSelected);
}

void XOR3::SaveComponent(ofstream& outfile)
{
	outfile << "XOR3 " << XOR3_ID << " " << GetLabel() << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

int XOR3::GetID()
{
	return XOR3_ID;
}

void XOR3::SetID(int ID)
{
	XOR3_ID = ID;
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
COPY_ITEMS XOR3::getType()
{
	return I_XOR3;
}