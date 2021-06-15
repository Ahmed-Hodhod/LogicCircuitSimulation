#include "XNOR2.h"

XNOR2::XNOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	XNOR2_ID = GATE_ID;
}
XNOR2::XNOR2(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(2, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	XNOR2_ID = ID;
	GATE_ID = ID;
}

void XNOR2::Operate()
{
	//caclulate the output status as the XNORing of the two input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() == m_InputPins[1].getStatus()))
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}


// Function Draw
// Draws 2-input XNOR gate
void XNOR2::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawXNOR2(m_GfxInfo, isSelected);
}

int XNOR2::GetID()
{
	return XNOR2_ID;
}

void XNOR2::SetID(int ID)
{
	XNOR2_ID = ID;
}

//returns status of outputpin
int XNOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XNOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

void XNOR2::SaveComponent(ofstream& outfile)
{
	outfile << "XNOR2" << XNOR2_ID << " " << GetLabel() << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

//Set status of an input pin ot HIGH or LOW
void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

COPY_ITEMS XNOR2::getType()
{
	return I_XNOR2;
}