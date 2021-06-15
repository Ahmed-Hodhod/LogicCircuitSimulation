#include "AddNANDgate2.h"
#include "..\ApplicationManager.h"
#include <math.h>
#include <string>
#include "..\Components\Connection.h"
AddNANDgate2::AddNANDgate2(ApplicationManager* pApp) :Action(pApp)
{
}

AddNANDgate2::~AddNANDgate2(void)
{
}

void AddNANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input NAND Gate: Click to add the gate");

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


void AddNANDgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the NAND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	NAND2* pA = new NAND2(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddNANDgate2::Undo()
{}

void AddNANDgate2::Redo()
{}

