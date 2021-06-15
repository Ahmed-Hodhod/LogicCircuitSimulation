#include "Output.h"
#include "Input.h"
Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode
	UI.bartype = DSN_BAR;   // Default bar type is design toolbar 
	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");
	//There are two remaining sub-toolbars like ADDGATES toolbar and ADDTOOLS toolbar we only show DSN at first and the rest will be shown according to actions in Test 4 
	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	color myc(14, 44, 166);
	pWind->SetPen(myc, 1);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	color myc(14, 44, 166);
	pWind->SetPen(myc, 3);
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	color G(88, 88, 88);
	pWind->SetPen(G);
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (design) area
void Output::ClearDrawingArea() const
{
	color myc(14, 44, 166);
	pWind->SetPen(myc, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
void Output::PrintLabel(string msg, int x, int y) const
{
	// Set the Message in Drawing Area
	//Print the Message
	pWind->SetFont(18, BOLD | ITALICIZED, BY_NAME, "Arial");
	color b;
	pWind->SetPen(b);
	pWind->DrawString(x, y, msg);
}
void Output::EditLabel(string msg, int x, int y, int z) const
{	//Draws a rectangle
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(x - 20, y - 20, z * (x + 25), y + 20);
	//Print the Message
	pWind->SetFont(18, BOLD | ITALICIZED, BY_NAME, "Arial");
	color b;
	pWind->SetPen(b);
	pWind->DrawString(x, y, msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode
	UI.bartype = DSN_BAR;
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	// I redesigned the tool bar so that these items appear first not the gates
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_ADDGATE] = "images\\Menu\\Menu_ADD.jpg";
	MenuItemImages[ITM_ADDTOOL] = "images\\Menu\\Menu_TOOLS.jpg";
	MenuItemImages[ITM_EDIT] = "images\\Menu\\Menu_EDIT.jpg";
	MenuItemImages[ITM_LABEL] = "images\\Menu\\Menu_LABEL.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Menu\\Menu_DELETE.jpg";
	MenuItemImages[ITM_COPY] = "images\\Menu\\Menu_COPY.jpg";
	MenuItemImages[ITM_CUT] = "images\\Menu\\Menu_CUT.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Menu\\Menu_PASTE.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Menu_LOAD.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_SAVE.jpg";
	MenuItemImages[ITM_SIM] = "images\\Menu\\Menu_SIM.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(ITM_DSN_CNT* UI.ToolItemWidth, 0, UI.width, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	UI.bartype = SIM_BAR;
	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_VALIDATE] = "images\\Menu\\Menu_Validate.jpg";
	MenuItemImages[ITM_PROBE] = "images\\Menu\\Menu_PROBE.jpg";
	MenuItemImages[ITM_EDIT1] = "images\\Menu\\Menu_EDIT.jpg";
	MenuItemImages[ITM_LABEL1] = "images\\Menu\\Menu_LABEL.jpg";
	MenuItemImages[ITM_TRUTH] = "images\\Menu\\Menu_TT.jpg";
	MenuItemImages[ITM_DESIGN] = "images\\Menu\\Menu_DESIGN.jpg";
	MenuItemImages[ITM_LOAD1] = "images\\Menu\\Menu_LOAD.jpg";
	MenuItemImages[ITM_SAVE1] = "images\\Menu\\Menu_SAVE.jpg";
	MenuItemImages[ITM_EXIT1] = "images\\Menu\\Menu_Exit.jpg";
	//Draw menu item one image at a time
	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(ITM_SIM_CNT* UI.ToolItemWidth, 0, UI.width, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}
void Output::CreateGATESToolBar() const
{
	UI.AppMode = DESIGN;
	UI.bartype = ADDGATES_BAR;
	string MenuItemImages[ITM_NGATES];
	MenuItemImages[ITM_BUFF] = "images\\Menu\\Menu_BUFF.jpg";
	MenuItemImages[ITM_INV] = "images\\Menu\\Menu_INV.jpg";
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2] = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_XOR2] = "images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2] = "images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_AND3] = "images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_XOR3] = "images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_NOR3] = "images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_EXITGATES] = "images\\Menu\\Menu_RETURN.jpg";


	//Draw menu item one image at a time
	for (int i = 0; i < ITM_NGATES; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);

	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(ITM_NGATES * UI.ToolItemWidth, 0, UI.width, UI.ToolBarHeight);
	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
void Output::CreateTOOLStoolbar() const
{
	UI.AppMode = DESIGN;
	UI.bartype = ADDTOOLS_BAR;
	string MenuItemImages[ITM_NTOOLS];
	MenuItemImages[ITM_WIRE] = "images\\Menu\\Menu_WIRE.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\Menu_Switch.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\Menu_LED.jpg";
	MenuItemImages[ITM_EXITTOOLS] = "images\\Menu\\Menu_RETURN.jpg";
	for (int i = 0; i < ITM_NTOOLS; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(4 * UI.ToolItemWidth, 0, UI.width, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawBUFF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_BUFF_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_BUFF.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawINV(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_INV_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_INV.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawSwitch(GraphicsInfo r_GfxInfo, bool selected, bool stat) const
{
	string GateImage;
	if (UI.AppMode == SIMULATION && stat)    //1 means switch is closed
		GateImage = "Images\\Gates\\Switch_closed.jpg";
	else if (selected)
		GateImage = "Images\\Gates\\Switch_opened_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Switch_opened.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}


void Output::DrawLED(GraphicsInfo r_GfxInfo, bool selected, bool stat) const
{
	string GateImage;
	if (UI.AppMode == SIMULATION && stat)    //SIMULATION MODE and status is high
		GateImage = "Images\\Gates\\LED_on.jpg";
	else if (selected) // Assume in Design Mode
		GateImage = "Images\\Gates\\LED_Hi.jpg";
	else
		GateImage = "Images\\Gates\\LED_off.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}



void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	if (selected) {
		pWind->SetPen(RED, 3);
	}
	else {

		pWind->SetPen(BLACK, 3);

	}
	pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, (r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y1);
	pWind->DrawLine((r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y1, (r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y2);
	pWind->DrawLine((r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
}


Output::~Output()
{
	delete pWind;
}
