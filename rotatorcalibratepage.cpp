#include "rotatecalibratepage.h"
#include <stdio.h>

#define TITLEROW 15
#define ROWSTART 60
#define COL1 0
#define COL2 65
#define COL3 167
#define COL4 230

#define ROWSPACING 15
#define BOXHEIGHT 30
#define BOXWIDTH 60
#define BUTTONHEIGHT 30
#define BUTTONWIDTH 85
#define BUTTONCOLOR BLUE
#define RECORDTEXT "Record"
#define BUTTONLEFT 5
#define BUTTONTOP 7
#define TEXTLEFT 5
#define TEXTTOP 10
#define TITLEMESSAGE "Sensor :";


rotatorCalibratePage::rotatorCalibratePage(tftDISP* disp, myTS* tp, Rotator* Rin)
{
    d = disp;
    t = tp;
    r=Rin;
/*    
 *    txtBox* title;
      txtBox* currentreading;
      txtBox* deg0;
      txtButton deg0button;
      txtBox* deg90;
      txtButton deg90button;
      txtBox* deg180;
      txtButton deg180button;
      txtBox* deg270;
      txtButton deg270button;
      txtBox* deg360;
      txtButton deg360button;
      txtBox* deg450;
      txtButton deg450button; 
      txtButton saveBtn;
      txtButton cancelBtn;
 */



 /*Page Title*/
    heading = new txtBox(d,t);
    addtxtBox(heading);
    heading->x=COL1;
    heading->y=0;
    heading->height=10;
    heading->width=150;
    heading->fontsize=1;
    heading->border=false;
    heading->message="Rotor azimuth calibration settings";

 /*Page Title*/
    title = new txtBox(d,t);
    addtxtBox(title);
    title->x=COL1;
    title->y=TITLEROW;
    title->height=25;
    title->width=175;
    title->fontsize=2;
    title->border=false;
    title->message=TITLEMESSAGE;

 
 //Page Title
    currentreading = new txtBox(d,t);
    addtxtBox(currentreading);
    currentreading->x=COL3;
    currentreading->y=TITLEROW;
    currentreading->height=25;
    currentreading->width=50;
    currentreading->fontsize=2;
    currentreading->border=false;
    currentreading->message="000";


    BtnReset = new txtButton(d,t);
    addtxtButton(BtnReset);
    BtnReset->x=250;
    BtnReset->y=0;
    BtnReset->height=25;
    BtnReset->width=70;
    BtnReset->fontsize=2;
    BtnReset->border=true;
    BtnReset->fillcolor=WHITE;
    BtnReset->txtcolor=BLACK;
    BtnReset->message="reset";
    BtnReset->id=IDRESET;


//Zero Degrees Reading
    deg0 = new txtBox(d,t);
    addtxtBox(deg0);
    deg0->x=COL1;
    deg0->y=ROWSTART;
    deg0->height=BOXHEIGHT;
    deg0->width=BOXWIDTH;
    deg0->topmargin=TEXTTOP;
    deg0->leftmargin=TEXTLEFT;
    deg0->fontsize=1;
    deg0->border=true;
    deg0->message="000:1023";

//Button to save this reading
    deg0button = new txtButton(d,t);
    addtxtButton(deg0button);
    deg0button->x=COL2;
    deg0button->y=ROWSTART;
    deg0button->height=BUTTONHEIGHT;
    deg0button->width=BUTTONWIDTH;
    deg0button->fontsize=2;
    deg0button->topmargin=BUTTONTOP;
    deg0button->leftmargin=BUTTONLEFT;
    deg0button->border=true;
    deg0button->fillcolor=BUTTONCOLOR;
    deg0button->message=RECORDTEXT;
    deg0button->id=IDDEG0;


//90 Degrees Reading
    deg90 = new txtBox(d,t);
    addtxtBox(deg90);
    deg90->x=COL1;
    deg90->y=ROWSTART+BOXHEIGHT+ROWSPACING;
    deg90->height=BOXHEIGHT;
    deg90->width=BOXWIDTH;
    deg90->topmargin=TEXTTOP;
    deg90->leftmargin=TEXTLEFT;
    deg90->fontsize=1;
    deg90->border=true;
    deg90->message="090:1023";

//Button to save this reading
    deg90button = new txtButton(d,t);
    addtxtButton(deg90button);
    deg90button->x=COL2;
    deg90button->y=ROWSTART+BOXHEIGHT+ROWSPACING;
    deg90button->height=BUTTONHEIGHT;
    deg90button->width=BUTTONWIDTH;
    deg90button->fontsize=2;
    deg90button->topmargin=BUTTONTOP;
    deg90button->leftmargin=BUTTONLEFT;
    deg90button->border=true;
    deg90button->fillcolor=BUTTONCOLOR;
    deg90button->message=RECORDTEXT;
    deg90button->id=IDDEG90;



//90 Degrees Reading
    deg180 = new txtBox(d,t);
    addtxtBox(deg180);
    deg180->x=COL1;
    deg180->y=ROWSTART+2* (BOXHEIGHT+ROWSPACING);
    deg180->height=BOXHEIGHT;
    deg180->width=BOXWIDTH;
    deg180->topmargin=TEXTTOP;
    deg180->leftmargin=TEXTLEFT;
    deg180->fontsize=1;
    deg180->border=true;
    deg180->message="180:1023";

//Button to save this reading
    deg180button = new txtButton(d,t);
    addtxtButton(deg180button);
    deg180button->x=COL2;
    deg180button->y=ROWSTART+2*(BOXHEIGHT+ROWSPACING);
    deg180button->height=BUTTONHEIGHT;
    deg180button->width=BUTTONWIDTH;
    deg180button->fontsize=2;
    deg180button->topmargin=BUTTONTOP;
    deg180button->leftmargin=BUTTONLEFT;
    deg180button->border=true;
    deg180button->fillcolor=BUTTONCOLOR;
    deg180button->message=RECORDTEXT;
    deg180button->id=IDDEG180;
/*


    //Zero Degrees Reading*/
    deg270 = new txtBox(d,t);
    addtxtBox(deg270);
    deg270->x=COL3;
    deg270->y=ROWSTART;
    deg270->height=BOXHEIGHT;
    deg270->width=BOXWIDTH;
    deg270->topmargin=TEXTTOP;
    deg270->leftmargin=TEXTLEFT;
    deg270->fontsize=1;
    deg270->border=true;
    deg270->message="270:1023";

//Button to save this reading
    deg270button = new txtButton(d,t);
    addtxtButton(deg270button);
    deg270button->x=COL4;
    deg270button->y=ROWSTART;
    deg270button->height=BUTTONHEIGHT;
    deg270button->width=BUTTONWIDTH;
    deg270button->fontsize=2;
    deg270button->topmargin=BUTTONTOP;
    deg270button->leftmargin=BUTTONLEFT;
    deg270button->border=true;
    deg270button->fillcolor=BUTTONCOLOR;
    deg270button->message=RECORDTEXT;
    deg270button->id=IDDEG270;


//90 Degrees Reading
    deg360 = new txtBox(d,t);
    addtxtBox(deg360);
    deg360->x=COL3;
    deg360->y=ROWSTART+BOXHEIGHT+ROWSPACING;
    deg360->height=BOXHEIGHT;
    deg360->width=BOXWIDTH;
    deg360->topmargin=TEXTTOP;
    deg360->leftmargin=TEXTLEFT;
    deg360->fontsize=1;
    deg360->border=true;
    deg360->message="360:1023";

//Button to save this reading
    deg360button = new txtButton(d,t);
    addtxtButton(deg360button);
    deg360button->x=COL4;
    deg360button->y=ROWSTART+BOXHEIGHT+ROWSPACING;
    deg360button->height=BUTTONHEIGHT;
    deg360button->width=BUTTONWIDTH;
    deg360button->fontsize=2;
    deg360button->topmargin=BUTTONTOP;
    deg360button->leftmargin=BUTTONLEFT;
    deg360button->border=true;
    deg360button->fillcolor=BUTTONCOLOR;
    deg360button->message=RECORDTEXT;
    deg360button->id=IDDEG360;



//90 Degrees Reading
    deg450 = new txtBox(d,t);
    addtxtBox(deg450);
    deg450->x=COL3;
    deg450->y=ROWSTART+2* (BOXHEIGHT+ROWSPACING);
    deg450->height=BOXHEIGHT;
    deg450->width=BOXWIDTH;
    deg450->topmargin=TEXTTOP;
    deg450->leftmargin=TEXTLEFT;
    deg450->fontsize=1;
    deg450->border=true;
    deg450->message="450:1023";

//Button to save this reading
    deg450button = new txtButton(d,t);
    addtxtButton(deg450button);
    deg450button->x=COL4;
    deg450button->y=ROWSTART+2*(BOXHEIGHT+ROWSPACING);
    deg450button->height=BUTTONHEIGHT;
    deg450button->width=BUTTONWIDTH;
    deg450button->fontsize=2;
    deg450button->topmargin=BUTTONTOP;
    deg450button->leftmargin=BUTTONLEFT;
    deg450button->border=true;
    deg450button->fillcolor=BUTTONCOLOR;
    deg450button->message=RECORDTEXT;
    deg450button->id=IDDEG450;


    //Current Reading
    cancelBtn = new txtButton(d,t);
    addtxtButton(cancelBtn);
    cancelBtn->x=170;
    cancelBtn->y=200;
    cancelBtn->height=40;
    cancelBtn->width=120;
    cancelBtn->fontsize=3;
    cancelBtn->border=true;
    cancelBtn->topmargin=10;
    cancelBtn->leftmargin=10;
    cancelBtn->message="CANCEL";
    cancelBtn->fillcolor=GREEN;
    cancelBtn->id=IDCANCEL;

    //Current Reading
    saveBtn = new txtButton(d,t);
    addtxtButton(saveBtn);
    saveBtn->x=20;
    saveBtn->y=200;
    saveBtn->height=40;
    saveBtn->width=120;
    saveBtn->fontsize=3;
    saveBtn->border=true;
    saveBtn->leftmargin=25;
    saveBtn->topmargin=10;
    saveBtn->message="SAVE";
    saveBtn->fillcolor=RED;
    saveBtn->id=IDSAVE;

    
}

