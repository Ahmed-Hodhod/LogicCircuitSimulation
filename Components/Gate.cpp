#include "Gate.h"
#include "Connection.h"
//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut) :m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	//Associate the output pin to this gate
	m_OutputPin.setComponent(this);
	//Associate all input pins to this gate
	for (int i = 0; i < m_Inputs; i++) {
		m_InputPins[i].setComponent(this);
		m_InputPins[i].setNumber(i + 1);
	}
}

bool Gate::Checkaround(int Cx, int Cy) {
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

bool Gate::Checkinside(int x, int y) {
	GraphicsInfo G = m_GfxInfo;
	if ((G.x1 <= x && G.x2 >= x) && (G.y1 <= y && G.y2 >= y)) {
		return true;
	}
	else return false;


}

COPY_ITEMS Gate::getType()
{
	return NUMP;
}

//IF ALL connected return true, else return false
bool Gate::CheckinputPins() {
	//trivial case: case of switch
	if (m_InputPins == 0) { return true; }
	for (int i = 0; i < m_Inputs; i++) {
		if (!m_InputPins[i].isConnected())
			return false;

	}return true;


}

void Gate::DeleteGate()
{
	for (int i = 0; i < m_OutputPin.ConnectionsCount(); i++)
	{
		m_OutputPin.getConnectionByIndex(i)->setSourcePin(NULL);
	}

	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].isConnected())
		{
			m_InputPins[i].GetConnection()->setDestPin(NULL);
		}
	}
}

InputPin* Gate::GetInputPin(int n) {
	return &(m_InputPins[n - 1]);

}
OutputPin* Gate::GetOutputPin() {
	return &m_OutputPin;
}

Gate::~Gate()
{
}



