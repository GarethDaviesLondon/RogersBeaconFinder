#include "beaconpage.h"
#include "RotatorControl.h"
#include <stdio.h>



beaconPage::beaconPage(tftDISP* disp, myTS* tp, beaconTable* tin, Rotator *rt)
{
    d = disp;
    t = tp;
    b=tin;
    r=rt;
    

 /*Create callsign box*/
    call = new txtBox(d,t);
    addtxtBox(call);
    call->x=0;
    call->y=15;
    call->height=40;
    call->width=200;
    call->fontsize=4;
    call->border=false;
    call->message="G3OHH";

     /*Create callsign box*/
    locator = new txtBox(d,t);
    addtxtBox(locator);
    locator->x=190;
    locator->y=75;
    locator->height=25;
    locator->width=100;
    locator->fontsize=2;
    locator->border=false;
    locator->message="G3OHH";
    
 /*Create Frequency box*/
    freq = new txtBox(d,t);
    addtxtBox(freq);
    freq->x=0;
    freq->y=65;
    freq->height=30;
    freq->width=160;
    freq->fontsize=3;
    freq->border=false;
    freq->message="FREQ 1296.500";

    /*Create current bearing data information box*/
   /*Needs to be rendered behind the containing items*/
   
    txtBox* databox = new txtBox(d,t);
    addtxtBox(databox);
    databox->x=0;
    databox->y=107;
    databox->height=30;
    databox->width=320;
    databox->border=true;
    databox->message="";
    

  /*Create Target Bearing box*/
    bearing = new txtBox(d,t);
    addtxtBox(bearing);
    bearing->x=150;
    bearing->y=110;
    bearing->height=25;
    bearing->width=160;
    bearing->fontsize=2;
    bearing->border=false;
    bearing->message="AZ: 180";

   /*Create range box*/
    range = new txtBox(d,t);
    addtxtBox(range);
    range->x=5;
    range->y=110;
    range->height=25;
    range->width=120;
    range->fontsize=2;
    range->border=false;
    range->message="Range 2000KM";

    
   /*Create current heading information box*/
   /*Needs to be rendered behind the containing items*/
   
    txtBox* controlbox = new txtBox(d,t);
    addtxtBox(controlbox);
    controlbox->x=0;
    controlbox->y=145;
    controlbox->height=95;
    controlbox->width=320;
    controlbox->border=true;
    controlbox->message="";
    

   /*Create current heading title box*/
    currentHeadingTitle = new txtBox(d,t);
    addtxtBox(currentHeadingTitle);
    currentHeadingTitle->x=250;
    currentHeadingTitle->y=155;
    currentHeadingTitle->height=25;
    currentHeadingTitle->width=50;
    currentHeadingTitle->fontsize=1;
    currentHeadingTitle->border=false;
    currentHeadingTitle->message="Beaming";


   /*Create current heading information box*/
    currentHeading = new txtBox(d,t);
    addtxtBox(currentHeading);
    currentHeading->x=250;
    currentHeading->y=170;
    currentHeading->height=25;
    currentHeading->width=50;
    currentHeading->fontsize=2;
    currentHeading->txtcolor=BLUE;
    currentHeading->border=false;
    currentHeading->message="135";


    /*Generate Rotate Buttong*/

    BtnRotate = new txtButton(d,t);
    addtxtButton(BtnRotate);
    BtnRotate->x=90;
    BtnRotate->y=155;
    BtnRotate->height=35;
    BtnRotate->width=120;
    BtnRotate->fontsize=3;
    BtnRotate->topmargin=7;
    BtnRotate->leftmargin=8;
    BtnRotate->border=true;
    BtnRotate->fillcolor=RED;
    BtnRotate->message="ROTATE";
    BtnRotate->id=ROTATEID;

    /*Generate Sort Button */
    BtnSort = new txtButton(d,t);
    addtxtButton(BtnSort);
    BtnSort->x=130;
    BtnSort->y=210;
    BtnSort->height=25;
    BtnSort->width=60;
    BtnSort->fontsize=2;
    BtnSort->border=true;
    BtnSort->fillcolor=GREEN;
    BtnSort->message="BAND";
    BtnSort->id=SORTID;
    
    /*Generate Next Button */
    BtnNext = new txtButton(d,t);
    addtxtButton(BtnNext);
    BtnNext->x=220;
    BtnNext->y=210;
    BtnNext->height=25;
    BtnNext->width=95;
    BtnNext->fontsize=2;
    BtnNext->border=true;
    BtnNext->fillcolor=BLACK;
    BtnNext->message="NEXT >>";
    BtnNext->id=NEXTID;

    /*Generate Prev Button */

    BtnPrev = new txtButton(d,t);
    addtxtButton(BtnPrev);
    BtnPrev->x=5;
    BtnPrev->y=210;
    BtnPrev->height=25;
    BtnPrev->width=95;
    BtnPrev->fontsize=2;
    BtnPrev->border=true;
    BtnPrev->fillcolor=BLACK;
    BtnPrev->message="<< PREV";
    BtnPrev->id=PREVID;

    /*Generate SetUp Button */

    BtnSetup = new txtButton(d,t);
    addtxtButton(BtnSetup);
    BtnSetup->x=250;
    BtnSetup->y=0;
    BtnSetup->height=25;
    BtnSetup->width=70;
    BtnSetup->fontsize=2;
    BtnSetup->border=true;
    BtnSetup->fillcolor=WHITE;
    BtnSetup->txtcolor=BLACK;
    BtnSetup->message="setup";
    BtnSetup->id=SETUPID;
}

