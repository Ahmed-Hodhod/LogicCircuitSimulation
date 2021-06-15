#include "Probe.h"

#include "..\ApplicationManager.h"

Probe::Probe(ApplicationManager* pApp) :Action(pApp)
{
}

Probe::~Probe(void)
{
}

void Probe::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pIn->GetPointClicked(Cx, Cy);
	//Clear Status Bar
	pOut->ClearStatusBar();
}

void Probe::Execute()
{
	ReadActionParameters();

	//pManager->PasteComponent(Cx, Cy);
	//pManager->Paste2(Cx, Cy);
	pManager->ProbeCircuit(Cx,Cy);
		

}

void Probe::Undo()
{}

void Probe::Redo()
{}

