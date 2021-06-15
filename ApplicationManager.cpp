#include "ApplicationManager.h"
#include "Actions\Actionheaders.h"

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	nGates = 0;
	nfullGates = 0;
	CutItem = NULL;
	CutElement = { NUMP , -1 };
	CopyType = NUMP;
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	if (dynamic_cast<Gate*>(pComp)) { nGates++; };
	CompList[CompCount++] = pComp;		
	
}
////////////////////////////////////////////////////////////////////
void  ApplicationManager::DeleteGate(Component* comp)
{
	if (!comp) return;
	Gate* g = (Gate*)(comp);
	g->DeleteGate();
	nGates -= 1;
	FindAndReplace(g);

	// Update Interface
	OutputInterface->ClearDrawingArea();
	UpdateInterface();
}


////////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteComponent(int Cx, int Cy)
{

	int i = FindComp(Cx, Cy);
	Component* comp = CompList[i];
	if (dynamic_cast<Gate*> (comp)) // if it is a gate 
	{
		DeleteGate(comp);
		OutputInterface->PrintMsg("Gate is Deleted Successfully!");
	}
	else if (dynamic_cast<Connection*>(comp))
	{
		Connection* c = (Connection*)(comp);
		DeleteConnection(c);
		OutputInterface->PrintMsg("Connection is  Deleted  Successfully! ");
	}
}
////////////////////////////////////////////////////////////////////
int ApplicationManager::FindComp(Component* c)
{
	if (!c)
		return -1;
	for (int i = 0; i < CompCount; i++)
	{
		if (c == CompList[i])
		{
			return i;
		}
	}
}

////////////////////////////////////////////////////////////////////
int ApplicationManager::FindComp(int Cx, int Cy)
{
	for (int i = 0; i < CompCount; i++)
	{
		Component* comp = CompList[i];
		if (comp->Checkinside(Cx, Cy))
		{
			return i;
		}

	}
	return -1;

}

////////////////////////////////////////////////////////////////////
void ApplicationManager::FindAndReplace(Component* c)
{
	int index = FindComp(c);
	if (!c || index == -1) return;
	CompCount -= 1;
	delete CompList[index];
	CompList[index] = CompList[CompCount];
	CompList[CompCount] = NULL;

}




////////////////////////////////////////////////////////////////////

void ApplicationManager::DeleteConnection(Connection* c)
{
	if (!c) return;
	c->DeleteConnection();
	FindAndReplace(c);

	// Update the interface 
	OutputInterface->ClearDrawingArea();
	UpdateInterface();
}



