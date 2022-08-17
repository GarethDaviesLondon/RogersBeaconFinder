#include "rotatepage.h"
#include <stdio.h>

rotatePage::rotatePage(tftDISP* disp, myTS* tp, beaconTable* bt,Beacon *bIn, Rotator *rt, eepromSettings *set)
{
    d = disp;
    t = tp;
    b=bIn;
    r=rt;
    settings=set;
    String msg;
    
    heading=bt->CalcBearing((char *)b->Locator);
    
    call = new txtBox(d,t);
    addtxtBox(call);
    call->x=0;
    call->y=15;
    call->height=40;
    call->width=200;
    call->fontsize=4;
    call->border=false;
    call->message=b->Name;

     /*Create callsign box*/
    locator = new txtBox(d,t);
    addtxtBox(locator);
    locator->x=190;
    locator->y=75;
    locator->height=25;
    locator->width=100;
    locator->fontsize=2;
    locator->border=false;
    locator->message=b->Locator;
    
 /*Create Frequency box*/
    freq = new txtBox(d,t);
    addtxtBox(freq);
    freq->x=0;
    freq->y=65;
    freq->height=30;
    freq->width=160;
    freq->fontsize=3;
    freq->border=false;
    freq->message=String(b->Mhz);
    


 /*Create callsign box*/
    currentHeading = new txtBox(d,t);
    addtxtBox(currentHeading);
    currentHeading->x=0;
    currentHeading->y=120;
    currentHeading->height=40;
    currentHeading->width=150;
    currentHeading->fontsize=2;
    //currentHeading->topmargin=3;
    //currentHeading->leftmargin=3;
    currentHeading->border=false;
    msg = "Starting: "+String(r->BeamHeading());
    currentHeading->message=msg;

     /*Create callsign box*/
    targetHeading = new txtBox(d,t);
    addtxtBox(targetHeading);
    targetHeading->x=0;
    targetHeading->y=155;
    targetHeading->height=40;
    targetHeading->width=150;
    targetHeading->fontsize=2;
    //targetHeading->topmargin=3;
    //targetHeading->leftmargin=3;
    targetHeading->border=false;
    msg = "Target: "+String(heading);
    targetHeading->message=msg;
     
}

void rotatePage::displayHeading(char *mess)
{
    currentHeading->message=mess;
    currentHeading->redraw();
}

int rotatePage::loop()
{
  Serial.println("Initiating Rotation Sequence");
  r->RotateTo(heading);
  Serial.println("Completed");
  return 1;
}