void rotatorCalibratePage::updateDegree(int deg,int temp)
{

  txtBox* box=NULL;
  String red;
  switch (deg){
      case 0:
          box=deg0;
          red="000:";
          break;
      case 90:
          box=deg90;
          red="090:";
          break;
      case 180:
          box=deg180;
          red="180:";
          break;
      case 270:
          box=deg270;
          red="270:";
          break;
      case 360:
          box=deg360;
          red="360:";
          break;
      case 450:
          red="450:";
          box=deg450;
          break;
    }       

    if (box != NULL)
    {
      String msg=red+String(temp);
      box->message=msg;
      box->redraw();
    }
}




int rotatorCalibratePage::loop()
{

  unsigned int tmpDegree0 = eepromSettings::data.Degree0;
  unsigned int tmpDegree90 = eepromSettings::data.Degree90;
  unsigned int tmpDegree180 = eepromSettings::data.Degree180;
  unsigned int tmpDegree270 = eepromSettings::data.Degree270;
  unsigned int tmpDegree360 = eepromSettings::data.Degree360;
  unsigned int tmpDegree450 = eepromSettings::data.Degree450;
  updateDegree(0,tmpDegree0);
  updateDegree(90,tmpDegree90);
  updateDegree(180,tmpDegree180);
  updateDegree(270,tmpDegree270);
  updateDegree(360,tmpDegree360);
  updateDegree(450,tmpDegree450);
  title->message=TITLEMESSAGE;
  title->fontsize=2;
  title->txtcolor=WHITE;
  title->redraw();
  
  int buttonID = waitforClick();
  
  while ( ( buttonID !=  IDSAVE) & ( buttonID !=  IDCANCEL) & ( buttonID !=  IDRESET))
  {
    
    switch(buttonID)
    {
      case IDDEG0:
          tmpDegree0=r->Voltage();
          updateDegree(0,tmpDegree0);
          break;
      case IDDEG90:
          tmpDegree90=r->Voltage();
          updateDegree(90,tmpDegree90);
          break;
      case IDDEG180:
          tmpDegree180=r->Voltage();
          updateDegree(180,tmpDegree180);
          break;
      case IDDEG270:
          tmpDegree270=r->Voltage();
          updateDegree(270,tmpDegree270);
          break;
      case IDDEG360:
          tmpDegree360=r->Voltage();
          updateDegree(360,tmpDegree360);
          break;
      case IDDEG450:
          tmpDegree450=r->Voltage();
          updateDegree(450,tmpDegree450);
          break;
    }
    buttonID = waitforClick();
  }

  /*Save or cancel as required*/
  currentreading->hide();
  switch (buttonID ) {

      case IDSAVE:
          title->message="SAVING CALIBRATION";
          title->txtcolor=RED;
          title->fontsize=1;
          title->redraw();
          delay(350);
          eepromSettings::data.Degree0 = tmpDegree0;
          eepromSettings::data.Degree90 =tmpDegree90;
          eepromSettings::data.Degree180 = tmpDegree180;
          eepromSettings::data.Degree270 =  tmpDegree270;
          eepromSettings::data.Degree360 = tmpDegree360;
          eepromSettings::data.Degree450 = tmpDegree450;
          eepromSettings::save();
          r->init();      
      break;
      case IDCANCEL:
          title->message="CANCELLED";
          title->txtcolor=GREEN;
          title->fontsize=1;
          title->redraw();
          delay(350);
      break;
      case IDRESET:
          title->message="resetting to default";
          title->txtcolor=BLUE;
          title->fontsize=1;
          title->redraw();
          delay(350);
          eepromSettings::reset();
      
      default:
          int junk=0;
  }
  Serial.println("Time for a new window");
  hide();
  return buttonID;
}

//Implemented here in order to display the current Rotator Bearing
int rotatorCalibratePage::waitforClick()
{
  if (_active == false) return -1;
  if (firstButton==NULL) return -1;
  TSPoint pageP;
  Serial.println("Waiting for Press");
  while (1)
   {
     pageP = t->pressDetected();
     int cnt=0;
     int lastvolt,nowvolt=0;
     while (pageP.z == 0)
     {
      pageP = t->pressDetected();
      if (cnt=10000)
      {
        cnt=0;
        nowvolt=r->Voltage();
        if (nowvolt != lastvolt)
        {
          lastvolt = nowvolt;
          currentreading->message=String(nowvolt);
          currentreading->redraw();
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