////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user

	return InputInterface->GetUserAction(a,b); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case EDIT_Label:
		if (CompCount > 0)
			Edit(this).Execute();
		else { OutputInterface->PrintMsg("There isn't enough gates"); }
		break;
		case ADD_Label:
		if (CompCount > 0)
			Label(this).Execute();
		else { OutputInterface->PrintMsg("There isn't enough gates"); }
		break;
		case ADD_GATE:
			OutputInterface->PrintMsg("Action: Add a gate , Click anywhere");
			OutputInterface->CreateGATESToolBar();
			break;
		case ADD_Buff:
			AddBUFFgate(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked Buffer Gate , Click anywhere");
			break;
		case ADD_INV:
			AddINVgate(this).Execute();
			OutputInterface->PrintMsg("Action: CLicked Inverter , Click anywhere");
			break;
		case ADD_AND_GATE_2:
			//TESTOS: MISSION STEINSO GATO 
			AddANDgate2 (this).Execute();
			OutputInterface->PrintMsg("Action: Clicked AND GATE with 2 inputs , Click anywhere");
			break;
		case ADD_OR_GATE_2:
			AddORgate2(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked OR GATE with 2 inputs , Click anywhere");
			break;
		case ADD_NAND_GATE_2:
			AddNANDgate2(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked NAND gate with 2 inputs  , Click anywhere");
			break;
		case ADD_NOR_GATE_2:
			AddNORgate2(this).Execute();
			OutputInterface->PrintMsg("Action: CLicked NOR GATE with 2 inputs, Click anywhere");
			break;
		case ADD_XOR_GATE_2:
			AddXORgate2(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked XOR GATE with 2 inputs , Click anywhere");
			break;
		case ADD_XNOR_GATE_2:
			AddXNORgate2(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked XNOR GATE with 2 inputs , Click anywhere");
			break;
		case ADD_AND_GATE_3:
			AddANDgate3(this).Execute();
			OutputInterface->PrintMsg("Action: CLicked AND GATE with 3 inputs , Click anywhere");
			break;
		case ADD_XOR_GATE_3:
			AddXORgate3(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked XOR GATE with 3 inputs, Click anywhere");
			break;
		case ADD_NOR_GATE_3:
			AddNORgate3(this).Execute();
			OutputInterface->PrintMsg("Action: Clicked NOR GATE with 3 inputs, Click anywhere");
			break;
		case ADD_TOOL:
			OutputInterface->PrintMsg("Action: Add a tool , Click anywhere");
			OutputInterface->CreateTOOLStoolbar();
			break;
		case ADD_CONNECTION:
			//if all is full 
			if (CompCount >= 2 && !(isAllfull()))
				CONNECT(this).Execute();
			else {
				OutputInterface->PrintMsg("There isn't Enough Gates");
				if (isAllfull())OutputInterface->PrintMsg("All Gates are full");
			}

			break;
		case ADD_Switch:
			AddSwitch(this).Execute();
			OutputInterface->PrintMsg("Action: Add a switch , Click anywhere");
			break;
		case ADD_LED:
			AddLED(this).Execute();
			OutputInterface->PrintMsg("Action : Add an LED , Click anywhere");
			break;
		case DEL:
			if (!CompCount)
			{
				OutputInterface->PrintMsg("Not enough elments to delete. ");
			}
			else
			{
				Delete(this).Execute();
			}
			break;
		case MOVE:
			OutputInterface->PrintMsg("Action: clicked MOVE , Click anywhere");
			break;
		case COPY:
			if (!nGates)
			{
				OutputInterface->PrintMsg("There is no any gate to copy. ");
			}
			else
			{
				Copy(this).Execute();
				OutputInterface->PrintMsg("Elmenet is added to the Clipboard! ");

			}
			break;
		case CUT:
			if (!nGates)
			{

				OutputInterface->PrintMsg("There is no any gate to Cut. ");
			}
			else
			{
				CutA(this).Execute();
				OutputInterface->PrintMsg("Elmenet is added to the Clipboard! ");
			}
			break;
		case PASTE:
			if (CopyType == ITM_NGATES && CutElement.CutType == ITM_NGATES)
			{
				OutputInterface->PrintMsg("No elments in the Clipboard. ");
			}
			else
			{
				Paste(this).Execute();
			}
			break;
		case LOAD:
			Load(this).Execute();
			break;
		case SAVE:
			if (!CompCount) {
				OutputInterface->PrintMsg("No Items to Save ");
			}
			else {
				Save(this).Execute();
			}
			break;
		case SELECT:
			if (Checkinside(a, b)) {
				SelectComponent(a, b);
				OutputInterface->PrintMsg("Component Selected");
			}
			else
				OutputInterface->PrintMsg("A click on the design Area, Click on any Comp to highlight it.");
			break;
		case STATUS_BAR:
			OutputInterface->PrintMsg("Action: a click on the Status Bar, Click anywhere");
			break;
		case DSN_TOOL:
			OutputInterface->PrintMsg("Action: a click on empty area in the Tool Bar, Click anywhere");
			break;
		case SIM_MODE:
			OutputInterface->PrintMsg("Action: Switch to Simulation Mode, creating simualtion tool bar");
			OutputInterface->CreateSimulationToolBar();
			break;
		case Create_TruthTable:
			OutputInterface->PrintMsg("Action : clicked Create Truth Table , Click anywhere");
			break;
		case VALIDATE:
			OutputInterface->PrintMsg("Action : clicked Validate , Click anywhere");
			break;
		case PROBE:
			OutputInterface->PrintMsg("Action : clicked Probe , Click anywhere");
			break;
		case DSN_MODE:
			OutputInterface->PrintMsg("Action: Return to Design Mode, creating Design tool bar");
			OutputInterface->CreateDesignToolBar();
			break;
		case EXIT:
			break;
		
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	OutputInterface->ClearDrawingArea();
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]))
		{
			Connection* c = (Connection*)(CompList[i]);
			if (!c->getDestPin() || !c->getSourcePin())
			{
				DeleteConnection(c);
				continue;
			}
		}
			CompList[i]->Draw(OutputInterface);
	}
}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}
////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::SelectComponent(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) {
			CompList[i]->Select();
		}

	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::LabelComponent(string x, int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) {
			if (CompList[i]->SetLabel(x, OutputInterface)) {
				OutputInterface->PrintMsg("Component Labeled");
			}
			else { OutputInterface->PrintMsg("Component Already Named"); };

			break;
		}

	}
	
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::EditComponent(string x, int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) {
			CompList[i]->EditLabel(x, OutputInterface); break;
		}
	}

}
////////////////////////////////////////////////////////////////////
bool ApplicationManager::ChecksameComponent(int Cx1, int Cy1, int Cx2, int Cy2)
{
	if (CompCount == 0) { return false; }
	int i;
	for (i = 0; i < CompCount; i++) {
		//if It's a gate:
		if (dynamic_cast<Gate*>(CompList[i])) {
			if (CompList[i]->Checkinside(Cx1, Cy1)) { break; }
		}
	}int k;
	for (k = 0; k < CompCount; k++) {
		//if It's a gate:
		if (dynamic_cast<Gate*>(CompList[k])) {
			if (CompList[k]->Checkinside(Cx2, Cy2)) { break; }
		}
	}
	return i == k;
}
////////////////////////////////////////////////////////////////////

