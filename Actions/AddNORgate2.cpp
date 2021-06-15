#include "AddNORgate2.h"
#include "..\ApplicationManager.h"
#include <math.h>
#include <string>
#include "..\Components\Connection.h"
AddNORgate2::AddNORgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddNORgate2::~AddNORgate2(void)
{
}

void AddNORgate2::ReadActionParameters()
{//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input NOR Gate: Click to add the gate");

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


void AddNORgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the NOR2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	NOR2* pA = new NOR2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddNORgate2::Undo()
{}

void AddNORgate2::Redo()
{}

