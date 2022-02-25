#include "bandpage.h"
#include <stdio.h>



bandPage::bandPage(tftDISP* disp, myTS* tp, beaconTable* tin)
{
    d = disp;
    t = tp;
    b=tin;
    
 /*Create callsign box*/
    title = new txtBox(d,t);
    addtxtBox(title);
    title->x=0;
    title->y=15;
    title->height=40;
    title->width=200;
    title->fontsize=4;
    title->border=false;
    title->message="SELECT BAND";

     
    /*Generate Rotate Buttong*/

    Btn50 = new txtButton(d,t);
    addtxtButton(Btn50);
    Btn50->x=0;
    Btn50->y=80;
    Btn50->height=50;
    Btn50->width=300;
    Btn50->fontsize=4;
    Btn50->topmargin=7;
    Btn50->leftmargin=100;
    Btn50->border=true;
    Btn50->fillcolor=RED;
    Btn50->message="6M";
    Btn50->id=ID50;

    Btn144 = new txtButton(d,t);
    addtxtButton(Btn144);
    Btn144->x=0;
    Btn144->y=135;
    Btn144->height=50;
    Btn144->width=300;
    Btn144->fontsize=4;
    Btn144->topmargin=7;
    Btn144->leftmargin=100;
    Btn144->border=true;
    Btn144->fillcolor=BLUE;
    Btn144->message="2M";
    Btn144->id=ID144;

    Btn1296 = new txtButton(d,t);
    addtxtButton(Btn1296);
    Btn1296->x=0;
    Btn1296->y=190;
    Btn1296->height=50;
    Btn1296->width=300;
    Btn1296->fontsize=4;
    Btn1296->topmargin=7;
    Btn1296->leftmargin=100;
    Btn1296->border=true;
    Btn1296->fillcolor=GREEN;
    Btn1296->message="23CM";
    Btn1296->id=ID1296;

}


int bandPage::loop()
{
  int buttonID = waitforClick();
  b->setActiveBand(buttonID); 
  hide();
  return buttonID;
}
