#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <stdint.h>
#include "tftdisp.h"
//#define DEBUG

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

txtBox sm =  txtBox();

 
 void statusMsg(String msg)
{
    sm.clr();
    sm.message=msg;
    sm.show();
}


myTS::myTS(tftDISP* disp,eepromSettings* set)
{
  d=disp;
  touchSettings=set;
  /*
  calXmin=set->data.TS_MINX;
  calYmin=set->data.TS_MINY;
  calXmax=set->data.TS_MAXX;
  calYmax=set->data.TS_MAXY;
  Serial.print("Touch Screen Constructor sets Xmax ");Serial.println(calXmin);
  */
}

void myTS::releasePins()
{
pinMode( YP,OUTPUT);  
pinMode (XM,OUTPUT);  
pinMode (YM,OUTPUT);
pinMode (XP,OUTPUT); 
}

TSPoint myTS::pressDetected()
{
  TSPoint p1;
  // a point object holds x y and z coordinates
  p1 = ts.getPoint();
  releasePins();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p1.z > ts.pressureThreshhold) {
     delay(100);
     TSPoint p2 = orientPoint(p1);
     return p2;
  }
  delay(100);
  p1.z=0;
  return p1;
}
   
TSPoint myTS::orientPoint(TSPoint p)
{
    int16_t nTmpX = p.x;
    int TS_MINX = touchSettings->data.TS_MINX;
    int TS_MINY = touchSettings->data.TS_MINY;
    int TS_MAXX = touchSettings->data.TS_MAXX;
    int TS_MAXY = touchSettings->data.TS_MAXX;

    /*
     * 
    int TS_MINX = calXmin;
    int TS_MINY = calYmin;
    int TS_MAXX = calXmax;
    int TS_MAXY = calYmax;
    */
    Serial.print("Touch Screen Point Orientaton sets Xmax ");Serial.println(calXmin);
    
    int Rotation=d->ROTATION;
    if (Rotation<1) Rotation = SCREENROTATION;
    if (Rotation>4) Rotation = SCREENROTATION;


    if (Rotation==1)
      {
              // scale from 0->1023 to tft..width

        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width()); 
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height()); 
      }
      
      if (Rotation==2)
      {
        // scale from 0->1023 to tft..width
        p.x = map(p.y, TS_MINX, TS_MAXX, 0, tft.width()); 
        p.y = map(nTmpX, TS_MAXY, TS_MINY, 0, tft.height()); 
      }
    
      if (Rotation==3)
      {
        int16_t nTmpX = p.x;
        // scale from 0->1023 to tft..width
        p.x = map(p.x, TS_MAXX, TS_MINX, 0, tft.width()); 
        p.y = map(p.y, TS_MAXY, TS_MINY, 0, tft.height()); 
      }
    
        if (Rotation==4)
      {
        // scale from 0->1023 to tft..width
        p.x = map(p.y, TS_MAXX,TS_MINX, 0,tft.width()); 
        p.y = map(nTmpX, TS_MINY, TS_MAXY , 0,tft.height()); 
      }
return p;
}


   

/*
 * Implements the tftDISP class which is a wrapper around the tft object and then used by other classes.
 * This will enable the type of display to be changed at a later date.
 */



tftDISP::tftDISP()
{
  
}

void tftDISP::disconectTouch()
{
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
}


void tftDISP::init()
{
    tft.reset();
    delay(250);
    uint16_t identifier = tft.readID();
    tft.begin(identifier);
    delay(250);
    tft.setRotation(ROTATION);
    tft.fillScreen(backgroundcolor);

    sm.d=(tftDISP*) this;
    sm.valid=true;
    sm.x=0;
    sm.y=0;
    sm.height=6;
    sm.topmargin=2;
    sm.leftmargin=2;
    sm.width=100;
    sm.fontsize=1;
    sm.border=false;
    sm.message="Calcluated from G30HH at IO87WD";
    sm.show();
    
}

void tftDISP::report()
{

  Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  //tft.reset();

  uint16_t identifier = tft.readID();
identifier=0x9341;
  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));

    return;
  }
}


void tftDISP::fillRect(int x,int y, int width, int height, int color)
{
  tft.fillRect(x, y, width, height, color);
}

void tftDISP::drawRect(int x,int y, int width, int height, int color)
{
  tft.drawRect(x, y, width, height, color);
}

void tftDISP::setCursor (int x, int y)
{
  tft.setCursor(x,y);
}
void tftDISP::setTextColor (int txtcolor, int fillcolor)
{
  tft.setTextColor(txtcolor,fillcolor); 
}
void tftDISP::setTextSize (int fontsize)
{
 tft.setTextSize(fontsize);
}
void tftDISP::print (String message)
{
 tft.print(message);
}

