#ifndef CONST_H
#define CONST_H

//This header file contains some defenitions to be used all over the application

//All possible actions
enum ActionType
{
	ADD_GATE,
	ADD_TOOL,
	ADD_Buff,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection

	Create_TruthTable,	//Create Truth Table of the Circuit

	Change_Switch,		//Change Switch Status in Simulation Mode

	SELECT,		//Select a Component, a Connection
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection
	COPY, CUT, PASTE,
	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled

	VALIDATE,         //validate that there is no floating pins
	PROBE,           //Check the pin's status 

	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode

	EXIT,		//Exit the application

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar

};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};
enum TOOLBARTYPE
{
	DSN_BAR,
	SIM_BAR,
	ADDGATES_BAR,
	ADDTOOLS_BAR,
};

enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_ADDGATE,	//ADD gate 
	ITM_ADDTOOL,  // ADD TOOL ITEM 
	ITM_LABEL,
	ITM_EDIT,
	ITM_DELETE,
	ITM_MOVE,
	ITM_COPY,
	ITM_CUT,
	ITM_PASTE,
	ITM_LOAD,
	ITM_SAVE,
	ITM_SIM,
	ITM_EXIT,	//Exit item
	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum

};

enum TOOLS {
	ITM_WIRE,
	ITM_SWITCH,
	ITM_LED,
	ITM_EXITTOOLS,
	ITM_NTOOLS   // TOOLS NUMBER
};

enum GATES {
	ITM_BUFF,
	ITM_INV,
	ITM_AND2,
	ITM_OR2,
	ITM_NAND2,
	ITM_NOR2,
	ITM_XOR2,
	ITM_XNOR2,
	ITM_AND3,
	ITM_XOR3,
	ITM_NOR3,
	ITM_EXITGATES,
	ITM_NGATES,   // GATES NUMBER 
};

enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
		//Simulate menu item
	ITM_VALIDATE,
	ITM_PROBE,
	ITM_LABEL1,
	ITM_EDIT1,
	ITM_TRUTH,	//Truth table menu item
	ITM_DESIGN, //BACK TO DESIGN 
	ITM_LOAD1,
	ITM_SAVE1,
	ITM_EXIT1,
	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};






//used for copying action

enum COPY_ITEMS
{
	I_BUFF,
	I_INV,
	I_AND2,
	I_OR2,
	I_NAND2,
	I_NOR2,
	I_XOR2,
	I_XNOR2,
	I_AND3,
	I_XOR3,
	I_NOR3,
	I_SWITCH,
	I_LED,
	NUMP

};

struct Cut
{
	COPY_ITEMS CutType;
	int ind; // Index of this item in CompList 
};

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5	//Default fan out of 2-input AND gate
};

//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1, y1, x2, y2;
};

#ifndef NULL
#define NULL 0
#endif

#endif