#include "CutA.h"

#include "..\ApplicationManager.h"

CutA::CutA(ApplicationManager* pApp) :Action(pApp)
{
}

CutA::~CutA(void)
{
}

void CutA::ReadActionParameters()
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
			pOut->PrintMsg("Choose a Component to Cut.");
		}
	}
}


void CutA::Execute()
{
	ReadActionParameters();

	//pManager->CopyComponent(Cx, Cy);
	pManager->Cut2(Cx, Cy);

}


void CutA::Undo()
{}

void CutA::Redo()
{}

