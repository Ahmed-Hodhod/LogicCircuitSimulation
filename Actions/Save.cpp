#include "Save.h"

Save::Save(ApplicationManager* pAppMan):Action(pAppMan)
{
}

void Save::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
}

void Save::Execute()
{
	ReadActionParameters();
	
		outwrite.open("circuit.txt");
		outwrite.clear(); //Clears txt file for new circuit (demo)
		pManager->SaveCircuit(outwrite);
		outwrite << "-1\n";
		pManager->GetOutput()->PrintMsg("Circuit Saved Successfully");
}

void Save::Undo()
{
}

void Save::Redo()
{
}

Save::~Save()
{
	outwrite.close();
}
