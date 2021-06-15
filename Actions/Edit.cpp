#include "Edit.h"
#include "..\ApplicationManager.h"
#include "Connect.h"
Edit::Edit(ApplicationManager* pApp) :Action(pApp)
{
	LabelorPins = 1; //1 for label, 0 for pins
}

Edit::~Edit(void)
{
}

void Edit::ReadActionParameters()
{//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Choose which component you want to edit");
	bool flag = true;
	while (flag) {
		//Wait for User Input
		pIn->GetPointClicked(Cx, Cy);
		//Check for status and tool bars:

		if (UI.ToolBarHeight - Cy + 50 > 0 || (UI.height - UI.StatusBarHeight) - Cy - 50 < 0) {
			flag = true;
		}
		else {

			flag = !(pManager->Checkinside(Cx, Cy));

		}
		if (flag) {
			pOut->PrintMsg("It's not allowed to edit the label here, please try again. ");
		}
		else {//if it's not a gate
			if (!pManager->ConnorGate(Cx, Cy)) {
				int s = stoi(pIn->GetSrting(pOut, "Choose what action do you want: 0 for changing pins and 1 for Label."));
				if (s==0){
					LabelorPins = 0;
				}
				else { LabelorPins = 1; }
			}
		}

	}
	//Print Action Message and
	//Wait for User Input

	//If it's label
	if (LabelorPins) {
		L = pIn->GetSrting(pOut, "Please Enter the label");
	}
	else {
		//If it's pins
		//GET the source and validate the click
		Connection* wire = pManager->GetConnection(Cx, Cy);
		flag = true;
		while (flag) {
			pOut->PrintMsg("Choose the source gate: ");
			pIn->GetPointClicked(x1, y1);
			//Check for status and tool bars:
			if (UI.ToolBarHeight - Cy + 50 > 0 || (UI.height - UI.StatusBarHeight) - Cy - 50 < 0) {
				flag = true;
			}
			else {
				flag = !(pManager->Checkinside(Cx, Cy));
			}
			if (flag) {
				pOut->PrintMsg("It's not allowed to start the connection here, please try again. ");
			}
		}
		//Get the destination and make sure it doesn't override an existing pin (except if it was the original one)
		//Tell the user to choose the destination gate 
		pOut->PrintMsg("Choose the destination gate : ");
		flag = true;
		while (flag) {
			//Wait for User Input
			pIn->GetPointClicked(x2, y2);

			//Check for status and tool bars:
			if (UI.ToolBarHeight - y2 + 50 > 0 || (UI.height - UI.StatusBarHeight) - y2 - 50 < 0) {
				flag = true;
			}
			else {
				//Shouldn't accept a component with full input
				//First it checks if the click is inside any component
				if (pManager->Checkinside(x2, y2)) {
					//Doesn't Accept Same Component
					if (!pManager->ChecksameComponent(x1, y1, x2, y2)) {
						//Check if component is full but passes the if it's the same as the same original component AND SAME PIN
						IPn = stoi(pIn->GetSrting(pOut, "Which Input Pin ? : "));
						
						//check if original pin
						if (wire->GetInputPin(IPn) == pManager->GetInputPin(x2, y2, IPn)) {
							flag = false;
						}//If not original pin:
						else {
							//Check if the comp is full
							if (!pManager->isCompfull(x2, y2)) { 
								//Check if this exact pin is connected
								while (flag) {
									//Get the dest Pin 
								InputPin* DstPin = pManager->GetInputPin(x2, y2, IPn);
								if (!DstPin->isConnected()) {
										flag = false;
								}
								else
								 IPn = stoi(pIn->GetSrting(pOut, "The Input is already connected. Try another one"));
								}
								
								
								flag = false; }
							else{ pOut->PrintMsg("The Component is full, choose another component "); }
						}

					}
					else { pOut->PrintMsg("You can't Choose the same component. "); }

				}
				else {
					pOut->PrintMsg("It's not allowed to place the connection here, please try again. ");

				}

			}



		}

		//Clear Status Bar
		pOut->ClearStatusBar();
	}
}


void Edit::Execute()
{
	ReadActionParameters();
	if(LabelorPins)
	pManager->EditComponent(L, Cx, Cy);

	//if he chose to change pins
	else { 
		// Get Pins:
		OutputPin* SrcPin = pManager->GetOutputPin(x1, y1);
		InputPin* DstPin = pManager->GetInputPin(x2, y2, IPn);


		// Get the graphics info of its gate separately and decide nearly the terminals of the connection with respect to them

		GraphicsInfo Comp1 = pManager->getGraphicsInfo(x1, y1);
		GraphicsInfo Comp2 = pManager->getGraphicsInfo(x2, y2);
		GraphicsInfo m_GfxInfo;

		m_GfxInfo.x1 = Comp1.x2;
		m_GfxInfo.y1 = ((Comp1.y1 + Comp1.y2 - 4) / 2);
		m_GfxInfo.x2 = Comp2.x1;
		if (IPn == 1 || IPn < 1) {
			m_GfxInfo.y2 = Comp2.y1 + 13;
		}
		else if (IPn == 2) { m_GfxInfo.y2 = Comp2.y2 - 13; }
		else if (IPn == 3 || IPn > 3) { m_GfxInfo.y2 = y2; }

		//ACCESS an existing connection
		Connection* wire =pManager->GetConnection(Cx, Cy);
		//if the user didn't choose the originial source apply the same as connect
		if (SrcPin != wire->GetOutputPin()) {
			if (!SrcPin->ConnectTo(wire)) {
				Output* pOut = pManager->GetOutput();
				pOut->PrintMsg("The number of outputs reached its maximum.");
				

			}
			else {
				//Set old pin's connection to null
				wire->GetInputPin(IPn)->Disconnect();
				Output* pOut = pManager->GetOutput();

				//Sets the wire's pin to dest
				wire->setDestPin(DstPin);
				//Sets the new pin's connection to the wire
				DstPin->setConnection(wire);
				wire->SetGraphics(m_GfxInfo);
				pOut->PrintMsg("Successfully edited the connection");
			}


		}
		//Else: the user chose the same source: no need to change Source 
		else {
			wire->GetInputPin(IPn)->Disconnect();
			Output* pOut = pManager->GetOutput();
			//Sets the wire's pin to dest
			wire->setDestPin(DstPin);
			DstPin->setConnection(wire);
			wire->SetGraphics(m_GfxInfo);
			pOut->PrintMsg("Successfully edited the connection");

		}
		}
	//Access a connection and change it's destination and Source, if output is full don't except if it's the same source.
}

void Edit::Undo()
{}

void Edit::Redo()
{}

