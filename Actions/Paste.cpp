#include "Paste.h"

#include "..\ApplicationManager.h"

Paste::Paste(ApplicationManager* pApp) :Action(pApp)
{
	Cx = 2000;
	Cy = 1500;  // Cx, Cy are initially set to values out of the drawing area  [FOR VALIDATION ONLY] 
}

Paste::~Paste(void)
{
}

void Paste::ReadActionParameters()
{//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	// Get Point clicked and detect (Component & Connection ) 
	bool flag = true;
	pIn->GetPointClicked(Cx,Cy); 



}

void Paste::Execute()
{
	ReadActionParameters();

	//pManager->PasteComponent(Cx, Cy);
	pManager->Paste2(Cx, Cy);
}

void Paste::Undo()
{}

void Paste::Redo()
{}

