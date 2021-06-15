//#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
    pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int& x, int& y)
{
    pWind->FlushMouseQueue();
    pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output* pOut, string x)
{
    pWind->FlushKeyQueue();
    char* A = new char[25];
    bool flag = 1;
    keytype ktInput;
    int i = 0;
    pOut->PrintMsg(x);
    do {
        ktInput = pWind->WaitKeyPress(A[i]);
        //ESCAPE
        if (ktInput == ESCAPE) {
            for (int i = 0; i < 25; i++) {
                A[i] = '  ';
            }
            flag = 0;
        } //ASCII
        else
            //BACKSPACE
            if (A[i] == 8 && i > 0) {
                A[i - 1] = '  ';
                i -= 2;
            }
            else
                //ENTER
                if (A[i] == 13) {
                    flag = 0;
                }
        // CORNER CASE: if backspace is pressed in the beginning of array:
        if (i == 0 && A[i] == 8) {
            A[i] = '  ';
            i -= 1;
            pOut->PrintMsg(x);
        }
        else {
            //To ensure there is no garbage displayed:
            char* B = new char[i + 2]; //size=i+1 normally, so accounting for the extra
            B[i + 1] = '\0';                                   //..NULL Terminator..
            strncpy(B, A, i + 1);
            pOut->PrintMsg(B);
            delete[] B;
        }
        i++;
        if (i > 24) {
            flag = false;
        }
    } while (flag);
    //Converting the array into string to return it
    //one last time because B is deleted inside the loop
    A[i-1] = (A[i-1] == 8 || A[i-1] == 13 ? ' ' : A[i-1]);
    char* B = new char[i + 1];
    B[i] = '\0';
    strncpy(B, A, i);
    pOut->PrintMsg(B);
    string s(B);
    delete[]A;
    delete[] B;
    return s;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction(int &a, int &b) const
{
    int x, y;
    pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
    a = x; b = y;
    
    if (y >= 0 && y < UI.ToolBarHeight) { // If the user clicks on the tool bar
        if (UI.bartype == DSN_BAR)	// Design Toolbar
        {
            //Check whick Menu item was clicked
            //==> This assumes that menu items are lined up horizontally <==
            int ClickedItemOrder = (x / UI.ToolItemWidth);
            //Divide x coord of the point clicked by the menu item width (int division)
            //if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

            switch (ClickedItemOrder)
            {
            case ITM_ADDGATE: return ADD_GATE;
            case ITM_ADDTOOL: return ADD_TOOL;
            case ITM_EDIT:return EDIT_Label;
            case ITM_LABEL:return ADD_Label;
            case ITM_DELETE: return DEL;
            case ITM_COPY: return COPY;
            case ITM_CUT: return CUT;
            case ITM_PASTE:return PASTE;
            case ITM_LOAD:return LOAD;
            case ITM_SAVE:return SAVE;
            case ITM_SIM:return SIM_MODE;
            case ITM_EXIT:return EXIT;
            default: return DSN_TOOL;	//A click on empty place in desgin toolbar
            }
        }
        else if (UI.bartype == SIM_BAR) {                  //Modify SImulation Tool bar
            int ClickedItemOrder = (x / UI.ToolItemWidth);
            switch (ClickedItemOrder) {
            case ITM_VALIDATE:return VALIDATE;
            case ITM_PROBE:return PROBE;
            case ITM_EDIT1:return EDIT_Label;
            case ITM_LABEL1:return ADD_Label;
            case ITM_TRUTH: return Create_TruthTable;
            case ITM_DESIGN:return DSN_MODE;
            case ITM_LOAD1:return LOAD;
            case ITM_SAVE1:return SAVE;
            case ITM_EXIT1:return EXIT;
            default:return DSN_TOOL;
            }
        }
        else if (UI.bartype == ADDGATES_BAR) {    //If the user clicks addgates toolbar menu item
            int ClickedItemOrder = (x / UI.ToolItemWidth);
            switch (ClickedItemOrder) {
            case ITM_BUFF:return ADD_Buff;
            case ITM_INV:return ADD_INV;
            case ITM_AND2:return ADD_AND_GATE_2;
            case ITM_OR2:return ADD_OR_GATE_2;
            case ITM_NAND2:return ADD_NAND_GATE_2;
            case ITM_NOR2:return ADD_NOR_GATE_2;
            case ITM_XOR2:return ADD_XOR_GATE_2;
            case ITM_XNOR2:return ADD_XNOR_GATE_2;
            case ITM_AND3:return ADD_AND_GATE_3;
            case ITM_XOR3:return ADD_XOR_GATE_3;
            case ITM_NOR3:return ADD_NOR_GATE_3;
            case ITM_EXITGATES:return DSN_MODE;   //Back to the main menu , create design toolbar
            default:return DSN_TOOL;
            }
        }
        else {
            int ClickedItemOrder = (x / UI.ToolItemWidth);     //ADDTOOLStoolbar
            switch (ClickedItemOrder) {
            case ITM_WIRE:return ADD_CONNECTION;
            case ITM_SWITCH:return ADD_Switch;
            case ITM_LED:return ADD_LED;
            case ITM_EXITTOOLS:return DSN_MODE;
            default:return DSN_TOOL;     //empty area in the toolbar
            }
        }
    }
    //[2] User clicks on the drawing area
    if (y >= UI.ToolBarHeight && y < (UI.height - UI.StatusBarHeight))
    {
        return SELECT;	//user want to select/unselect a component
    }
    if (y >= (UI.height - UI.StatusBarHeight) && y < UI.height) {
        //[3] User clicks on the status bar
        return STATUS_BAR;
    }
}
Input::~Input()
{
}