InputPin* ApplicationManager::GetInputPin(int Cx, int Cy, int n) {
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) { return CompList[i]->GetInputPin(n); }
	}
}



////////////////////////////////////////////////////////////////////

bool ApplicationManager::Checkinside(int Cx, int Cy) {
	if (CompCount == 0) { return false; }
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) { return true; }
	}
	return false;
}

////////////////////////////////////////////////////////////////////

bool ApplicationManager::Checkaround(int Cx, int Cy) {
	if (CompCount == 0) { return false; }
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkaround(Cx, Cy)) { return true; }
	}
	return false;



}

////////////////////////////////////////////////////////////////////
//1 for gate, 0 for connection
bool ApplicationManager::ConnorGate(int Cx, int Cy) {
	if (CompCount == 0) { return false; }
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->Checkinside(Cx, Cy)) {
			if (dynamic_cast<Gate*>(CompList[i])) {
				return true;    //1 for gate 
			}
			else { return false; }
		}
	}
}
////////////////////////////////////////////////////////////////////

OutputPin* ApplicationManager::GetOutputPin(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {

		if (dynamic_cast<Gate*>(CompList[i]) && CompList[i]->Checkinside(Cx, Cy))
		{
			return CompList[i]->GetOutputPin();
		}

	}

}

////////////////////////////////////////////////////////////////////

Connection* ApplicationManager::GetConnection(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {

		if (CompList[i]->Checkinside(Cx, Cy))
		{
			return dynamic_cast<Connection*>(CompList[i]);
		}

	}


}
////////////////////////////////////////////////////////////////////


GraphicsInfo ApplicationManager::getGraphicsInfo(int Cx, int Cy) {
	for (int i = 0; i < CompCount; i++) {
		//if It's a gate:
		if (dynamic_cast<Gate*>(CompList[i])) {
			if (CompList[i]->Checkinside(Cx, Cy)) { return CompList[i]->GetGraphicsInfo(); }
		}

	}

}

Component* ApplicationManager::getCompbyID(int compID)
{
	for (int i = 0; i < CompCount; i++) {
		if (CompList[i]->GetID() == compID) {
			return CompList[i];
		}
	}
}