void beaconPage::scroll()
{
  while (b->atLast()==false)
  {
    setBeaconInfo();
    redrawBeacon();
    b->next();
    delay(2000);
  }
  setBeaconInfo();
  redrawBeacon();
}

void beaconPage::redrawBeacon()
{
  call->redraw();
  freq->redraw();
  range->redraw();
  bearing->redraw();
  locator->redraw();
}

void beaconPage::clrBeacon()
{
  call->message="";
  freq->message="";
  range->message="";
  bearing->message="";
  locator->message="";
}

void beaconPage::setBeaconInfo()
{
   String msg1;
   String msg2;
   char buf[21];
       
   call->message=b->beacon()->Name;
   locator->message=b->beacon()->Locator;

   /*Be nice to format the Frequency Better, but not yet worked out how*/
   //snprintf(buf,sizeof(buf),"%f",(long)b->beacon()->Mhz);
   //freq->message=String(buf);

   freq->message=b->beacon()->Mhz;


   long distance=b->CalcDistance((char *)b->beacon()->Locator);

    
   if (distance>=1000)
       snprintf(buf,sizeof(buf),"%ld,%03ld",distance/1000,distance%1000);
    else  
       snprintf(buf,sizeof(buf),"%ld",distance);

   msg1 = String(buf)+" Miles";
   range->message=msg1;
   msg2 = "Bearing: "+String (b->CalcBearing((char *)b->beacon()->Locator));
   bearing->message=msg2;
}

void beaconPage::makeActive()
{
   setBeaconInfo();
   page::makeActive();
}


int beaconPage::loop()
{
  int buttonID = waitforClick();
  
  while ( ( buttonID !=  SORTID) & ( buttonID !=  SETUPID) & (buttonID != ROTATEID) )
  {
    switch (buttonID ) {
      case PREVID:
          if (b->atFirst())
            { 
              clrBeacon();
              call->message="START";
              redrawBeacon();
            } else {
               b->prev();
            }
          setBeaconInfo();
          redrawBeacon();
      break;
      case NEXTID:

          if (b->atLast())
            { 
              clrBeacon();
              call->message="END";
              redrawBeacon();
            } else {
              b->next();
            }
          setBeaconInfo();
          redrawBeacon();
      break;
    }
    buttonID = waitforClick();
  }
  hide();
  return buttonID;
}

//Implemented here in order to display the current Rotator Bearing
int beaconPage::waitforClick()
{
  if (_active == false) return -1;
  if (firstButton==NULL) return -1;
  TSPoint pageP;
  Serial.println("Waiting for Press");
  while (1)
   {
     pageP = t->pressDetected();
     int cnt=0;
     int lastbeam,nowbeam=0;
     while (pageP.z == 0)
     {
      pageP = t->pressDetected();
      if (cnt=10000)
      {
        cnt=0;
        nowbeam=r->BeamHeading();
        if (nowbeam != lastbeam)
        {
          lastbeam = nowbeam;
          currentHeading->message=String(nowbeam);
          currentHeading->redraw();
        }
      }
      cnt++;
     }
     txtButton* b = firstButton;
     //Serial.println("Press Detected");
     while (b != NULL)
     {
        if (b->wasitMe(pageP) == true ) 
        {
          b->hide();
          delay(250);
          b->show();
          return b->id;
        }
        b=b->nextBox;
     }
   }
}
