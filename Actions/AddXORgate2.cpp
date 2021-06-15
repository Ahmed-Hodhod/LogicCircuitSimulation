#include "AddXORgate2.h"
#include "..\ApplicationManager.h"
#include <math.h>
#include <string>
#include "..\Components\Connection.h"
AddXORgate2::AddXORgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddXORgate2::~AddXORgate2(void)
{
}

void AddXORgate2::ReadActionParameters()
{//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input XOR Gate: Click to add the gate");

	bool flag = true;
	while (flag) {
		//Wait for User Input
		pIn->GetPointClicked(Cx, Cy);
		//Check for status and tool bars:

		if (UI.ToolBarHeight - Cy + 50 > 0 || (UI.height - UI.StatusBarHeight) - Cy - 50 < 0) {
			flag = true;
		}
		else {

			flag = pManager->Checkaround(Cx, Cy);
		}
		if (flag) {
			pOut->PrintMsg("It's not allowed to place the gate here, please try again. ");
		}

	}
	//Clear Status Bar
	pOut->ClearStatusBar();
}


void AddXORgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the XOR2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	XOR2* pA = new XOR2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddXORgate2::Undo()
{}

void AddXORgate2::Redo()
{}

