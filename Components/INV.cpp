#include "INV.h"

INV::INV(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	INV_ID = GATE_ID;
}
INV::INV(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(1, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	INV_ID = ID;
	GATE_ID = ID;
}

void INV::Operate()
{
	//caclulate the output status as the INVof the input pin

	//Add you code here
	if ((m_InputPins[0].getStatus() == 1))
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}


// Function Draw
// Draws 1-input INV gate
void INV::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawINV(m_GfxInfo, isSelected);
}

int INV::GetID()
{
	return INV_ID;
}

void INV::SetID(int ID)
{
	INV_ID = ID;
}

//returns status of outputpin
int INV::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int INV::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

void INV::SaveComponent(ofstream& outfile)
{
	outfile << "INV" << " " << INV_ID << " " << GetLabel() << " " << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

//Set status of an input pin ot HIGH or LOW
void INV::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}


COPY_ITEMS INV::getType()
{
	return I_INV;
}
