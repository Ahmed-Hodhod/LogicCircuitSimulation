#include "AddANDgate2.h"
#include "..\ApplicationManager.h"
#include <math.h>
#include <string>
#include "..\Components\Connection.h"
AddANDgate2::AddANDgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddANDgate2::~AddANDgate2(void)
{
}

void AddANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input AND Gate: Click to add the gate");

	bool flag = true;
	while (flag) {
		//Wait for User Input
		pIn->GetPointClicked(Cx, Cy);
		//Check for status and tool bars:

		if (UI.ToolBarHeight - Cy + 50 > 0 || (UI.height - UI.StatusBarHeight) - Cy - 50 < 0) {
			flag = true;
			pOut->PrintMsg("It's not allowed to place the gate here, please try again. ");
		}
		else {

			if (pManager->GetCompCount() == 0) { flag = false; }
			//CHECK FOR GATES & CONNECTIONS
			for (int i = 0; i < pManager->GetCompCount(); i++) {

				Component** C = (pManager->GetCompList());
				//check for gates
				if (dynamic_cast<Gate*>(C[i])) {
					GraphicsInfo G = C[i]->GetCoordinates();
					int COGx = (G.x2 + G.x1) / 2;  //COG=Center of Gate
					int COGy = (G.y2 + G.y1) / 2; //COG= Center of Gate	
				//Draw an imaginary circle around each gate, and this is how you validate, (1.5*r)^2 was chosen because it's suitable
					if ((pow((Cx - COGx), 2) + pow((Cy - COGy), 2)) <= pow(1.5 * 50, 2))
					{
						flag = true;
						pOut->PrintMsg("It's not allowed to place the gate here, please try again.");
						break;
					}
					else flag = false;
					//CHECK FOR CONNECTIONS
					if (dynamic_cast<Connection*>(C[i])) {

					}

				}
			}
		}

	}
	//Clear Status Bar
	pOut->ClearStatusBar();

}


void AddANDgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AND2* pA = new AND2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddANDgate2::Undo()
{}

void AddANDgate2::Redo()
{}

