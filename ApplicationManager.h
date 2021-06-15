#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H
#include<fstream>
#include<string>
#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"

//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	int nGates;         // no. of gates
	int nfullGates;      //no. of gates whose inputs are full

	int a, b;            //Varaible only used to save one click during the select

	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)

	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface
	int FindComp(Component*);
	int FindComp(int Cx, int Cy);
	void FindAndReplace(Component* c);
	Component* CutItem;
	COPY_ITEMS CopyType;
	Cut CutElement;

public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	
	void UpdateInterface();	//Redraws all the drawing window

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Gets the Inputpin of clicks comp
	InputPin* GetInputPin(int x, int y, int n);

	//Gets the Outputpin of the clicked comp
	OutputPin* GetOutputPin(int x, int y);
	
	//Gets the connection which the user clicked
	Connection* GetConnection(int Cx, int Cy);
	
	//Checks around the click
	bool Checkaround(int Cx, int Cy);

	//Determines if the comp is connection or gate 1 for gate, 0 for connection
	bool ConnorGate(int Cx, int Cy);
	//Checks if the click is inside each component
	bool Checkinside(int Cx, int Cy);

	//Checks if the clicks correspond to the same component or not
	bool ChecksameComponent(int Cx1, int Cy1, int Cx2, int Cy2);
	
	
	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	//Deletes Component
	void DeleteComponent(int Cx, int Cy);
	
	//Deletes Gate
	void DeleteGate(Component* comp);

	//Deles Connection
	void DeleteConnection(Connection* c);


	//Selects Component and highlights it 
	void SelectComponent(int Cx, int Cy);

	//Labels Component
	void LabelComponent(string x, int Cx, int Cy);

	//Edits the label of component or changes pins of connection
	void EditComponent(string x, int Cx, int Cy);

	//Checks if the component is full
	bool isCompfull(int Cx, int Cy);
	
	//Checks if all the components are full
	bool isAllfull();

	//Checks if the given compnent is the only one free
	bool isonlyCompfree(int Cx, int Cy);
	
	//Gets the graphicsinfo of some component
	GraphicsInfo getGraphicsInfo(int Cx, int Cy);
	Component* getCompbyID(int compID); //facilitates the loaded connection process 
	void Paste2(int Cx, int Cy);
	void Copy2(int Cx, int Cy);
	void Cut2(int Cx, int Cy);
	void SaveCircuit(ofstream& outfile);
	void LoadCircuit(ifstream& infile);

	//destructor
	~ApplicationManager();
};

#endif