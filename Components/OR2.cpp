#include "OR2.h"

OR2::OR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	OR2_ID = GATE_ID;
}
OR2::OR2(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(2, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	OR2_ID = ID;
	GATE_ID = ID;
}


void OR2::Operate()
{
	//caclulate the output status as the ORing of the two input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() + m_InputPins[1].getStatus()) == 1)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 2-input OR gate
void OR2::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawOR2(m_GfxInfo, isSelected);
}

int OR2::GetID()
{
	return OR2_ID;
}

void OR2::SetID(int ID)
{
	OR2_ID = ID;
}

//returns status of outputpin
int OR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int OR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

void OR2::SaveComponent(ofstream& outfile)
{
	outfile << "OR2 " << OR2_ID << " " << GetLabel()<< (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

//Set status of an input pin ot HIGH or LOW
void OR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

COPY_ITEMS OR2::getType()
{
	return I_OR2;
}