#include "CONNECT.h"
#include "..\ApplicationManager.h"
#include <math.h>
#include <string>
#include "..\Components\Connection.h"

#include "..\Components\Gate.h"



CONNECT::CONNECT(ApplicationManager* pApp) :Action(pApp)
{
    pManager = pApp;
}

CONNECT::~CONNECT(void)
{
}

void CONNECT::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    //Tell the user to choose the source gate 
    pOut->PrintMsg("Choose the source gate : ");
    //Get the source Pin 
    bool flag = true;
    while (flag) {
        //Wait for User Input
        pIn->GetPointClicked(x1, y1);
        //Check for status and tool bars:

        if (UI.ToolBarHeight - y1 + 50 > 0 || (UI.height - UI.StatusBarHeight) - y1 - 50 < 0) {
            flag = true;
        }
        else {
            flag = !(pManager->Checkinside(x1, y1)) || pManager->isonlyCompfree(x1, y1);
        }
        if (flag) {
            pOut->PrintMsg("It's not allowed to start the connection here, please try again. ");
        }
        if(pManager->isonlyCompfree(x1, y1)){ pOut->PrintMsg("This is the only component free, you can't connect it to itself."); }
    }
    //Tell the user to choose the destination gate 
    pOut->PrintMsg("Choose the destination pin : ");
    //Get the dest Pin 
    flag = true;
    while (flag) {
        //Wait for User Input
        pIn->GetPointClicked(x2, y2);
        //Check for status and tool bars:

        if (UI.ToolBarHeight - y2 + 50 > 0 || (UI.height - UI.StatusBarHeight) - y2 - 50 < 0) {
            flag = true;
        }
        else {
            //Doesn't Accept Same Component
            //Shouldn't accept a component with full input
            flag = !(pManager->Checkinside(x2, y2)) ||pManager->ChecksameComponent(x1, y1, x2, y2)||pManager->isCompfull(x2,y2);
        }

        if (flag) {
            pOut->PrintMsg("It's not allowed to place the connection here, please try again. ");
        }
        
        if (pManager->Checkinside(x2, y2)&&pManager->isCompfull(x2, y2)) {
            pOut->PrintMsg("The Component is full, choose another component ");
        }
    }

    //Which input Pin 
        pOut->PrintMsg("Which Input Pin? :  ");
    flag = true;
    int k = 0;
    while (flag) {
        //Get the dest Pin 
        if (k == 0)
        IPn = stoi(pIn->GetSrting(pOut,"Which Input Pin ? : "));
        else IPn = stoi(pIn->GetSrting(pOut, "The Input is already connected. Try another one"));
        InputPin* DstPin = pManager->GetInputPin(x2, y2, IPn);
        if (DstPin->isConnected()) {
            k++;
        }else flag = false;
    }
    //Clear Status Bar
    pOut->ClearStatusBar();

}

void CONNECT::Execute()
{
    //Get source,dest gates and the inputPin 
    ReadActionParameters();

    // Get Pins:
    OutputPin* SrcPin = pManager->GetOutputPin(x1, y1);
    InputPin* DstPin = pManager->GetInputPin(x2, y2,IPn);

 
    // Get the graphics info of its gate separately and decide nearly the terminals of the connection with respect to them
    
    GraphicsInfo Comp1= pManager->getGraphicsInfo(x1, y1);
    GraphicsInfo Comp2 = pManager->getGraphicsInfo(x2, y2);
    GraphicsInfo m_GfxInfo;
    
    m_GfxInfo.x1 = Comp1.x2;
    m_GfxInfo.y1 = ((Comp1.y1+Comp1.y2-4)/2)   ;
    m_GfxInfo.x2 = Comp2.x1;
    if (IPn == 1||IPn<1) {
        m_GfxInfo.y2 = Comp2.y1+13;
    }
    else if (IPn == 2) { m_GfxInfo.y2 = Comp2.y2-13; }
    else if (IPn == 3 ||IPn>3) { m_GfxInfo.y2 = y2; }
    
    
    //SHOULDN'T WE DELETE IT 

    Connection* wire = new Connection(m_GfxInfo, SrcPin, DstPin);
    if (!SrcPin->ConnectTo(wire)) {
    Output* pOut = pManager->GetOutput();
    pOut->PrintMsg("The number of outputs reached its maximum.");
    delete wire;
    
    }
    else { Output* pOut = pManager->GetOutput();
    pManager->AddComponent(wire);
    DstPin->setConnection(wire);
    pOut->PrintMsg("Successfully added the connection"); };

}

void CONNECT::Undo()
{}

void CONNECT::Redo()
{}