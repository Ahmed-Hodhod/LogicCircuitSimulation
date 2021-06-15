#include "AddSwitch.h"
#include "..\ApplicationManager.h"
#include <math.h>
#include <string>
#include "..\Components\Connection.h"
AddSwitch::AddSwitch(ApplicationManager* pApp) :Action(pApp)
{

}

AddSwitch::~AddSwitch(void)
{
}

void AddSwitch::ReadActionParameters() {
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Switch: Click Anywhere to add the switch ");

	bool flag = true;
	while (flag) {
		//Wait for User Input
		pIn->GetPointClicked(Cx, Cy);
		//Check for status and tool bars and sides:

		if (UI.ToolBarHeight - Cy + 50 > 0 || (UI.height - UI.StatusBarHeight) - Cy - 50 < 0 || (UI.width - 150 - Cx) < 0 || (UI.width - Cx) > 950) {
			flag = true;
		}
		else {

			flag = pManager->Checkaround(Cx, Cy);
		}
		if (flag) {
			pOut->PrintMsg("It's not allowed to place the switch here, please try again. ");
		}
	}
	//Clear Status Bar
	pOut->ClearStatusBar();
}

void AddSwitch::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct LED

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	Switch* pA = new Switch(GInfo, AND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddSwitch::Undo()
{
}

void AddSwitch::Redo()
{
}

