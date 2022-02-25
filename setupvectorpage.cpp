#include "setupvectorPage.h"
#include "stationinfoPage.h"

#include <stdio.h>



setupvectorPage::setupvectorPage(tftDISP* disp, myTS* tp, rotatorCalibratePage* rc, stationinfoPage* st)


{
    d = disp;
    t = tp;
    rcp=rc;
    station=st;
    
    //rotatorCalibratePage* rcp = new rotatorCalibratePage(d,t,r,settings);


 /*Create callsign box*/
    title = new txtBox(d,t);
    addtxtBox(title);
    title->x=0;
    title->y=15;
    title->height=40;
    title->width=200;
    title->fontsize=4;
    title->border=false;
    title->message="SETUP MENU";

    /*Generate Rotate Buttong*/

    BtnAzimuth = new txtButton(d,t);
    addtxtButton(BtnAzimuth);
    BtnAzimuth->x=0;
    BtnAzimuth->y=70;
    BtnAzimuth->height=50;
    BtnAzimuth->width=300;
    BtnAzimuth->fontsize=2;
    BtnAzimuth->topmargin=20;
    BtnAzimuth->leftmargin=40;
    BtnAzimuth->border=true;
    BtnAzimuth->fillcolor=RED;
    BtnAzimuth->message="Calibtrate Azimuth";
    BtnAzimuth->id=IDAZIMUTH;

    BtnStation = new txtButton(d,t);
    addtxtButton(BtnStation);
    BtnStation->x=0;
    BtnStation->y=130;
    BtnStation->height=50;
    BtnStation->width=300;
    BtnStation->fontsize=2;
    BtnStation->topmargin=20;
    BtnStation->leftmargin=70;
    BtnStation->border=true;
    BtnStation->fillcolor=BLUE;
    BtnStation->message="Station Details";
    BtnStation->id=IDAZIMUTH;

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
    BtnExit->id=IDEXITSETUP;
}


int setupvectorPage::loop()
{
  
  int buttonID = waitforClick();

  Serial.println("About to loop in setup vector");
  while ( ( buttonID !=  IDEXITSETUP))
  {
    switch(buttonID)
    {
      case IDAZIMUTH:
          deActive();
          hide();
          rcp->makeActive();
          rcp->show();
          rcp->loop();
          rcp->hide();
          rcp->deActive();
          break;
      case IDSTATION:
          deActive();
          hide();
          station->makeActive();
          station->show();
          station->loop();
          station->hide();
          station->deActive();
          break;
    }
    makeActive();
    show();
    buttonID = waitforClick();
  }
  Serial.print("Exited SetupVector Loop with Button ID =");Serial.println(buttonID);
  deActive();
  hide();
  return buttonID;
}
