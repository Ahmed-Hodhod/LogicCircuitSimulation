#include "Connection.h"

Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
}

void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::Draw(Output* pOut)
{
	pOut->PrintLabel(this->GetLabel(), m_GfxInfo.x1 + 20, m_GfxInfo.y1 - 25);
	pOut->DrawConnection(m_GfxInfo,isSelected);
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

void Connection::DeleteConnection()
{

	if (DstPin)
		DstPin->setConnection(NULL);

	if (SrcPin)
		SrcPin->Disconnect(this);

	SrcPin = NULL;
	DstPin = NULL;
}








//Draw three rectangles around the each line and validate over them
bool Connection::Checkaround(int x, int y) {
	GraphicsInfo G = m_GfxInfo;
	int xm = (G.x1 + G.x2) / 2; //middle point between the 2 points
	// First line 
	if (G.x1 <= x && x <= xm + 50 && G.y1 - 50 <= y && G.y1 + 50 >= y) {
		return true;
	}
	else if (xm - 50 <= x && x <= xm + 50 && G.y1 - 50 <= y && G.y2 + 50 >= y) { return true; }
	else if (xm - 50 <= x && x <= G.x2 + 50 && G.y2 - 50 <= y && G.y2 + 50 >= y) { return true; }

	return false;
}

bool Connection::Checkinside(int x, int y) {
	GraphicsInfo G = m_GfxInfo;
	int xm = (G.x1 + G.x2) / 2; //middle point between the 2 points
	// First line 
	if (G.x1 <= x && x <= xm && G.y1 - 20 <= y && G.y1 + 20 >= y) {
		return true;
	}
	else if (xm - 20 <= x && x <= xm + 20 && G.y1 - 20 <= y && G.y2 + 20 >= y) { return true; }
	else if (xm - 20 <= x && x <= G.x2 + 20 && G.y2 - 20 <= y && G.y2 + 20 >= y) { return true; }

	return false;
}

int Connection::GetID()
{
	return 0;
}

void Connection::SetID(int ID)
{
	return;
}

InputPin* Connection::GetInputPin(int n) {
	return DstPin;

}
OutputPin* Connection::GetOutputPin() {
	return SrcPin;
}

void Connection::SaveComponent(ofstream& outfile)
{
	outfile << (SrcPin->getComponent()->GetID()) << " " << (DstPin->getComponent()->GetID()) << " " << (DstPin->getNumber()) << endl;

}

bool Connection::CheckinputPins() { return false; }