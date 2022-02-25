#include "stationinfoPage.h"

#include <stdio.h>



stationinfoPage::stationinfoPage(tftDISP* disp, myTS* tp)
{
    d = disp;
    t = tp;

    char msg[9];;

 /*Create callsign box*/
    title = new txtBox(d,t);
    addtxtBox(title);
    title->x=0;
    title->y=15;
    title->height=40;
    title->width=200;
    title->fontsize=2;
    title->border=false;
    title->message="Station Information";

    /*Generate Rotate Buttong*/

    BtnCall = new txtButton(d,t);
    addtxtButton(BtnCall);
    BtnCall->x=0;
    BtnCall->y=70;
    BtnCall->height=50;
    BtnCall->width=300;
    BtnCall->fontsize=2;
    BtnCall->topmargin=20;
    BtnCall->leftmargin=10;
    BtnCall->border=true;
    BtnCall->fillcolor=BLACK;

    strncpy(msg,eepromSettings::data.HomeCall,8);

    msg[7]='\0';
    
    BtnCall->message=String("Call Sign : ")+String(msg);
    BtnCall->id=IDCALLSIGN;

    BtnLocator = new txtButton(d,t);
    addtxtButton(BtnLocator);
    BtnLocator->x=0;
    BtnLocator->y=130;
    BtnLocator->height=50;
    BtnLocator->width=300;
    BtnLocator->fontsize=2;
    BtnLocator->topmargin=20;
    BtnLocator->leftmargin=10;
    BtnLocator->border=true;
    BtnLocator->fillcolor=BLACK;
        

    strncpy(msg,eepromSettings::data.HomeLocator,6);

    msg[6]='\0';
    BtnLocator->message=String("Locator : ")+String(msg);
    BtnLocator->id=IDLOCATOR;

       //Current Reading
    BtnExit = new txtButton(d,t);
    addtxtButton(BtnExit);
    BtnExit->x=190;
    BtnExit->y=200;
    BtnExit->height=40;
    BtnExit->width=120;
    BtnExit->fontsize=3;
    BtnExit->border=true;
    BtnExit->leftmargin=25;
    BtnExit->topmargin=10;
    BtnExit->message="EXIT";
    BtnExit->fillcolor=GREEN;
    BtnExit->id=IDEXITBUTTON;
}


int stationinfoPage::loop()
{
  
  int buttonID = waitforClick();

  while ( ( buttonID !=  IDEXITBUTTON))
  {
    switch(buttonID)
    {
      case IDLOCATOR:
          BtnLocator->hide();
          delay(1000);
          BtnLocator->show();
          break;
      case IDCALLSIGN:
          BtnCall->hide();
          delay(1000);
          BtnCall->show();
          break;
    }
    makeActive();
    show();
    buttonID = waitforClick();
  }
  deActive();
  hide();
  return buttonID;
}