/*txtBox Object
 * 
 * Implements a text box for use with tft displays
 * 
 * To do is to create a page object with which to attach objects and display when required.
 * 
 */

txtBox::txtBox(tftDISP* disp,myTS* touchscreen)
{
  init(disp,touchscreen);
}

void txtBox::init(tftDISP* disp, myTS* touchscreen)
{
  d=disp;
  t=touchscreen;
  valid=true;
}

txtBox::txtBox()
{
  d=NULL;
  t=NULL;
  valid=false;
}


void txtBox::show()
{
    if (valid==false) return;
    d->fillRect(x, y, width, height, fillcolor);
    if (border == true) 
        d->drawRect(x, y, width, height, bordercolor);
    d->setCursor(x+leftmargin,y+topmargin);
    d->setTextColor(txtcolor,fillcolor);  
    d->setTextSize(fontsize);
    d->print(message); 
}

void txtBox::hide(){
  if (valid==false) return;
  d->fillRect(x, y, width, height, d->backgroundcolor);
}

void txtBox::changetext()
{
  if (valid==false) return;
  clr();
  d->setCursor(x+leftmargin,y+topmargin);
  d->setTextColor(txtcolor,fillcolor);  
  d->setTextSize(fontsize);
  d->print(message); 
}

void txtBox::clr(){
    if (valid==false) return;
    d->fillRect(x, y, width, height, fillcolor);
    if (border == true) 
        tft.drawRect(x, y, width, height, bordercolor);
}

void txtBox::redraw()
{
  if (valid==false) return;
  hide();
  show();
}

/*
 * Implements txtButton
 */
    txtButton::txtButton(tftDISP* s,myTS* t)
    {
       new txtBox(s,t);
    }
    
    txtButton::txtButton()
    {
      
    }

    boolean txtButton::wasitMe(TSPoint t)
    {

#ifdef DEBUG
      Serial.print("Button ID : ");Serial.print(id);Serial.print(" check X ");Serial.print(t.x);Serial.print(" Y ");Serial.println(t.y);
      Serial.print(" X: ");Serial.print(x);Serial.print(" - ");Serial.println(x+width);
      Serial.print(" Y: ");Serial.print(y);Serial.print(" - ");Serial.println(y+height);
#endif
      
      if (t.x < x) return false;
      if (t.y < y) return false;
      if (t.x > (x+width) ) return false;
      if (t.y > (y+height) ) return false;
      
#ifdef DEBUG
      Serial.println("HIT");
#endif

      return true;
    }

/*
 * Implements the page object
 */

page::page()
{
  
}

page::page(tftDISP* disp, myTS* tp)
{
    tftDISP *d = disp;
    disp->ROTATION=SCREENROTATION;
    myTS *t = tp;
    lastBox=NULL;
    firstBox=NULL;
}

void page::makeActive()
{
  _active=true;
}

void page::deActive()
{
  _active=false;
}

void page::addtxtButton(txtButton* tb)
{
  tb->d=d;
  tb->t=t;
  tb->valid=true;
  
  if (lastButton==NULL) //First text box added
  {
    firstButton=tb;
    lastButton=tb;
    tb->nextBox=NULL;
  } else {
    lastButton->nextBox=tb;
    lastButton=tb;
    tb->nextBox=NULL;
  }
}

int page::waitforClick()
{
  if (_active == false) return -1;
  if (firstButton==NULL) return -1;
  TSPoint pageP;
  Serial.println("Waiting for Press");
  while (1)
   {
     pageP = t->pressDetected();
     while (pageP.z == 0)
     {
      pageP = t->pressDetected();
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

void page::addtxtBox(txtBox* tb)
{
  tb->d=d;
  tb->t=t;
  tb->valid=true;
  
  if (lastBox==NULL) //First text box added
  {
    firstBox=tb;
    lastBox=tb;
    tb->nextBox=NULL;
  } else {
    lastBox->nextBox=tb;
    lastBox=tb;
    tb->nextBox=NULL;
  }
}

int page::hide()
{
  if (_active == false) return -1;
  tft.fillScreen(backgroundcolor);
  _active=false;
}

int page::show()
{
  if (_active == false) return -1;
  tft.fillScreen(backgroundcolor);
  if (firstBox == NULL) return 0;
  int elements=0;
  
  txtBox* tb=firstBox;
  while (tb != NULL)
  {
    tb->show();
    tb=tb->nextBox;
    elements++;
  }
  
  tb=firstButton;
  while (tb != NULL)
  {
    tb->show();
    tb=tb->nextBox;
    elements++;
  }
  return elements;
}
