#include "Load.h"

Load::Load(ApplicationManager* pAppMan):Action(pAppMan)
{
}

void Load::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
}

void Load::Execute()
{
	//What if our user decided suddenly to load a new design ? 
	pManager->GetOutput()->ClearDrawingArea();
	Output* pOut = pManager->GetOutput();
	readout.open("circuit.txt");
	if (readout.peek() == EOF) {
		pManager->GetOutput()->PrintMsg("File is empty ");
	}
	else {
		pManager->LoadCircuit(readout);
		pManager->GetOutput()->PrintMsg("Circuit Loaded Successfully");
	}
	
	
}


void Load::Undo()
{
}

void Load::Redo()
{
}

Load::~Load()
{
	readout.close();
}
