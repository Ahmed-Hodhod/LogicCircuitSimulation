#include "CreateTT.h"

CreateTT::CreateTT(ApplicationManager* pApp):Action(pApp)
{ 
}

void CreateTT::ReadActionParameters()
{
	return;
}

void CreateTT::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	truth.open("TruthTable.txt");
	truth.clear();
	truth << "Truth Table";
	pManager->CreateTruth(truth);
	
}

void CreateTT::Undo()
{
	return;
}

void CreateTT::Redo()
{
	return;
}

CreateTT::~CreateTT()
{
	truth.close();
}
