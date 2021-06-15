#include "NOR2.h"

NOR2::NOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	NOR2_ID = GATE_ID;
}
NOR2::NOR2(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(2, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	NOR2_ID = ID;
	GATE_ID = ID;
}

void NOR2::Operate()
{
	//caclulate the output status as the NORing of the two input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() + m_InputPins[1].getStatus()) >= 1)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);

}


// Function Draw
// Draws 2-input NOR gate
void NOR2::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	//Call output class and pass gate drawing info to it
	pOut->DrawNOR2(m_GfxInfo, isSelected);
}

int NOR2::GetID()
{
	return NOR2_ID;
}

void NOR2::SetID(int ID)
{
	NOR2_ID = ID;
}

//returns status of outputpin
int NOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

void NOR2::SaveComponent(ofstream& outfile)
{
	outfile << "NOR2 " << NOR2_ID << " " << GetLabel() << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

//Set status of an input pin ot HIGH or LOW
void NOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

COPY_ITEMS NOR2::getType()
{
	return I_NOR2;
}
