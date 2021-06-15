#include "Component.h"
//THIS IS AN ABSTRACT CLASS 
int Component::GATE_ID = 0;
Component::Component(const GraphicsInfo &r_GfxInfo)
{
	bool isSelected = 0;
	m_GfxInfo = r_GfxInfo;

}
//Returns the graphics info of component
GraphicsInfo Component::GetGraphicsInfo() { return m_GfxInfo; }



void Component::SetGraphics(GraphicsInfo G) { m_GfxInfo=G; }

//Selects and unselects the component

void Component::Select() {
	if (isSelected)
		isSelected = 0;
	else isSelected = 1;

}


string Component::GetLabel() {
	return m_Label;
}

bool Component::SetLabel(string x, Output* pOut) {
	 if (!(size(m_Label) == 0)) { return false; }
	m_Label = x;
	return true;
}
void Component::SetLabel(string x)
{
	m_Label = x;
}
void Component::EditLabel(string x, Output* pOut) {
	int L = size(m_Label); //Get Length of existing string to replace it 
	m_Label = x;

}

void Component::PrintLabel(Output* pOut) {
	int L = size(m_Label);
	pOut->PrintLabel(m_Label, m_GfxInfo.x1 + 15, m_GfxInfo.y1 - 25);
}

Component::Component()
{}

Component::~Component()
{}