void ApplicationManager::SaveCircuit(ofstream& outfile)
{
	outfile << nGates << endl;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Gate*>(CompList[i])) {
			CompList[i]->SaveComponent(outfile);
		}
	}
	
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Connection*>(CompList[i])) {
			outfile << "Connections" << endl;
			CompList[i]->SaveComponent(outfile);
		}
	}
}
void ApplicationManager::LoadCircuit(ifstream& infile)
{
	string ctype, clabel;
	int cID, cID2, noOfgates, noOfpin;
	GraphicsInfo gfxload;
	infile >> noOfgates;
	while (infile>>ctype , ctype!="-1") { 
		if (infile.eof()) { break; }
		if (ctype == "Connections") {
			infile >> cID >> cID2 >> noOfpin;
			OutputPin* SrcPin = GetOutputPin((getCompbyID(cID)->GetGraphicsInfo().x1), (getCompbyID(cID)->GetGraphicsInfo().y1));
			InputPin* DstPin = GetInputPin((getCompbyID(cID2)->GetGraphicsInfo().x1), (getCompbyID(cID2)->GetGraphicsInfo().y1), noOfpin);
			gfxload.x1 = (getCompbyID(cID)->GetGraphicsInfo().x1) + 50;
			gfxload.y1 = getCompbyID(cID)->GetGraphicsInfo().y1 + 23;
			gfxload.x2 = getCompbyID(cID2)->GetGraphicsInfo().x1;
			if (noOfpin == 1 || noOfpin < 1) {
				gfxload.y2 = getCompbyID(cID2)->GetGraphicsInfo().y1 + 13;
			}
			else if (noOfpin == 2) { gfxload.y2 = getCompbyID(cID2)->GetGraphicsInfo().y2 - 13; }
			else if (noOfpin == 3 || noOfpin > 3) { gfxload.y2 = getCompbyID(cID2)->GetGraphicsInfo().y2; }
			Connection* wire = new Connection(gfxload, SrcPin, DstPin);
			CompList[CompCount++] = wire;
		}
		else{
			infile >>cID >> clabel >> gfxload.x1 >> gfxload.y1;
			if (ctype == "AND2") {
				AND2* pAND2 = new AND2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pAND2;
				nGates++;
			}
			else if (ctype == "OR2") {
				OR2* pOR2 = new OR2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pOR2;
				nGates++;
			}
			else if (ctype == "BUFF") {
				BUFF* pBUFF = new BUFF(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pBUFF;
				nGates++;
			}
			else if (ctype == "INV") {
				INV* pINV = new INV(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pINV;
				nGates++;
			}
			else if (ctype == "NAND2") {
				NAND2* pNAND2 = new NAND2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pNAND2;
				nGates++;
			}
			else if (ctype == "NOR2") {
				NOR2* pNOR2 = new NOR2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pNOR2;
				nGates++;
			}
			else if (ctype == "XOR2") {
				XOR2* pXOR2 = new XOR2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pXOR2;
				nGates++;
			}
			else if (ctype == "XNOR2") {
				XNOR2* pXNOR2 = new XNOR2(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pXNOR2;
				nGates++;
			}
			else if (ctype == "XOR3") {
				XOR3* pXOR3 = new XOR3(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pXOR3;
				nGates++;
			}
			else if (ctype == "AND3") {
				AND3* pAND3 = new AND3(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pAND3;
				nGates++;
			}
			else if (ctype == "NOR3") {
				NOR3* pNOR3 = new NOR3(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pNOR3;
				nGates++;
			}
			else if (ctype == "LED") {
				Led* pLED = new Led(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pLED;
				nGates++;
			}
			else if (ctype == "SWITCH") {
				Switch* pSWITCH = new Switch(gfxload, cID, clabel, AND2_FANOUT);
				CompList[CompCount++] = pSWITCH;
				nGates++;
			}
		}
			
		
	}
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::Copy2(int Cx, int Cy)
{
	int i = FindComp(Cx, Cy);
	if (dynamic_cast<Gate*>(CompList[i]))
	{
		Gate* item = (Gate*)(CompList[i]);
		CopyType = item->getType();
	}
}

void ApplicationManager::Cut2(int Cx, int Cy)
{
	int i = FindComp(Cx, Cy);
	if (dynamic_cast<Gate*>(CompList[i]))
	{
		Gate* item = (Gate*)(CompList[i]);
		CutElement.CutType = item->getType();
		CutElement.ind = i;
		CutItem = CompList[i];
		// Remove the copied element from the clipboard 
		CopyType = NUMP;
	}
}





void ApplicationManager::Paste2(int Cx, int Cy)
{
	// Check for CopyType 


	if (CopyType != NUMP)
	{
		switch (CopyType)
		{
		case I_AND2:
			AddANDgate2(this).Execute();
			OutputInterface->PrintMsg("2-AND Gate is Pasted!");
			break;
		case I_BUFF:
			AddBUFFgate(this).Execute();
			OutputInterface->PrintMsg("Buff Gate is Pasted!");
			break;
		case I_INV:
			AddINVgate(this).Execute();
			OutputInterface->PrintMsg("INVERTER Gate is Pasted!");
			break;
		case I_OR2:
			AddORgate2(this).Execute();
			OutputInterface->PrintMsg("2-OR Gate is Pasted!");
			break;
		case I_NAND2:
			AddNANDgate2(this).Execute();
			OutputInterface->PrintMsg("2-NAND Gate is Pasted!");
			break;
			/*case I_NOR2:
				(this).Execute();
				OutputInterface->PrintMsg("2-AND Gate is Pasted!");
				break;*/
		case I_XOR2:
			AddXORgate2(this).Execute();
			OutputInterface->PrintMsg("2-XOR Gate is Pasted!");
			break;
		case I_XNOR2:
			AddXNORgate2(this).Execute();
			OutputInterface->PrintMsg("2-XNOR Gate is Pasted!");
			break;
		case I_AND3:
			AddANDgate3(this).Execute();
			OutputInterface->PrintMsg("3-AND Gate is Pasted!");
			break;
		case I_XOR3:
			AddXORgate3(this).Execute();
			OutputInterface->PrintMsg("3-XOR Gate is Pasted!");
			break;
		case I_NOR3:
			AddNORgate3(this).Execute();
			OutputInterface->PrintMsg("3-NOR Gate is Pasted!");
			break;
		case I_SWITCH:
			AddSwitch(this).Execute();
			OutputInterface->PrintMsg("SWITCH Gate is Pasted!");
			break;
		case I_LED:
			AddLED(this).Execute();
			OutputInterface->PrintMsg("LED Gate is Pasted!");
			break;
		default:
			CopyType = NUMP;

		}
	}

	// Check for CutType 
	if (CutElement.CutType != NUMP && CompList[CutElement.ind] == CutItem)
	{
		switch (CutElement.CutType)
		{
		case I_AND2:
			AddANDgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-AND Gate is Pasted!");
			break;
		case I_BUFF:
			AddBUFFgate(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("Buff Gate is Pasted!");
			break;
		case I_INV:
			AddINVgate(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("INVERTER Gate is Pasted!");
			break;
		case I_OR2:
			AddORgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-OR Gate is Pasted!");
			break;
		case I_NAND2:
			AddNANDgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-NAND Gate is Pasted!");
			break;
			/*case I_NOR2:
				(this).Execute();
				OutputInterface->PrintMsg("2-AND Gate is Pasted!");
				break;*/
		case I_XOR2:
			AddXORgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-XOR Gate is Pasted!");
			break;
		case I_XNOR2:
			AddXNORgate2(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("2-XNOR Gate is Pasted!");
			break;
		case I_AND3:
			AddANDgate3(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("3-AND Gate is Pasted!");
			break;
		case I_XOR3:
			AddXORgate3(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("3-XOR Gate is Pasted!");
			break;
		case I_NOR3:
			AddNORgate3(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("3-NOR Gate is Pasted!");
			break;
		case I_SWITCH:
			AddSwitch(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("SWITCH Gate is Pasted!");
			break;
		case I_LED:
			AddLED(this).Execute();
			DeleteGate(CutItem);
			OutputInterface->PrintMsg("LED Gate is Pasted!");
			break;
		default:

			CutElement.CutType = NUMP;
			CutItem = NULL;
			CutElement.ind = -1;
			break;
		}
	}
}

bool ApplicationManager::isCompfull(int Cx, int Cy) {

	for (int i = 0; i < CompCount; i++) {

		if (dynamic_cast<Gate*>(CompList[i]) && CompList[i]->Checkinside(Cx, Cy))
		{
			return CompList[i]->CheckinputPins();
		}

	}
	//if it's not a gate assume it's true
	return true;

}

////////////////////////////////////////////////////////////////////

bool ApplicationManager::isonlyCompfree(int Cx, int Cy) {
	//Calculates nfullGates
	isAllfull();
	for (int i = 0; i < CompCount; i++) {

		if (dynamic_cast<Gate*>(CompList[i]) && CompList[i]->Checkinside(Cx, Cy))
		{
			//If it's the only one free
			if (nfullGates == nGates - 1 && !(CompList[i]->CheckinputPins()))
			{
				return true;
			}
		}

	}
	return false;


}


////////////////////////////////////////////////////////////////////

bool ApplicationManager::isAllfull() {
	//Get number of full gates to decide later
	nfullGates = 0;
	for (int i = 0; i < CompCount; i++) {
		if (dynamic_cast<Gate*>(CompList[i]))
		{
			if (CompList[i]->CheckinputPins()) { nfullGates++; }
		}

	}
	if (nfullGates == nGates) { return true; }

	for (int i = 0; i < CompCount; i++) {

		if (dynamic_cast<Gate*>(CompList[i]))
		{
			if (CompList[i]->CheckinputPins()) {}
			else return false;
		}
	}
	return true;

}


ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}