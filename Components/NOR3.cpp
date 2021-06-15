#include "NOR3.h"

NOR3::NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	NOR3_ID = GATE_ID;
}

NOR3::NOR3(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(3, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	NOR3_ID = ID;
	GATE_ID = ID;
}
void NOR3::Operate()
{
	//caclulate the output status as the NORing of the three input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() + m_InputPins[1].getStatus() >= 1) && m_InputPins[2].getStatus() == 0)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 3-input NOR gate
void NOR3::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawNOR3(m_GfxInfo, isSelected);
}

int NOR3::GetID()
{
	return NOR3_ID;
}

void NOR3::SetID(int ID)
{
	NOR3_ID = ID;
}

//returns status of outputpin
int NOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

void NOR3::SaveComponent(ofstream& outfile)
{
	outfile << "NOR3 " << NOR3_ID << " " << GetLabel() << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

//Set status of an input pin ot HIGH or LOW
void NOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

COPY_ITEMS NOR3::getType()
{
	return I_NOR3;
}
