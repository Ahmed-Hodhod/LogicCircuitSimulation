
#include "Delete.h"

#include "..\ApplicationManager.h"

Delete::Delete(ApplicationManager* pApp) :Action(pApp)
{
}

Delete::~Delete(void)
{
}

void Delete::ReadActionParameters()
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
			pOut->PrintMsg("Choose an element to delete .");
		}
	}



}

void Delete::Execute()
{
	ReadActionParameters();

	pManager->DeleteComponent(Cx, Cy);

}

void Delete::Undo()
{}

void Delete::Redo()
{}

