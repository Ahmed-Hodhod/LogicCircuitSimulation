#include "AND2.h"

AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	AND2_ID = GATE_ID;
}

AND2::AND2(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut):Gate(2,r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	AND2_ID = ID;
	GATE_ID = ID;
}




void AND2::Operate()
{
	//caclulate the output status as the ANDing of the two input pins

	//Add you code here
	if ((m_InputPins[0].getStatus() * m_InputPins[1].getStatus()) == 1)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it
	pOut->DrawAND2(m_GfxInfo, isSelected);
	//Prints the label
	Component::PrintLabel(pOut);
}

//returns status of outputpin
int AND2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int AND2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void AND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

void AND2::SaveComponent(ofstream& outfile)
{
	outfile << "AND2" << " " << AND2_ID <<" " <<GetLabel() << " " << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

int AND2::GetID()
{
	return AND2_ID;
}

void AND2::SetID(int ID)
{
	AND2_ID = ID;
}

COPY_ITEMS AND2::getType()
{
	return I_AND2;
}


