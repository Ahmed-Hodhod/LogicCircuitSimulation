#include "Simulate.h"
#include <string>
#include "..\ApplicationManager.h"

Simulate::Simulate(ApplicationManager *pApp):Action(pApp)
{
}

Simulate::~Simulate(void)
{
}

void Simulate::ReadActionParameters()
{

}


void Simulate::Execute()
{
	pManager->Sortelementsgraphically();
	pManager->OperateAll();
	
	



}

void Simulate::Undo()
{}

void Simulate::Redo()
{}
