#include "Copy.h"

#include "..\ApplicationManager.h"

Copy::Copy(ApplicationManager* pApp) :Action(pApp)
{
}

Copy::~Copy(void)
{
}

void Copy::ReadActionParameters()
{//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Get Point clicked and detect (Component & Connection ) 
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
			pOut->PrintMsg("Choose a Component to copy.");
		}
	}
}

void Copy::Execute()
{
	ReadActionParameters();

	//pManager->CopyComponent(Cx, Cy);
	pManager->Copy2(Cx, Cy);

}

void Copy::Undo()
{}

void Copy::Redo()
{}

