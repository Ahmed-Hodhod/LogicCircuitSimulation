#include "Label.h"
#include "..\ApplicationManager.h"

Label::Label(ApplicationManager* pApp) :Action(pApp)
{
}

Label::~Label(void)
{
}

void Label::ReadActionParameters()
{//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Choose which component you want to label");
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
			pOut->PrintMsg("It's not allowed to put a label here, please try again. ");
		}

	}
	//Print Action Message and
	//Wait for User Input
	L = pIn->GetSrting(pOut, "Please Enter the label");

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Label::Execute()
{
	ReadActionParameters();
	pManager->LabelComponent(L,Cx,Cy);

}

void Label::Undo()
{}

void Label::Redo()
{}

