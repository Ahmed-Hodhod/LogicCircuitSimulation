#include "Switch.h"

Switch::Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut):Gate(0,r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	GATE_ID += 10;
	SWITCH_ID = GATE_ID;
}
Switch::Switch(const GraphicsInfo& gfxload, int ID, string label, int r_FanOut) :Gate(0, r_FanOut) //loaded version
{
	m_GfxInfo.x1 = gfxload.x1;
	m_GfxInfo.y1 = gfxload.y1;
	m_GfxInfo.x2 = gfxload.x2;
	m_GfxInfo.y2 = gfxload.y2;
	SetLabel(label);
	SWITCH_ID = ID;
	GATE_ID = ID;
}

void Switch::Operate()
{
	return;
}

void Switch::Draw(Output* pOut)
{
	//Prints the label
	Component::PrintLabel(pOut);
	pOut->DrawSwitch(m_GfxInfo, isSelected);
}

void Switch::SaveComponent(ofstream& outfile)
{
	outfile << "SWITCH " << SWITCH_ID << " " << GetLabel() << (m_GfxInfo.x1) << " " << (m_GfxInfo.y1) << endl;
}

int Switch::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int Switch::GetInputPinStatus(int n)
{
	return -1;
}

void Switch::setInputPinStatus(int n, STATUS s)
{
	return;
}
bool Switch::Checkaround(int Cx, int Cy)
{
	GraphicsInfo G = m_GfxInfo;
	int COGx = (G.x2 + G.x1) / 2;  //COG=Center of Gate
	int COGy = (G.y2 + G.y1) / 2; //COG= Center of Gate	
//Draw an imaginary circle around each gate, and this is how you validate, (1.5*r)^2 was chosen because it's suitable
	if ((pow((Cx - COGx), 2) + pow((Cy - COGy), 2)) <= pow(1.5 * 50, 2))
	{
		return true;
	}
	else return false;
}

int Switch::GetID()
{
	return SWITCH_ID;
}
void Switch::SetID(int ID)
{
	SWITCH_ID = ID;
}
COPY_ITEMS Switch::getType()
{
	return I_SWITCH;
}
